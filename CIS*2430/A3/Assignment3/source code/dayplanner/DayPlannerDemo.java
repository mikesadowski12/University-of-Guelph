//package Assignment3;
import java.util.Scanner;
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
import java.awt.Color;
import java.awt.GridLayout;
import javax.swing.BoxLayout;
import javax.swing.JButton;
import javax.swing.JComboBox;
import static javax.swing.JFrame.EXIT_ON_CLOSE;
import javax.swing.JTextArea;
import javax.swing.JTextField;

/**
 * DayPlannerDemo class
 *
 * @author Fei Song
 *
 */
public class DayPlannerDemo extends JFrame implements ActionListener {

    public static final int WIDTH = 820;
    public static final int HEIGHT = 400;

    private JFrame addWindow;
    private JFrame searchWindow;
    private JFrame quitWindow;

    private JComboBox typeChoice;
    private JTextField titleInput;
    private JTextField startTime;
    private JTextField endTime;
    private JTextField place;
    private JTextField comments;
    private JTextArea feedBack;

    DayPlanner planner = new DayPlanner();

    public static void main(String[] args) {
        DayPlannerDemo gui = new DayPlannerDemo();
        gui.setVisible(true);
    }

    public void actionPerformed(ActionEvent e) {
        String actionCommand = e.getActionCommand();

        if (actionCommand.equals("Add")) {
            this.setVisible(false);
            searchWindow.setVisible(false);
            quitWindow.setVisible(false);
            addActivity();
        } else if (actionCommand.equals("Search")) {
            this.setVisible(false);
            addWindow.setVisible(false);
            quitWindow.setVisible(false);
            searchActivity();
        } else if (actionCommand.equals("Quit")) {
            addWindow.setVisible(false);
            searchWindow.setVisible(false);
            quitPlanner();
        } else if (actionCommand.equals("Reset")) {
            typeChoice.setSelectedIndex(1);
            titleInput.setText("");
            startTime.setText("");
            endTime.setText("");
            place.setText("");
            comments.setText("");
            feedBack.setText("");
        } else if (actionCommand.equals("Enter")) {
            String type = (String) typeChoice.getSelectedItem();
            Time start = null;
            Time end = null;

            start = planner.getTime(startTime.getText());
            end = planner.getTime(endTime.getText());

            feedBack.setText("Activity was added!");
            if (type.equals("Home")) {
                HomeActivity home = new HomeActivity(titleInput.getText(), start, end, comments.getText());
                planner.addHomeActivity(home);
            } else if (type.equals("School")) {
                SchoolActivity school = new SchoolActivity(titleInput.getText(), start, end, comments.getText());
                planner.addSchoolActivity(school);
            } else if (type.equals("Other")) {
                OtherActivity other = new OtherActivity(titleInput.getText(), start, end, place.getText(), comments.getText());
                planner.addOtherActivity(other);
            }
        } else if (actionCommand.equals("Search Planner")) {
            String type = (String) typeChoice.getSelectedItem();
            Time start = null;
            Time end = null;
            String[] keywords = titleInput.getText().split("[ ,\n]+");
            HomeActivity[] matches1 = null;
            SchoolActivity[] matches2 = null;
            OtherActivity[] matches3 = null;
            String thePrint = "";
            start = planner.getTime(startTime.getText());
            end = planner.getTime(endTime.getText());    
            if (type.equals("Home")) {
                matches1 = planner.searchHomeActivities(start, end, keywords);
                for (int i = 0; i < matches1.length; i++) {
                    if(matches1[i] != null){
                       thePrint = combineStrings(thePrint,matches1[i].toString());
                    }   
                    feedBack.setText(thePrint);
                }
            } else if (type.equals("School")) {
                matches2 = planner.searchSchoolActivities(start, end, keywords);
                for (int i = 0; i < matches2.length; i++) {
                    if(matches2[i] != null){
                       thePrint = combineStrings(thePrint,matches2[i].toString());
                    } 
                    feedBack.setText(thePrint);
                }
            } else if (type.equals("Other")) {
                matches3 = planner.searchOtherActivities(start, end, keywords);
                for (int i = 0; i < matches3.length; i++) {
                    if(matches3[i] != null){
                       thePrint = combineStrings(thePrint,matches2[i].toString());
                    } 
                    feedBack.setText(thePrint);
                }
            }
        } else if (actionCommand.equals("Yes")) {
            System.exit(0);
        } else if (actionCommand.equals("No")) {
            quitWindow.setVisible(false);
            addActivity();
        }
    }
    public String combineStrings(String original, String addition){  
        return original + "\n" + addition;
    }
    public void addActivity() {
        /*ADD SCREEN FRAME*/
        addWindow.setVisible(true);
        addWindow.setSize(WIDTH, HEIGHT);
        addWindow.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        addWindow.setLayout(new BorderLayout());
        addWindow.setTitle("Day Planner");

        String[] types = {"Home", "School", "Other"};

        /*MENU OPTIONS*/
        JMenu cmdMenu = new JMenu("Commands");
        JMenuItem addActivity = new JMenuItem("Add");
        addActivity.addActionListener(this);
        cmdMenu.add(addActivity);
        JMenuItem searchActivity = new JMenuItem("Search");
        searchActivity.addActionListener(this);
        cmdMenu.add(searchActivity);
        JMenuItem quitChoice = new JMenuItem("Quit");
        quitChoice.addActionListener(this);
        cmdMenu.add(quitChoice);
        JMenuBar bar = new JMenuBar();
        bar.add(cmdMenu);
        addWindow.setJMenuBar(bar);

        /*ADD MENU*/
        JPanel activity = new JPanel();
        activity.setLayout(new BorderLayout());

        //BUTTONS
        JPanel buttons = new JPanel();
        buttons.setLayout(new GridLayout(2, 1));
        JButton reset = new JButton("Reset");
        reset.addActionListener(this);
        JButton enter = new JButton("Enter");
        enter.addActionListener(this);
        JLabel empty1 = new JLabel();
        JLabel empty2 = new JLabel();
        buttons.add(empty1);
        buttons.add(empty2);
        buttons.add(reset);
        buttons.add(enter);

        //ENTER INFORMATION FORM
        JPanel infoField = new JPanel();
        infoField.setLayout(new GridLayout(1, 2));
        JPanel labels = new JPanel();
        labels.setLayout(new GridLayout(7, 1));
        JPanel text = new JPanel();
        text.setLayout(new GridLayout(7, 1));

        JLabel welcome = new JLabel("                     Adding an activity: ");
        JLabel blank = new JLabel();

        JLabel type = new JLabel("                                           Type:");
        typeChoice = new JComboBox(types);

        JLabel title = new JLabel("                                           Title:");
        titleInput = new JTextField(30);

        JLabel start = new JLabel("Start time (year, month, day, hour, minute):");
        startTime = new JTextField(30);

        JLabel end = new JLabel("End time (year, month, day, hour, minute):");
        endTime = new JTextField(30);

        JLabel location = new JLabel("                                           Location:");
        place = new JTextField(30);

        JLabel comment = new JLabel("                                           Comment");
        comments = new JTextField(30);
        typeChoice.setSelectedIndex(1);
        
        //JLabel msgs = new JLabel("Messages:");
        
        text.add(welcome);
        labels.add(blank);
        text.add(type);
        labels.add(typeChoice);
        text.add(title);
        labels.add(titleInput);
        text.add(start);
        labels.add(startTime);
        text.add(end);
        labels.add(endTime);
        text.add(location);
        labels.add(place);
        text.add(comment);
        labels.add(comments);
        //text.add(msgs);
        
        infoField.add(text, BorderLayout.CENTER);
        infoField.add(labels, BorderLayout.WEST);
        infoField.add(buttons, BorderLayout.EAST);

        JPanel messages = new JPanel();
        feedBack = new JTextArea(10, 40);
        messages.add(feedBack);

        activity.add(infoField, BorderLayout.CENTER);
        activity.add(messages, BorderLayout.SOUTH);

        addWindow.add(activity, BorderLayout.CENTER);
    }

