package ws;

import ucBusca.meta1.Notification;
import ucBusca.meta1.RMIInterface;
import ucBusca.model.ClientBean;
import ucBusca.model.ServerConnection;
import java.io.IOException;
import java.rmi.RemoteException;
import java.util.ArrayList;
import java.util.Hashtable;
import java.util.Set;
import java.util.concurrent.CopyOnWriteArraySet;
import java.util.concurrent.atomic.AtomicInteger;
import javax.websocket.server.ServerEndpoint;
import javax.websocket.OnOpen;
import javax.websocket.OnClose;
import javax.websocket.OnMessage;
import javax.websocket.OnError;
import javax.websocket.Session;

@ServerEndpoint(value = "/ws")
public class WebSocketAnnotation{
    private String username;
    private Session session;
    private ClientBean client;
    private ServerConnection sv;

    // O CopyOnWriteArraySet consegue juntar todos os onlineUsers
    public Set<WebSocketAnnotation> onlineUsers = new CopyOnWriteArraySet<>();

    private ArrayList<String> admins = null;
    //ArrayList<String> users = new ArrayList<>();

    public WebSocketAnnotation() {
        onlineUsers.add(this);
    }

    @OnOpen
    public void start(Session session) throws RemoteException {
        this.session = session;
    }

    @OnClose
    public void end() {
        onlineUsers.remove(this);
    }


    @OnMessage
    public void receiveMessage(String message) {

        this.username = message;
        System.out.println("Admin Priveliges");
        for(WebSocketAnnotation user: onlineUsers) {
            if(message.equals(user.username)) {
                try {
                    user.session.getBasicRemote().sendText("Admin");
                    break;
                } catch (IOException e) {}
            }
        }

    }

    @OnError
    public void handleError(Throwable t) {
        t.printStackTrace();
    }

}
