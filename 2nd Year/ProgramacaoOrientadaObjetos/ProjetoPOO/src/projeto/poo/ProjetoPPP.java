/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package projeto.poo;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.ItemEvent;
import java.awt.event.ItemListener;
import java.io.*;
import static java.lang.Integer.parseInt;
import static java.lang.Math.sqrt;
import java.util.*;
import javax.swing.AbstractListModel;
import javax.swing.DefaultListModel;
import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JList;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JTextField;
import javax.swing.ListSelectionModel;
/**
 *
 * @author Magui
 */
public class ProjetoPPP implements ActionListener{

    /**
     * @param args the command line arguments
     */
    public ProjetoPPP(){}
    
    int max=0;
    
    private ArrayList<JFrame> frame = new ArrayList<>();
    private ArrayList<JPanel> panel = new ArrayList<>();
    private ArrayList<JTextField> field = new ArrayList<>();
    private ArrayList<JButton> button = new ArrayList<>();
    private ArrayList<JComboBox> combo = new ArrayList<>();
    private ArrayList<JList> list = new ArrayList<>();
    private ArrayList<ArrayList<String>> contList = new ArrayList<>();
    private ArrayList<DefaultListModel> contDef = new ArrayList<>();
    
    private ArrayList<Local> locais = new ArrayList<>();
    private ArrayList<Aluno> alunos= new ArrayList<>();
    private ArrayList<Viagem> viagens= new ArrayList<>();
    
    /**
     * Generalized method to create frame
     * @param frameName 
     * @param x
     * @param y
     * @return 
     */
    public JFrame addFrame(String frameName, int x, int y){
        JFrame frame= new JFrame();
        frame.setTitle(frameName);
        frame.setSize(x, y);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        return frame;
    }
    
    /**
     * Geeneralized method to create panel
     * @param frame frame that will contain the panel
     * @return returns the panel created
     */
    public JPanel addPanel(JFrame frame){
        JPanel panel = new JPanel();
        frame.add(panel);
        return panel;
    }
    /**
     * Generalized method to create buttons
     * @param panel panel that will use said button
     * @param nome name of the button
     * @return returns the button created
     */
    public JButton addButton(JPanel panel, String nome){
        JButton button = new JButton(nome);
        panel.add(button);
        return button;
    }
    /**
     * generalized method to create a textfield
     * @param panel panel that will use said textfield
     * @param espaco space needed to create the textfield
     * @return 
     */
    public JTextField addField(JPanel panel, int espaco){
        JTextField txt= new JTextField(espaco);
        panel.add(txt);
        return txt;
    }
    /**
     * generalized method to create a label
     * @param panel panel that will contain the label
     * @param txt text displayed in the label
     * @return label
     */
    public JLabel addLabel(JPanel panel, String txt){
        JLabel label= new JLabel(txt);
        panel.add(label);
        return label;
    }
    /**
     * checks if the name inserted by the user is valid
     * @param alunos array list of all the students
     * @param input name inserted by the user
     * @return 
     */
        //Leitura dos ficheiros
    public boolean checkLogin(ArrayList<Aluno> alunos, String input){
        for(int i=0; i<alunos.size(); i++){
            if(alunos.get(i).var_nome()==input){
                return true;
            }
        }
        return false;
    }
    /**
     * reads the file locais.txt
     * @return returns an arrayList of the places in the text file 
     */
    
