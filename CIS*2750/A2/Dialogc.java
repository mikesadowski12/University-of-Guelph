/*
#NAME: Mike Sadowski
#DATE: February 5th, 2015
#STUDENT ID: 0864810
#ASSIGNEMNT: CIS2750 A2
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

/* *******SOURCES*******
 * 
 * 1. http://www.java2s.com/Code/Java/Swing-JFC/JEditorPaneExample13.htm
 * 2. http://stackoverflow.com/questions/4801386/how-do-i-add-an-image-to-a-jbutton
 * 3. All button images are from google searches and are all public domain
 * 4. http://www.tutorialspoint.com/java/java_string_endswith.htm
 * 5. http://stackoverflow.com/questions/12899953/in-java-how-to-append-a-string-more-efficiently
 * 6. http://stackoverflow.com/questions/1099300/whats-the-difference-between-getpath-getabsolutepath-and-getcanonicalpath
 * 7. http://stackoverflow.com/questions/3153337/how-do-i-get-my-current-working-directory-in-java
 * 8. http://www.codejava.net/java-se/swing/show-simple-open-file-dialog-using-jfilechooser
 * 9. http://stackoverflow.com/questions/12478309/using-jeditorpane-to-open-a-text-file
 * 10. http://www.mkyong.com/java/how-to-write-to-file-in-java-bufferedwriter-example/
 * 11. http://docs.oracle.com/javase/tutorial/uiswing/events/documentlistener.html
 * 12. http://stackoverflow.com/questions/9228542/java-how-to-add-a-joptionpane-for-yes-and-no-options
 * 13. http://www.java2s.com/Code/JavaAPI/javax.swing/JFrameaddWindowListenerWindowListenerlis.htm
 * 14. http://www.coderanch.com/t/527038/java/java/Reading-text-file-FileReader-BufferedReader
 * 15. http://compsci.ca/v3/viewtopic.php?t=3486
 * 16. http://www.java2s.com/Tutorial/Java/0240__Swing/UsingJOptionPanetoObtainUserInput.htm
 * 17. http://stackoverflow.com/questions/9596468/open-only-xml-file-in-jfilechooser
 */

public class Dialogc extends JFrame implements KeyListener
{
	/*BUTTON items*/
	private JToolBar buttonBar;
	private JButton fileNewButton;
	private JButton fileOpenButton;
	private JButton fileSaveButton;
	private JButton fileSaveAsButton;
	private JButton compCompileButton;
	private JButton compCompileRunButton;
	private ImageIcon fileNewButtonImage;
	private ImageIcon fileOpenButtonImage;
	private ImageIcon fileSaveButtonImage;
	private ImageIcon fileSaveAsButtonImage;		
	private ImageIcon compCompileButtonImage;
	private ImageIcon compCompileRunButtonImage;
	
	private JMenuBar menuBar;
	
	/*FILE tab items*/
	private JMenu fileTab;
	private JMenuItem fileNew;
	private JMenuItem fileOpen;
	private JMenuItem fileSave;
	private JMenuItem fileSaveAs;
	private JMenuItem fileQuit;
	private ActionListener fileNewListener;
	private ActionListener fileOpenListener;
	private ActionListener fileSaveListener;
	private ActionListener fileSaveAsListener;
	private ActionListener fileQuitListener;
	
	/*COMPILE tab items*/
	private JMenu compileTab;
	private JMenuItem compCompile;
	private JMenuItem compCompileRun;
	private ActionListener compCompileListener;
	private ActionListener compCompileRunListener;
	
	/*CONFIG tab items*/
	private JMenu configTab;
	private JMenuItem configJavaCompiler;
	private JMenuItem configCompilerOptions;
	private JMenuItem configJavaRunTime;
	private JMenuItem configRunTimeOptions;
	private JMenuItem configWorkingDirectory;
	private ActionListener configJavaCompilerListener;
	private ActionListener configCompilerOptionsListener;
	private ActionListener configJavaRunTimeListener;
	private ActionListener configRunTimeOptionsListener;
	private ActionListener configWorkingDirectoryListener;
	private File javaCompilerFile;
	private String compilerOptionsString;
	private File JavaRunTimeFile;
	private String RunTimeOptionsString;
	private File workingDirectoryFile;
		
	/*HELP tab items*/
	private JMenu helpTab;
	private JMenuItem helpHelp;
	private JMenuItem helpAbout;
	private ActionListener helpHelpListener;
	private ActionListener helpAboutListener;
	
