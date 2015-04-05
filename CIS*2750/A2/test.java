import java.awt.*;
import java.io.*;
import javax.swing.*;
import javax.swing.text.*;
import java.util.*;
import java.lang.String;
import java.awt.*;
import java.awt.event.*;
import javax.swing.JFileChooser;
import java.io.File;
import javax.swing.event.*;
import javax.swing.filechooser.FileNameExtensionFilter;

public class test extends JFrame
{
	private JLabel NameLabel;
	private JLabel Student_IDLabel;
	private JLabel A1Label;
	private JLabel A2Label;
	private JLabel A3Label;
	private JLabel A4Label;
	private JLabel AverageLabel;

	private JTextField NameTextField;
	private JTextField Student_IDTextField;
	private JTextField A1TextField;
	private JTextField A2TextField;
	private JTextField A3TextField;
	private JTextField A4TextField;
	private JTextField AverageTextField;

	private JButton AddButton;
	private JButton UpdateButton;
	private JButton DeleteButton;
	private JButton QueryButton;

	private JScrollPane scroller;
	private JTextArea statusBox;
		
	public static void main(String[] args)
	{
		new test();
	}	
	
	public test()
	{
		super("test");
		setSize(800,600);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		
		JPanel statusWindow = new JPanel();
		JPanel buttonsPanel = new JPanel();
		JPanel paramsPanel = new JPanel(new BorderLayout());
	
		scroller = new JScrollPane(statusBox);		
		statusWindow.add(new JLabel("Status", JLabel.CENTER), BorderLayout.NORTH);
						
		NameTextField = new JTextField(10);
		Student_IDTextField = new JTextField(10);
		A1TextField = new JTextField(10);
		A2TextField = new JTextField(10);
		A3TextField = new JTextField(10);
		A4TextField = new JTextField(10);
		AverageTextField = new JTextField(10);				
		NameLabel = new JLabel("Name", JLabel.LEFT);
		Student_IDLabel = new JLabel("Student_ID");
		A1Label = new JLabel("A1");
		A2Label = new JLabel("A2");
		A3Label = new JLabel("A3");
		A4Label = new JLabel("A4");
		AverageLabel = new JLabel("Average");
		
		paramsPanel.add(NameLabel,BorderLayout.WEST);
		paramsPanel.add(NameTextField,BorderLayout.CENTER);
		paramsPanel.add(Student_IDLabel,BorderLayout.WEST);
		paramsPanel.add(Student_IDTextField,BorderLayout.CENTER);
		paramsPanel.add(A1Label,BorderLayout.WEST);
		paramsPanel.add(A1TextField,BorderLayout.CENTER);

														
		AddButton = new JButton("Add");
		UpdateButton = new JButton("Update");
		DeleteButton = new JButton("Delete");
		QueryButton = new JButton("Query");
		buttonsPanel.add(AddButton);
		buttonsPanel.add(UpdateButton);
		buttonsPanel.add(DeleteButton);
		buttonsPanel.add(QueryButton);
		
		add(paramsPanel,BorderLayout.NORTH);
		add(buttonsPanel,BorderLayout.CENTER);
		add(statusWindow,BorderLayout.SOUTH); 
		setVisible(true);		
	}
	
}
