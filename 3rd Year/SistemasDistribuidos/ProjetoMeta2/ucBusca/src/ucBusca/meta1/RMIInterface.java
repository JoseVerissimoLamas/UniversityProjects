package ucBusca.meta1;

import java.io.IOException;
import java.net.ProtocolException;
import java.net.UnknownHostException;
import java.rmi.Remote;
import java.rmi.RemoteException;
import java.util.ArrayList;
import java.util.HashMap;
import ucBusca.model.ClientBean;
import javax.websocket.Session;
import javax.websocket.server.PathParam;
import java.util.Hashtable;
import java.util.Set;
import java.util.concurrent.ConcurrentHashMap;

/**
 * Interface que premite a comunicação entre o cliente rmi, o servidor rmi e os
 * servidores multicast
 */
public interface RMIInterface extends Remote {

    void clientSubscribe(String username, RMIClient client) throws RemoteException;
    void browserSubscribe(String username, ClientBean client) throws  RemoteException;
    HashMap<String,String> register(String username, String password) throws RemoteException, UnknownHostException;
    HashMap<String,String> login(String username, String password) throws RemoteException;
    HashMap<String, String> search(String search, String username, String log) throws RemoteException;
    HashMap<String, String> searchHistory(String username) throws RemoteException;
    HashMap<String, String> indexUrl(String username, String link) throws RemoteException;
    HashMap<String, String> givePrevilige(String username, boolean isWeb) throws RemoteException;
    HashMap<String, String> browseURL(String link) throws RemoteException;
    HashMap<String,String> logout(String username) throws RemoteException;
    ArrayList<String> yandexTranslate(String title, String description) throws IOException;
    String yandexTranslateDetect(String title, String description) throws IOException;
    boolean active() throws RemoteException;
}