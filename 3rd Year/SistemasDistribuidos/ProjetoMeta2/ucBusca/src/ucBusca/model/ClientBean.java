package ucBusca.model;

import ucBusca.meta1.RMIInterface;

import java.rmi.NotBoundException;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;

public class ClientBean {
    private String username;
    private String password;
    private String message;
    private Boolean Admin;
    private String Log;

    public void setUsername(String username){
        this.username = username;
    }
    public String getUsername(){
        return this.username;
    }
    public void setPassword(String password){
        this.password = password;
    }
    public String getPassword(){
        return this.password;
    }
    public void setMessage(String message){this.message = message; }
    public String getMessage(){return message; }
    public void setAdmin(Boolean Admin){ this.Admin = Admin;}
    public Boolean getAdmin(){
       return this.Admin;}
    public void setLog(String log){this.Log = log;}
    public String getLog(){
        return this.Log;
    }
        public void pingMe(String s) {
        System.out.println(s);
    }
}