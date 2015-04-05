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

public class example extends JFrame
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
	private JTextArea statusBox = new JTextArea();
	private JPanel statusBoxPanel;
	private JPanel buttonPanel;
	private JPanel topPanel;
	private JPanel textPanel;
	private JPanel paramsPanel;

	public static void main(String[] args)
	{
		new example();
	}
	
	public String getDCName()
	{
		return NameTextField.getText();
	}
	public String getDCStudent_ID()
	{
		return Student_IDTextField.getText();
	}
	public String getDCA1()
	{
		return A1TextField.getText();
	}
	public String getDCA2()
	{
		return A2TextField.getText();
	}
	public String getDCA3()
	{
		return A3TextField.getText();
	}
	public String getDCA4()
	{
		return A4TextField.getText();
	}
	public String getDCAverage()
	{
		return AverageTextField.getText();
	}
	public void setDCName(String Name)
	{
		NameTextField.setText(Name);
	}
	public void setDCStudent_ID(String Student_ID)
	{
		Student_IDTextField.setText(Student_ID);
	}
	public void setDCA1(String A1)
	{
		A1TextField.setText(A1);
	}
	public void setDCA2(String A2)
	{
		A2TextField.setText(A2);
	}
	public void setDCA3(String A3)
	{
		A3TextField.setText(A3);
	}
	public void setDCA4(String A4)
	{
		A4TextField.setText(A4);
	}
	public void setDCAverage(String Average)
	{
		AverageTextField.setText(Average);
	}
	public void appendToStatusArea(String message)
	{
		statusBox.append(message);
	}

	public example()
	{
		super("compiled_example");

		setVisible(true);
		setSize(1000, 900);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

		buttonPanel = new JPanel();
		paramsPanel = new JPanel();
		textPanel = new JPanel();

		NameTextField = new JTextField(10);
		textPanel.add(NameTextField);
		Student_IDTextField = new JTextField(10);
		textPanel.add(Student_IDTextField);
		A1TextField = new JTextField(10);
		textPanel.add(A1TextField);
		A2TextField = new JTextField(10);
		textPanel.add(A2TextField);
		A3TextField = new JTextField(10);
		textPanel.add(A3TextField);
		A4TextField = new JTextField(10);
		textPanel.add(A4TextField);
		AverageTextField = new JTextField(10);
		textPanel.add(AverageTextField);

		NameLabel = new JLabel("Name", JLabel.RIGHT);
		paramsPanel.add(NameLabel);
		Student_IDLabel = new JLabel("Student_ID", JLabel.RIGHT);
		paramsPanel.add(Student_IDLabel);
		A1Label = new JLabel("A1", JLabel.RIGHT);
		paramsPanel.add(A1Label);
		A2Label = new JLabel("A2", JLabel.RIGHT);
		paramsPanel.add(A2Label);
		A3Label = new JLabel("A3", JLabel.RIGHT);
		paramsPanel.add(A3Label);
		A4Label = new JLabel("A4", JLabel.RIGHT);
		paramsPanel.add(A4Label);
		AverageLabel = new JLabel("Average", JLabel.RIGHT);
		paramsPanel.add(AverageLabel);

		AddButton = new JButton("Add");
		UpdateButton = new JButton("Update");
		DeleteButton = new JButton("Delete");
		QueryButton = new JButton("Query");
		buttonPanel.add(AddButton);
		buttonPanel.add(UpdateButton);
		buttonPanel.add(DeleteButton);
		buttonPanel.add(QueryButton);

		add(textPanel,BorderLayout.LINE_START);
		add(buttonPanel, BorderLayout.SOUTH);
		add(paramsPanel, BorderLayout.NORTH);
	}

}