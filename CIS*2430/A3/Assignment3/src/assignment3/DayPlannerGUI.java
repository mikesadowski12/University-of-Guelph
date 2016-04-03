/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package assignment3;

import javax.swing.JFrame;
import javax.swing.JMenu;
import javax.swing.JMenuItem;
import javax.swing.JMenuBar;
import javax.swing.JPanel;
import javax.swing.JLabel;
import java.awt.FlowLayout;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import java.awt.BorderLayout;
import java.awt.GridLayout;
import javax.swing.BoxLayout;


/**
 *
 * @author michaelsadowski
 */
public class DayPlannerGUI extends JFrame {

    public static final int WIDTH = 600;
    public static final int HEIGHT = 400;

    private JPanel welcomePanel;
    private JPanel addPanel;
    private JPanel searchPanel;

    public static void main(String[] args) {
        DayPlannerGUI gui = new DayPlannerGUI();
        gui.setVisible(true);
    }

    private class AddListener implements ActionListener {

        public void actionPerformed(ActionEvent e) {
            welcomePanel.setVisible(false);
            searchPanel.setVisible(false);
            addPanel.setVisible(true);

        }
    }

    private class SearchListener implements ActionListener {

        public void actionPerformed(ActionEvent e) {
            welcomePanel.setVisible(false);
            searchPanel.setVisible(true);
            addPanel.setVisible(false);

            JLabel locationLabel = new JLabel(" Location: ");

        }
    }

    private class QuitListener implements ActionListener {

        public void actionPerformed(ActionEvent e) {
            System.exit(0);
        }
    }

    public DayPlannerGUI() {
        super("Day Planner");
        setSize(WIDTH, HEIGHT);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    
        
        //MENU OPTIONS
        JMenu cmdMenu = new JMenu("Commands");

        JMenuItem addActivity = new JMenuItem("Add");
        addActivity.addActionListener(new DayPlannerGUI.AddListener());
        cmdMenu.add(addActivity);

        JMenuItem searchActivity = new JMenuItem("Search");
        searchActivity.addActionListener(new DayPlannerGUI.SearchListener());
        cmdMenu.add(searchActivity);

        JMenuItem quitChoice = new JMenuItem("Quit");
        quitChoice.addActionListener(new DayPlannerGUI.QuitListener());
        cmdMenu.add(quitChoice);

        JMenuBar bar = new JMenuBar();
        bar.add(cmdMenu);
        setJMenuBar(bar);
        //ADD PANEL
        addPanel = new JPanel();
        addPanel.setLayout(new BorderLayout());
        JLabel addLabel = new JLabel("Add an activity: ");
        JLabel typeLabel = new JLabel(" Type: ");
        JLabel titleLabel = new JLabel(" Title: ");
        JLabel startTimeLabel = new JLabel(" Starting time(year,month,day,hour,minute): ");
        JLabel endTimeLabel = new JLabel(" Ending time(year,month,day,hour,minute): ");
        JLabel commentLabel = new JLabel(" Comment: ");
        addPanel.add(addLabel, BorderLayout.NORTH);
        addPanel.add(typeLabel, BorderLayout.CENTER);
        addPanel.add(titleLabel, BorderLayout.SOUTH);
        addPanel.setVisible(false);
        add(addPanel, BorderLayout.NORTH);
        
         //SEARCH PANEL
        searchPanel = new JPanel();
        searchPanel.setVisible(false);
        searchPanel.setLayout(new BorderLayout());       
        
        //WELCOME PANEL
        welcomePanel = new JPanel();
        welcomePanel.setLayout(new BorderLayout());
        JLabel welcomeLabel = new JLabel("      Welcome to the Day Planner!");
        JLabel useLabel = new JLabel("      Choose a command from the 'Commands' menu above for ");
        JLabel useLabel2 = new JLabel("      adding an activity, searching activities, or quitting the program.");
        welcomePanel.add(welcomeLabel, BorderLayout.NORTH);
        welcomePanel.add(useLabel, BorderLayout.CENTER);
        welcomePanel.add(useLabel2, BorderLayout.SOUTH);
        welcomePanel.setVisible(true);
        add(welcomePanel, BorderLayout.NORTH);




    }
}
