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
public class Feira extends PontosInteresse{
    private ArrayList<Atracoes> atracoes= new ArrayList<Atracoes>();
     
    public Feira(String nome, int custo, Horario abr, Horario fecho) {
        super(nome, custo, abr, fecho);
    }
    public void addAtracoes(String nome, int custo_ext){
        Atracoes e = new Atracoes(nome, custo_ext);
        atracoes.add(e);
    }
     
    public void print(){
        System.out.println("Feira: "+var_nome());
        System.out.println("\nHorario de abertura"+var_abr()[0]+":"+var_abr()[1]);
        System.out.println("\nHorario de fecho"+var_fecho()[0]+":"+var_fecho()[1]);
        System.out.println("\nCusto do guia: "+var_custo());
        if(atracoes.size()>0){
            for(int i=0; i<atracoes.size(); i++){
                System.out.println("\nAtracao: "+atracoes.get(i));
            }
        }
    }
}