    public void searchActivity() {
        /*SEARCH SCREEN FRAME*/
        searchWindow.setVisible(true);
        searchWindow.setSize(WIDTH, HEIGHT);
        searchWindow.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        searchWindow.setLayout(new BorderLayout());
        searchWindow.setTitle("Day Planner");

        String[] types = {"Home", "School", "Other"};

        /*MENU OPTIONS*/
        JMenu cmdMenu = new JMenu("Commands");
        JMenuItem addActivity = new JMenuItem("Add");
        addActivity.addActionListener(this);
        cmdMenu.add(addActivity);
        JMenuItem searchActivity = new JMenuItem("Search");
        searchActivity.addActionListener(this);
        cmdMenu.add(searchActivity);
        JMenuItem quitChoice = new JMenuItem("Quit");
        quitChoice.addActionListener(this);
        cmdMenu.add(quitChoice);
        JMenuBar bar = new JMenuBar();
        bar.add(cmdMenu);
        searchWindow.setJMenuBar(bar);

        /*ADD MENU*/
        JPanel activity = new JPanel();
        activity.setLayout(new BorderLayout());

        //BUTTONS
        JPanel buttons = new JPanel();
        buttons.setLayout(new GridLayout(2, 1));
        JButton reset = new JButton("Reset");
        reset.addActionListener(this);
        JButton enter = new JButton("Search Planner");
        enter.addActionListener(this);
        JLabel empty1 = new JLabel();
        JLabel empty2 = new JLabel();
        buttons.add(empty1);
        buttons.add(empty2);
        buttons.add(reset);
        buttons.add(enter);

        //ENTER INFORMATION FORM
        JPanel infoField = new JPanel();
        infoField.setLayout(new GridLayout(1, 2));
        JPanel labels = new JPanel();
        labels.setLayout(new GridLayout(7, 1));
        JPanel text = new JPanel();
        text.setLayout(new GridLayout(7, 1));

        JLabel welcome = new JLabel("                     Searching activities: ");
        JLabel blank = new JLabel();

        JLabel type = new JLabel("                                           Type:");
        typeChoice = new JComboBox(types);

        JLabel title = new JLabel("                                           Title:");
        titleInput = new JTextField(30);

        JLabel start = new JLabel("Start time (year, month, day, hour, minute):");
        startTime = new JTextField(30);

        JLabel end = new JLabel("End time (year, month, day, hour, minute):");
        endTime = new JTextField(30);
        typeChoice.setSelectedIndex(1);
        
        JLabel msgs = new JLabel("Search Results:");
        
        text.add(welcome);
        labels.add(blank);
        text.add(type);
        labels.add(typeChoice);
        text.add(title);
        labels.add(titleInput);
        text.add(start);
        labels.add(startTime);
        text.add(end);
        labels.add(endTime);
        text.add(msgs);

        
        infoField.add(text, BorderLayout.CENTER);
        infoField.add(labels, BorderLayout.WEST);
        infoField.add(buttons, BorderLayout.EAST);

        JPanel messages = new JPanel();
        feedBack = new JTextArea(10, 40);
        messages.add(feedBack);
        
        activity.add(infoField, BorderLayout.CENTER);
        activity.add(messages, BorderLayout.SOUTH);

        searchWindow.add(activity, BorderLayout.CENTER);
    }

