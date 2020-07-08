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
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;

public class GetHistoryAction extends ActionSupport implements SessionAware {
    private static final long serialVersionUID = 5590830L;
    private static final String FAIL = "fail";
    private Map<String, Object> session;
    HashMap<String, String> answer;

    public String execute() throws Exception {
        ClientBean login = getClientBean();
        ServerConnection sv = getServerConnection();
        if(login.getLog().compareTo("no")==0) return FAIL;

        try {
            if(sv.getServer()==null){
                try {
                    Registry registry = LocateRegistry.getRegistry("127.0.0.1",1099);
                    sv.setServer((RMIInterface) registry.lookup("rmiserver"));
                } catch (RemoteException | NotBoundException e) {
                }
            }
            Browser results = getBrowser();
            HashMap<String, String> answer = sv.getServer().searchHistory(login.getUsername());
            ArrayList<String> searches = new ArrayList<>();
            for(String key: answer.keySet()){
                if(key.compareTo("type")!=0 && key.compareTo("id")!=0){
                    searches.add(answer.get(key));
                }
            }
            results.setResults(searches);

        } catch (RemoteException e){
            return FAIL;
        }

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

    public void setBrowser(Browser browser){
        this.session.put("browser", browser);
    }
    public Browser getBrowser(){
        if(!session.containsKey("browser"))
            this.setBrowser(new Browser());
        return (Browser) session.get("browser");
    }
}
