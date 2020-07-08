package ucBusca.meta1;

import java.rmi.*;

/**
 * Interface remota das notificações para ajudar a
 * dar as notificações em tempo real
 */
public interface Notification extends Remote {
    void note(String notification) throws RemoteException;
    void admin() throws RemoteException;
    //void remove() throws RemoteException;
    void logout() throws RemoteException;
}