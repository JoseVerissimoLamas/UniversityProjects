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

public class GetParentUrlsAction extends ActionSupport implements SessionAware {
    private static final long serialVersionUID = 5590830L;
    private Map<String, Object> session;

    @Override
    public String execute() throws Exception {
        ServerConnection sv = getServerConnection();
        Browser sessBrowser = getBrowser();
        try {

            //Registry registry = LocateRegistry.getRegistry("127.0.0.1",1099);
            //sessBrowser.setServer((RMIInterface) registry.lookup("rmiserver"));

            // sends sendrequest to RMI Server
            if(sv.getServer()==null){
                try {
                    Registry registry = LocateRegistry.getRegistry("127.0.0.1",1099);
                    sv.setServer((RMIInterface) registry.lookup("rmiserver"));
                } catch (RemoteException | NotBoundException e) {
                    e.printStackTrace();
                }
            }
            HashMap<String, String> resultados = sv.getServer().browseURL(sessBrowser.getQuery());

            ArrayList<String> aux = new ArrayList<>();
            for(String key:resultados.keySet()){
                if(key.compareTo("type")!=0 && key.compareTo("id")!=0){
                    aux.add(key);
                }
            }
            sessBrowser.setResults(aux);

        } catch (RemoteException e) {
            e.printStackTrace();
        }
        return SUCCESS;
    }

    @Override
    public void setSession(Map<String, Object> session) {
        this.session = session;
    }

    public void setBrowser(Browser browser){
        this.session.put("browser", browser);
    }
    public Browser getBrowser(){
        if(!session.containsKey("browser"))
            this.setBrowser(new Browser());
        return (Browser) session.get("browser");
    }

    public void setServerConnection(ServerConnection serverConnection){
        this.session.put("serverConnection", serverConnection);
    }
    public ServerConnection getServerConnection(){
        if(!session.containsKey("serverConnection"))
            this.setServerConnection(new ServerConnection());
        return (ServerConnection) session.get("serverConnection");
    }

    public void setClientBean(ClientBean index){
        this.session.put("clientBean", index);
    }
    public ClientBean getClientBean(){
        if(!session.containsKey("clientBean"))
            this.setClientBean(new ClientBean());
        return (ClientBean) session.get("clientBean");
    }
}
