package ucBusca.action;

import ucBusca.meta1.RMIInterface;
import ucBusca.model.Browser;
import ucBusca.model.ClientBean;
import ucBusca.model.Index;
import com.opensymphony.xwork2.ActionSupport;
import org.apache.struts2.interceptor.SessionAware;
import ucBusca.model.ServerConnection;
import ucBusca.action.*;

import java.rmi.NotBoundException;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.util.HashMap;
import java.util.Map;



public class IndexAction extends ActionSupport implements SessionAware{
    private static final long serialVersionUID = 5590830L;
    private Map<String, Object> session;

    public String execute() throws Exception {
        /* Vai indexar o url fornecido */
        ServerConnection sv = getServerConnection();
        Index sessIndex = getIndex();
        Browser sessBrowser = getBrowser();
        ClientBean client = getClientBean();
        try {

            Registry registry = LocateRegistry.getRegistry("127.0.0.1",1099);
            sv.setServer((RMIInterface) registry.lookup("rmiserver"));

            // sends sendrequest to RMI Server
            System.out.println(sessIndex.getLink());
            HashMap<String, String> answer = sv.getServer().indexUrl(null, sessIndex.getLink());
            sessIndex.setAnswerMsg(answer.get("ack"));

        } catch (RemoteException | NotBoundException e) {
            e.printStackTrace();
        }
        return SUCCESS;
    }

    @Override
    public void setSession(Map<String, Object> session) {
        this.session = session;
    }

    // create a session
    public void setIndex(Index toIndex){
        this.session.put("index", toIndex);
    }
    // get a session
    public Index getIndex(){
        if(!session.containsKey("index"))
            this.setIndex(new Index());
        return (Index) session.get("index");
    }

    // create a session
    public void setClientBean(ClientBean index){
        this.session.put("clientBean", index);
    }
    // get a session
    public ClientBean getClientBean(){
        if(!session.containsKey("clientBean"))
            this.setClientBean(new ClientBean());
        return (ClientBean) session.get("clientBean");
    }

    public void setServerConnection(ServerConnection serverConnection){
        this.session.put("serverConnection", serverConnection);
    }
    public ServerConnection getServerConnection(){
        if(!session.containsKey("serverConnection"))
            this.setServerConnection(new ServerConnection());
        return (ServerConnection) session.get("serverConnection");
    }

    public void setBrowser(Browser browser){
        this.session.put("browser", browser);
    }
    public Browser getBrowser(){
        if(!session.containsKey("browser"))
            this.setBrowser(new Browser());
        return (Browser) session.get("browser");
    }

}
