package ucBusca.myObjects;

import java.net.URI;

import javax.websocket.ClientEndpoint;

import javax.websocket.OnMessage;
import javax.websocket.Session;
import javax.websocket.WebSocketContainer;

@ClientEndpoint
public class WebSocketClient{
	public Session userSession = null;
	public String username;
	private MessageHandler messageHandlr;
	
	public WebSocketClient(URI endpointURI, String username) {
		try {
			WebSocketContainer websocket = javax.websocket.ContainerProvider.getWebSocketContainer();
			this.username=username;
			System.out.println(websocket);
			System.out.println(endpointURI);
			websocket.connectToServer(this, endpointURI);
			
			
		}catch (Exception e) {}
	}
	
	@javax.websocket.OnOpen
	public void OnOpen(Session userSession) {
		System.out.println("Criou o WebSocket");
		this.userSession = userSession;
	}
	
	public Session getUserSession() {
		return userSession;
	}

	public void setUserSession(Session userSession) {
		this.userSession = userSession;
	}

	public String getUsername() {
		return username;
	}

	public void setUsername(String username) {
		this.username = username;
	}

	public void sendMessage(String message) {
        this.userSession.getAsyncRemote().sendText(message);
    }

	public interface MessageHandler {
        void handleMessage(String message);
    }

	@OnMessage
	public void onMessage(String message) {
		if (this.messageHandlr != null) {
			this.messageHandlr.handleMessage(message);
		}
	}
	
	public void addMessageHandler(MessageHandler msgHandler) {
        this.messageHandlr = msgHandler;
    }
	
	@javax.websocket.OnError
	public void OnError(Throwable t) throws Throwable {
		System.out.println("ERRO");
		t.printStackTrace();
	}
}