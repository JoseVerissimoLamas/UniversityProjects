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
public class ParqueAquatico extends PontosInteresse{
    private ArrayList<Piscinas> piscinas = new ArrayList<Piscinas>();
    private ArrayList<Espetaculos> espetaculos = new ArrayList<Espetaculos>();
    
    public ParqueAquatico(String nome, int custo, Horario abr, Horario fecho) {
        super(nome, custo, abr, fecho);
    }
    public void addEspetaculo(String nome, int custo_ext){
        Espetaculos e= new Espetaculos(nome, custo_ext);
        espetaculos.add(e);
    }
    public void addPiscina(String nome, int numero){
        Piscinas p= new Piscinas(nome, numero);
        piscinas.add(p);
    }
    public void print(){
        System.out.println("Parque Aquatico: "+var_nome());
        System.out.println("\nHorario de abertura"+var_abr()[0]+":"+var_abr()[1]);
        System.out.println("\nHorario de fecho"+var_fecho()[0]+":"+var_fecho()[1]);
        System.out.println("\nCusto de entrada: "+var_custo());
        if(piscinas.size()>0){
            for(int i=0; i<piscinas.size(); i++){
                System.out.println("\nPiscina: "+piscinas.get(i));
            }
        }
    }
    
}
