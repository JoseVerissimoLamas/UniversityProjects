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
public class Licenciatura extends Aluno{
    private PontosInteresse hot;
    public Licenciatura(String nome, int max_gastar, PontosInteresse phot) {
        super(nome, max_gastar);
        this.hot = phot;
        super.defineType("L");
    }
    
    public PontosInteresse getHot(){
        return hot;
    }
}
