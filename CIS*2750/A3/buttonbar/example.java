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

	private ActionListener AddListener;
	private ActionListener UpdateListener;
	private ActionListener DeleteListener;
	private ActionListener QueryListener;

	private JScrollPane scroller;
	private JTextArea statusBox = new JTextArea();
	private JPanel fieldsPanel = new JPanel(new BorderLayout());
	private JPanel buttonsPanel = new JPanel();
	private JPanel upperPanel = new JPanel(new BorderLayout());
	private JPanel statusPanel = new JPanel(new BorderLayout());

	public example()
	{
		super("compiled_example");
		setSize(400, 400);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		upperPanel.add(fieldsPanel, BorderLayout.NORTH);
		upperPanel.add(buttonsPanel, BorderLayout.CENTER);
		getContentPane().add(upperPanel, BorderLayout.NORTH);
		getContentPane().add(statusPanel, BorderLayout.CENTER);
		JPanel labelPanel = new JPanel(new GridLayout(7, 1));
		JPanel textFieldPanel = new JPanel(new GridLayout(7, 1));
		fieldsPanel.add(labelPanel, BorderLayout.WEST);
		fieldsPanel.add(textFieldPanel, BorderLayout.CENTER);

		NameLabel = new JLabel("Name", JLabel.RIGHT);
		Student_IDLabel = new JLabel("Student_ID", JLabel.RIGHT);
		A1Label = new JLabel("A1", JLabel.RIGHT);
		A2Label = new JLabel("A2", JLabel.RIGHT);
		A3Label = new JLabel("A3", JLabel.RIGHT);
		A4Label = new JLabel("A4", JLabel.RIGHT);
		AverageLabel = new JLabel("Average", JLabel.RIGHT);

		NameTextField = new JTextField();
		NameTextField.setPreferredSize( new Dimension( 20, 24 ) );
		Student_IDTextField = new JTextField();
		Student_IDTextField.setPreferredSize( new Dimension( 20, 24 ) );
		A1TextField = new JTextField();
		A1TextField.setPreferredSize( new Dimension( 20, 24 ) );
		A2TextField = new JTextField();
		A2TextField.setPreferredSize( new Dimension( 20, 24 ) );
		A3TextField = new JTextField();
		A3TextField.setPreferredSize( new Dimension( 20, 24 ) );
		A4TextField = new JTextField();
		A4TextField.setPreferredSize( new Dimension( 20, 24 ) );
		AverageTextField = new JTextField();
		AverageTextField.setPreferredSize( new Dimension( 20, 24 ) );

		NameLabel.setLabelFor(NameTextField);
		Student_IDLabel.setLabelFor(Student_IDTextField);
		A1Label.setLabelFor(A1TextField);
		A2Label.setLabelFor(A2TextField);
		A3Label.setLabelFor(A3TextField);
		A4Label.setLabelFor(A4TextField);
		AverageLabel.setLabelFor(AverageTextField);

		AddButton = new JButton("Add");
		UpdateButton = new JButton("Update");
		DeleteButton = new JButton("Delete");
		QueryButton = new JButton("Query");

		labelPanel.add(NameLabel);
		textFieldPanel.add(NameTextField);
		labelPanel.add(Student_IDLabel);
		textFieldPanel.add(Student_IDTextField);
		labelPanel.add(A1Label);
		textFieldPanel.add(A1TextField);
		labelPanel.add(A2Label);
		textFieldPanel.add(A2TextField);
		labelPanel.add(A3Label);
		textFieldPanel.add(A3TextField);
		labelPanel.add(A4Label);
		textFieldPanel.add(A4TextField);
		labelPanel.add(AverageLabel);
		textFieldPanel.add(AverageTextField);

		JScrollPane statusScroller = new JScrollPane(statusBox);
		statusPanel.add(new JLabel("Status", JLabel.CENTER), BorderLayout.NORTH);
		statusBox.setLineWrap(true);
		statusBox.setEditable(false);
		statusPanel.add(statusScroller, BorderLayout.CENTER);
		AddListener = new ActionListener()
		{
			public void actionPerformed(ActionEvent event)
			{

			}
		};
		UpdateListener = new ActionListener()
		{
			public void actionPerformed(ActionEvent event)
			{

			}
		};
		DeleteListener = new ActionListener()
		{
			public void actionPerformed(ActionEvent event)
			{

			}
		};
		QueryListener = new ActionListener()
		{
			public void actionPerformed(ActionEvent event)
			{

			}
		};

		AddButton.addActionListener(AddListener);
		UpdateButton.addActionListener(UpdateListener);
		DeleteButton.addActionListener(DeleteListener);
		QueryButton.addActionListener(QueryListener);

		buttonsPanel.add(AddButton);
		buttonsPanel.add(UpdateButton);
		buttonsPanel.add(DeleteButton);
		buttonsPanel.add(QueryButton);
		setVisible(true);

	}


	public static void main(String[] args)
	{
		new example();
	}

	public String getDCName() throws IllegalFieldValueException
	{
		return NameTextField.getText();
	}
	public String getDCStudent_ID() throws IllegalFieldValueException
	{
		try
		{
			Integer.parseInt(Student_IDTextField.getText());
		}
		catch(Exception e)
		{
			throw new IllegalFieldValueException(Student_IDTextField.getText());
		}
		return Student_IDTextField.getText();
	}
	public String getDCA1() throws IllegalFieldValueException
	{
		try
		{
			Integer.parseInt(A1TextField.getText());
		}
		catch(Exception e)
		{
			throw new IllegalFieldValueException(A1TextField.getText());
		}
		return A1TextField.getText();
	}
	public String getDCA2() throws IllegalFieldValueException
	{
		try
		{
			Integer.parseInt(A2TextField.getText());
		}
		catch(Exception e)
		{
			throw new IllegalFieldValueException(A2TextField.getText());
		}
		return A2TextField.getText();
	}
	public String getDCA3() throws IllegalFieldValueException
	{
		try
		{
			Integer.parseInt(A3TextField.getText());
		}
		catch(Exception e)
		{
			throw new IllegalFieldValueException(A3TextField.getText());
		}
		return A3TextField.getText();
	}
	public String getDCA4() throws IllegalFieldValueException
	{
		try
		{
			Integer.parseInt(A4TextField.getText());
		}
		catch(Exception e)
		{
			throw new IllegalFieldValueException(A4TextField.getText());
		}
		return A4TextField.getText();
	}
	public String getDCAverage() throws IllegalFieldValueException
	{
		try
		{
			Float.parseFloat(AverageTextField.getText());
		}
		catch(Exception e)
		{
			throw new IllegalFieldValueException(AverageTextField.getText());
		}
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

	public void appendToStatusArea(String appendMe)
	{
		statusBox.append(appendMe + "\n");
	}

	public class IllegalFieldValueException extends Exception
	{
		public IllegalFieldValueException()
		{
			super();
		}
		public IllegalFieldValueException(String printMe)
		{
			super(printMe);
		}

	}
	public void keyPressed(KeyEvent e)
	{
	}
	public void keyTyped(KeyEvent e)
	{
	}
	public void keyReleased(KeyEvent e)
	{
	}

}