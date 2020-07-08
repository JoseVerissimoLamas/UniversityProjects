package ucBusca.meta1;

import org.jsoup.Jsoup;
import ucBusca.myObjects.UrlObject;

import java.net.*;
import java.io.*;
import java.util.*;
import java.util.concurrent.ConcurrentHashMap;

public class MulticastServerB implements Serializable{

    public static ConcurrentHashMap<String, Client> Clients = new ConcurrentHashMap<String, Client>();
    public static ConcurrentHashMap<String, String> sentRequests = new ConcurrentHashMap<>();
    public static ArrayList<String> onlineUsers = new ArrayList<>();
    public static ArrayList<String> offlineUsers = new ArrayList<>();
    private static MulticastSocket MULTICASTsocket;
    public static InetAddress RMIaddress;
    private static int port = 3456;
    private static String ADDR = "226.0.224.0";
    private static WebCrawler web;
    public static long ID;

    public MulticastServerB() {
        super();
    }

    /**
     * Função ler os utilzadores do ficheiro e colocá-los na hashmap Clients.
     * A hashmap tem como chave uma string com o username do cliente e as chaves são a classe Client associado
     * a esse username.
     */
    public static void loadUsers(){
        try {

            ObjectInputStream ow = new ObjectInputStream(new FileInputStream(new File("Clients")));
            Clients= (ConcurrentHashMap<String, Client>) ow.readObject();
            ow.close();

        }catch (FileNotFoundException e) {
            File f = new File("Clients");
        }catch (IOException e) {
            System.out.println("[Empty File clientes]");
        }catch (ClassNotFoundException e) {
            e.printStackTrace();
        }

    }

