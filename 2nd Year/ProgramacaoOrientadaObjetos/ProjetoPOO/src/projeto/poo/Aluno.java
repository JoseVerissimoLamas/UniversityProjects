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
public class Aluno {
    private String nome;
    private int max_gastar;
    private String tipo ="";
    //private Viagem viagem;
    
    public Aluno(String nome, int max_gastar){
        this.nome=nome;
        this.max_gastar = max_gastar;
    }
    public void defineType(String tipo){
        this.tipo= tipo;
    }
    public String var_nome(){
        return nome;
    }
    public int var_gastar(){
        return max_gastar;
    } 
    public String var_tipo(){
        return tipo;
    }
}
