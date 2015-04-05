/*
#NAME: Mike Sadowski
#DATE: February 5th, 2015
#STUDENT ID: 0864810
#ASSIGNEMNT: CIS2750 A2
*/

/*
 * Sources: 
 * 1. http://www.tutorialspoint.com/java/java_file_class.htm
 * 2. http://www.docjar.com/html/api/java/lang/ArrayIndexOutOfBoundsException.java.html
 * 3. http://stackoverflow.com/questions/21803908/how-to-check-if-a-string-is-a-valid-integer
 */ 
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


public class DialogcCompiler
{
	/*Parameter Manager Specific*/
	PM_Converter parameters_pass1;/*saves first pass of parsing*/
	PM_Converter parameters_pass2;/*saves second pass of parsing*/
	private File configFile;
	private File javaCompilerFile;
	private String compilerOptionsString;
	private File JavaRunTimeFile;
	private String runTimeOptionsString;
	private File workingDirectoryFile;
	String compileCommand;
	private String runCommand;
	int error_flag = 0;	
	
	/*Dialogc Specific*/
	String[] title;
	String[] fields;
	String[] buttons;
	String fileName;
	
	public static void main(String[] args)
	{
		File a1 = new File("example.config");
		File b1 = new File(".");
		
		DialogcCompiler compiler = new DialogcCompiler(a1,b1,"","","javac","java");
		compiler.buildClassFile();
	}
			
	/*constructor parses config file twice, gets all parameter values, saves them in the 2 instance variables*/
	public DialogcCompiler(File configFile, File workingDirectoryFile, String compilerOptionsString, String RunTimeOptionsString, String compileCommand, String runCommand)
	{
		title = new String[100];
		fields = new String[100];
		buttons = new String[100];
		
		/*initialize 2 blank parameter managers*/
		parameters_pass1 = new PM_Converter();
		parameters_pass2 = new PM_Converter();
		parameters_pass1.PM_create_J(parameters_pass1.parameters);
		parameters_pass2.PM_create_J(parameters_pass2.parameters);
		
		/*make instance vriables in this class hold all required information for compilation*/
		this.configFile = configFile;
		this.workingDirectoryFile = workingDirectoryFile;
		this.compileCommand = compileCommand;
		this.runCommand = runCommand;
		
		this.compilerOptionsString = compilerOptionsString;
		this.runTimeOptionsString = RunTimeOptionsString;
		
		fileName = configFile.getName();
		fileName = fileName.replace(".config",".java");
				

		/*run the first pass on the config file*/
		parameters_pass1.PM_manage_J("title",'s',1,parameters_pass1.parameters);
		parameters_pass1.PM_manage_J("fields",'l',1,parameters_pass1.parameters);
		parameters_pass1.PM_manage_J("buttons",'l',1,parameters_pass1.parameters);	
			
		if(parameters_pass1.PM_parseFrom_J(configFile.getPath(),'#',parameters_pass1.parameters) != 0)
		{
			title = parameters_pass1.PM_getValue_J("title",parameters_pass1.parameters);
			fields = parameters_pass1.PM_getValue_J("fields",parameters_pass1.parameters);
			buttons = parameters_pass1.PM_getValue_J("buttons",parameters_pass1.parameters);
			parameters_pass1.PM_destroy_J(parameters_pass1.parameters);
					
			/*run the second pass on the config file*/
			for(int i = 0; i < fields.length;i++)
			{
				parameters_pass2.PM_manage_J(fields[i],'s',1,parameters_pass2.parameters);
						
			}
			for(int i = 0; i < buttons.length;i++)
			{
				parameters_pass2.PM_manage_J(buttons[i],'s',1,parameters_pass2.parameters);
			}		
				
			if(parameters_pass2.PM_parseFrom_J(configFile.getPath(),'#',parameters_pass2.parameters) != 1)
			{
				error_flag = 1;
			}
		}
		else
		{
			error_flag = 1;
		}
										
	}

	public void compileAndRun()
	{
		String runProgram = runCommand + runTimeOptionsString + " " + fileName.replace(".java","");				
		try 
		{
			compile();
			run(runProgram);
		} 
		catch (Exception e) 
		{		
		}
	}

