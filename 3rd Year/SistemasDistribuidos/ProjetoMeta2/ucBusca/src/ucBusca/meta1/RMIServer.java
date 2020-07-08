package ucBusca.meta1;

import jdk.nashorn.internal.parser.JSONParser;
import org.apache.commons.codec.Encoder;
import org.json.simple.JSONArray;
import org.json.simple.JSONObject;
import org.json.simple.JSONValue;
import ucBusca.model.ClientBean;
import ucBusca.myObjects.WebSocketClient;

import java.rmi.*;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.rmi.server.*;
import java.net.*;
import java.io.*;
import java.util.*;
import java.util.concurrent.ConcurrentHashMap;

/**
 *  Class responsável pelas funções do Servidor RMI
 */
public class RMIServer extends UnicastRemoteObject implements RMIInterface {

    private static MulticastSocket MULTICASTsocket;
    private static InetAddress MULTICASTaddress;
    private long id_msg = 0;
    private static int port = 3456;
    private static String ADDR = "226.0.224.0";
    private static String RMIHost = "127.0.0.1";
    private static int RMIport= 1099;
    private Hashtable<String, Notification> onlineClients = new Hashtable<>();
    private static ConcurrentHashMap<Long, Boolean> multicastServersId = new ConcurrentHashMap<Long, Boolean>();

    private ConcurrentHashMap<String, RMIClient> subClient = new ConcurrentHashMap<>(); // List of subscribed clients
    private ConcurrentHashMap<String, ClientBean> browserClients = new ConcurrentHashMap<>(); // List of browser clients

    /**
     *  Cria o grupo Multicast e junta-se a ele
     * @throws RemoteException
     */
    RMIServer() throws RemoteException {
        super();
        try{
            MULTICASTsocket = new MulticastSocket(port);
            MULTICASTaddress = InetAddress.getByName(ADDR);
            MULTICASTsocket.joinGroup(MULTICASTaddress);
        }catch (IOException e){
            e.printStackTrace();
        }

    }

    /**
     * @return Host name do RMI server
     */
    public String getRMIhost(){
        return RMIHost;
    }

    /**
     * @return Porto do RMI server
     */
    public int getRMIport(){
        return RMIport;
    }


    /**
     * Função para retirar partes da mensagem de protocolo enviada entre rmi server, rmi client e multicast server.
     * @param protocolMessage Mensagem recebida de acordo com o protocolo estabelecido.
     * @param type escolher o tipo de conteúdo que se retira da mensagem.
     * @return devolve a mensagem de acordo com o conteúdo escolhido.
     */
    //In this function we use string tokenizer to split the message sent between servers in different parts in order
    //to check the information of certain type.
    public static String protocolType(String protocolMessage, String type) {
        //Split the message in the different fields(type, message, id,...)
        String msgValue;
        String value;
        StringTokenizer message = new StringTokenizer(protocolMessage, "|");
        while (message.hasMoreElements()) {
            msgValue = message.nextToken();
            StringTokenizer result = new StringTokenizer(msgValue, ";");
            value = result.nextToken();
            if (value.equals(type)) {
                return result.nextToken();
            }
        }
        return null;
    }

    /*The new Protocol!!*/
    public static HashMap<String, String> newProtocolType(String type, String protocolMessage) {
        HashMap<String, String> msg = new HashMap<>(); // Final message to send
        StringTokenizer message = new StringTokenizer(protocolMessage, "|");;
        msg.put("type", type);// Register de request type

        // Tens que ver para as outras funcs... isto so esta para o search
        if(type.compareTo("search")==0){
            String[] splited = protocolMessage.split(";");
            for (String s : splited){
                System.out.println(s);
            }
            System.out.println(splited.length);
            if (splited.length > 1){
                msg.put("query", splited[0]);
                msg.put("username", splited[1]);
            }else{
                msg.put("query", protocolMessage);
            }
        }
        else if(type.compareTo("index")==0 || type.compareTo("parentUrl") == 0){
            msg.put("url", protocolMessage);
        }
        else if(type.compareTo("register")==0){
            StringTokenizer tokenizedToken;
            String token;
            while (message.hasMoreTokens()){
                token = message.nextToken();
                tokenizedToken = new StringTokenizer(token, ";");
                msg.put(tokenizedToken.nextToken(), tokenizedToken.nextToken());
            }
        }
        else if(type.compareTo("login")==0){
            StringTokenizer tokenizedToken;
            String token;
            while (message.hasMoreTokens()){
                token = message.nextToken();
                tokenizedToken = new StringTokenizer(token, ";");
                msg.put(tokenizedToken.nextToken(), tokenizedToken.nextToken());
            }
        }
        else if(type.compareTo("history")==0){
            msg.put("username", protocolMessage);
        }
        else if(type.compareTo("logout")==0){
            msg.put("logout", protocolMessage);
            System.out.println(protocolMessage);
        }
        else if(type.compareTo("givePremission")==0){
            msg.put("client", protocolMessage);
        }

        return msg;
    }