	/*MISC items*/
	private JFileChooser fileChooser;
	private JEditorPane editorPane;
	private ActionListener editorPaneListener;
	private JScrollPane scrollPane;
	
	Boolean changesMadeFlag;
	
	String documentName;
	String documentPath;
	
	public static void main(String[] args)
	{
		new Dialogc();
	}
	
	/*Mutator for the documentName variable,always have .config at the end no matter what*/
	public void setDocumentName(String newName)
	{
		StringBuilder stringBuilder = new StringBuilder(newName);
				
		/*always make sure the string ends with .config*/
		if(newName.endsWith(".config") == false)
		{
			stringBuilder.append(".config");
		}
		documentName = stringBuilder.toString();
	}
	
	/*Accessor for the documentName variable*/
	public String getDocumentName()
	{
		return documentName;
	}
		
	/* theFileChooserBox
	 * 
	 * 		Call the file chooser box to the screen according to the type (save/open), return the file
	 */ 	
	public File theFileChooserBox()
	{
		File selectedFile = null;
		int result = 0;
			
		/*see citation for JFileChooser at the top*/
		result = fileChooser.showOpenDialog(this);
		
		if (result == JFileChooser.APPROVE_OPTION) 
		{
			selectedFile = fileChooser.getSelectedFile();
		}	
		return selectedFile;
		/*(selectedFile.getAbsolutePath().substring(selectedFile.getAbsolutePath().lastIndexOf("\\")+1));*/					
	}
	
	public void fileSaveAsOption()
	{
		File selectedFile = null;
		int result = 0;
		
		fileChooser.setDialogTitle("Save As ...");		
		fileChooser = new JFileChooser(workingDirectoryFile);
		
		result = fileChooser.showSaveDialog(this);		
		if (result == JFileChooser.APPROVE_OPTION) 
		{
			selectedFile = fileChooser.getSelectedFile();
		}
		documentPath = selectedFile.getAbsolutePath();
		setDocumentName(selectedFile.getName());			
		saveToTheFile();
		changesMadeFlag = false;
	}
	
	/* changesAndSaveCheck
	 * 
	 * 		Check if any unsaved changes were made
	 */ 
	public void changesAndSaveCheck()
	{
		/*if changes were made or the work has not been saved, prompt to save*/
			if(changesMadeFlag == true)
			{
				int dialogResult = JOptionPane.showConfirmDialog (null, "Unsaved work, would you like to save?","Warning",JOptionPane.YES_NO_OPTION);
				
				if(dialogResult == 0)
				{
					if(getDocumentName().equals("untitled.config"))
					{
						fileSaveAsOption();
					}
					else
					{
						saveToTheFile();
					}	
					changesMadeFlag = false;			
				}
				return;				
			}			
	}
	
	/*see citation #15 + #16*/
	public String getOptionsFromUser(String defaultStr, String windowName)
	{
		Object newObj = JOptionPane.showInputDialog(this, windowName, "",
		JOptionPane.PLAIN_MESSAGE, null, null, defaultStr);
		if(newObj != null)/*if user didn't hit cancel*/
		{
			return (String) newObj;
		}
		return defaultStr;			
	}
			
