package ucBusca.meta1;

import java.rmi.*;
import java.rmi.registry.*;
import java.lang.*;
import java.io.*;
import java.sql.SQLOutput;
import java.util.*;

public class RMIClient implements RMIClientIniterface {

    private static RMIClient client;
    private static RMIInterface rmiInterface = null;
    private static boolean logged_in = false;
    private static boolean is_admin = false;
    private static String username = null;
    private static String password = null;
    private static NotificationImpl notifs;

    public void pingMe(String s){
        System.out.print("");
    }

    public boolean getLogged_in(){
        return logged_in;
    }
    public void setLogged_in(boolean logged_in){this.logged_in = logged_in; }
    public boolean getIsAdmin(){
        return is_admin;
    }
    public String getUsername(){
        return username;
    }
    private void setUsernamePassword(String Username, String Password){
        this.username = Username;
        this.password = Password;
    }

    public void setAdmin(boolean ad){
        this.is_admin = ad;
    }
    public String getPassword(){ return password; }

    private RMIClient() {
        logged_in = false;
        is_admin = false;
        username = null;
        password = null;
        /*try {
            notifs = new NotificationImpl(client);
        } catch (RemoteException e) {
            e.printStackTrace();
        }*/
    }

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

    private void login_user(){
        BufferedReader bf = new BufferedReader(new InputStreamReader(System.in));
        try {
            System.out.println("Your username:");
            String username = bf.readLine();
            System.out.println("Your password:");
            String password = bf.readLine();
            HashMap<String, String> answer = rmiInterface.login(username, password);
            if(answer.get("login").equals("yes")){
                setUsernamePassword(username, password);
                setAdmin(Boolean.parseBoolean(answer.get("admin")));
                setLogged_in(true);
                rmiInterface.clientSubscribe(username, client);
            }
        } catch (RemoteException e) {
            connectRMI();
            //e.printStackTrace();
        } catch (IOException e) {
            //e.printStackTrace();
        }
    }

    private void regist_user() {
        BufferedReader bf = new BufferedReader(new InputStreamReader(System.in));
        try {
            System.out.println("Choose username:");
            String username = bf.readLine();
            System.out.println("Choose password:");
            String password = bf.readLine();
            HashMap<String, String> answer = rmiInterface.register(username, password);
            System.out.println(answer.get("message"));
        } catch (RemoteException e) {
            connectRMI();
            //e.printStackTrace();
        } catch (IOException e) {
            //e.printStackTrace();
        }
    }

    private void search_menu(){
        BufferedReader bf = new BufferedReader(new InputStreamReader(System.in));
        int sum = 0;
        String log = "";
        System.out.println("Web Search:");
        try{
            String search= bf.readLine();

            HashMap<String, String> answer = rmiInterface.search(search, client.getUsername(), null);
            int counter = 0;
            for (String url : answer.keySet()){
                if(!url.equals("id") && !url.equals("type")){
                    System.out.println(url);
                    counter++;
                    if(counter == 10) break;
                }
            }
        } catch (IOException e) {
            connectRMI();
            //e.printStackTrace();
        }
    }

    private void logout(){
        try {
            HashMap<String, String> answer = rmiInterface.logout(client.getUsername());
            client.setAdmin(false);
            client.setLogged_in(false);
            System.out.println(answer.get("message"));

        }catch (RemoteException e){
            //connectRMI();
        }
    }

    private void indexURL(){
        BufferedReader bf = new BufferedReader(new InputStreamReader(System.in));
        try{
            System.out.println("Write the link:");
            String link = bf.readLine();
            HashMap<String, String> answer = rmiInterface.indexUrl(null, link);
            System.out.println(answer.get("ack"));
        }catch (RemoteException e){
            connectRMI();
            //e.printStackTrace();
        } catch (IOException e) {
            //e.printStackTrace();
        }
    }

    private static void givePriviliges(){
        BufferedReader bf = new BufferedReader(new InputStreamReader(System.in));
        try{
            System.out.println("Username of the Client:");
            String clientUsername = bf.readLine();
            HashMap<String, String> answer = rmiInterface.givePrevilige(clientUsername, false);
            System.out.println(answer.get("ack"));
        }catch (RemoteException e){
            connectRMI();
            //e.printStackTrace();
        } catch (IOException e) {
            //e.printStackTrace();
        }

    }

    private static void searchHistory() {
        try{
            HashMap<String, String> answer = rmiInterface.searchHistory(username);
            System.out.println(" --- Search History ---");
            for (String key : answer.keySet()){
                if(!key.equals("type") && !key.equals("id")){
                    System.out.println(key);
                }
            }
        }catch (RemoteException e){
            //connectRMI();
            //e.printStackTrace();
        }
    }