    public synchronized HashMap<String, String> Hash_to_Multicast(HashMap<String, String> info){
        try {
            byte[] buffer = new byte[640000];
            long id = this.id_msg++; //TODO tambem podemos simplesmente registar o time stamp
            info.put("id", Long.toString(id));

            // Send to Multicast
            ByteArrayOutputStream bStream = new ByteArrayOutputStream();
            ObjectOutput oo = new ObjectOutputStream(bStream);
            oo.writeObject(info);
            oo.close();
            byte[] data = bStream.toByteArray();
            MULTICASTsocket.send(new DatagramPacket(data, data.length, MULTICASTaddress, port));

            // Receive from Multicast
            while (true){
                MULTICASTsocket.receive(new DatagramPacket(buffer, buffer.length));
                ObjectInputStream iStream = new ObjectInputStream(new ByteArrayInputStream(buffer));
                HashMap<String, String> receivedInfo = (HashMap<String, String>)iStream.readObject();
                iStream.close();

                for (String key: receivedInfo.keySet()){
                    System.out.println(key+" "+receivedInfo.get(key));
                }

                if (receivedInfo.get("type").compareTo("answer") == 0 && Long.parseLong(receivedInfo.get("id")) == id){
                    return receivedInfo;
                }
            }

        } catch (ClassNotFoundException | IOException e) {
        }
        return null;
    }

    @Override
    public String yandexTranslateDetect(String title, String description){
        String translation = null;
        JSONObject obj;
        try{
            URL url = new URL("https://translate.yandex.net/api/v1.5/tr.json/translate");
            HttpURLConnection connection = (HttpURLConnection)url.openConnection();
            connection.setRequestMethod("POST");
            connection.setDoOutput(true);
            connection.setInstanceFollowRedirects(false);
            connection.setRequestProperty("Accept","application/json");
            OutputStreamWriter os = new OutputStreamWriter(connection.getOutputStream());
            String apikey = "trnsl.1.1.20191206T135622Z.47531590b98cdb6a.e23cc87e9029d6c22bc92270c65932093f0cc639";
            os.write("key="+apikey+"&text="+URLEncoder.encode(title,"UTF-8")+"&text="+URLEncoder.encode(description,"UTF-8")+"&lang=pt");
            os.flush();
            BufferedReader in = new BufferedReader(new InputStreamReader(connection.getInputStream()));
            String inputLine;
            while ((inputLine = in.readLine()) != null){
                obj = (JSONObject) JSONValue.parse(inputLine);
                String lang = (String) obj.get("lang");
                StringTokenizer lan = new StringTokenizer(lang,"-");
                translation = lan.nextToken();
                System.out.println(translation);
            }
            in.close();
        }catch (IOException e){
            //e.printStackTrace();
        }
        return translation;
    }

    @Override
    public ArrayList<String> yandexTranslate(String title, String description){
        ArrayList<String> translation = new ArrayList<>();
        JSONObject obj;
        JSONArray jsonArray;
        try{
            URL url = new URL("https://translate.yandex.net/api/v1.5/tr.json/translate") ;
            HttpURLConnection connection = (HttpURLConnection)url.openConnection();
            connection.setRequestMethod("POST");
            connection.setDoOutput(true);
            connection.setInstanceFollowRedirects(false);
            connection.setRequestProperty("Accept","application/json");
            OutputStreamWriter os = new OutputStreamWriter(connection.getOutputStream());
            String apikey = "trnsl.1.1.20191206T135622Z.47531590b98cdb6a.e23cc87e9029d6c22bc92270c65932093f0cc639";
            os.write("key="+apikey+"&text="+URLEncoder.encode(title,"UTF-8")+"&text="+URLEncoder.encode(description,"UTF-8")+"&lang=pt");
            os.flush();
            BufferedReader in = new BufferedReader(new InputStreamReader(connection.getInputStream()));
            String inputLine;
            while ((inputLine = in.readLine()) != null){
                obj = (JSONObject) JSONValue.parse(inputLine);
                String lang = (String) obj.get("lang");
                StringTokenizer lan = new StringTokenizer(lang,"-");
                String original = lan.nextToken();
                String translated = lan.nextToken();
                jsonArray = (JSONArray) obj.get("text");
                String tit = (String) jsonArray.get(0);
                String desc = (String) jsonArray.get(1);
                translation.add(tit);
                translation.add(desc);
            }
            in.close();
        }catch (IOException e){
            //e.printStackTrace();
        }
        return translation;
    }