    public void quitPlanner() {
        quitWindow.setVisible(true);
        quitWindow.setDefaultCloseOperation(EXIT_ON_CLOSE);
        quitWindow.setSize(300, 200);

        quitWindow.setTitle("Closing Day Planner");

        quitWindow.setLayout(new BorderLayout());
        JLabel warning = new JLabel("<html>Are you sure you want to exit?");
        JPanel buttons = new JPanel();
        JButton exit = new JButton("Yes");
        exit.addActionListener(this);
        JButton resume = new JButton("No");
        resume.addActionListener(this);
        resume.setBackground(Color.GREEN);
        buttons.add(exit);
        buttons.add(resume);

        quitWindow.add(warning, BorderLayout.CENTER);
        quitWindow.add(buttons, BorderLayout.SOUTH);
        quitWindow.setResizable(false);
    }

    public DayPlannerDemo() {
        /*Initialize JFrame*/
        super("Day Planner");
        setSize(WIDTH, HEIGHT);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLayout(new BorderLayout());

        addWindow = new JFrame();
        addWindow.setVisible(false);
        searchWindow = new JFrame();
        searchWindow.setVisible(false);
        quitWindow = new JFrame();
        quitWindow.setVisible(false);
        
        
        /*MENU OPTIONS*/
        JMenu cmdMenu = new JMenu("Commands");
        JMenuItem addActivity = new JMenuItem("Add");
        addActivity.addActionListener(this);
        cmdMenu.add(addActivity);
        JMenuItem searchActivity = new JMenuItem("Search");
        searchActivity.addActionListener(this);
        cmdMenu.add(searchActivity);
        JMenuItem quitChoice = new JMenuItem("Quit");
        quitChoice.addActionListener(this);
        cmdMenu.add(quitChoice);
        JMenuBar bar = new JMenuBar();
        bar.add(cmdMenu);
        setJMenuBar(bar);

        /*WELCOME SCREEN PANEL*/
        JPanel blankE = new JPanel();
        JPanel blankW = new JPanel();
        JPanel blankS = new JPanel();
        JPanel blankLine = new JPanel();
        JPanel welcomePanel = new JPanel();
        welcomePanel.setLayout(new BorderLayout());
        JLabel welcomeLabel = new JLabel("<html>Welcome to the Day Planner! <br><br>" + "Choose a command from the 'Commands' menu above for " + "adding an activity, searching activities, or quitting the program.");
        welcomePanel.add(blankLine, BorderLayout.WEST);
        welcomePanel.add(welcomeLabel, BorderLayout.CENTER);
        add(welcomePanel);
        add(blankE, BorderLayout.EAST);
        add(welcomePanel, BorderLayout.NORTH);
        add(blankW, BorderLayout.WEST);
        add(blankS, BorderLayout.SOUTH);

        /*ADD SCREEN*/
        /*SEARCH SCREEN*/
    }

}
