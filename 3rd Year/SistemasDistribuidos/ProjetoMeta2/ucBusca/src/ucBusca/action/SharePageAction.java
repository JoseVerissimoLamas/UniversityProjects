package ucBusca.action;

import com.github.scribejava.core.builder.ServiceBuilder;
import com.github.scribejava.core.model.Token;
import com.github.scribejava.core.oauth.OAuthService;
import com.opensymphony.xwork2.ActionSupport;
import org.apache.struts2.interceptor.SessionAware;
import uc.sd.apis.FacebookApi2;
import ucBusca.model.Browser;
import ucBusca.model.ClientBean;
import ucBusca.model.ServerConnection;

import java.util.Map;

public class SharePageAction extends ActionSupport implements SessionAware {
    private static final long serialVersionUID = 5590830L;
    private Map<String, Object> session;
    private String query;

    private String ShareUrl;

    public void setShareUrl(String ShareUrl) {
        this.ShareUrl = ShareUrl;
    }

    public String getShareUrl(){
        return ShareUrl;
    }

    public String execute() {
        Browser sessBrowser = getBrowser();
        String redirectlink ="http://sputnikgo.pt/ucBusca/search.jsp?terms="+sessBrowser.getQuery();
        ShareUrl = "http://www.facebook.com/dialog/feed?app_id=678936679308160+"+"&display=popup&link="+redirectlink+"&redirect_uri=http://sputnikgo.pt/ucBusca/index.jsp";
        setShareUrl(ShareUrl);
        return "redirect";
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