    @Override
    public HashMap<String, String> login(String username, String password) throws RemoteException {
        String protocolString = "username;" + username + "|password;" + password;
        HashMap<String, String> sendInfo = newProtocolType("login", protocolString);
        return Hash_to_Multicast(sendInfo);
    }

    @Override
    public void clientSubscribe(String username, RMIClient client) throws RemoteException{
        subClient.put(username, client);
    }

    @Override
    public void browserSubscribe(String username, ClientBean client) throws RemoteException{
        browserClients.put(username, client);
    }



    /**
     * Envia uma mensagem register de acordo com o protocolo
     * para o grupo multicast
     *
     * @param username username a ser registado
     * @param password password do user
     * @return resposta do servidor multicast
     * @throws RemoteException ignora a exception
     */
    @Override
    public HashMap<String, String> register(String username, String password) throws RemoteException {
        String protocolString = "username;" + username + "|password;" + password;
        HashMap<String, String> sendInfo = newProtocolType("register", protocolString);
        return Hash_to_Multicast(sendInfo);
    }


    /**
     * Envia uma mensagem de pesquisa de acordo com o protocolo
     * para o grupo multicast
     *
     * @param search palavra a ser pesquisada
     * @param username username do user para registar a pesquisa
     * @param log serve para saber se o utilizador esta
     *            logedin
     * @return resposta do servidor multicast
     * @throws RemoteException ignora a exception
     */
    @Override
    public HashMap<String, String> search(String search, String username, String log){
        System.out.println("search_search:"+search+"_username:"+username);
        String protocolMessage;
        if(username!=null){
            protocolMessage = search+";"+username;
        }else{
            protocolMessage = search;
        }
        HashMap<String, String> sendInfo = newProtocolType("search", protocolMessage);
        System.out.println("search_sendInfo:");
        for (String key:sendInfo.keySet()){
            System.out.println(key+" "+sendInfo.get(key));
        }
        return Hash_to_Multicast(sendInfo);
    }

    /*
     * Envia uma mensagem para ver o registo de acordo
     * com o protocolo
     * para o grupo multicast
     * @param username username do utilizador
     * @return resposta do servidor multicast
     * @throws RemoteException ignora a exception
     */
    @Override
    public HashMap<String, String> searchHistory(String username){
        HashMap<String, String> sendInfo = newProtocolType("history", username);
        return Hash_to_Multicast(sendInfo);
    }

    /**
     * Envia uma mensagem de indexação de acordo com o protocolo
     * para o grupo multicast
     * @param username username do utilizador
     * @param link link a ser indexado
     * @return resposta do servidor multicast
     * @throws RemoteException ignora a exception
     */
    @Override
    public HashMap<String, String> indexUrl(String username, String link) throws RemoteException {
        HashMap<String, String> sendInfo = newProtocolType("index", link);
        return Hash_to_Multicast(sendInfo);
    }

    /**
     * Envia uma mensagem para dar previlégio de acordo com o protocolo
     * para o grupo multicast
     * @param clientUsername username de quem vai receber
     *                       previlegios
     * @return resposta do servidor multicast
     * @throws RemoteException ignora a exception
     */
    @Override
    public HashMap<String, String> givePrevilige(String clientUsername, boolean isWeb)  {
        HashMap<String, String> sendInfo = newProtocolType("givePremission", clientUsername);
        HashMap<String, String> McAnswer = Hash_to_Multicast(sendInfo);
        if(isWeb){
            System.out.println("entrei no if, sou web");
            if(McAnswer.get("ack").equals("success")){
                try{
                    // cria o web socket
                    WebSocketClient wcc = new WebSocketClient(new URI("ws://"+RMIHost+":8080/ucBusca/ws"), McAnswer.get("client"));
                    wcc.addMessageHandler(new WebSocketClient.MessageHandler() {
                        @Override
                        public void handleMessage(String message) {
                            System.out.println(message);
                        }
                    });
                    wcc.sendMessage(McAnswer.get("client"));
                } catch (Exception e){}
            }
        }
        return McAnswer;
    }


    /**
     * Envia uma mensagem para pesquisa dos
     * parent do link
     * de acordo com o protocolo
     * para o grupo multicast
     * @param link link a ser pesquisado
     * @return resposta do servidor
     * @throws RemoteException ignora a exception
     */
    @Override
    public HashMap<String, String> browseURL(String link) throws RemoteException {
        HashMap<String, String> sendInfo = newProtocolType("parentUrl", link);
        return Hash_to_Multicast(sendInfo);
    }


