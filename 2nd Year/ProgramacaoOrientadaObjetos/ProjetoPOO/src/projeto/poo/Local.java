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
public class Local {
    private String nome;
    private int[] coords= new int[2];
    
    private ArrayList<PontosInteresse> pntsInt= new ArrayList<>();
    
  
    public Local(String nome, int x, int y){
        this.nome= nome;
        coords[0]= x;
        coords[1]= y;
    }
    
    public String var_nome(){
        return this.nome;
    }
    public int[] var_coords(){
        return coords;
    }
    
    public void addPnt(PontosInteresse pnt){
        this.pntsInt.add(pnt);
    }
    public ArrayList<PontosInteresse> getPnts(){
        return this.pntsInt;
    }
}