    public ArrayList<Local> lerLocais(){
        try{ 
            /* O fich precisa de ter o seginte formato:
            L, <nome do local>, <coord:x>, <coord:y>
            U, <nome da uni.>, <custo de entrada>, <h_abr:min_abr>, <h_fch:min_fch>, <preco do guia>, <nome curso>
            C, <nome do p_cultural>, <custo de entrada>, <h_abr:min_abr>, <h_fch:min_fch>
            A, <nome do p_aqua>, <Custo de entrada>, <h_abr:min_abr>, <h_fch:min_fch>, <tipo de extra>:<nome>:<quantidade/preco(no caso de ser um espetaculo)>
            F, <nome da feira>, <custo de entrada>, <h_abr:min_abr>, <h_fch:min_fch>, <atraçao>:<custo>
            M, <nome do museu>, <custo de entrada>, <h_abr:min_abr>, <h_fch:min_fch>, <tema do museu>, <custo do guia>
            B, <nome do ber>, <consumo min>, <h_abr:min_abr>, <h_fch:min_fch>, <classificaçao>, <bebida>:<custo>
            */
            File locs = new File("locais.txt");
            FileReader fr = new FileReader(locs);
            BufferedReader br = new BufferedReader(fr);
            String line = (br.readLine());
            String[] arrLine;
            ArrayList<Local> locais= new ArrayList<>();
            
            Local atual;
            Bar bar;
            Museu mus;
            Feira feira;
            ParqueCultural cult;
            Universidade uni;
            ParqueAquatico aqua;
            
            Horario abr;
            Horario fch;
            
            //while(line != null){
                arrLine=line.split(", ");
                atual = new Local(arrLine[1], Integer.parseInt(arrLine[2]), Integer.parseInt(arrLine[3]));
                
                line= br.readLine();
                while(line != null){
                    arrLine=line.split(", ");
                    if("U".equals(arrLine[0])){
                            abr= new Horario(Integer.parseInt( ( (arrLine[3]).split(":"))[0] ) , Integer.parseInt( (arrLine[3].split(":"))[1] ) );
                            fch= new Horario(Integer.parseInt( ( (arrLine[4]).split(":"))[0] ) , Integer.parseInt( (arrLine[4].split(":"))[1] ) );
                            uni = new Universidade(arrLine[1], Integer.parseInt(arrLine[2]), Integer.parseInt(arrLine[5]), abr, fch);

                            for(int i=6; i<arrLine.length; i++){//serve para adicionar varios cursos
                                uni.addCurso(arrLine[i]);
                            }
                            atual.addPnt(uni);
                            line= br.readLine();                            
                                //System.out.println(Integer.parseInt((arrLine[3].split(":"))[1]));
                    }
                    else if("C".equals(arrLine[0])){ 
                            abr= new Horario(Integer.parseInt( ( (arrLine[3]).split(":"))[0] ) , Integer.parseInt( (arrLine[3].split(":"))[1] ) );                            
                            fch= new Horario(Integer.parseInt( ( (arrLine[4]).split(":"))[0] ) , Integer.parseInt( (arrLine[4].split(":"))[1] ) );
                            cult = new ParqueCultural(arrLine[1], Integer.parseInt(arrLine[2]), abr, fch);
                            atual.addPnt(cult);
                            line= br.readLine();
                    }
                    else if("A".equals(arrLine[0])){
                            abr= new Horario(Integer.parseInt( ( (arrLine[3]).split(":"))[0] ) , Integer.parseInt( (arrLine[3].split(":"))[1] ) );
                            fch= new Horario(Integer.parseInt( ( (arrLine[4]).split(":"))[0] ) , Integer.parseInt( (arrLine[4].split(":"))[1] ) );
                            aqua = new ParqueAquatico(arrLine[1], Integer.parseInt(arrLine[2]), abr, fch);
                            for(int i=5; i< arrLine.length; i++){
                                if("e".equals(((arrLine[i]).split(":"))[0])){
                                    aqua.addEspetaculo( ((arrLine[5]).split(":"))[1], Integer.parseInt(((arrLine[5]).split(":"))[2]) );
                                }
                                else if("p".equals(((arrLine[i]).split(":"))[0])){
                                    aqua.addPiscina( ((arrLine[5]).split(":"))[1], Integer.parseInt(((arrLine[5]).split(":"))[2]) );
                                }
                                else{
                                    System.out.println("Parque aquatico mal configurado");
                                }
                            }
                            atual.addPnt(aqua);
                            line= br.readLine();
                    }
                    else if("F".equals(arrLine[0])){
                            abr= new Horario(Integer.parseInt( ( (arrLine[3]).split(":"))[0] ) , Integer.parseInt( (arrLine[3].split(":"))[1] ) );
                            fch= new Horario(Integer.parseInt( ( (arrLine[4]).split(":"))[0] ) , Integer.parseInt( (arrLine[4].split(":"))[1] ) );
                            feira = new Feira(arrLine[1], Integer.parseInt(arrLine[2]),abr, fch);
                            for(int i=4; i<arrLine.length; i++){
                                feira.addAtracoes( (arrLine[i].split(":"))[0] , Integer.parseInt( (arrLine[i].split(":"))[1] ) );
                            }
                            atual.addPnt(feira);
                            line= br.readLine();
                    }
                    else if("M".equals(arrLine[0])){
                            abr= new Horario(Integer.parseInt( ( (arrLine[3]).split(":"))[0] ) , Integer.parseInt( (arrLine[3].split(":"))[1] ) );
                            fch= new Horario(Integer.parseInt( ( (arrLine[4]).split(":"))[0] ) , Integer.parseInt( (arrLine[4].split(":"))[1] ) );
                            mus = new Museu(arrLine[1], Integer.parseInt(arrLine[2]), abr, fch, arrLine[5],Integer.parseInt(arrLine[6]));
                            atual.addPnt(mus);
                            line= br.readLine();
                    }
                    else if("B".equals(arrLine[0])){
                            abr= new Horario(parseInt( ( (arrLine[3]).split(":"))[0] ) , parseInt( (arrLine[3].split(":"))[1] ) );
                            fch= new Horario(parseInt( ( (arrLine[4]).split(":"))[0] ) , parseInt( (arrLine[4].split(":"))[1] ) );
                            bar = new Bar(arrLine[1], parseInt(arrLine[2]), abr, fch,parseInt(arrLine[5]));
                            for(int i=6; i<arrLine.length; i++){
                                bar.addBebida( (((arrLine[i]).split(":"))[0]), parseInt( ((arrLine[i]).split(":"))[1] ));
                            }
                            atual.addPnt(bar);
                            line= br.readLine();
                    }
                    else if("L".equals(arrLine[0])){
                        locais.add(atual);
                        atual= new Local(arrLine[1], parseInt(arrLine[2]), parseInt(arrLine[3]));
                        line=br.readLine();
                    }                   
                }
            //}
            
            br.close();
            return locais;
        }catch (FileNotFoundException ex){
            System.out.println("Erro a abrir fich");
        }catch(IOException ex){
            System.out.println("Erro "+ ex +" coiso");
        }
        return null;
    }
    /**
     * checks if the place chosen exists
     * @param locais arraylist of all the places obtained
     * @param nome string of the place chosen by the user
     * @return returns the coordinates of the place
     */
    public int[] checkLocal(ArrayList<Local> locais, String nome){
        for(int i=0; i<locais.size(); i++){
            if(locais.get(i).var_nome().equals(nome)){
                return locais.get(i).var_coords();
            }
        }
        return null;
    }
    /**
     * 
     * @param locais arraylist fo the places available
     * @param viagens arrayList of the trip that the fuction will read
     * @return returns the trip read
     */
    public ArrayList<Viagem> lerViagem(ArrayList<Local> locais, ArrayList<Viagem> viagens){
        try{
                File f = new File("viagens.obj");
                FileInputStream fos = new FileInputStream(f);
                ObjectInputStream oos = new ObjectInputStream(fos);
                fos = new FileInputStream(f);
                String line = new String();
                String[] arrLine;
                Viagem v = new Viagem();
                int o=0;
                while(line!=null){
                    line= (String)oos.readObject();
                    arrLine = line.split(", ");
                    v.addLocal(new Local(arrLine[1], parseInt(arrLine[2]), parseInt(arrLine[3]) ));
                    if(arrLine[0]=="V"){
                        v.addLocal(new Local(arrLine[1], parseInt(arrLine[2]), parseInt(arrLine[3]) ));
                        if(o==2){
                            o=0;
                            viagens.add(v);
                            v = new Viagem();
                        }
                        else{o++;}
                    }
                    else{
                        Horario a = new Horario(parseInt(arrLine[2]), parseInt(arrLine[3]) );
                        Horario fw = new Horario(parseInt(arrLine[4]), parseInt(arrLine[5]) );
                        PontosInteresse ik = new PontosInteresse(arrLine[0], parseInt(arrLine[1]), a, fw );
                        v.getLocais().get(o).addPnt(ik);
                    }
                    
                }
            }catch (IOException | ClassNotFoundException ex) { 
                return 0;
        }    
        return 1;
    }
    /**
     * Writed the trip created in a file object
     * @param viagem trip that was created
     */
    public void registarViagem(Viagem viagem){
        try{
            File f = new File("viagens.obj");
            FileOutputStream fos= new FileOutputStream(f);
            ObjectOutputStream oos= new ObjectOutputStream(fos);
            
            for(int i=0; i<viagem.getLocais().size(); i++){
                oos.writeObject("V, "+viagem.getLocais().get(i).var_nome()+", "+viagem.getLocais().get(i).var_coords()[0]+", "+viagem.getLocais().get(i).var_coords()[1]);
                for(int j=0; j< viagem.getLocais().get(i).getPnts().size(); j++){
                    oos.writeObject( ", "+viagem.getLocais().get(i).getPnts().get(j).var_nome()
                            +", "+ viagem.getLocais().get(i).getPnts().get(j).var_custo()
                            +", "+ viagem.getLocais().get(i).getPnts().get(j).var_abr()[0]
                            +", "+ viagem.getLocais().get(i).getPnts().get(j).var_abr()[1]
                            +", "+ viagem.getLocais().get(i).getPnts().get(j).var_fecho()[0]
                            +", "+ viagem.getLocais().get(i).getPnts().get(j).var_fecho()[1] );
                }
                /*
                V, nome do local, infos do loca...
                nome ponto, infos ponto
                ...
                */
                //ver mais tarde quando tivermos a registar a viagem
            }
            
            oos.close();
        }catch (IOException ex) {
        }
    }   
    /**
     * function that will register the user in an object file, if he is of the type licenciado
     * @param aluno Student that the user inteds to create
     */
    public void registarAlunoL(Licenciatura aluno){
        try{
            File f = new File("alunos.obj");
            FileOutputStream fos= new FileOutputStream(f);
            ObjectOutputStream oos= new ObjectOutputStream(fos);
            
            oos.writeObject(aluno.var_tipo()+", "+aluno.var_nome()+", "+aluno.var_gastar()+", "+aluno.getHot().var_nome());
            
            oos.close();
        }catch (IOException ex){}
    }
    /**
     * function that will write in an object file the data of the student, if said student is of type mestrado
     * @param aluno Student that the user intends to create 
     */
    public void registarAlunoM(Mestrado aluno){
        try{
            File f = new File("alunos.obj");
            FileOutputStream fos= new FileOutputStream(f);
            ObjectOutputStream oos= new ObjectOutputStream(fos);
            
            oos.writeObject(aluno.var_tipo()+", "+aluno.var_nome()+", "+aluno.var_gastar()+", "+aluno.getEvitar().var_nome());
            
            oos.close();
        }catch (IOException ex){}
    }
    /** 
     * function that search for the hotspot
     * @param locais arraylist of the places availables to the user
     * @param nome name of the hotspot chosen
     * @return the hotspot chosen by the user
     */
    public PontosInteresse searchPnt(ArrayList<Local> locais, String nome){
        for(int i=0; i<locais.size(); i++){
            for(int j=0; j<locais.get(i).getPnts().size(); j++){
                if( locais.get(i).getPnts().get(j).var_nome().equals(nome) ){
                    return locais.get(i).getPnts().get(j);
                }
            }
        }
        return null;
    }
    /**
     * function that searches for the place 
     * @param locais arraylist of the places available to the user
     * @param nome name of the place chosen by the user
     * @return returns the place chosen by the user, if this place exists
     */
    public Local searchLocal(ArrayList<Local> locais, String nome){
        for(int i=0; i<locais.size(); i++){
            if( locais.get(i).var_nome() == nome ){
                return locais.get(i);
            }
        }
        return null;
    }
    /**
     * functions that reads the object file of the students
     * @param alunos arraylist of students created
     * @param locais arraylist of places available
     * @return  ret
     */
    public ArrayList<Aluno> lerAlunosObj(ArrayList<Aluno> alunos, ArrayList<Local> locais){
        
        try{
            File f = new File("alunos.obj");
            FileInputStream fos= new FileInputStream(f);
            try (ObjectInputStream oos = new ObjectInputStream(fos)) {
                String line = new String();
                String[] arrLine;
                
                while(line!=null){
                    line= (String)oos.readObject();
                    arrLine = line.split(", ");
                    if("L".equals(arrLine[0])){
                        if(searchPnt(locais, arrLine[3]) != null){
                            Licenciatura actual = new Licenciatura(arrLine[1], parseInt(arrLine[2]), searchPnt(locais, arrLine[3]));
                            alunos.add(actual);
                        }
                    }
                    else if("M".equals(arrLine[0])){
                        if(searchLocal(locais, arrLine[3]) != null){
                            Mestrado actual = new Mestrado(arrLine[1], parseInt(arrLine[2]), searchLocal(locais, arrLine[3]));
                            alunos.add(actual);
                        }
                    }
                    else{
                        System.out.println("Erro");
                    }
                }
            }
        }catch (IOException | ClassNotFoundException ex) {       
        }
        return alunos;
    }
    /**
     * this function created and treats the user interface that the user interacts with
     * @return the frame that will log the user in 
     */
    public JFrame Login(){
        frame.add(addFrame("Aluno", 400, 100));
            JFrame frameLogin = frame.get(0);
        panel.add(addPanel(frameLogin));
            JPanel panelLogin = panel.get(0);
        addLabel(panelLogin, "Nome");
        field.add(addField(panelLogin, 10));
            //frameLogin = p.frame.get(0)
        addLabel(panelLogin, "Max. a Gastar");
        field.add(addField(panelLogin, 3));
            //frameLoginMaxGastar= p.frame.get(1)
        JComboBox l_m = new JComboBox();
            l_m.addItem("Licenciatura");
            l_m.addItem("Mestrado");
        combo.add(l_m);
            //comboLogin = p.combo.get(0)
        JComboBox aux = new JComboBox(); //selecao do pontohot ou local a evitar
        
        for(int i=0; i<locais.size(); i++){
            for(int j=0; j<locais.get(i).getPnts().size(); j++){
                aux.addItem(locais.get(i).getPnts().get(j).var_nome());
            }
        }
        
        //Estas duas prox linhas vao mudar o conteudo da combo box
        MyItemListener c = new MyItemListener();
        l_m.addItemListener(c);
        
        combo.add(aux); //pntHot|local a evitar = combo.get(1)
        
        panelLogin.add(combo.get(0));
        panelLogin.add(combo.get(1));
        button.add(addButton(panel.get(0), "Login"));
            JButton buttonLogin = button.get(0);
        combo.get(0).addActionListener(this);
        buttonLogin.addActionListener(this);
        return frameLogin;
    }
    /**
     * creates the UI that will display the trip
     * @return returns the frame that contains the trip created
     */
    public JFrame printViagem(){
        frame.add(addFrame("Display Viagem", 400, 400));
            JFrame frameV= frame.get(1);
        panel.add(addPanel(frameV));
            JPanel panelV= panel.get(1);
        for(int i=0; i<viagens.size(); i++){
            for(int j=0; j<viagens.get(i).getLocais().size(); j++){
                addLabel(panelV, "\n"+viagens.get(i).getLocais().get(j).var_nome());                
            }
        }
        button.add(addButton(panelV, "OK"));
        button.get(1).addActionListener(this);
        return frameV;
    }
    /**
     * function that creates the UI of the menu
     * @return frame that will return the frame that will display the menu to the user
     */
    public JFrame Menu(){
        frame.add(addFrame("Menu", 400, 100));
            JFrame frameMenu = frame.get(2);
        panel.add(addPanel(frameMenu));
            JPanel menu= panel.get(2);
        button.add(addButton(menu, "Login"));
            button.get(2).addActionListener(this);
        button.add(addButton(menu, "Display Viagens"));
            button.get(3).addActionListener(this);
            
        return frameMenu;
    }
    /**
     * function that creates the trip i reletion to the users choices
     * @return returns the trip created from the students choices
     */
    public JFrame fazerViagem(){
        frame.add(addFrame("Fazer Viagem", 280, 200));
            JFrame ff = frame.get(3);
        panel.add(addPanel(ff));
            JPanel maker = panel.get(3);
        
        DefaultListModel locs = new DefaultListModel(); // contList = 0
        ArrayList<String> s = new ArrayList<>();
        for(int i=0; i<locais.size(); i++){
            locs.addElement(locais.get(i).var_nome());
            s.add(locais.get(i).var_nome());
        }
        contList.add(s);
        contDef.add(locs);
        
        JList p = new JList(locs); // list = 0
        p.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
        addLabel(maker,"Locais");
        maker.add(p);
        list.add(p);
        
        button.add(addButton(maker, "Add")); // button = 4
        
        locs = new DefaultListModel(); // contList = 1
        s = new ArrayList<>();
        p= new JList(locs); // list = 1
        addLabel(maker, "Locais Selecionados");
        maker.add(p);
        
        contList.add(s);
        contDef.add(locs);
        list.add(p);

        button.add(addButton(maker, "Remove")); //button = 5
        button.get(4).addActionListener(this);
        button.get(5).addActionListener(this);
        
        button.add(addButton(maker, "Next")); //button = 6
        button.get(6).addActionListener(this);
        
        return ff;
    }  
    /**
     * 
     * @param panel_frame frame that will display the hotspots to be chosen
     * @param cont_list 
     * @param button_0 button that will create the hotspots chosen
     * @param index index of the place chosen, from wich the hotspots will be chosen from
     * @return returns the hotspots chosen to the trip
     */
    public JFrame fV_pnts(int panel_frame, int cont_list, int button_0, int index){
        frame.add(addFrame("Setup "+contList.get(1).get(index), 400, 300)); // frame 4
            JFrame ff = frame.get(panel_frame);
        panel.add(addPanel(ff)); // panel 4
            JPanel p = panel.get(panel_frame);
        
        DefaultListModel pts = new DefaultListModel();
        ArrayList<String> s = new ArrayList<>();
        //verificar qual é o local escolhido e guardar os seus pontos de interesse
        for(int i=0; i<locais.size(); i++){
            if(locais.get(i).var_nome() == contList.get(1).get(index)){ //1o local dos locais selecionados
                for(int j=0; j<locais.get(i).getPnts().size(); j++){//precorrer todos os pontos de interesse do local
                    pts.addElement(locais.get(i).getPnts().get(j).var_nome());
                    s.add(locais.get(i).getPnts().get(j).var_nome());
                }
            }
        }
        contList.add(s); //contList = 2
        contDef.add(pts);
        JList lista = new JList(pts);
        lista.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
        addLabel(p,"PntsInt");
        p.add(lista); //display da jlist
        list.add(lista); // list = 2
        
        button.add(addButton(p, "Add")); // button = 7
        
        pts= new DefaultListModel();
        s= new ArrayList<>();
        lista= new JList(pts);
            addLabel(p, "Pnts Selecionados");
        p.add(lista);
        contList.add(s); // contList = 3
        contDef.add(pts);
        list.add(lista); //list= 3
        
        button.add(addButton(p, "Remove")); //button = 8
        button.get(button_0).addActionListener(this);
        button.get(button_0+1).addActionListener(this);
        
        button.add(addButton(p, "Next")); //button = 9
        button.get(button_0+2).addActionListener(this);
        
        return ff;
    }
    /**
     * Its the main function
     * @param args 
     */
    public static void main(String[] args) {
        ProjetoPPP p = new ProjetoPPP();
            
        //Leitura do ficheiro onde estao os locais e pontos de interesse e tudo o resto...
        p.locais=p.lerLocais();
        //Leitura do ficheiro onde estao os alunos e isso assim...
        p.alunos=p.lerAlunosObj(p.alunos, p.locais);
        
            //Login 
        //frame = 0 | panel = 0 | field = 0, 1 | combo = 0, 1 | button = 0
        JFrame login = p.Login();
        login.setVisible(false);
        
            //display 
        //frame = 1 | panel = 1 | field =  | combo =  | button = 1
        JFrame printViagem = p.printViagem();
        printViagem.setVisible(false);
        
            //Menu 
        //frame = 2 | panel = 2 | field =  | combo =  | button = 2, 3
        JFrame menu= p.Menu();
        menu.setVisible(true);
        
            //Maker 
        //frame = 3 | panel = 3 | field =  | combo =  | button = 4, 5, 6 | list = 0, 1 | contList = 0, 1
        JFrame maker = p.fazerViagem();
        maker.setVisible(false);
        
        //frame = 4 | panel = 4 | field =  | combo =  | button = 7, 8, 9 | list = 2, 3 | contList = 2, 3
        //JFrame pnt = p.fV_pnts(4, 2, 7);
        //pnt.setVisible(false);
        //frame = 5 | panel = 5 | field =  | combo =  | button = 10, 11, 12 | list = 4, 5 | contList = 4, 5
        //JFrame pnt = p.fV_pnts(4, 2, 7);
        //pnt.setVisible(false);
        //frame = 6 | panel = 6 | field =  | combo =  | button = 13, 14, 15 | list = 6, 7 | contList = 6, 7
        //JFrame pnt = p.fV_pnts(4, 2, 7);
        //pnt.setVisible(false);
        
    }
    
