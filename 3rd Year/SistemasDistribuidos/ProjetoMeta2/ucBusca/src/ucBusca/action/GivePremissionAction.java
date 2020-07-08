package ucBusca.action;

import com.opensymphony.xwork2.ActionSupport;
import org.apache.struts2.interceptor.SessionAware;
import ucBusca.meta1.RMIInterface;
import ucBusca.model.Browser;
import ucBusca.model.ClientBean;
import ucBusca.model.ServerConnection;
import ucBusca.action.*;

import java.rmi.NotBoundException;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.util.HashMap;
import java.util.Map;

public class GivePremissionAction extends ActionSupport implements SessionAware {

    private static final long serialVersionUID = 5590830L;
    private static final String FAIL = "fail";
    private Map<String, Object> session;
    HashMap<String, String> answer;

    public String execute() {
        Browser aux = getBrowser();
        ServerConnection sv = getServerConnection();
        try {

            answer = sv.getServer().givePrevilige(aux.getQuery(), true);
            aux.setMessage(answer.get("ack"));

        } catch (RemoteException e){
            e.printStackTrace();
            return FAIL;
        }
        return SUCCESS;
    }

    @Override
    public void setSession(Map<String, Object> session) {
        this.session = session;
    }

    public void setClientBean(ClientBean index){
        this.session.put("clientBean", index);
    }
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