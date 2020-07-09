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
public class Mestrado extends Aluno{
    private Local localEvitar;
    public Mestrado(String nome, int max_gastar,Local levit) {
        super(nome, max_gastar);
        this.localEvitar = levit;
        super.defineType("M");
    }
    
    public Local getEvitar(){
        return localEvitar;
    }
}