	public void compile()
	{
		String compileRunMe = compileCommand + compilerOptionsString + " " + fileName;
		
		buildClassFile();
		try 
		{
		  run(compileRunMe);
		  JOptionPane.showMessageDialog(null, "Compilation Complete",null, JOptionPane.INFORMATION_MESSAGE);
		} 
		catch (Exception e) 
		{	
			JOptionPane.showMessageDialog(null, "Compilation Unsuccessful",null, JOptionPane.INFORMATION_MESSAGE);	
		}
		
	}
	
	private static void printLines(String name, InputStream ins) throws Exception 
	{
		String line = null;
		BufferedReader in = new BufferedReader(new InputStreamReader(ins));
		while ((line = in.readLine()) != null) 
		{
			System.out.println(name + " " + line);
		}
	 }
	
	public static void run(String command) throws Exception 
	{
		Process pro = Runtime.getRuntime().exec(command);
		printLines(command + " stdout:", pro.getInputStream());
		printLines(command + " stderr:", pro.getErrorStream());
		pro.waitFor();
		//System.out.println(command + " exitValue() " + pro.exitValue());		
	}
	
	public static void run2(String runMe) throws Exception 
	{
		System.out.println(runMe);
		
		final Process p = Runtime.getRuntime().exec(runMe);

		new Thread(new Runnable() {
			public void run() {
				BufferedReader input = new BufferedReader(new InputStreamReader(p.getInputStream()));
				String line = null; 

				try {
					while ((line = input.readLine()) != null) {
						System.out.println(line);
					}
				} catch (IOException e) {
					e.printStackTrace();
				}
			}
		}).start();

		p.waitFor();
	}

