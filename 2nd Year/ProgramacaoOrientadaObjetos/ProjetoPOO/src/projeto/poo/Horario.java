/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package projeto.poo;

/**
 *
 * @author Magui
 */
public class Horario {
    private int hora;
    private int mins;
    
    public Horario(int hora, int mins){
        this.hora= hora;
        this.mins= mins;
    }
    
    public int var_hora(){
        return hora;
    }
    public int var_min(){
        return mins;
    }
}
