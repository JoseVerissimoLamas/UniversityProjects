package ucBusca.action;

import com.opensymphony.xwork2.ActionSupport;
import com.sun.org.apache.xpath.internal.objects.XObject;
import org.apache.struts2.interceptor.SessionAware;
import org.json.simple.JSONObject;
import org.json.simple.JSONValue;
import ucBusca.model.Browser;
import ucBusca.model.ClientBean;
import ucBusca.model.ServerConnection;
import ucBusca.myObjects.UrlObject;

import java.io.IOException;
import java.sql.SQLOutput;
import java.util.ArrayList;
import java.util.Map;
import java.util.StringTokenizer;

public class YandexAction extends ActionSupport implements SessionAware {
    private static final long serialVersionUID = 5590830L;
    private Map<String, Object> session;

    public String execute() {
        ServerConnection sv = getServerConnection();
        Browser sessBrowser = getBrowser();
        ArrayList<String> result = new ArrayList<>();
        ArrayList<UrlObject> aux2 = new ArrayList<>();
        try{
            ArrayList<UrlObject> aux = sessBrowser.getDetailedResults();
            for(UrlObject elem : aux){
                result = sv.getServer().yandexTranslate(elem.getTitle(),elem.getDescription());
                aux2.add(new UrlObject(elem.getTitle(),result.get(0),result.get(1)));
            }
            sessBrowser.setTranslatedResults(aux2);
        }catch (IOException e){
            e.printStackTrace();
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
}