    /**
     * adds elements chosen by the user to the list
     * @param um
     * @param botao 
     */
    private void Add(int um, int botao){
        int flag =0;
        for(int i=0; i< contList.get(um).size(); i++){ //para verificar se ja la esta
            if(contList.get(um).get(i) == list.get(um-1).getSelectedValue()){
                flag=1;
            }
        }
        if(flag==0){
            //adiciona a lista
            contList.get(um).add((String)list.get(um-1).getSelectedValue());
            contDef.get(um).addElement(list.get(um-1).getSelectedValue());
            if(um==1){
                if(contList.get(um).size() == 3){
                    button.get(botao).setEnabled(false);
                    button.get(botao+2).setEnabled(true); //qd se seleciona fazerViagem tens de por o butao 6 em disable
                }
                else{
                    button.get(botao).setEnabled(true);
                    button.get(botao+2).setEnabled(false);
                }
            }
            else{
                //vai servir para a contagem do dinheiro €€
            }
        }
    }
    /**
     * removes elements chosen by the user from the list
     * @param um 
     */
    private void Remove(int um){
        contList.get(um).remove((String)list.get(um).getSelectedValue());
        contDef.get(um).removeElement(list.get(um).getSelectedValue());
    }
    
    private int[] searchCoordsLocal(String nome){
        for(int i=0; i<locais.size(); i++){
            if(locais.get(i).var_nome().equals(nome)){
                return locais.get(i).var_coords();
            }
        }
        return null;
    }
    private int getCustoPnt(String nome){
        for(int i=0; i<locais.size(); i++){
            for(int j=0; j<locais.get(i).getPnts().size(); j++){
                if(locais.get(i).getPnts().get(j).var_nome().equals(nome)){
                    return locais.get(i).getPnts().get(j).var_custo();
                }
            }
        }
        return -1;
    }
    private Horario getHorAbrPnt(String nome){
         for(int i=0; i<locais.size(); i++){
            for(int j=0; j<locais.get(i).getPnts().size(); j++){
                if(locais.get(i).getPnts().get(j).var_nome().equals(nome)){
                    return locais.get(i).getPnts().get(j).var_Habr();
                }
            }
        }
        return null;
    }
    private Horario getHorFchPnt(String nome){
         for(int i=0; i<locais.size(); i++){
            for(int j=0; j<locais.get(i).getPnts().size(); j++){
                if(locais.get(i).getPnts().get(j).var_nome().equals(nome)){
                    return locais.get(i).getPnts().get(j).var_Hfecho();
                }
            }
        }
        return null;
    }
    
