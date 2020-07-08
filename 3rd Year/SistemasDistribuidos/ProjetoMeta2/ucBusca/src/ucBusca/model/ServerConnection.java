package ucBusca.model;

import com.sun.security.ntlm.Server;
import ucBusca.meta1.RMIInterface;

import java.rmi.NotBoundException;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;

public class ServerConnection {
    private RMIInterface server = null;

    public ServerConnection(){
        try {
            Registry registry = LocateRegistry.getRegistry("127.0.0.1",1099);
            server = ((RMIInterface) registry.lookup("rmiserver"));
        } catch (RemoteException | NotBoundException e) {
            //e.printStackTrace();
        }
    }

    public void setServer(RMIInterface server) {
        this.server = server;
    }

    public RMIInterface getServer() {
        return server;
    }
}
