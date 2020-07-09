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
public class Bar extends PontosInteresse{
    private int classificacao;
    private ArrayList<String> bebidas = new ArrayList<String>();
    private ArrayList<Integer> p_bebidas = new ArrayList<Integer>();
    
    public Bar(String nome, int custo, Horario abr, Horario fecho, int classif) {
        super(nome, custo, abr, fecho);
        if(classif > 10 || classif < 0){
            System.out.println("O ficheiro deu erro");
        }
        else{this.classificacao= classif;}
    }
    public void addBebida(String n_beb, int custoBeb){
        bebidas.add(n_beb);
        p_bebidas.add(custoBeb);
    }
    public void print(){
        System.out.println("Bar: "+var_nome());
        System.out.println("\nHorario de abertura"+var_abr()[0]+":"+var_abr()[1]);
        System.out.println("\nHorario de fecho"+var_fecho()[0]+":"+var_fecho()[1]);
        System.out.println("\nConsumo minimo: "+var_custo());
        if(bebidas.size()>0){
            for(int i=0; i<bebidas.size(); i++){
                System.out.println("\nBebida: "+bebidas.get(i));
                System.out.println(" Preço: "+p_bebidas.get(i));
            }
        }
    }
}
