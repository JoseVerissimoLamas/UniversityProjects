package ucBusca.action;

import com.opensymphony.xwork2.ActionSupport;
import org.apache.struts2.interceptor.SessionAware;

import java.io.IOException;
import java.rmi.RemoteException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;
import java.util.StringTokenizer;

import ucBusca.model.Browser;
import ucBusca.model.ClientBean;
import ucBusca.model.ServerConnection;
import ucBusca.myObjects.UrlObject;

public class SearchAction extends ActionSupport implements SessionAware {
    private static final long serialVersionUID = 5590830L;
    private Map<String, Object> session;
    private String query;

    public void setQuery(){
        this.query = query;
    }

    public String getQuery(){
        return query;
    }

    @Override
    public String execute(){
        ServerConnection sv = getServerConnection();
        Browser sessBrowser = getBrowser();
        ClientBean client = getClientBean();
        String lang = null;
        try {

            String username = null;
            if(client != null) username = client.getUsername();

            HashMap<String, String> resultados = sv.getServer().search(sessBrowser.getQuery(), username, null);
            ArrayList<UrlObject> aux = new ArrayList<>();
            for(String key : resultados.keySet()){
                if(key.compareTo("type")!=0 && key.compareTo("id")!=0){
                    StringTokenizer tokenizer = new StringTokenizer(resultados.get(key),"§");
                    String originalTitle = tokenizer.nextToken();
                    System.out.println(originalTitle);
                    String originalDesc = "No Description!";
                    if(tokenizer.hasMoreTokens()){
                        originalDesc = tokenizer.nextToken();
                        System.out.println(originalDesc);
                    }
                    lang = sv.getServer().yandexTranslateDetect(originalTitle,originalDesc);
                    aux.add(new UrlObject(key, originalTitle, originalDesc));
                }
            }
            sessBrowser.setLang(lang);
            sessBrowser.setDetailedResults(aux);
        } catch (RemoteException e) {
            e.printStackTrace();
        } catch (IOException e) {
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
            return null;
        return (ClientBean) session.get("clientBean");
    }
}
