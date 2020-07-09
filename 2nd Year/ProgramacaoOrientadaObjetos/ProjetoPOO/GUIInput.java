package projeto;

import java.awt.Panel;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JTextField;

public class GUIInput extends JFrame {
    private final JButton btnAdd;
    private final JLabel labelName;
    private final JTextField tfName;
    private final JLabel labelAge;
    private final JTextField tfAge;
    private final GUI gui;
    
    GUIInput(GUI gui) {
        this.gui = gui;
        setTitle("Add Clientes");
        setSize(250, 150);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setResizable(false);
        
        JPanel panel = new JPanel();
        panel.setLayout(null);
        
        btnAdd = new JButton("Add");
        btnAdd.setBounds(10,80,200,25);
        btnAdd.addActionListener(new ButtonListener());
        panel.add(btnAdd);
        
        labelName = new JLabel("Name");
        labelName.setBounds(10,10,50,25);
        panel.add(labelName);
        
        tfName = new JTextField();
        tfName.setBounds(60,10,200,25);
        panel.add(tfName);
        
        labelAge = new JLabel("Age");
        labelAge.setBounds(10,35,50,25);
        panel.add(labelAge);
        
        tfAge = new JTextField();
        tfAge.setBounds(60,35,200,25);
        panel.add(tfAge);
        
        add(panel);
    }

    private class ButtonListener implements ActionListener {
        @Override
        public void actionPerformed(ActionEvent e) {
            System.out.println("BOTTON");
            addCliente();
        }
    }

    private void addCliente() {
        this.setVisible(false);
        gui.setVisible(true);
        gui.addCliente(tfName.getText(),tfAge.getText());
    }
}
