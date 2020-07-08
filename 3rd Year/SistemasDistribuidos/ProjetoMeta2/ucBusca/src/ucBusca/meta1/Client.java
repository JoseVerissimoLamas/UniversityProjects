package ucBusca.meta1;

import java.io.Serializable;
import java.util.*;


/**
 * Class do cliente com os seus atributos
 */
public class Client implements Serializable {
    private String name;
    private String password;
    private boolean isAdmin;
    private ArrayList<String> searches;
    private ArrayList<String> notifications;

    public Client(String name, String password, boolean isAdmin) {
        this.name = name;
        this.password = password;
        this.isAdmin = isAdmin;
        searches= new ArrayList<>();
        notifications = new ArrayList<>();
    }

    public void setName(String name) {
        this.name = name;
    }

    public void setPassword(String password) {
        this.password = password;
    }

    public void setAdmin(boolean admin) {
        isAdmin = admin;
    }

    public String getName() {
        return name;
    }

    public String getPassword() {
        return password;
    }

    public boolean Admin() {
        return isAdmin;
    }

    public ArrayList<String> getSearches() {
        return searches;
    }

    public ArrayList<String> notifications() {return notifications;}
}