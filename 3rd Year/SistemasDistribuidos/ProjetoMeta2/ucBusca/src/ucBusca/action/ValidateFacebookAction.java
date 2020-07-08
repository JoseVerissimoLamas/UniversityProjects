package ucBusca.action;

import com.github.scribejava.core.model.*;
import com.github.scribejava.core.model.Verifier;
import com.github.scribejava.core.oauth.OAuthService;
import com.opensymphony.xwork2.ActionSupport;
import org.apache.struts2.interceptor.SessionAware;
import org.json.simple.JSONObject;
import org.json.simple.JSONValue;
import ucBusca.meta1.RMIInterface;
import ucBusca.model.ClientBean;
import ucBusca.model.ServerConnection;

import java.net.UnknownHostException;
import java.rmi.NotBoundException;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.util.HashMap;
import java.util.Map;
import java.util.StringTokenizer;

import org.json.*;

public class ValidateFacebookAction extends ActionSupport implements SessionAware {
    private static final long serialVersionUID = 5590830L;
    private static final String FAIL = "fail";
    private Map<String, Object> session;
    private static final String NETWORK_NAME = "Facebook";
    private static final String PROTECTED_RESOURCE_URL = "https://graph.facebook.com/me";
    private static final Token EMPTY_TOKEN = null;
    private String code;
    HashMap<String, String> answer;

    public String execute(){
        ClientBean register = getClientBean();
        OAuthService service = (OAuthService) session.get("service");
        String accessTok = getCode();
        System.out.println(getCode());
        session.put("token",accessTok);
        Verifier ver = new Verifier(accessTok);
        Token accessToken = accessToken = service.getAccessToken(EMPTY_TOKEN,ver);
        OAuthRequest request = new OAuthRequest(Verb.GET, PROTECTED_RESOURCE_URL, service);
        service.signRequest(accessToken, request);
        Response response = request.send();
        System.out.println(response.getBody());

        JSONObject obj = (JSONObject) JSONValue.parse(response.getBody());
        String username = (String) obj.get("name");;
        /*StringTokenizer usernameTokens = new StringTokenizer((String) obj.get("name")," ");
        username = usernameTokens.nextToken()+"_"+usernameTokens.nextToken();*/
        register.setUsername(username);

        System.out.println(obj.get("name"));
        System.out.println(obj.get("id"));

        try {
            ServerConnection sv = getServerConnection();
            answer = sv.getServer().register(username,"null");
            if((answer.get("message").compareTo("Username already taken!")==0)){
                answer = sv.getServer().login(username,"null");
                register.setMessage(answer.get("message"));
                register.setLog((answer.get("login")));
                if(answer.get("login").compareTo("no")==0){
                    return FAIL;
                }else{
                    register.setAdmin(Boolean.parseBoolean(answer.get("admin")));
                }
            }else{
                answer = sv.getServer().login(username,"null");
                register.setMessage(answer.get("message"));
                register.setLog((answer.get("login")));
                if(answer.get("login").compareTo("no")==0){
                    return FAIL;
                }else{
                    register.setAdmin(Boolean.parseBoolean(answer.get("admin")));
                }
            }
        } catch (RemoteException | UnknownHostException e){
            return FAIL;
        }
        register.setMessage("");
        return SUCCESS;
    }

    public void setCode(String code){ this.code = code; }

    public String getCode(){ return code; }

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
