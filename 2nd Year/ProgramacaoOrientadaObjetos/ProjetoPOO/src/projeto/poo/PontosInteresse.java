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
public class PontosInteresse {
    private String nome;
    private int custos;
    private Horario horAbertura;
    private Horario horFecho;
    
    public PontosInteresse(String nome, int custo, Horario abr, Horario fecho){
        this.nome= nome;
        this.custos= custo;
        horAbertura= abr;
        horFecho= fecho;
    }
    
    public void addCusto(int custoAdd){
        this.custos+= custoAdd;
    }
    
    public String var_nome(){
        return this.nome;
    }
    public int[] var_abr(){
        int[] horario = new int[2];
        horario[0]=horAbertura.var_hora();
        horario[1]=horAbertura.var_min();
        return horario;
    }
    public int[] var_fecho(){
        int[] horario = new int[2];
        horario[0]=horFecho.var_hora();
        horario[1]=horFecho.var_min();
        return horario;
    }
    public int var_custo(){
        return this.custos;
    }
    public Horario var_Habr(){
        return this.horAbertura;
    }
    public Horario var_Hfecho(){
        return this.horFecho;
    }
}
