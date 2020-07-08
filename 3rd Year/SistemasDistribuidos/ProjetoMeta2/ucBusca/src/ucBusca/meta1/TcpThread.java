package ucBusca.meta1;

import java.io.*;
import java.net.*;
import java.util.ArrayList;
import java.util.StringTokenizer;
import java.util.concurrent.ConcurrentHashMap;

/**
 *  Classe onde vão ser guardadas as HashMaps que vão ser enviadas pelo TPC
 */
class Informacao implements Serializable{
    ConcurrentHashMap<String, ArrayList<String>> WordList;
    ConcurrentHashMap<String, ArrayList<String>> UrlList;
    ConcurrentHashMap<String, Integer> NumbLinks;
    Informacao(ConcurrentHashMap<String, ArrayList<String>> WordList, ConcurrentHashMap<String, ArrayList<String>> UrlList, ConcurrentHashMap<String, Integer> NumbLinks){
        this.WordList = WordList;
        this.UrlList = UrlList;
        this.NumbLinks = NumbLinks;
    }
}


/**
 *  Connecção TCP responsável por enviar a nova informação a ser atualizada
 *  nos outros servidores Multicast
 */
class TcpClient implements Runnable{

    Socket socket = null;
    private ObjectOutputStream out = null;
    String address;
    int port;
    Informacao newInfo = null;

    TcpClient(String address, int port, ConcurrentHashMap<String, ArrayList<String>> newInfoWordList, ConcurrentHashMap<String, ArrayList<String>> newInfoUrlList, ConcurrentHashMap<String, Integer> newInfoNumbLinks){
        this.address = address;
        this.port = port;
        this.newInfo = new Informacao(newInfoWordList, newInfoUrlList, newInfoNumbLinks);
    }

    @Override
    public synchronized void run(){
        try {

            socket = new Socket(address, port);
            out    = new ObjectOutputStream(socket.getOutputStream());

            out.writeObject(this.newInfo);

            out.close();
            socket.close();
            Thread.currentThread().interrupt();

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}


/**
 *  Connecção TCP responsável por receber as novas informações
 *  e atualizar a que tem no ser servidor
 */
class TcpServer implements Runnable{

    private Socket socket;
    private ServerSocket server;
    private ObjectInputStream in;
    int port;
    ConcurrentHashMap<String, ArrayList<String>> selfWordList;
    ConcurrentHashMap<String, ArrayList<String>> selfUrlList;
    ConcurrentHashMap<String, Integer> selfNumbLinks;
    TcpServer(int port, ConcurrentHashMap<String, ArrayList<String>> selfWordList, ConcurrentHashMap<String, ArrayList<String>> selfUrlList, ConcurrentHashMap<String, Integer> selfNumbLinks){
        this.port = port;
        this.selfWordList = selfWordList;
        this.selfUrlList = selfUrlList;
        this.selfNumbLinks = selfNumbLinks;
    }

    @Override
    public synchronized void run(){
        try {
            System.out.println("TCP Server Online");
            server = new ServerSocket(port);
            Object command;
            while (Thread.currentThread().isAlive()){
                socket = server.accept();
                System.out.println("Accepted!");
                in = new ObjectInputStream(new BufferedInputStream(socket.getInputStream()));
                command= in.readObject();
                Informacao newInfo = (Informacao) command;


                for(String newKey : newInfo.WordList.keySet()){
                    if(!selfWordList.containsKey(newKey)){
                        selfWordList.put(newKey, newInfo.WordList.get(newKey));
                    }else{
                        for(String newUrl : newInfo.WordList.get(newKey)){
                            if(!selfWordList.get(newKey).contains(newUrl)){
                                selfWordList.get(newKey).add(newUrl);
                            }
                        }
                    }
                }

                for(String newKey : newInfo.UrlList.keySet()){
                    if(!selfUrlList.containsKey(newKey)){
                        selfUrlList.put(newKey, newInfo.UrlList.get(newKey));
                    }else{
                        for(String newUrl : newInfo.UrlList.get(newKey)){
                            if(!selfUrlList.get(newKey).contains(newUrl)){
                                selfUrlList.get(newKey).add(newUrl);
                            }
                        }
                    }
                }
                for(String newKey : newInfo.NumbLinks.keySet()){
                    if(!selfNumbLinks.containsKey(newKey)){
                        selfNumbLinks.put(newKey, newInfo.NumbLinks.get(newKey));
                    }
                }

            }

            socket.close();
            in.close();
            System.out.println("TCP Server Shutting Down...");
            Thread.currentThread().interrupt();

        } catch (IOException | ClassNotFoundException e) {
            e.printStackTrace();
        }
    }

}


/**
 *  Função que manda um sinal de Ping ao grupo Multicast para que os
 *  outros servidores recebam o porto do socket do servidor tcp
 */
class PingTcpPort implements Runnable{
    String multAddr;
    int multPort;
    String tcpPort;

    PingTcpPort(String addr, int port,  String msgPort){
        this.tcpPort = msgPort+";";
        multAddr = addr;
        multPort = port;
    }


    @Override
    public synchronized void run() {
        try {
            InetAddress group = InetAddress.getByName(multAddr);

            MulticastSocket multicastSocket = new MulticastSocket();
            DatagramPacket pack = new DatagramPacket(tcpPort.getBytes(), tcpPort.length(), group, multPort);
            while(true){

                    multicastSocket.send(pack);

                    Thread.sleep(5000);
            }
            //multicastSocket.close();

        }catch(Exception e){

        }
    }
}


/**
 *  Função que vai ler os pings e receber os portos e os addresses
 *  dos outros servidores TCP dos outros servidores Multicast
 */
class RcvPing implements Runnable{
    String ADDR;
    int port;
    ConcurrentHashMap<String, Integer> tcpPortList;
    int selfServerPort;

    RcvPing(ConcurrentHashMap<String, Integer> tcpPortList, String addr, int port, int selfServerPort){
        this.tcpPortList = tcpPortList;
        this.ADDR = addr;
        this.port = port;
        this.selfServerPort = selfServerPort;
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

    private void rcvMsg(){
        try {
            // Cria o socket e junta se ao grupo
            InetAddress group = InetAddress.getByName(ADDR);
            MulticastSocket multicastSocket = new MulticastSocket(port);
            multicastSocket.joinGroup(group);

            // Prepara-se para receber o Datagram do grupo
            byte[] buffer = new byte[256];
            DatagramPacket pack = new DatagramPacket(buffer, buffer.length);
            System.out.println("Receiving...");

            // Recebe e reage a mensagem com o web crawler
            while (true){

                multicastSocket.receive(pack);
                String command = new String(buffer);
                String type = protocolType(command, "Msgtype");
                if(type!=null || type.compareTo("answer")==0){
                    multicastSocket.send(pack);
                }else{
                    String addr = pack.getAddress().getHostAddress();

                    //acrescenta a list
                    if( !tcpPortList.containsValue(Integer.parseInt(command.split(";")[0])) && Integer.parseInt(command.split(";")[0])!=selfServerPort){
                        tcpPortList.put(addr, Integer.parseInt(command.split(";")[0]));
                        System.out.println("added");
                    }
                }
            }

        }catch (Exception e){
            //e.printStackTrace();
        }
    }

    @Override
    public synchronized void run(){
        rcvMsg();
    }
}