    private double calcDistancia(int x1, int y1, int x2, int y2){
        return sqrt( Math.pow(y1 + y2, 2)+Math.pow(x1 + x2, 2) ) * 0.10;
    }
    
    @Override
    public void actionPerformed(ActionEvent e){
        if(e.getSource() == button.get(0)){ //Button do login
            if("".equals(field.get(0).getText()) || "".equals(field.get(1).getText())){
                JOptionPane.showMessageDialog(null, "Introduza tudo por favor...", "Error", JOptionPane.PLAIN_MESSAGE);
            }
            else{
                if(combo.get(0).getSelectedItem() == "Licenciatura"){
                    JOptionPane.showMessageDialog(null, field.get(0).getText()+" Licenciatura\nCriado com sucesso!", "Aluno", JOptionPane.PLAIN_MESSAGE);
                    Licenciatura aluno = new Licenciatura(field.get(0).getText(), parseInt(field.get(1).getText()), searchPnt(locais, (String)combo.get(1).getSelectedItem()));
                    registarAlunoL(aluno);
                }
                else{
                    JOptionPane.showMessageDialog(null, field.get(0).getText()+" Mestrado\nCriado com sucesso!", "Aluno", JOptionPane.PLAIN_MESSAGE);
                    Mestrado aluno = new Mestrado(field.get(0).getText(), parseInt(field.get(1).getText()), searchLocal(locais, (String)combo.get(1).getSelectedItem()));
                    registarAlunoM(aluno);
                }  
                frame.get(0).setVisible(false);
                frame.get(3).setVisible(true);
                max=parseInt(field.get(1).getText());
            }   
        }
        else if(e.getSource() == button.get(1)){ //Button do display viagens
            //JOptionPane.showMessageDialog(null, "OK", "Okayzado", JOptionPane.PLAIN_MESSAGE);
            frame.get(1).setVisible(false);
            frame.get(2).setVisible(true);
        }
        else if(e.getSource() == button.get(2)){
            frame.get(2).setVisible(false);
            frame.get(0).setVisible(true);
        }
        else if(e.getSource() == button.get(3)){
            frame.get(2).setVisible(false);
            frame.get(1).setVisible(true);
        }
        else if(e.getSource() == button.get(4)){ //add
            Add(1, 4);
        }
        else if(e.getSource() == button.get(5)){ //remove
            Remove(1);
        }
        else if(e.getSource() == button.get(6)){ //maker "Next"
            Viagem nova = new Viagem();
            //nova.addLocal();
            
            JFrame pnt = fV_pnts(4, 2, 7, 0);
            pnt.setVisible(false);
            
            frame.get(3).setVisible(false);
            frame.get(4).setVisible(true);
        }
        else if(e.getSource() == button.get(7)){
            Add(3, 7);
        }
        else if(e.getSource() == button.get(8)){
            Remove(3);
        }
        else if(e.getSource() == button.get(9)){
            JFrame pnt = fV_pnts(5, 4, 10, 1);
            
            frame.get(4).setVisible(false);
            frame.get(5).setVisible(true);
        }
        else if(e.getSource() == button.get(10)){
            Add(5, 10);
        }
        else if(e.getSource() == button.get(11)){
            Remove(5);
        }
        else if(e.getSource() == button.get(12)){
            JFrame pnt = fV_pnts(6, 4, 13, 2);
            
            frame.get(5).setVisible(false);
            frame.get(6).setVisible(true);
        }
        else if(e.getSource() == button.get(13)){
            Add(7, 13);
        }
        else if(e.getSource() == button.get(14)){
            Remove(7);
        }
        else if(e.getSource() == button.get(15)){
            Viagem nova = new Viagem();
            
            int x1 = searchCoordsLocal(contList.get(0).get(0))[0];
            int y1 = searchCoordsLocal(contList.get(0).get(0))[1];
            int x2 = searchCoordsLocal(contList.get(0).get(1))[0];
            int y2 = searchCoordsLocal(contList.get(0).get(1))[1];
            int x3 = searchCoordsLocal(contList.get(0).get(2))[0];
            int y3 = searchCoordsLocal(contList.get(0).get(2))[1];
            
            if(( calcDistancia( x1,y1, x2,y2 )+calcDistancia( x2,y2, x3,y3 ) )>  max){
                JOptionPane.showMessageDialog(null, "Ultrapassou o preço!", "Error", JOptionPane.PLAIN_MESSAGE);
                frame.get(6).setVisible(false);
                frame.get(3).setVisible(true);
            }
            else{
                for(int j=0; j<contList.get(1).size(); j++){
                    Local dest = new Local(contList.get(1).get(j), searchCoordsLocal(contList.get(1).get(j))[0], searchCoordsLocal(contList.get(1).get(j))[1]);
                    for(int i=0; i<contList.get(3+j*2).size(); i++){ //é sempre mais +j*2 pq queres o input e este fica nos contList 3, 5, 7
                        dest.addPnt(new PontosInteresse(contList.get(3+j*2).get(i), getCustoPnt(contList.get(3+j*2).get(i)), getHorAbrPnt(contList.get(3+j*2).get(i)), getHorFchPnt(contList.get(3+j*2).get(i))));
                    }
                    nova.addLocal(dest);
                }
            registarViagem(nova);
            }
            
        }
        /*else if(e.getSource() == button.get(2)){
            
        }*/
    }
    
    class MyItemListener implements ItemListener{

        @Override
        public void itemStateChanged(ItemEvent evt) {
        JComboBox cb = (JComboBox) evt.getSource();

        Object item = evt.getItem();

        if (evt.getStateChange() == ItemEvent.SELECTED) {
          // Item was just selected
            if(combo.get(0).getSelectedItem() == "Licenciatura"){
                for(int i=0; i<locais.size(); i++){
                    for(int j=0; j<locais.get(i).getPnts().size(); j++){
                        combo.get(1).addItem(locais.get(i).getPnts().get(j).var_nome());
                    }
                }
            }
            else{
                for(int i=0; i<locais.size(); i++){
                    combo.get(1).addItem(locais.get(i).var_nome());
                }
            }
            
        } else if (evt.getStateChange() == ItemEvent.DESELECTED) {
          // Item is no longer selected
          combo.get(1).removeAllItems();
        }
    }
    }
}
