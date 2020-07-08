package ucBusca.action;
import java.io.*;
import java.net.*;
import java.util.Map;

import com.github.scribejava.core.builder.ServiceBuilder;
import com.github.scribejava.core.exceptions.OAuthException;
import com.github.scribejava.core.model.*;
import com.github.scribejava.core.oauth.OAuthService;
import com.opensymphony.xwork2.ActionSupport;
import org.apache.commons.io.IOUtils;
import org.apache.struts2.interceptor.SessionAware;
import org.jsoup.Jsoup;
import org.jsoup.nodes.Document;
import org.jsoup.nodes.Element;
import org.jsoup.select.Elements;
import uc.sd.apis.FacebookApi2;
import ucBusca.model.*;

public class FacebookAction extends ActionSupport implements SessionAware {
    private static final long serialVersionUID = 5590830L;
    private Map<String, Object> session;
    private static final String NETWORK_NAME = "Facebook";
    private static final String PROTECTED_RESOURCE_URL = "https://graph.facebook.com/me";
    private static final Token EMPTY_TOKEN = null;

    private String authorizationUrl;

    public void setAuthorizationUrl(String authorizationUrl) {
        this.authorizationUrl = authorizationUrl;
    }

    public String getAuthorizationUrl(){
        return authorizationUrl;
    }


    public String execute() {
        // Replace these with your own api key and secret
        String apiKey = "678936679308160";
        String apiSecret = "0d0deaa07b813505b0ce076bf4347f05";

        OAuthService service = new ServiceBuilder()
                .provider(FacebookApi2.class)
                .apiKey(apiKey)
                .apiSecret(apiSecret)
                .callback("http://localhost:8080/ucBusca/token.action")
                .scope("public_profile")
                .build();

        authorizationUrl = service.getAuthorizationUrl(EMPTY_TOKEN);
        setAuthorizationUrl(authorizationUrl);
        session.put("service",service);


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

}


