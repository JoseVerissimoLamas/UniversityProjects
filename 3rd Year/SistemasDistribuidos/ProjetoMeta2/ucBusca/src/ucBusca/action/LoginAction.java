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

public class LoginAction extends ActionSupport implements SessionAware {

    private static final long serialVersionUID = 5590830L;
    private static final String FAIL = "fail";
    private Map<String, Object> session;
    HashMap<String, String> answer;

    public String execute() throws Exception {
        ClientBean login = getClientBean();
        ServerConnection sv = getServerConnection();
        try {

            answer = sv.getServer().login(login.getUsername(),login.getPassword());
            login.setMessage(answer.get("message"));
            login.setLog((answer.get("login")));

            if(answer.get("login").compareTo("no")==0){
                return FAIL;
            }else{
                login.setAdmin(Boolean.parseBoolean(answer.get("admin")));
                sv.getServer().browserSubscribe(login.getUsername(), getClientBean());
                session.put("username", login.getUsername());
                session.put("loggedin", "yes");
                session.put("admin", login.getAdmin());
            }
        } catch (RemoteException e){
            return FAIL;
        }
        login.setMessage("");
        return SUCCESS;
    }

    public void validate(){
        ClientBean login = getClientBean();
        if(login.getUsername() == null || login.getUsername().length() == 0){
            addFieldError("clientBean.username","Username is required!");
        }
        if(login.getPassword() == null || login.getPassword().length()==0){
            addFieldError("clientBean.password","Password is required!");
        }
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