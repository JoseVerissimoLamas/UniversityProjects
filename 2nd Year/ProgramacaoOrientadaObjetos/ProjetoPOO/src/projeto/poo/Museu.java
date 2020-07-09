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
public class Museu extends PontosInteresse{
    private String tematica;
    
    public Museu(String nome, int custo, Horario abr, Horario fecho, String tematica, int guia){
        super(nome, custo+guia, abr, fecho);
        this.tematica = tematica;
    }
    public void print(){
        System.out.println("Museu: "+var_nome());
        System.out.println("\nHorario de abertura"+var_abr()[0]+":"+var_abr()[1]);
        System.out.println("\nHorario de fecho"+var_fecho()[0]+":"+var_fecho()[1]);
        System.out.println("\nCusto de entrada: "+var_custo());
        
    }
}
