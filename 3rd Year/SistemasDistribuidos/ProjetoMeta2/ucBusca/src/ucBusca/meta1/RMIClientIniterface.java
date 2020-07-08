package ucBusca.meta1;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.rmi.NotBoundException;
import java.rmi.Remote;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.util.HashMap;
import java.util.StringTokenizer;

public interface RMIClientIniterface extends Remote {

    // TODO tens que acabar de implementar a interface e ainda tens de fazer um thread para poderes mandar msgs de
    // TODO confirmação aos clientes para poder saber se eles estão online...

    void pingMe(String s);
    boolean getLogged_in();
    void setLogged_in(boolean logged_in);
    boolean getIsAdmin();
    String getUsername();

    void setAdmin(boolean ad);
    String getPassword();


}