    private static void browseLinkToURL(){
        BufferedReader bf = new BufferedReader(new InputStreamReader(System.in));
        try{
            System.out.println("Insert link:");
            String link = bf.readLine();
            HashMap<String, String> answer = rmiInterface.browseURL(link);
            for (String key: answer.keySet()){
                if (!key.equals("id") && !key.equals("type")){
                    System.out.println(key);
                }
            }
        }catch (RemoteException e){
            connectRMI();
            //e.printStackTrace();
        } catch (IOException e) {
            //e.printStackTrace();
        }
    }


    private static void connectRMI(){
        //connect to RMIserver
        while(true){
            try {
                //Registry registry = LocateRegistry.getRegistry("192.168.1.161",1099);
                Registry registry = LocateRegistry.getRegistry("127.0.0.1",1099);
                rmiInterface = (RMIInterface) registry.lookup("rmiserver");
                if(client.getUsername()!= null && client.getPassword()!=null){
                    HashMap<String, String> login = rmiInterface.login(client.getUsername(),client.getPassword());
                    //System.out.println(login);
                }
                break;
            } catch (RemoteException | NotBoundException e) {
                System.out.println("Please wait, we are trying to establish connection!");
                try {
                    Thread.sleep(1000);
                }catch (InterruptedException ignored){};
            }
        }
    }


    public static void LoggedMenu() throws IOException {

        BufferedReader bf = new BufferedReader(new InputStreamReader(System.in));
        System.out.println("------ ucBUSCA--------");
        System.out.println("1 - Log Out");
        System.out.println("2 - Search");
        System.out.println("3 - Search history");
        System.out.println("4 - Browse pages that link to URL");
        if(client.getIsAdmin()){
            System.out.println("5 - Admin Area");
        }
        String opcao = bf.readLine();
        switch (Integer.parseInt(opcao)) {
            case 1:
                client.logout();
                break;
            case 2:
                client.search_menu();
                break;
            case 3:
                client.searchHistory();
                break;
            case 4:
                client.browseLinkToURL();
                break;
            case 5:
                adminMenu();
                break;
            default:
                System.out.println("Choose one of the options on the menu!");
                break;
        }
    }

    public static void adminMenu() throws IOException {
        BufferedReader bf = new BufferedReader(new InputStreamReader(System.in));
        if (!client.getIsAdmin()) {
            System.out.println("You don't have administrator privilege!");
        } else {
            while (client.getIsAdmin()) {
                System.out.println("------ ucBUSCA--------");
                System.out.println("1 - Index URL");
                System.out.println("2 - Give privileges ");
                System.out.println("3 - Go back");
                String opcao2 = bf.readLine();
                switch (Integer.parseInt(opcao2)) {
                    case 1:
                        client.indexURL();
                        break;
                    case 2:
                        client.givePriviliges();
                        break;
                    case 3:
                        LoggedMenu();
                        return;
                    default:
                        System.out.println("Choose one of the options on the menu!");
                        break;
                }
            }
        }
    }

    private static void mainMenu() {
        BufferedReader bf = new BufferedReader(new InputStreamReader(System.in));
        try {
            while (true) {
                System.out.println(client.getLogged_in());
                if(client.getLogged_in()){
                    //getNotifications();
                    while (client.getLogged_in()) {
                        LoggedMenu();
                    }
                } else{
                    BufferedReader bf3 = new BufferedReader(new InputStreamReader(System.in));
                    System.out.println("------ ucBUSCA--------");
                    System.out.println("1 - Login");
                    System.out.println("2 - Register");
                    System.out.println("3 - Search");
                    System.out.println("4 - Exit");
                    String menu_choice = bf3.readLine();
                    switch (Integer.parseInt(menu_choice)){
                        case 1:
                            client.login_user();
                            break;
                        case 2:
                            client.regist_user();
                            break;
                        case 3:
                            client.search_menu();
                            break;
                        case 4:
                            client.setAdmin(false);
                            client.setLogged_in(false);
                            client.logout();
                            System.exit(0);
                        default:
                            System.out.println("Choose one of the options on the menu!");
                            break;
                    }
                }

            }
        }catch (IOException e) { //e.printStackTrace();
        }
    }


    public static void main(String[] args) {
        try {
            client = new RMIClient();
            connectRMI();
            mainMenu();
        } catch (Exception e) {
            //e.printStackTrace();
        }
    }
}