    /**
     * Função para guardar novos utilizadores no ficheiro e alterações a clientes já registados no ficheiro.
     */
    public static void saveUsers(){
        try{
            ObjectOutputStream wo = new ObjectOutputStream(new FileOutputStream(new File("Clients")));
            // Write objects to file
            wo.writeObject(Clients);
            wo.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static HashMap<String, String> newProtocolType(String type, String protocolMessage, int clientId) {
        HashMap<String, String> msg = new HashMap<>(); // Final message to send
        msg.put("id", Integer.toString(clientId));  // Register the client ID
        msg.put("type", type);// Register de request type


        StringTokenizer message = new StringTokenizer(protocolMessage, "|");
        StringTokenizer tokenizedToken;
        String token;
        msg.put("query", protocolMessage);
        return msg;
    }

    /**
     * Devolve a mensagem para o RMI Server. Coloca o Id da mensagem na hashmap antes de enviar e depois retira.
     * @param msg Mensagem do protocolo  desenvolver.
     */
    //Return answer to RMI SERVER. Puts the request ID in the hashmap and removes it from the hashmap
    //as soon as its sent.
    public static void sendBack(HashMap<String, String> msg) {
        try {
            ByteArrayOutputStream baos = new ByteArrayOutputStream(6400);
            ObjectOutputStream oos = new ObjectOutputStream(baos);

            oos.writeObject(msg);
            byte[] data = baos.toByteArray();
            MULTICASTsocket.send(new DatagramPacket(data, data.length, RMIaddress, port));
        } catch (IOException e) {
        }
    }

    /*
     * Faz login do utilizador e envia uma mensagem para o rmi com o sucesso do processo.
     * @param password password que o utilizador colocou
     * @param username username que o utilizador colocou
     * @param requestID id dado à mensagem vindo do rmi
     * @return devolve uma String de protocolo para o rmi server.
     */
    //Verifies if the username is on the clients hashmap in order to login. If the condition returns true checks if the
    //password is the same as the one in the hashmap else sends a message with login failed.
    public static HashMap<String, String> login(HashMap<String, String> request){
        HashMap<String, String> msg = new HashMap<>();
        ArrayList<String> offline = new ArrayList<>();
        for (String c: Clients.keySet()){
            System.out.println(c);
            System.out.println(Clients.get(c).Admin());
        }
        msg.put("id", request.get("id"));
        msg.put("type", "answer");
        synchronized (onlineUsers){
            if (onlineUsers.contains(request.get("username"))) {
                // Para o browser, quando esta loggedin pode fazer login
                if(Clients.get(request.get("username")).getPassword().equals(request.get("password"))){
                    msg.put("login","yes");
                    msg.put("admin",Boolean.toString(Clients.get(request.get("username")).Admin()));
                    msg.put("message","Login successful!");
                    return msg;
                }
                msg.put("login","no");
                msg.put("message", "Login failed!");
                //msg.put("message", "Login failed! You are already logged in!");
                return msg;
            }
        }
        if(Clients.containsKey(request.get("username"))){
            if(Clients.get(request.get("username")).getPassword().equals(request.get("password"))){
                synchronized (onlineUsers) {
                    onlineUsers.add(request.get("username"));
                }
                synchronized (offlineUsers){
                    if(offlineUsers.contains(request.get("username"))){
                        offlineUsers.remove(request.get("username"));
                    }
                }
                msg.put("login","yes");
                msg.put("admin",Boolean.toString(Clients.get(request.get("username")).Admin()));
                msg.put("message","Login successful!");
            }else{
                msg.put("login","no");
                msg.put("message","Login failed! Wrong Password!");
            }
        }else{
            msg.put("login","no");
            msg.put("message","Not registered!");
        }
        return msg;
    }

    /*
     * Faz o registo do utilizador. Verifica se o utilizador já está na haspmap Clients e se esta condição não se verificar
     * coloca na hasmap.
     * @param password password introduzida pelo utilizador
     * @param username username escolhido pelo utilizador
     * @param requestID id do pedido dado no rmi client.
     * @return
     */
    //Regists client saving his credentials(username and password) in the Clients hasmap if the username isn't found and returns a message
    //to be sent to the rmi server.
    public static HashMap<String,String> Registry(HashMap<String, String> request) {
        boolean isAdmin = false;
        HashMap<String,String> msg = new HashMap<>();
        String username = request.get("username");
        String password = request.get("password");
        String id = request.get("id");

        msg.put("id",id);
        msg.put("type", "answer");

        if (Clients.containsKey(username) == false) {
            if (Clients.size() == 0) {
                isAdmin = true;
            }
            Client newClient = new Client(username, password, isAdmin);
            Clients.put(username, newClient);
            saveUsers();

            msg.put("register","success");
            msg.put("admin",Boolean.toString(isAdmin));
            msg.put("message","Registered with success!Welcome!");
        }else{
            msg.put("register","fail");
            msg.put("admin",Boolean.toString(isAdmin));
            msg.put("message","Username already taken!");
        }
        return msg;
    }

    /*
     * Função de pesquisa do utilizdor, vai utilizar a classe web crawler que irá devolver uma arraylist com os links
     * do resultado de pesquisa e são enviados por string para o rmi server.
     * @param username Username do utilzador que pesquisou para guardar no historico de pesquisas do proprio.
     * @param query Palavras escolhidas
     * @param requestID Id do pedido dado no rmi server
     * @param log variavel para saber so o utilzador esta logged in
     * @return devolve uma string com os resultados d pesquisa em formato string para o utilzador.
     */
    public static HashMap<String, String> Search(HashMap<String, String> request){
        String query = request.get("query");
        if(request.containsKey("username")) Clients.get(request.get("username")).getSearches().add(query);
        HashMap<String, String> answer = new HashMap<>();
        if(request.containsKey("id")) answer.put("id", request.get("id"));
        answer.put("type", "answer");

        ArrayList<UrlObject> results = web.searchURLs(web.wordList, query, true);

        if(results==null){
            answer.put("Nao ha resultados","supposedTitle");
        }
        else{
            for(UrlObject result: results){
                answer.put(result.getUrl(), result.getTitle()+"§"+result.getDescription());
            }
        }

        System.out.println("Send_answer:");
        for (String key:answer.keySet()){
            System.out.println(key+" "+answer.get(key));
        }

        return answer;
    }

    /*
     * Vai verificar quais os termos que o utilizador escolheu. Na classe client existe uma arraylist com as pesquisas
     * do utilizador
     * @param username
     * @param requestId
     * @return
     */
    public static HashMap<String, String> searchHistory(HashMap<String, String> request){
        HashMap<String, String> answer = new HashMap<>();
        ArrayList<String> searches = Clients.get(request.get("username")).getSearches();
        if(searches.isEmpty()){
            answer.put("search", "You haven't searched anything!");
        }else{
            for (String search : searches) {
                answer.put("search", search);
            }
        }
        answer.put("type", "answer");
        answer.put("id", request.get("id"));
        return answer;
    }

    /*
     * Função para indexar link pedido por utilzador caso seja admnistrador.
     * @param username Username do cliente que efetuou o pedido
     * @param requestID Id do pedido dado à mesagem no rmi server.
     * @param link link inserido pelo utilizador para indexar
     * @return
     */
    // TODO DONEEEEE
    public static HashMap<String, String> indexLinks(HashMap<String, String> request){

        HashMap<String, String> answer = new HashMap<>();
        answer.put("type", "answer");
        answer.put("id", request.get("id"));
            System.out.println(request.get("url"));

        Thread indexThread = new Thread(new AddUrl(request.get("url"), web.wordList, web.urlList, web.numbLinks));
        Thread saveIndexedLinks = new Thread(new FileSaver(web.wordList, web.urlList, web.numbLinks));
        indexThread.start();
        saveIndexedLinks.start();

        answer.put("ack", "Indexing with sucess");

        return answer;
    }

    /*
     * Pesquisar os links que apontam para certo url. Chama um método da classe web crawler que pesquisa
     * os parents de determinado url, ou seja os links que contêm o link procurado.
     * @param requestID id do pedido dado pelo rmi server
     * @param link link pesquisado
     * @return devolve mensagem protocolo enviada para o rmi server
     */
    public static HashMap<String, String> browseLink(HashMap<String, String> request){
        HashMap<String, String> answer = new HashMap<>();
        answer.put("type", "answer");
        answer.put("id", request.get("id"));

        ArrayList<String> parentUrls = web.parentUrl(request.get("url"), web.urlList);

        if(parentUrls==null){
            answer.put("Nao ha resultados","supposedTitle");
        }
        else{
            for(String result: parentUrls){
                answer.put(result, "supposedTitle");
            }
        }
        return answer;
    }

    /*
     * Função para dar permissões a determinado utilizador.
     * @param clientUsername username do cliente a que se pretende dar permissões
     * @param requestID id do pedido de cedencia de permissões
     * @return devolve mensagem protocolo para o rmi server.
     */
    public static HashMap<String, String> givePrev(HashMap<String, String> request){
        HashMap<String, String> answer = new HashMap<>();
        answer.put("type", "answer");
        answer.put("id", request.get("id"));
        if(Clients.containsKey(request.get("client"))) {
            synchronized (Clients){
                Clients.get(request.get("client")).setAdmin(true);
            }
            answer.put("ack", "success");
        } else {
            answer.put("ack", "User not found");
        }
        return answer;
    }

    /*
     * Função para fazer logout de determinado utilizador.
     * @param username username do utilzador que pretende fazer logout
     * @param requestID id do pedido
     * @return devolve mensagem protocolo para o rmi server.
     */
    public static HashMap<String,String> logout(HashMap<String, String> request){
        HashMap<String, String> answer = new HashMap<>();

        answer.put("type", "answer");
        answer.put("id", request.get("id"));

        synchronized (onlineUsers){
            onlineUsers.remove(request.get("logout"));
        }
        synchronized (offlineUsers){
            offlineUsers.add(request.get("logout"));
        }
        answer.put("logout","yes");
        answer.put("message","Logged out with success!");
        return answer;
    }

    /**
     * Função para enviar as notificações guardadas de certo utilizador para o rmi server através de string.
     * @param username username do utilizador para devolver as notificações do próprio
     * @param requestID id do pedido
     * @return devolve mensagem protocolo para o rmi server.
     */
    public static String getNotifsClient(String username, String requestID){
        String message="";
        String messageFinal="";
        ArrayList<String> notif = Clients.get(username).notifications();
        if(!notif.isEmpty()){
            for(String i: notif){
                message = message+"}"+i;
            }
            notif.clear();

        }else{
            message = "none";
        }
        messageFinal = "type;answer|message;"+message+"|id;"+requestID;
        return messageFinal;
    }

    /**
     * Cria o servidor multicast começando por dar load dos users e colocar todos os existentes no array de clientes
     * offline, depois cria o multicast socket e junta-se ao grupo de forma a poder comunicar com o rmi server.
     * Fica sempre à espera de pedidos do rmi server.
     * @param args
     */
    public static void main(String[] args) {
        String s = "";
        web = new WebCrawler();
        loadUsers();
        if(!Clients.isEmpty()){
            for(String user: Clients.keySet()){
                System.out.println(user);
                offlineUsers.add(user);
            }
        }
        try {
            RMIaddress = InetAddress.getByName(ADDR);
            MULTICASTsocket = new MulticastSocket(port);
            MULTICASTsocket.joinGroup(RMIaddress);

            // Manda uma msg para o servidor RMI guardar o seu ID
            ID= System.currentTimeMillis();
            String ping = "identify;"+Long.toString(ID)+";";
            MulticastSocket multicastSocket = new MulticastSocket();
            DatagramPacket pack = new DatagramPacket(ping.getBytes(), ping.length(), RMIaddress, port-1);
            multicastSocket.send(pack);

        } catch (IOException e) {
            e.printStackTrace();
        }

        byte[] buffer = new byte[640000];
        while (true) {
            try {
                MULTICASTsocket.receive(new DatagramPacket(buffer, buffer.length));
                ObjectInputStream iStream = new ObjectInputStream(new ByteArrayInputStream(buffer));
                HashMap<String, String> receivedInfo = (HashMap<String, String>)iStream.readObject();
                iStream.close();

                for (String key: receivedInfo.keySet()){
                    System.out.println(key+" "+receivedInfo.get(key));
                }

                if(receivedInfo.get("type").compareTo("search") == 0){
                    sendBack(Search(receivedInfo));
                }else if(receivedInfo.get("type").compareTo("index") == 0){
                    sendBack(indexLinks(receivedInfo));
                }else if(receivedInfo.get("type").compareTo("parentUrl") == 0){
                    sendBack(browseLink(receivedInfo));
                }else if(receivedInfo.get("type").compareTo("register")==0){
                    sendBack(Registry(receivedInfo));
                }else if(receivedInfo.get("type").compareTo("login")==0){
                    sendBack(login(receivedInfo));
                }else if(receivedInfo.get("type").compareTo("history") == 0){
                    sendBack(searchHistory(receivedInfo));
                }else if(receivedInfo.get("type").compareTo("logout")==0){
                    sendBack(logout(receivedInfo));
                }else if(receivedInfo.get("type").compareTo("givePremission")==0){
                    sendBack(givePrev(receivedInfo));
                }else if(receivedInfo.get("type").compareTo("getAdmins")==0) {
                    HashMap<String, String> answer = new HashMap<>();
                    answer.put("type", "answer");
                    answer.put("id", receivedInfo.get("id"));
                    for (String username : Clients.keySet()) {
                        if (Clients.get(username).Admin()) {
                            answer.put(username, "admin");
                        }
                    }
                    sendBack(answer);
                }
                else{
                    //DatagramPacket resend = new DatagramPacket(s.getBytes(), s.getBytes().length);
                    //MULTICASTsocket.send(resend);
                }
            } catch (IOException | ClassNotFoundException e) {
                // e.printStackTrace();
            }
        }
    }
}