	/* saveTheFile
	 * 
	 * 		Save the contents of the JEditorPane to a file
	 * 
	 *      NOTE: See citation at top
	 */ 	
	public void saveToTheFile()
	{
		try 
		{ 
			File file = new File(documentPath);
 
			/*if file doesnt exists, then create it*/
			if (!file.exists()) {
				file.createNewFile();
			}
		
			FileWriter fw = new FileWriter(file.getAbsoluteFile());
			BufferedWriter bw = new BufferedWriter(fw);
			bw.write(editorPane.getText());
			bw.close(); 			 
		} 
		catch (IOException e) 
		{			  
		}
		changesMadeFlag = false;
	}
	public Dialogc()
	{
		/*Create JFrame super class instance with size of 800x600, make all flags false*/
		super();
		setSize(800, 600);
		setLocation(100,100);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		addWindowListener(new FrameListener());	
		
		javaCompilerFile = new File("javac");
		JavaRunTimeFile = new File("java");
		compilerOptionsString = "";
		RunTimeOptionsString = "";
		workingDirectoryFile = new File(".");
				
		/*Set up the MENU and BUTTON bar, the EDITOR pane with SCROLL pane, and a FILECHOOSER*/
		menuBar = new JMenuBar();
		buttonBar = new JToolBar();
		editorPane = new JEditorPane();
		scrollPane = new JScrollPane(editorPane);/*Make the editor window scrollable*/
		fileChooser = new JFileChooser();/*File chooser for choosing file windows, suggested in the requirements*/
		FileNameExtensionFilter configFilter = new FileNameExtensionFilter("config files (*.config)", "config");
		fileChooser.setFileFilter(configFilter);
		getContentPane().add(BorderLayout.CENTER, scrollPane);	
		editorPane.getDocument().addDocumentListener(new MyDocumentListener());
		editorPane.setEditable(true);
		changesMadeFlag = false;
		
		/*create new document by default*/
		editorPane.setText(""); 
		setDocumentName("untitled");
		setTitle(getDocumentName());
		editorPane.setEditable(true);
				
		/*create path to ../../untitled.config */
		documentPath = System.getProperty("user.dir");
		StringBuilder stringBuilder = new StringBuilder(documentPath);
		stringBuilder.append("/" + documentName);
		documentPath = stringBuilder.toString();
		changesMadeFlag = false;			
	
			
/*----------------------------------------------------------------------------------------------------------*/		 
		/*ALL ACTION EVENT LISTENERS FOR EVERY BUTTON*/
/*----------------------------------------------------------------------------------------------------------*/	
	
		/*FILE TAB LISTENERS*/
		
		/*  -start a new project 
		 *  -if a project is currently opened, the user should be given the option to save it if is has been changed since it was open 
		 *  -if the current project is new, the user should be prompted for a name for the saved file(s) (you can assign a default if you like, but the user should still be prompted); 
		 *   	note that the file associated with the project should have a .config extension. 
		 */
		fileNewListener = new ActionListener()
		{
			public void actionPerformed(ActionEvent event)
			{								
				changesAndSaveCheck();
				editorPane.setText(""); 
				setDocumentName("untitled");
				setTitle(getDocumentName());
				editorPane.setEditable(true);
				
				/*create path to ../../untitled.config */
				documentPath = System.getProperty("user.dir");
				StringBuilder stringBuilder = new StringBuilder(documentPath);
				stringBuilder.append("/" + documentName);
				documentPath = stringBuilder.toString();
				changesMadeFlag = false;
			}
		};	
		
		/*  -open an existing project 
		 *  -if a project is currently opened, the user should be given the option to save it if is has been changed since it was open; 
		 * 		note that the file associated with the project should have a .config extension. 
		 *  -if the current project is new, the user should be prompted for a name for the project 
		 * 		(you can assign a default if you like, but the user should still be prompted) 
		 * 
		 * 		NOTE: Citation at the top of the file*/	
		fileOpenListener = new ActionListener()
		{
			public void actionPerformed(ActionEvent event)
			{					
				changesAndSaveCheck();
				fileChooser.setDialogTitle("Open ...");
				File openMe = theFileChooserBox();
										
				try 
				{
					Reader filereader = new FileReader(openMe.getAbsolutePath());
					editorPane.setPage(openMe.toURI().toURL());
				}
				catch (IOException e) 
				{				
					System.out.println("ERROR: File does not exist");
				}
				editorPane.getDocument().addDocumentListener(new MyDocumentListener());
				setDocumentName(openMe.getName());
				setTitle(getDocumentName());
				documentPath = openMe.getAbsolutePath();
				changesMadeFlag = false;
			}
		};
		
		/* -save current file 
		 * -if the current project is new, the user should be prompted for a name for the project (you can assign a default if you like, but the user should still be prompted); 
		 * 	note that the file associated with the project should have a .config extension. */
		fileSaveListener = new ActionListener()
		{
			public void actionPerformed(ActionEvent event)
			{
 				if(documentName.equals("untitled.config"))
 				{
					fileSaveAsOption();
				}
				else
				{
					saveToTheFile();
				}
				setTitle(getDocumentName());
			}	
		};
		
		/* -save current file with new name 
		 * -identical to the Save option, however the user should be immediately provided with the dialog to save a project with a new name 
		 * 		(keeping in mind the .config extension). 
		 * - if the project is already named, that name should be already loaded into the filename box*/		
		fileSaveAsListener = new ActionListener()
		{
			public void actionPerformed(ActionEvent event)
			{
					fileChooser.setDialogTitle("Save As ...");
					fileSaveAsOption();
					setTitle(getDocumentName());
			}
		};
		
		/* -terminate the program 
		 * -if a currently opened project is modified, the user should be prompted to save it */			
		fileQuitListener = new ActionListener()
		{
			public void actionPerformed(ActionEvent event)
			{		
				changesAndSaveCheck();		
				System.exit(0);			
			}
			
		};				
/*----------------------------------------------------------------------------------------------------------*/		
		/*COMPILE TAB LISTENERS*/
		
		/* -compile the currently loaded file 
		 * -see language section below for discussion of the two files involved in compilation 
		 * -the compiled application (the collection of .java source files that implements the dialog box) should be created in a subdirectory with the same name as the project 
		 * 	(i.e. the .config file with no extension) and the file containing the main method (i.e. the application) should also have the same 
		 * 	name as the project file, with a .java extension; you can generate as many additional files, according to whatever conventions you deem appropriate, as may be necessary to realize a dialog application. 
		 * -if the project is new and/or unsaved, the user should be prompted to save it, and give it a name, first (keep in mind the .config extension); 
		 *  if there already exists a project by the same name as that which would be created, a yes/no dialog box should be 
		 * 	presented asking if the file(s) should be overwritten 
		 * -errors in compilation should be written to a separate pop-up text window with a scrollbar and a single "Dismiss" button that closes this window 
		 * */
		compCompileListener = new ActionListener()
		{
			//File configFile, File workingDirectoryFile, String compilerOptionsString, String RunTimeOptionsString, String compileCommand, String runCommand)
			public void actionPerformed(ActionEvent event)
			{
				changesAndSaveCheck();
				File configFile = new File(documentPath);
				DialogcCompiler theCompiler = new DialogcCompiler(configFile,workingDirectoryFile,compilerOptionsString,RunTimeOptionsString, javaCompilerFile.getName(), JavaRunTimeFile.getName());					
				theCompiler.compile();					
			}
		};
		
		/* -identical to the "Compile" option, however on successful compilation the resulting 
		 * Java application should be compiled and executed immediately (see "Config" menu for Java compiler settings) */		
		compCompileRunListener = new ActionListener()
		{
			public void actionPerformed(ActionEvent event)
			{
				changesAndSaveCheck();
				File configFile = new File(documentPath);
				DialogcCompiler theCompiler = new DialogcCompiler(configFile,workingDirectoryFile,compilerOptionsString,RunTimeOptionsString, javaCompilerFile.getName(), JavaRunTimeFile.getName());				
				theCompiler.compileAndRun();	
			}
		};
/*----------------------------------------------------------------------------------------------------------*/			
		/*CONFIG TAB LISTENERS*/
		
		/* -specify the external Java compiler to be used when compiling the code your dialog compiler generates
		   -the current setting should always be displayed as part of the menu
			when editing this value, the user should be allowed to either enter a complete path to the compiler manually, 
			or browse for the application on the file system.  */
		configJavaCompilerListener = new ActionListener()
		{
			public void actionPerformed(ActionEvent event)
			{
				fileChooser.setDialogTitle("Locate JAVA Compiler");
				fileChooser.setSelectedFile(javaCompilerFile);
				javaCompilerFile = theFileChooserBox();								
			}
		};	
		
		/* -options to be used when compiling Java
           -the current setting should always be displayed as part of the menu
			editing the compiler arguments should be free-form, and whatever the user specifies here should be used explicitly as options to the Java compiler when doing external compilation 
     		(i.e. allowing the user to set a classpath or other parameters that may be relevant to the project)   */		
		/*See citation #15 + #16*/	
		configCompilerOptionsListener = new ActionListener()
		{
			public void actionPerformed(ActionEvent event)
			{
				compilerOptionsString = getOptionsFromUser(compilerOptionsString, "Compile Options");
			}
		};
		
		/* -specify the external Java runtime command to be used when running the code generated by the dialog compiler
		   -the current setting should always be displayed as part of the menu
			when editing this value, the user should be allowed to either enter a complete path to the JVM manually, 
			or browse for the application on the file system */
		configJavaRunTimeListener = new ActionListener()
		{
			public void actionPerformed(ActionEvent event)
			{
				fileChooser.setDialogTitle("Locate JAVA Run-time");
				fileChooser.setSelectedFile(JavaRunTimeFile);
				JavaRunTimeFile = theFileChooserBox();					
			}
		};
		
		/* -options to be used when invoking the external JVM
			-the current setting should always be displayed as part of the menu
			 editing the jvm arguments should be free-form, and whatever the user specifies here should be used explicitly as options to the JVM when invoking the external run-time
             (i.e. allowing the user to set a classpath or other parameters that may be relevant to the execution of the code)  */
		/*See citation #15 + #16*/		
		configRunTimeOptionsListener = new ActionListener()
		{
			public void actionPerformed(ActionEvent event)
			{
				RunTimeOptionsString = getOptionsFromUser(RunTimeOptionsString, "Run-Time Options");				
			}
		};
		
		
		/*-build directory for emitted Java code
            -the current setting should always be displayed as part of the menu
            -this should have a default value of the current directory (.), and if edited by the user should be used in place of "." as the leading 
				path to the location where the Java program, as described above, gets generated (i.e. if the "working directory" is set to foo/bar, and you are currently editing dialog.config, 
				the compiled dialog would appear in foo/bar/dialog with the main class called "dialog" appearing in foo/bar/dialog/dialog.java; directories should be created if they do not exist.  */			
		configWorkingDirectoryListener = new ActionListener()
		{
			public void actionPerformed(ActionEvent event)
			{
				fileChooser.setDialogTitle("Locate Working Directory");
				fileChooser.setSelectedFile(workingDirectoryFile);
				fileChooser.setFileSelectionMode(JFileChooser.DIRECTORIES_ONLY);
				fileChooser.setAcceptAllFileFilterUsed(false);				
				workingDirectoryFile = theFileChooserBox();
				fileChooser = new JFileChooser(workingDirectoryFile);/*update the directory of where we are working it*/
				fileChooser.setAcceptAllFileFilterUsed(true);						
			}
		};		
/*----------------------------------------------------------------------------------------------------------*/		
		/*HELP TAB LISTENERS*/
		
		/*-this option should pop-up a dialog which contains the information that you would normally include in your README file, 
		 * and any other documentation you feel like providing for your program. */
		helpHelpListener = new ActionListener()
		{
			public void actionPerformed(ActionEvent event)
			{
				File openMe = new File("README.txt");
				StringBuilder stringBuilder = new StringBuilder();
				
				try 
				{
					Reader filereader = new FileReader(openMe.getAbsolutePath());
					BufferedReader br = new BufferedReader(filereader); 
					while(br.readLine() != null)
					{
						stringBuilder.append(br.readLine());
						stringBuilder.append("\n");
					}
				}
				catch (IOException e) 
				{				
					System.out.println("ERROR: File does not exist");
				}
				
				JTextArea area = new JTextArea(stringBuilder.toString());
				area.setEditable(false);
				area.setRows(30);
				area.setColumns(75);
				JScrollPane helpMessage = new JScrollPane(area);
				JOptionPane.showMessageDialog(null, helpMessage, "Help", JOptionPane.PLAIN_MESSAGE);								
			}
		};
			
		/*-pops up a dialog with your submission information (name, id, etc.) and a dismiss button that closes this window. */	
		helpAboutListener = new ActionListener()
		{
			public void actionPerformed(ActionEvent event)
			{
				JOptionPane.showMessageDialog(null, "#NAME: Mike Sadowski\n#DATE: February 5th, 2015\n#STUDENT ID: 0864810\n#ASSIGNEMNT: CIS2750 A2","About", JOptionPane.INFORMATION_MESSAGE);
			}
		};
	
/*----------------------------------------------------------------------------------------------------------*/
		/*MENU BAR AND BUTTON BAR SETUP AND ADDITION TO JFRAME*/
/*----------------------------------------------------------------------------------------------------------*/		
		/*Create FILE tab, with all drop-down options*/
		fileTab = new JMenu("File");
		fileNew = new JMenuItem("New");
		fileOpen = new JMenuItem("Open");
		fileSave = new JMenuItem("Save");
		fileSaveAs = new JMenuItem("Save As");
		fileQuit = new JMenuItem("Quit");
		fileNew.addActionListener(fileNewListener);
		fileOpen.addActionListener(fileOpenListener);
		fileSave.addActionListener(fileSaveListener);
		fileSaveAs.addActionListener(fileSaveAsListener);
		fileQuit.addActionListener(fileQuitListener);
		/*keyboard shortcuts - figure out how to do this*/
		fileTab.add(fileNew);
		fileTab.add(fileOpen);
		fileTab.add(fileSave);
		fileTab.add(fileSaveAs);
		fileTab.add(fileQuit);
		menuBar.add(fileTab); /*add FILE tab to the menu bar*/
		
		/*Create COMPILE tab, with all drop-down options*/
		compileTab = new JMenu("Compile");
		compCompile = new JMenuItem("Compile");
		compCompileRun = new JMenuItem("Compile and run");
		compCompile.addActionListener(compCompileListener);
		compCompileRun.addActionListener(compCompileRunListener);		
		/*keyboard shortcuts - figure out how to do this*/
		compileTab.add(compCompile);
		compileTab.add(compCompileRun);
		menuBar.add(compileTab); /*add COMPILE tab to the bar*/
		
		/*Create CONFIG tab, with all drop-down options*/
		configTab = new JMenu("Config");
		configJavaCompiler = new JMenuItem("Java Compiler");
		configCompilerOptions = new JMenuItem("Compiler Options");
		configJavaRunTime = new JMenuItem("Java Run-time");
		configRunTimeOptions = new JMenuItem("Run-time Options");
		configWorkingDirectory = new JMenuItem("Working Directory");		
		configJavaCompiler.addActionListener(configJavaCompilerListener);
		configCompilerOptions.addActionListener(configCompilerOptionsListener);
		configJavaRunTime.addActionListener(configJavaRunTimeListener);
		configRunTimeOptions.addActionListener(configRunTimeOptionsListener);		
		configWorkingDirectory.addActionListener(configWorkingDirectoryListener);	
		/*keyboard shortcuts - figure out how to do this*/
		configTab.add(configJavaCompiler);
		configTab.add(configCompilerOptions);
		configTab.add(configJavaRunTime);
		configTab.add(configRunTimeOptions);		
		configTab.add(configWorkingDirectory);
		menuBar.add(configTab); /*add CONFIG tab to the menu bar*/
	
		/*Create HELP tab, with all drop-down options*/
		helpTab = new JMenu("Help");
		helpHelp = new JMenuItem("Help");
		helpAbout = new JMenuItem("About");
		helpHelp.addActionListener(helpHelpListener);
		helpAbout.addActionListener(helpAboutListener);
		helpTab.add(helpHelp);
		helpTab.add(helpAbout);
		menuBar.add(helpTab); /*add HELP tab to the menu bar*/
				
		/*Setup the BUTTON bar*/
		fileNewButtonImage = new ImageIcon("buttonbar/newfile.png");
		fileOpenButtonImage = new ImageIcon("buttonbar/open.png");
		fileSaveButtonImage = new ImageIcon("buttonbar/save-48x48.png");
		fileSaveAsButtonImage = new ImageIcon("buttonbar/saveas.png");		
		compCompileButtonImage = new ImageIcon("buttonbar/compile.png");
		compCompileRunButtonImage = new ImageIcon("buttonbar/run.png");
		fileNewButton = new JButton(fileNewButtonImage);
		fileOpenButton = new JButton(fileOpenButtonImage);
		fileSaveButton = new JButton(fileSaveButtonImage);
		fileSaveAsButton = new JButton(fileSaveAsButtonImage);		
		compCompileButton = new JButton(compCompileButtonImage);
		compCompileRunButton = new JButton(compCompileRunButtonImage);	
		fileNewButton.addActionListener(fileNewListener);
		fileOpenButton.addActionListener(fileOpenListener);
		fileSaveButton.addActionListener(fileSaveListener);
		fileSaveAsButton.addActionListener(fileSaveAsListener);
		compCompileButton.addActionListener(compCompileListener);
		compCompileRunButton.addActionListener(compCompileRunListener);		
		buttonBar.add(fileNewButton);		
		buttonBar.add(fileOpenButton);	
		buttonBar.add(fileSaveButton);		
		buttonBar.add(fileSaveAsButton);
		buttonBar.add(compCompileButton);		
		buttonBar.add(compCompileRunButton);						

		setJMenuBar(menuBar);
		getContentPane().add(buttonBar, BorderLayout.NORTH);
		setVisible(true);
	
								
	}		
/*-----------------------------------------------------------------------------------------------------*/
	public void keyPressed(KeyEvent e)
	{
		
	}
	public void keyTyped(KeyEvent e)
	{
		
	}
	public void keyReleased(KeyEvent e)
	{
		
	}
	
	/*See citation #13, i did not come up with this class*/
	class FrameListener extends WindowAdapter
	{
		public void windowClosing(WindowEvent e)
		{
			changesAndSaveCheck();
		}
	}	
    
    /*See citation #11, i did not come up with this class*/
	class MyDocumentListener implements DocumentListener 
	{
		public void insertUpdate(DocumentEvent e) 
		{
			changesMadeFlag = true;
		}
		public void removeUpdate(DocumentEvent e) 
		{
 			changesMadeFlag = true;         
		}
		public void changedUpdate(DocumentEvent e) 
		{
			changesMadeFlag = true;
		}
	}
}	
		


