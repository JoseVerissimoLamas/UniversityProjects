package ucBusca.meta1;

import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;

/**
 * Implementação da interface remota,
 * As funções dão print no cliente RMI
 */
public class NotificationImpl extends UnicastRemoteObject implements Notification {

    private RMIClient client;

    public NotificationImpl(RMIClient client) throws RemoteException {
        super();
        this.client = client;
    }

    @Override
    public void note(String notification) throws RemoteException {
        System.out.println(notification);
    }

    @Override
    public void admin() throws RemoteException {
        System.out.println("Someone gave you admin previliges!");

    }

    /*@Override
    public void remove() throws RemoteException {
        System.out.println("Someone took your admin previliges away!");

    }*/

    @Override
    public void logout() throws RemoteException{
        client.setLogged_in(false);
    }
}