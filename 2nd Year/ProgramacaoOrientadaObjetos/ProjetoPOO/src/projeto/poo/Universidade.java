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
public class Universidade extends PontosInteresse{
    private ArrayList<String> cursos = new ArrayList<String>();
    
    public Universidade(String nome, int custo, int guia, Horario abr, Horario fecho) {
        super(nome, custo+guia, abr, fecho);
    }
    
    public void addCurso(String nomeCurso){
        this.cursos.add(nomeCurso);
    }
    
}
