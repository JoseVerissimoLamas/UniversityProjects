/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package projeto.poo;

import java.util.ArrayList;

/**
 *
 * @author Magui
 */
public class Viagem {
    private ArrayList<Local> locais = new ArrayList<>();
    
    public Viagem(){
    }
    
    public void addLocal(Local loc){
        if(locais.size() == 3){
            System.out.println("Error");
        }
        else{
            locais.add(loc);
        }
    }
    
    public ArrayList<Local> getLocais(){
        return locais;
    }
    
    
}
