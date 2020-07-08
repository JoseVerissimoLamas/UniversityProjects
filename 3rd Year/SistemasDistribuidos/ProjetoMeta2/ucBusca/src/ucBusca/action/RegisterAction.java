package ucBusca.action;

import com.opensymphony.xwork2.ActionSupport;
import org.apache.struts2.interceptor.SessionAware;
import ucBusca.meta1.RMIInterface;
import ucBusca.model.ClientBean;
import ucBusca.model.ServerConnection;
import ucBusca.action.*;

import java.net.UnknownHostException;
import java.rmi.NotBoundException;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.util.HashMap;
import java.util.Map;

public class RegisterAction extends ActionSupport implements SessionAware {

    private static final long serialVersionUID = 5590830L;
    private static final String FAIL = "fail";
    private Map<String, Object> session;
    HashMap<String, String> answer;

    public String execute() throws Exception {
        ClientBean register = getClientBean();
        ServerConnection sv = getServerConnection();
        try {
            if(sv.getServer()==null){
                try {
                    Registry registry = LocateRegistry.getRegistry("127.0.0.1",1099);
                    sv.setServer((RMIInterface) registry.lookup("rmiserver"));
                } catch (RemoteException | NotBoundException e) {
                    e.printStackTrace();
                }
            }
            answer = sv.getServer().register(register.getUsername(),register.getPassword());
            register.setMessage(answer.get("message"));
            register.setAdmin(Boolean.parseBoolean(answer.get("admin")));
            if(answer.get("register").equals("fail")){
                return FAIL;
            }
        } catch (RemoteException e) {
        } catch (UnknownHostException e) {
        }
        register.setMessage("");
        return SUCCESS;
    }

    public void validate(){
        ClientBean register = getClientBean();
        if(register.getUsername() == null || register.getUsername().length() == 0){
            addFieldError("clientBean.username","Username is required!");
        }
        if(register.getPassword() == null || register.getPassword().length()==0){
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