	/*writes and compiles the .java file*/
	public void buildClassFile()
	{
		String path = System.getProperty("user.dir");
		StringBuilder stringBuilder = new StringBuilder(path);
		stringBuilder.append("/");
		stringBuilder.append(fileName);
		path = stringBuilder.toString();
	
		try 
		{ 
			File file = new File(path);
			/*if file doesnt exists, then create it*/
			if (!file.exists()) {
				file.createNewFile();
			}		
			FileWriter fw = new FileWriter(file.getAbsoluteFile());
			BufferedWriter bw = new BufferedWriter(fw);					
			/*------------------------------------------------------------*/
			bw.write("import java.awt.*;\n");
			bw.write("import java.io.*;\n");
			bw.write("import javax.swing.*;\n");
			bw.write("import javax.swing.text.*;\n");
			bw.write("import java.util.*;\n");
			bw.write("import java.lang.String;\n");
			bw.write("import java.awt.*;\n");
			bw.write("import java.awt.event.*;\n");
			bw.write("import javax.swing.JFileChooser;\n");
			bw.write("import java.io.File;\n");
			bw.write("import javax.swing.event.*;\n");
			bw.write("import javax.swing.filechooser.FileNameExtensionFilter;\n\n");
			/*------------START CLASS--------------------------------*/
			bw.write("public class " + file.getName().replace(".java","") + " extends JFrame");
			bw.write("\n{");
			/*------------VARIABLES--------------------------------*/
			for(int i = 0; i < fields.length;i++)
			{
				bw.write("\n");
				bw.write("\tprivate JLabel " + fields[i] + "Label;");
			}
			bw.write("\n");
			for(int i = 0; i < fields.length;i++)
			{
				bw.write("\n");
				bw.write("\tprivate JTextField " + fields[i] + "TextField;");			
			}	
			bw.write("\n");
			for(int i = 0; i < buttons.length;i++)
			{
				bw.write("\n");
				bw.write("\tprivate JButton " + buttons[i] + "Button;");
			}
			bw.write("\n");
			for(int i = 0; i < buttons.length;i++)
			{
				bw.write("\n");
				bw.write("\tprivate ActionListener " + buttons[i] + "Listener;");
			}							
			bw.write("\n\n\tprivate JScrollPane scroller;");
			bw.write("\n\tprivate JTextArea statusBox = new JTextArea();\n");			
			bw.write("\tprivate JPanel fieldsPanel = new JPanel(new BorderLayout());\n");
			bw.write("\tprivate JPanel buttonsPanel = new JPanel();\n");
			bw.write("\tprivate JPanel upperPanel = new JPanel(new BorderLayout());\n");
			bw.write("\tprivate JPanel statusPanel = new JPanel(new BorderLayout());\n\n");			
			/*------------CONSTRUCTOR--------------------------------*/
			bw.write("\tpublic " + file.getName().replace(".java","") + "()\n");
			bw.write("\t{\n");
			bw.write("\t\tsuper(\"" + file.getName().replace(".java","") +"\");\n");
			bw.write("\t\tsetSize(400, 400);\n");
			bw.write("\t\tsetDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);\n");				
			bw.write("\t\tupperPanel.add(fieldsPanel, BorderLayout.NORTH);\n");
			bw.write("\t\tupperPanel.add(buttonsPanel, BorderLayout.CENTER);\n");
			bw.write("\t\tgetContentPane().add(upperPanel, BorderLayout.NORTH);\n");
			bw.write("\t\tgetContentPane().add(statusPanel, BorderLayout.CENTER);\n");
			bw.write("\t\tJPanel labelPanel = new JPanel(new GridLayout(" + fields.length + ", 1));\n");
			bw.write("\t\tJPanel textFieldPanel = new JPanel(new GridLayout(" + fields.length + ", 1));\n");
			bw.write("\t\tfieldsPanel.add(labelPanel, BorderLayout.WEST);\n");
			bw.write("\t\tfieldsPanel.add(textFieldPanel, BorderLayout.CENTER);\n\n");			
			for(int i = 0; i < fields.length;i++)
			{
				bw.write("\t\t" + fields[i] + "Label = new JLabel(\"" + fields[i] + "\", JLabel.RIGHT);\n");
			}
			bw.write("\n");
			for(int i = 0; i < fields.length;i++)
			{
				bw.write("\t\t" + fields[i] + "TextField = new JTextField();\n");
				bw.write("\t\t" + fields[i] + "TextField.setPreferredSize( new Dimension( 20, 24 ) );\n");
			}
			bw.write("\n");
			for(int i = 0; i < fields.length;i++)
			{
				bw.write("\t\t" + fields[i] + "Label.setLabelFor(" + fields[i] + "TextField);\n");
			}
			bw.write("\n");						
			for(int i = 0; i < buttons.length;i++)
			{
				bw.write("\t\t" + buttons[i] + "Button = new JButton(\"" + buttons[i] + "\");\n");
			}
			bw.write("\n");						
			for(int i = 0; i < fields.length;i++)
			{						
				bw.write("\t\tlabelPanel.add(" + fields[i] + "Label);\n");
				bw.write("\t\ttextFieldPanel.add(" + fields[i] + "TextField);\n");
			}	
			bw.write("\n");				
			bw.write("\t\tJScrollPane statusScroller = new JScrollPane(statusBox);\n");								
			bw.write("\t\tstatusPanel.add(new JLabel(\"Status\", JLabel.CENTER), BorderLayout.NORTH);\n");
			bw.write("\t\tstatusBox.setLineWrap(true);\n");
			bw.write("\t\tstatusBox.setEditable(false);\n");			
			bw.write("\t\tstatusPanel.add(statusScroller, BorderLayout.CENTER);\n");
			
			
			bw.write("\n");
			for(int i = 0; i < buttons.length;i++)
			{						
				bw.write("\t\t" + buttons[i] + "Listener = new ActionListener()\n");
				bw.write("\t\t{\n");
				bw.write("\t\t\tpublic void actionPerformed(ActionEvent event)\n");
				bw.write("\t\t\t{\n");
				bw.write("\n");
				bw.write("\t\t\t}\n");
				bw.write("\t\t};\n");
			}		
			bw.write("\n");
			for(int i = 0; i < buttons.length;i++)
			{
				bw.write("\t\t" + buttons[i] + "Button.addActionListener(" + buttons[i] + "Listener);\n");
			}			
							
			bw.write("\n");
			for(int i = 0; i < buttons.length;i++)
			{						
				bw.write("\t\tbuttonsPanel.add(" + buttons[i] + "Button);\n");
			}					
						
			bw.write("\t\tsetVisible(true);\n");
			
			
			
			bw.write("\t}\n");
			bw.write("\t\n");												
			/*------------FUNCTIONS/METHODS--------------------------------*/
			bw.write("\n\n\tpublic static void main(String[] args)");
			bw.write("\n\t{");
			bw.write("\n\t\tnew " + file.getName().replace(".java","") + "();");
			bw.write("\n\t}");
			bw.write("\n");
			for(int i = 0; i < fields.length;i++)
			{
				String checkMe = parameters_pass2.PM_getValue_J(fields[i],parameters_pass2.parameters)[0];
				bw.write("\n\tpublic String getDC" + fields[i] + "() throws IllegalFieldValueException");
				bw.write("\n\t{");			
				if(checkMe.toLowerCase().equals("integer"))
				{
					bw.write("\n\t\ttry");
					bw.write("\n\t\t{");					
					bw.write("\n\t\t\tInteger.parseInt("+ fields[i] + "TextField.getText());");
					bw.write("\n\t\t}");
					bw.write("\n\t\tcatch(Exception e)\n");
					bw.write("\t\t{\n");				
					bw.write("\t\t\tthrow new IllegalFieldValueException(" + fields[i] + "TextField.getText());\n");				
					bw.write("\t\t}");					
				}
				else if(checkMe.toLowerCase().equals("float"))
				{
					bw.write("\n\t\ttry");
					bw.write("\n\t\t{");
					bw.write("\n\t\t\tFloat.parseFloat("+ fields[i] + "TextField.getText());");
					bw.write("\n\t\t}");
					bw.write("\n\t\tcatch(Exception e)\n");
					bw.write("\t\t{\n");				
					bw.write("\t\t\tthrow new IllegalFieldValueException(" + fields[i] + "TextField.getText());\n");				
					bw.write("\t\t}");									
				}												
				bw.write("\n\t\treturn " + fields[i] + "TextField.getText();");
				bw.write("\n\t}");
			}			
			for(int i = 0; i < fields.length;i++)
			{			
				bw.write("\n\tpublic void setDC" + fields[i] + "(String " + fields[i] + ")");
				bw.write("\n\t{");
				bw.write("\n\t\t" + fields[i] + "TextField.setText(" + fields[i] + ");");
				bw.write("\n\t}");
			}		
			bw.write("\n\n\tpublic void appendToStatusArea(String appendMe)");
			bw.write("\n\t{");
			bw.write("\n\t\tstatusBox.append(appendMe + \"\\n\");");
			bw.write("\n\t}");			
			/*------------IllegalFieldValueException SEE CITATION #2--------------------------------*/					
			bw.write("\n\n\tpublic class IllegalFieldValueException extends Exception");
			bw.write("\n\t{");
			bw.write("\n\t\tpublic IllegalFieldValueException()");
			bw.write("\n\t\t{");
			bw.write("\n\t\t\tsuper();");
			bw.write("\n\t\t}");			
			bw.write("\n\t\tpublic IllegalFieldValueException(String printMe)");
			bw.write("\n\t\t{");
			bw.write("\n\t\t\tsuper(printMe);");
			bw.write("\n\t\t}");						
			/*------------END--------------------------------*/	
			bw.write("\n\t}");
			
			bw.write("\tpublic void keyPressed(KeyEvent e)\n");
			bw.write("\t{\n");		
			bw.write("\t}\n");
			bw.write("\tpublic void keyTyped(KeyEvent e)\n");
			bw.write("\t{\n");		
			bw.write("\t}\n");
			bw.write("\tpublic void keyReleased(KeyEvent e)\n");
			bw.write("\t{\n");		
			bw.write("\t}\n");				
			
			
						
			bw.write("\n}");			
			bw.close();			 
		} 
		catch (IOException e) 
		{			  
		}								
	}
	
