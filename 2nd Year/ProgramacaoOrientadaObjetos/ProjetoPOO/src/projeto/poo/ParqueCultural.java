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
public class ParqueCultural extends PontosInteresse{
    
    public ParqueCultural(String nome, int custo, Horario abr, Horario fecho) {
        super(nome, custo, abr, fecho);
    }
    public void print(){
        System.out.println("Parque Cultural: "+var_nome());
        System.out.println("\nHorario de abertura"+var_abr()[0]+":"+var_abr()[1]);
        System.out.println("\nHorario de fecho"+var_fecho()[0]+":"+var_fecho()[1]);
        System.out.println("\nCusto de entrada: "+var_custo());
    }
}
