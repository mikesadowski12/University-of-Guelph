%{
#include <stdio.h>
#include <string.h>
#include "cfiles/ParameterList.h"
#include "cfiles/List.h"

char* title = NULL;
List *fields = NULL;
List *buttons = NULL;
List *fieldTypesTemp = NULL;
List *buttonTypesTemp = NULL;

List* newList = NULL;

ParameterList *fieldList = NULL;
ParameterList *buttonList = NULL;
ParameterList *fieldTypes = NULL;
ParameterList *buttonTypes = NULL;

void yyerror(const char *str)
{
        fprintf(stderr,"parse error: [%s]\n",str);
}
 
int yywrap()
{
        return 1;
} 
%}

%union 
{
	char *str;
} 

%token EQUALSIGN SEMICOLON OBRACE EBRACE COMMA NEWLINE
%token<str> WORD

%type <str> assign value expression listContents list


%%

commands: /* empty */
        | commands command
        ;

command:
		value
		|
		assign
		|
        expression
        |
        listContents
        |
        list
        ;
        
         
value:
		WORD SEMICOLON
		{
		}
		;
assign:
		WORD EQUALSIGN
		{
		}
		;
expression: 

		assign value
		{
			char *item = NULL;
			int x = 0;
			if(strcmp($1, "title") == 0)
			{
				title = $2;
			}
			if(fieldList != NULL && buttonList != NULL)
			{
				headOfList(fieldList->paramList);			
				for(x = 0; x < fieldList->paramList->count; x++)
				{			
					if(strcmp(fieldList->paramList->data[x],$1) == 0)
					{
						if(fieldTypesTemp == NULL)
						{
							fieldTypesTemp = createNewList();
						}
						endOfList(fieldTypesTemp);
						addAfterPointer(fieldTypesTemp,$2);
					}
				}
				headOfList(buttonList->paramList);			
				for(x = 0; x < buttonList->paramList->count; x++)
				{			
					if(strcmp(buttonList->paramList->data[x],$1) == 0)
					{
						if(buttonTypesTemp == NULL)
						{
							buttonTypesTemp = createNewList();
						}
						endOfList(buttonTypesTemp);
						addAfterPointer(buttonTypesTemp,$2);						
					}
				}				
			}
					
		}
		| assign list
		{
			if(strcmp($1, "fields") == 0)
			{
				fields = newList;
				headOfList(fields);
				fieldList = reverseList(fields);
				newList = createNewList();
			}
			else if(strcmp($1, "buttons") == 0)
			{
				buttons = newList;
				headOfList(buttons);
				buttonList = reverseList(buttons);				
				newList = createNewList();
			}				
		}	
		;
listContents:
		WORD COMMA listContents
		{
			if(newList == NULL)
			{
				newList = createNewList();			
			}
			headOfList(newList);
			addAfterPointer(newList,$1);
		}
		| WORD
		{
			if(newList == NULL)
			{
				newList = createNewList();			
			}
			headOfList(newList);
			addAfterPointer(newList,$1);			
		}
		;	
list:
		OBRACE listContents EBRACE SEMICOLON
		{
			
		}
		;	    						               
%%

extern FILE *yyin;

