package ucBusca.action;

import com.opensymphony.xwork2.ActionSupport;
import org.apache.struts2.interceptor.SessionAware;
import ucBusca.meta1.RMIInterface;
import ucBusca.model.ClientBean;
import ucBusca.model.ServerConnection;
import ucBusca.action.*;

import java.rmi.NotBoundException;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.util.HashMap;
import java.util.Map;

public class LogoutAction extends ActionSupport implements SessionAware {

    private static final long serialVersionUID = 5590830L;
    private static final String FAIL = "fail";
    private Map<String, Object> session;
    HashMap<String, String> answer;

    public String execute() throws Exception {
        ClientBean logout = getClientBean();
        ServerConnection sv = getServerConnection();
        try {

            answer = sv.getServer().logout(logout.getUsername());
            logout.setMessage(answer.get("message"));
            logout.setLog("no");

            session.put("loggedin", "no");
            session.put("admin", "no");

            if(answer.get("logout").compareTo("yes")!=0) {
                return FAIL;
            }
        } catch (RemoteException e){
            return FAIL;
        }
        logout.setMessage("");
        session.clear();
        return SUCCESS;
    }

    @Override
    public void setSession(Map<String, Object> session) {
        this.session = session;
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
}