    /**
     * Envia uma mensagem logout de acordo com o protocolo
     * para o grupo multicast
     * @param username username do utilizador a fazer logout
     * @return resposta do servidor
     * @throws RemoteException ignora a exception
     */
    @Override
    public HashMap<String, String> logout(String username) throws RemoteException {
        HashMap<String, String> sendInfo = newProtocolType("logout", username);
        return Hash_to_Multicast(sendInfo);
    }

   /* @Override
    public ArrayList<String> getAdmins() throws RemoteException{
        HashMap<String, String> aux = Hash_to_Multicast(newProtocolType("getAdmins", "null"));
        ArrayList<String> admins = new ArrayList();
        for(String key : aux.keySet()){
            if(!key.equals("id") && !key.equals("type")){
                admins.add(key);
            }
        }
        return admins;
    }*/

    /*@Override
    public Set<String> getOnline() throws RemoteException{
        return onlineClients.keySet();
    }*/

    /**
     * Resposta para saber se o user está
     * ativo
     * @return estado do user
     * @throws RemoteException
     */
    @Override
    public boolean active() throws RemoteException {
        return true;
    }

    /**
     * Vai inciar o servidor, ligar-se ao grupo
     * e preparar-se para receber um servidor backup
     *
     * @param args nao usado
     */
    public static void main(String args[]) {
        try {
            // Cria uma thread que estará a espera dos ids dos multicastServers
            Thread mcServerWaiter = new Thread(new WaitingForMulticastServer(ADDR, port-1, multicastServersId));
            mcServerWaiter.start();

            RMIServer server = new RMIServer();
            Registry registry;
            try {
                assert server != null;
                registry = LocateRegistry.getRegistry(server.getRMIhost(), server.getRMIport());
                RMIInterface primary = (RMIInterface) registry.lookup("rmiserver");
                if (primary.active()) {
                    System.out.println("BackUp Server");
                }
                while (primary.active()) {
                    Thread.sleep(10000);
                }
            } catch (NotBoundException | RemoteException e) {
                System.out.println("Main Server");
                registry = LocateRegistry.createRegistry(server.getRMIport());
                System.setProperty("java.rmi.server.hostname", server.getRMIhost());
                registry.rebind("rmiserver", server);
            }
        } catch (InterruptedException | IOException e){
        }
    }
}

/**
 * Thread que vai receber os ids dos servidores multicast
 * e vai guarda-los na HashMap
 */
class WaitingForMulticastServer implements Runnable{
    String addr;
    int port;
    ConcurrentHashMap<Long, Boolean> idList;

    /**
     * Parametros a associar
     * @param addr address
     * @param port porto
     * @param idList lista de ids dos servidores onde
     *               vai acrescentar o id do servidor
     *               que se connectou
     */
    WaitingForMulticastServer(String addr, int port, ConcurrentHashMap<Long, Boolean> idList){
        this.addr = addr;
        this.port = port;
        this.idList = idList;
    }
    @Override
    public void run() {
        try {
            // Cria o socket e junta se ao grupo
            InetAddress group = InetAddress.getByName(addr);
            MulticastSocket multicastSocket = new MulticastSocket(port);
            multicastSocket.joinGroup(group);

            // Prepara-se para receber o Datagram do grupo
            byte[] buffer = new byte[256];
            DatagramPacket pack = new DatagramPacket(buffer, buffer.length);

            while (true){

                multicastSocket.receive(pack);
                String command = new String(buffer);
                if(command.split(";")[0].compareTo("identify")==0){
                    idList.put(Long.parseLong(command.split(";")[1]), false);
                    System.out.println("a new ms joined! "+command.split(";")[1]);
                }
            }

        }catch (Exception e){
            //e.printStackTrace();
        }
    }
}
class CheckOnlineClients implements Runnable{
    ConcurrentHashMap<String, RMIClient> onlineClients;

    CheckOnlineClients(ConcurrentHashMap<String, RMIClient> clients){
        onlineClients = clients;
    }

    @Override
    public void run() {
        while(true){
            try{ Thread.sleep(5000); }catch(InterruptedException ignored){}

            if(!onlineClients.isEmpty()){
                for (String key : onlineClients.keySet()){
                    try{
                        onlineClients.get(key).pingMe("ping!");
                    }catch (Exception e){
                        onlineClients.remove(key);
                    }

                }
            }
        }
    }
}