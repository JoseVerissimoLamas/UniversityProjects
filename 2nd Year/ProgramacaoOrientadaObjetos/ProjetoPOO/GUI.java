package projeto;


import java.awt.Color;
import java.awt.TextField;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.ArrayList;
import javax.swing.DefaultListModel;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JList;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JTextField;
import javax.swing.ListSelectionModel;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;

public class GUI extends JFrame {
    private JList clients;
    private JButton btnAdd;
    private ArrayList<Aluno> names;
    private JTextField tfName;
    private JLabel labelName;
    private final JLabel labelAge;
    private final JTextField tfAge;
    
    public GUI(ArrayList<Aluno> names) {
        this.names = names;
        
        setTitle("Alunos");
        setSize(580, 250);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setResizable(false);
        setVisible(true);
        
        
//        names = new ArrayList<>();
//        names.add(new Cliente("Joao", 10));
//        names.add(new Cliente("Maria", 11));
        
        JPanel panel = new JPanel();
        panel.setLayout(null);
        
        clients = new JList();
        clients.setBackground(new Color(178,178,178));
        clients.setBounds(10, 10, 200, 150);
        clients.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
        clients.addListSelectionListener(new ListListener());
        panel.add(clients);
        
        btnAdd = new JButton("Add");
        btnAdd.setBounds(10,175,200,25);
        btnAdd.addActionListener(new ButtonListener());
        panel.add(btnAdd);
        
        labelName = new JLabel("Nome");
        labelName.setBounds(220,30,50,25);
        panel.add(labelName);
        
        tfName = new JTextField();
        tfName.setBounds(350,30,200,25);
        panel.add(tfName);
        
        labelAge = new JLabel("Numero do aluno");
        labelAge.setBounds(220,70,200,25);
        panel.add(labelAge);
        
        tfAge = new JTextField();
        tfAge.setBounds(350,70,200,25);
        panel.add(tfAge);
        
        updateList();
        
        
        
        add(panel);
    }

    void addCliente(String nome, String numAluno) {
        Aluno novoAluno = new Aluno();
        novoAluno.setNome(nome);
        novoAluno.setNumAluno(Integer.parseInt(numAluno));
        names.add(novoAluno);
        updateList();
    }
    
    private class ButtonListener implements ActionListener {
        @Override
        public void actionPerformed(ActionEvent e) {
//            String value = JOptionPane.showInputDialog(null, "Introduza o nome do cliente", "Nome", JOptionPane.QUESTION_MESSAGE);
//            names.add(new Cliente(value,0));
//            updateList();
            createInput();
        }
    }
    
    private void createInput() {
        GUIInput input = new GUIInput(this);
        input.setVisible(true);
        this.setVisible(false);
    }
    
    private class ListListener implements ListSelectionListener {
        @Override
        public void valueChanged(ListSelectionEvent e) {
            System.out.println("Escolhido: "+clients.getSelectedValue());
            
            String tf = clients.getSelectedValue()+"";
            
            for(Aluno c: names) {
                if(c.getNome().equals(tf)) {
                    tfName.setText(c.getNome());
                    tfAge.setText(""+c.getNumAluno());
                }
            }
            
        }
    }
    
    private void updateList() {
        DefaultListModel<String> model = new DefaultListModel<>();
        
        for(Aluno name: names) {
            model.addElement(name.getNome());
        }
        
        clients.setModel(model);
    }
    
//    public static void main(String[] args) {
//        GUI gui = new GUI();
//        gui.setTitle("Clientes");
//        gui.setSize(500, 300);
//        gui.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
//        gui.setResizable(false);
//        gui.setVisible(true);
//    }
}