void main(int argc, char** argv)
{
	char *item = NULL;
	char *pname;
	char *dname;
	FILE *out;
	FILE *in;
	int x;

	dname = argv[1];
	pname = argv[2];
	in = fopen(argv[3], "r");

	yyin = in;

	while(!feof(yyin))
	{
		yyparse();
	}




	headOfList(fieldTypesTemp);
	headOfList(buttonTypesTemp);
	fieldTypes = PL_create(fieldTypesTemp);
	buttonTypes = PL_create(buttonTypesTemp);
	
	if(fieldTypes->paramList->count != fieldList->paramList->count)
	{
		return;
	}
	if(buttonTypes->paramList->count != buttonList->paramList->count)
	{
		return;
	}	
	if(title == NULL)
	{
		return;
	}		
	
	out = fopen(dname, "w");
			
	fprintf(out, "import java.awt.*;\n");
	fprintf(out, "import java.io.*;\n");
	fprintf(out, "import javax.swing.*;\n");
	fprintf(out, "import javax.swing.text.*;\n");
	fprintf(out, "import java.util.*;\n");
	fprintf(out, "import java.lang.String;\n");
	fprintf(out, "import java.awt.*;\n");
	fprintf(out, "import java.awt.event.*;\n");
	fprintf(out, "import javax.swing.JFileChooser;\n");
	fprintf(out, "import java.io.File;\n");
	fprintf(out, "import javax.swing.event.*;\n");
	fprintf(out, "import javax.swing.filechooser.FileNameExtensionFilter;\n\n");

	fprintf(out, "public class %s extends JFrame",pname);
	fprintf(out, "\n{");

	for(x = 0; x < fieldList->paramList->count; x++)
	{	
		fprintf(out, "\n");
		fprintf(out, "\tprivate JLabel %sLabel;", (char*)fieldList->paramList->data[x]);
	}
	fprintf(out, "\n");
	for(x = 0; x < fieldList->paramList->count; x++)
	{	
		fprintf(out, "\n");
		fprintf(out, "\tprivate JTextField %sTextField;", (char*)fieldList->paramList->data[x]);
	}		
	fprintf(out, "\n");
	for(x = 0; x < buttonList->paramList->count; x++)
	{	
		fprintf(out, "\n");
		fprintf(out, "\tprivate JButton %sButton;", (char*)buttonList->paramList->data[x]);
	}
	fprintf(out, "\n");
	for(x = 0; x < buttonList->paramList->count; x++)
	{	
		fprintf(out, "\n");
		fprintf(out, "\tprivate ActionListener %sListener;", (char*)buttonList->paramList->data[x]);
	}		
	fprintf(out, "\n\n\tprivate JScrollPane scroller;");
	fprintf(out, "\n\tprivate JTextArea statusBox = new JTextArea();\n");			
	fprintf(out, "\tprivate JPanel fieldsPanel = new JPanel(new BorderLayout());\n");
	fprintf(out, "\tprivate JPanel buttonsPanel = new JPanel();\n");
	fprintf(out, "\tprivate JPanel upperPanel = new JPanel(new BorderLayout());\n");
	fprintf(out, "\tprivate JPanel statusPanel = new JPanel(new BorderLayout());\n\n");		

	fprintf(out, "\tpublic %s()\n",pname);
	fprintf(out, "\t{\n");
	fprintf(out, "\t\tsuper(\"%s\");\n",title);
	fprintf(out, "\t\tsetSize(400, 400);\n");
	fprintf(out, "\t\tsetDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);\n");				
	fprintf(out, "\t\tupperPanel.add(fieldsPanel, BorderLayout.NORTH);\n");
	fprintf(out, "\t\tupperPanel.add(buttonsPanel, BorderLayout.CENTER);\n");
	fprintf(out, "\t\tgetContentPane().add(upperPanel, BorderLayout.NORTH);\n");
	fprintf(out, "\t\tgetContentPane().add(statusPanel, BorderLayout.CENTER);\n");
	fprintf(out, "\t\tJPanel labelPanel = new JPanel(new GridLayout(%d, 1));\n",fieldList->paramList->count);
	fprintf(out, "\t\tJPanel textFieldPanel = new JPanel(new GridLayout(%d, 1));\n",fieldList->paramList->count);
	fprintf(out, "\t\tfieldsPanel.add(labelPanel, BorderLayout.WEST);\n");
	fprintf(out, "\t\tfieldsPanel.add(textFieldPanel, BorderLayout.CENTER);\n\n");	
	for(x = 0; x < fieldList->paramList->count; x++)
	{	
		fprintf(out, "\t\t%sLabel = new JLabel(\"%s\", JLabel.RIGHT);\n",(char*)fieldList->paramList->data[x],(char*)fieldList->paramList->data[x]);
	}
	fprintf(out, "\n");
	for(x = 0; x < fieldList->paramList->count; x++)
	{	
		fprintf(out, "\t\t%sTextField = new JTextField();\n", (char*)fieldList->paramList->data[x]);		
		fprintf(out, "\t\t%sTextField.setPreferredSize( new Dimension( 20, 24 ) );\n", (char*)fieldList->paramList->data[x]);
	}
	fprintf(out, "\n");
	for(x = 0; x < fieldList->paramList->count; x++)
	{	
		fprintf(out, "\t\t%sLabel.setLabelFor(%sTextField);\n", (char*)fieldList->paramList->data[x], (char*)fieldList->paramList->data[x]);
	}
	fprintf(out, "\n");
	for(x = 0; x < buttonList->paramList->count; x++)
	{	
		fprintf(out, "\t\t%sButton = new JButton(\"%s\");\n",(char*)buttonList->paramList->data[x], (char*)buttonList->paramList->data[x]);
	}	
	fprintf(out, "\n");	
	for(x = 0; x < fieldList->paramList->count; x++)
	{	
		fprintf(out, "\t\tlabelPanel.add(%sLabel);\n",(char*)fieldList->paramList->data[x]);
		fprintf(out, "\t\ttextFieldPanel.add(%sTextField);\n",(char*)fieldList->paramList->data[x]);
	}
	fprintf(out, "\n");				
	fprintf(out, "\t\tJScrollPane statusScroller = new JScrollPane(statusBox);\n");								
	fprintf(out, "\t\tstatusPanel.add(new JLabel(\"Status\", JLabel.CENTER), BorderLayout.NORTH);\n");
	fprintf(out, "\t\tstatusBox.setLineWrap(true);\n");
	fprintf(out, "\t\tstatusBox.setEditable(false);\n");			
	fprintf(out, "\t\tstatusPanel.add(statusScroller, BorderLayout.CENTER);\n");			
	
	
	for(x = 0; x < buttonList->paramList->count; x++)
	{	
		fprintf(out, "\t\t%sListener = new ActionListener()\n",(char*)buttonList->paramList->data[x], (char*)buttonList->paramList->data[x]);
		fprintf(out, "\t\t{\n");
		fprintf(out, "\t\t\tpublic void actionPerformed(ActionEvent event)\n");
		fprintf(out, "\t\t\t{\n");
		fprintf(out, "\n");
		fprintf(out, "\t\t\t}\n");
		fprintf(out, "\t\t};\n");		
	}	
	fprintf(out, "\n");
	for(x = 0; x < buttonList->paramList->count; x++)
	{	
		fprintf(out, "\t\t%sButton.addActionListener(%sListener);\n",(char*)buttonList->paramList->data[x], (char*)buttonList->paramList->data[x]);		
	}
	fprintf(out, "\n");
	for(x = 0; x < buttonList->paramList->count; x++)
	{	
		fprintf(out, "\t\tbuttonsPanel.add(%sButton);\n",(char*)buttonList->paramList->data[x]);
	}
	fprintf(out, "\t\tsetVisible(true);\n\n");
			
	fprintf(out, "\t}\n");

	fprintf(out, "\n\n\tpublic static void main(String[] args)");
	fprintf(out, "\n\t{");
	fprintf(out, "\n\t\tnew %s();",pname);
	fprintf(out, "\n\t}");
	fprintf(out, "\n");		
	for(x = 0; x < fieldList->paramList->count; x++)
	{		
		fprintf(out, "\n\tpublic String getDC%s() throws IllegalFieldValueException",(char*)fieldList->paramList->data[x]);
		fprintf(out, "\n\t{");	
		if(strcmp("integer", (char*)fieldTypes->paramList->data[x]) == 0)
		{
			fprintf(out, "\n\t\ttry");
			fprintf(out, "\n\t\t{");					
			fprintf(out, "\n\t\t\tInteger.parseInt(%sTextField.getText());",(char*)fieldList->paramList->data[x]);
			fprintf(out, "\n\t\t}");
			fprintf(out, "\n\t\tcatch(Exception e)\n");
			fprintf(out, "\t\t{\n");				
			fprintf(out, "\t\t\tthrow new IllegalFieldValueException(%sTextField.getText());\n",(char*)fieldList->paramList->data[x]);				
			fprintf(out, "\t\t}");			
		}
		if(strcmp("float",(char*)fieldTypes->paramList->data[x]) == 0)
		{
			fprintf(out, "\n\t\ttry");
			fprintf(out, "\n\t\t{");					
			fprintf(out, "\n\t\t\tFloat.parseFloat(%sTextField.getText());",(char*)fieldList->paramList->data[x]);
			fprintf(out, "\n\t\t}");
			fprintf(out, "\n\t\tcatch(Exception e)\n");
			fprintf(out, "\t\t{\n");				
			fprintf(out, "\t\t\tthrow new IllegalFieldValueException(%sTextField.getText());\n",(char*)fieldList->paramList->data[x]);					
			fprintf(out, "\t\t}");		
		}				
		fprintf(out, "\n\t\treturn %sTextField.getText();",(char*)fieldList->paramList->data[x]);
		fprintf(out, "\n\t}");
	}		
	for(x = 0; x < fieldList->paramList->count; x++)
	{		
		fprintf(out, "\n\tpublic void setDC%s(String %s)",(char*)fieldList->paramList->data[x],(char*)fieldList->paramList->data[x]);
		fprintf(out, "\n\t{");
		fprintf(out, "\n\t\t%sTextField.setText(%s);",(char*)fieldList->paramList->data[x],(char*)fieldList->paramList->data[x]);
		fprintf(out, "\n\t}");
	}		
	fprintf(out, "\n\n\tpublic void appendToStatusArea(String appendMe)");
	fprintf(out, "\n\t{");
	fprintf(out, "\n\t\tstatusBox.append(appendMe + \"\\n\");");
	fprintf(out, "\n\t}");	
				
	fprintf(out, "\n\n\tpublic class IllegalFieldValueException extends Exception");
	fprintf(out, "\n\t{");
	fprintf(out, "\n\t\tpublic IllegalFieldValueException()");
	fprintf(out, "\n\t\t{");
	fprintf(out, "\n\t\t\tsuper();");
	fprintf(out, "\n\t\t}");			
	fprintf(out, "\n\t\tpublic IllegalFieldValueException(String printMe)");
	fprintf(out, "\n\t\t{");
	fprintf(out, "\n\t\t\tsuper(printMe);");
	fprintf(out, "\n\t\t}");
	fprintf(out, "\n");						
	fprintf(out, "\n\t}");
	fprintf(out, "\n");

	fprintf(out, "\tpublic void keyPressed(KeyEvent e)\n");
	fprintf(out, "\t{\n");		
	fprintf(out, "\t}\n");
	fprintf(out, "\tpublic void keyTyped(KeyEvent e)\n");
	fprintf(out, "\t{\n");		
	fprintf(out, "\t}\n");
	fprintf(out, "\tpublic void keyReleased(KeyEvent e)\n");
	fprintf(out, "\t{\n");		
	fprintf(out, "\t}\n");				
	fprintf(out, "\n}");
	
	fclose(out);
	fclose(in);
	PL_destroy(fieldList);
	PL_destroy(buttonList);		
}
