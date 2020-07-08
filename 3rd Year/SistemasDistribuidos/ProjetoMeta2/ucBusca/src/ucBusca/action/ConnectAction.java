package ucBusca.action;

import ucBusca.meta1.RMIInterface;
import ucBusca.model.ClientBean;
import ucBusca.model.Index;
import com.opensymphony.xwork2.ActionSupport;
import org.apache.struts2.interceptor.SessionAware;
import ucBusca.model.ServerConnection;

import java.rmi.NotBoundException;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.util.HashMap;
import java.util.Map;

public class ConnectAction extends ActionSupport implements SessionAware{
    private static final long serialVersionUID = 5590830L;
    private Map<String, Object> session;

    public String startIndexing() throws Exception {
        /* Vai indexar o url fornecido */
        ServerConnection sessServer = getServerConnection();
        ClientBean client = getClientBean();
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

    // create a session
    public void setServerConnection(ServerConnection serverConnection){
        this.session.put("serverConnection", serverConnection);
    }
    // get a session
    public ServerConnection getServerConnection(){
        if(!session.containsKey("serverConnection"))
            this.setServerConnection(new ServerConnection());
        return (ServerConnection) session.get("serverConnection");
    }
}
