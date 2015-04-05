/*
#NAME: Mike Sadowski
#DATE: February 5th, 2015
#STUDENT ID: 0864810
#ASSIGNEMNT: CIS2750 A2
*/

/*
 * Sources: 
 * 1. http://www.tutorialspoint.com/java/java_file_class.htm
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
	private PM_Converter parameters_pass1;/*saves first pass of parsing*/
	private PM_Converter parameters_pass2;/*saves second pass of parsing*/
	private File configFile;
	private File javaCompilerFile;
	private String compilerOptionsString;
	private File JavaRunTimeFile;
	private String runTimeOptionsString;
	private File workingDirectoryFile;
	private String compileCommand;
	private String runCommand;	
	
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
		parameters_pass1.PM_parseFrom_J(configFile.getPath(),'#',parameters_pass1.parameters);
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
		parameters_pass2.PM_parseFrom_J(configFile.getPath(),'#',parameters_pass2.parameters);			
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
		} 
		catch (Exception e) 
		{		
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
	
	public void run(String command) throws Exception 
	{
		Process pro = Runtime.getRuntime().exec(command);
		printLines(command + " stdout:", pro.getInputStream());
		printLines(command + " stderr:", pro.getErrorStream());
		pro.waitFor();
		//System.out.println(command + " exitValue() " + pro.exitValue());		
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

			bw.write("public class " + file.getName().replace(".java","") + " extends JFrame");
			bw.write("\n{");
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
			bw.write("\n\n\tprivate JScrollPane scroller;");
			bw.write("\n\tprivate JTextArea statusBox = new JTextArea();\n");
			bw.write("\tprivate JPanel statusBoxPanel;\n");
			bw.write("\tprivate JPanel buttonPanel;\n");
			bw.write("\tprivate JPanel topPanel;\n");
			bw.write("\tprivate JPanel textPanel;\n");
			bw.write("\tprivate JPanel paramsPanel;\n");
			
			bw.write("\n\tpublic static void main(String[] args)");
			bw.write("\n\t{");
			bw.write("\n\t\tnew " + file.getName().replace(".java","") + "();");
			bw.write("\n\t}");
			bw.write("\n\t");
			
			for(int i = 0; i < fields.length;i++)
			{
				bw.write("\n\tpublic String getDC" + fields[i] + "()");
				bw.write("\n\t{");
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
			bw.write("\n\tpublic void appendToStatusArea(String message)");
			bw.write("\n\t{");
			bw.write("\n\t\tstatusBox.append(message);");
			bw.write("\n\t}");			
			bw.write("\n");	
														
			bw.write("\n\tpublic " + file.getName().replace(".java","") + "()");
			bw.write("\n\t{");
			bw.write("\n\t\tsuper(\"" + title[0] +"\");\n");	
			bw.write("\n\t\tsetVisible(true);\n");
			bw.write("\t\tsetSize(1000, 900);\n");			
			bw.write("\t\tsetDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);\n\n");
			bw.write("\t\tbuttonPanel = new JPanel();\n");
			bw.write("\t\tparamsPanel = new JPanel();\n");
			bw.write("\t\ttextPanel = new JPanel();\n\n");
								
			for(int i = 0; i < fields.length;i++)
			{
				bw.write("\t\t" + fields[i] + "TextField = new JTextField(10);\n");
				bw.write("\t\ttextPanel.add("+ fields[i] + "TextField);\n");
			}	
			bw.write("\n");
			for(int i = 0; i < fields.length;i++)
			{			
				bw.write("\t\t" + fields[i] + "Label = new JLabel(\"" + fields[i] + "\", JLabel.RIGHT);\n");
				bw.write("\t\tparamsPanel.add(" + fields[i] + "Label);\n"); 
			}
			bw.write("\n");			
			for(int i = 0; i < buttons.length;i++)
			{
				bw.write("\t\t" + buttons[i] + "Button = new JButton(\"" + buttons[i] + "\");\n");
			}
			for(int i = 0; i < buttons.length;i++)
			{			
				bw.write("\t\tbuttonPanel.add(" + buttons[i] + "Button);\n");
			}	
			bw.write("\n\t\tadd(textPanel,BorderLayout.LINE_START);\n");
			bw.write("\t\tadd(buttonPanel, BorderLayout.SOUTH);\n");
			bw.write("\t\tadd(paramsPanel, BorderLayout.NORTH);\n");
			
										
			bw.write("\t}\n");						
			bw.write("\n}");				
			bw.close();
		 
		} 
		catch (IOException e) 
		{			  
		}
									
	}
}