	public DialogcCompiler(File configFile, File workingDirectory, File mainDir)
	{
		String dpath = workingDirectory.getAbsolutePath().replace(".","");
		String mainpath = mainDir.getAbsolutePath().replace(".","");
		
		if(!dpath.substring(dpath.length() - 1).equals("/"))
		{
			dpath = dpath + "/";
		}
		if(!mainpath.substring(mainpath.length() - 1).equals("/"))
		{
			mainpath = mainpath + "/";
		}		
		String dpath2 = dpath + configFile.getName().replace(".config",".java");		
		String theLexCmd = mainpath + "yadc " + dpath2 + " " + configFile.getName().replace(".config","")+ " " + configFile.getPath(); // + " < " + configFile.getPath();//+ " " + dpath.replace(".java",".config");
		 		
		try 
		{
			run(theLexCmd);
			File javaFileExists = new File(dpath2);
			if(javaFileExists.exists())
			{
				JOptionPane.showMessageDialog(null, "Compilation Complete",null, JOptionPane.INFORMATION_MESSAGE);
			}
			else
			{
				error_flag = 1;
			}		  
		} 
		catch (Exception e) 
		{	
			JOptionPane.showMessageDialog(null, "Compilation Unsuccessful",null, JOptionPane.INFORMATION_MESSAGE);	
		}
	}	
}
	
