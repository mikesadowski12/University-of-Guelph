#ifndef lint
static const char yysccsid[] = "@(#)yaccpar	1.9 (Berkeley) 02/21/93";
#endif

#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define YYPATCH 20110908

#define YYEMPTY        (-1)
#define yyclearin      (yychar = YYEMPTY)
#define yyerrok        (yyerrflag = 0)
#define YYRECOVERING() (yyerrflag != 0)

#define YYPREFIX "yy"

#define YYPURE 0

#line 2 "yadc.y"
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
#line 31 "yadc.y"
#ifdef YYSTYPE
#undef  YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#endif
#ifndef YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
typedef union 
{
	char *str;
} YYSTYPE;
#endif /* !YYSTYPE_IS_DECLARED */
#line 59 "y.tab.c"

/* compatibility with bison */
#ifdef YYPARSE_PARAM
/* compatibility with FreeBSD */
# ifdef YYPARSE_PARAM_TYPE
#  define YYPARSE_DECL() yyparse(YYPARSE_PARAM_TYPE YYPARSE_PARAM)
# else
#  define YYPARSE_DECL() yyparse(void *YYPARSE_PARAM)
# endif
#else
# define YYPARSE_DECL() yyparse(void)
#endif

/* Parameters sent to lex. */
#ifdef YYLEX_PARAM
# define YYLEX_DECL() yylex(void *YYLEX_PARAM)
# define YYLEX yylex(YYLEX_PARAM)
#else
# define YYLEX_DECL() yylex(void)
# define YYLEX yylex()
#endif

/* Parameters sent to yyerror. */
#define YYERROR_DECL() yyerror(const char *s)
#define YYERROR_CALL(msg) yyerror(msg)

extern int YYPARSE_DECL();

#define EQUALSIGN 257
#define SEMICOLON 258
#define OBRACE 259
#define EBRACE 260
#define COMMA 261
#define NEWLINE 262
#define WORD 263
#define YYERRCODE 256
static const short yylhs[] = {                           -1,
    0,    0,    6,    6,    6,    6,    6,    2,    1,    3,
    3,    4,    4,    5,
};
static const short yylen[] = {                            2,
    0,    2,    1,    1,    1,    1,    1,    2,    2,    2,
    2,    3,    1,    4,
};
static const short yydefred[] = {                         1,
    0,    0,    0,    0,    3,    5,    6,    7,    2,    0,
    0,    9,    8,    0,    0,   10,   11,    0,   12,   14,
};
static const short yydgoto[] = {                          1,
    4,    5,    6,    7,    8,    9,
};
static const short yysindex[] = {                         0,
 -257, -254, -253, -252,    0,    0,    0,    0,    0, -251,
 -247,    0,    0, -254, -244,    0,    0, -243,    0,    0,
};
static const short yyrindex[] = {                         0,
    0,    0,    3,   16,    0,    0,    0,    0,    0,    1,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
};
static const short yygindex[] = {                         0,
    0,   13,    0,   -2,   14,    0,
};
#define YYTABLESIZE 266
static const short yytable[] = {                         11,
   13,    2,   13,   12,   13,    3,    2,   14,   10,   14,
   15,   19,   18,   13,   20,    4,   16,   17,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,   13,
   13,   13,    0,   13,    0,   13,
};
static const short yycheck[] = {                          2,
    0,  259,    0,  257,  258,  263,  259,  261,  263,  261,
  263,   14,  260,  258,  258,    0,    4,    4,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  259,
  260,  259,   -1,  263,   -1,  263,
};
#define YYFINAL 1
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 263
#if YYDEBUG
static const char *yyname[] = {

"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"EQUALSIGN","SEMICOLON","OBRACE",
"EBRACE","COMMA","NEWLINE","WORD",
};
static const char *yyrule[] = {
"$accept : commands",
"commands :",
"commands : commands command",
"command : value",
"command : assign",
"command : expression",
"command : listContents",
"command : list",
"value : WORD SEMICOLON",
"assign : WORD EQUALSIGN",
"expression : assign value",
"expression : assign list",
"listContents : WORD COMMA listContents",
"listContents : WORD",
"list : OBRACE listContents EBRACE SEMICOLON",

};
#endif

int      yydebug;
int      yynerrs;

int      yyerrflag;
int      yychar;
YYSTYPE  yyval;
YYSTYPE  yylval;

/* define the initial stack-sizes */
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH  YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 500
#define YYMAXDEPTH  500
#endif
#endif

#define YYINITSTACKSIZE 500

typedef struct {
    unsigned stacksize;
    short    *s_base;
    short    *s_mark;
    short    *s_last;
    YYSTYPE  *l_base;
    YYSTYPE  *l_mark;
} YYSTACKDATA;
/* variables for the parser stack */
static YYSTACKDATA yystack;
#line 157 "yadc.y"

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
#line 491 "y.tab.c"

#if YYDEBUG
#include <stdio.h>		/* needed for printf */
#endif

#include <stdlib.h>	/* needed for malloc, etc */
#include <string.h>	/* needed for memset */

/* allocate initial stack or double stack size, up to YYMAXDEPTH */
static int yygrowstack(YYSTACKDATA *data)
{
    int i;
    unsigned newsize;
    short *newss;
    YYSTYPE *newvs;

    if ((newsize = data->stacksize) == 0)
        newsize = YYINITSTACKSIZE;
    else if (newsize >= YYMAXDEPTH)
        return -1;
    else if ((newsize *= 2) > YYMAXDEPTH)
        newsize = YYMAXDEPTH;

    i = data->s_mark - data->s_base;
    newss = (short *)realloc(data->s_base, newsize * sizeof(*newss));
    if (newss == 0)
        return -1;

    data->s_base = newss;
    data->s_mark = newss + i;

    newvs = (YYSTYPE *)realloc(data->l_base, newsize * sizeof(*newvs));
    if (newvs == 0)
        return -1;

    data->l_base = newvs;
    data->l_mark = newvs + i;

    data->stacksize = newsize;
    data->s_last = data->s_base + newsize - 1;
    return 0;
}

#if YYPURE || defined(YY_NO_LEAKS)
static void yyfreestack(YYSTACKDATA *data)
{
    free(data->s_base);
    free(data->l_base);
    memset(data, 0, sizeof(*data));
}
#else
#define yyfreestack(data) /* nothing */
#endif

#define YYABORT  goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR  goto yyerrlab

int
YYPARSE_DECL()
{
    int yym, yyn, yystate;
#if YYDEBUG
    const char *yys;

    if ((yys = getenv("YYDEBUG")) != 0)
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
#endif

    yynerrs = 0;
    yyerrflag = 0;
    yychar = YYEMPTY;
    yystate = 0;

#if YYPURE
    memset(&yystack, 0, sizeof(yystack));
#endif

    if (yystack.s_base == NULL && yygrowstack(&yystack)) goto yyoverflow;
    yystack.s_mark = yystack.s_base;
    yystack.l_mark = yystack.l_base;
    yystate = 0;
    *yystack.s_mark = 0;

yyloop:
    if ((yyn = yydefred[yystate]) != 0) goto yyreduce;
    if (yychar < 0)
    {
        if ((yychar = YYLEX) < 0) yychar = 0;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, reading %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
    }
    if ((yyn = yysindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: state %d, shifting to state %d\n",
                    YYPREFIX, yystate, yytable[yyn]);
#endif
        if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack))
        {
            goto yyoverflow;
        }
        yystate = yytable[yyn];
        *++yystack.s_mark = yytable[yyn];
        *++yystack.l_mark = yylval;
        yychar = YYEMPTY;
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if ((yyn = yyrindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag) goto yyinrecovery;

    yyerror("syntax error");

    goto yyerrlab;

yyerrlab:
    ++yynerrs;

yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if ((yyn = yysindex[*yystack.s_mark]) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: state %d, error recovery shifting\
 to state %d\n", YYPREFIX, *yystack.s_mark, yytable[yyn]);
#endif
                if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack))
                {
                    goto yyoverflow;
                }
                yystate = yytable[yyn];
                *++yystack.s_mark = yytable[yyn];
                *++yystack.l_mark = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: error recovery discarding state %d\n",
                            YYPREFIX, *yystack.s_mark);
#endif
                if (yystack.s_mark <= yystack.s_base) goto yyabort;
                --yystack.s_mark;
                --yystack.l_mark;
            }
        }
    }
    else
    {
        if (yychar == 0) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, error recovery discards token %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
        yychar = YYEMPTY;
        goto yyloop;
    }

yyreduce:
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: state %d, reducing by rule %d (%s)\n",
                YYPREFIX, yystate, yyn, yyrule[yyn]);
#endif
    yym = yylen[yyn];
    if (yym)
        yyval = yystack.l_mark[1-yym];
    else
        memset(&yyval, 0, sizeof yyval);
    switch (yyn)
    {
case 8:
#line 63 "yadc.y"
	{
		}
break;
case 9:
#line 68 "yadc.y"
	{
		}
break;
case 10:
#line 74 "yadc.y"
	{
			char *item = NULL;
			int x = 0;
			if(strcmp(yystack.l_mark[-1].str, "title") == 0)
			{
				title = yystack.l_mark[0].str;
			}
			if(fieldList != NULL && buttonList != NULL)
			{
				headOfList(fieldList->paramList);			
				for(x = 0; x < fieldList->paramList->count; x++)
				{			
					if(strcmp(fieldList->paramList->data[x],yystack.l_mark[-1].str) == 0)
					{
						if(fieldTypesTemp == NULL)
						{
							fieldTypesTemp = createNewList();
						}
						endOfList(fieldTypesTemp);
						addAfterPointer(fieldTypesTemp,yystack.l_mark[0].str);
					}
				}
				headOfList(buttonList->paramList);			
				for(x = 0; x < buttonList->paramList->count; x++)
				{			
					if(strcmp(buttonList->paramList->data[x],yystack.l_mark[-1].str) == 0)
					{
						if(buttonTypesTemp == NULL)
						{
							buttonTypesTemp = createNewList();
						}
						endOfList(buttonTypesTemp);
						addAfterPointer(buttonTypesTemp,yystack.l_mark[0].str);						
					}
				}				
			}
					
		}
break;
case 11:
#line 113 "yadc.y"
	{
			if(strcmp(yystack.l_mark[-1].str, "fields") == 0)
			{
				fields = newList;
				headOfList(fields);
				fieldList = reverseList(fields);
				newList = createNewList();
			}
			else if(strcmp(yystack.l_mark[-1].str, "buttons") == 0)
			{
				buttons = newList;
				headOfList(buttons);
				buttonList = reverseList(buttons);				
				newList = createNewList();
			}				
		}
break;
case 12:
#line 132 "yadc.y"
	{
			if(newList == NULL)
			{
				newList = createNewList();			
			}
			headOfList(newList);
			addAfterPointer(newList,yystack.l_mark[-2].str);
		}
break;
case 13:
#line 141 "yadc.y"
	{
			if(newList == NULL)
			{
				newList = createNewList();			
			}
			headOfList(newList);
			addAfterPointer(newList,yystack.l_mark[0].str);			
		}
break;
case 14:
#line 152 "yadc.y"
	{
			
		}
break;
#line 795 "y.tab.c"
    }
    yystack.s_mark -= yym;
    yystate = *yystack.s_mark;
    yystack.l_mark -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: after reduction, shifting from state 0 to\
 state %d\n", YYPREFIX, YYFINAL);
#endif
        yystate = YYFINAL;
        *++yystack.s_mark = YYFINAL;
        *++yystack.l_mark = yyval;
        if (yychar < 0)
        {
            if ((yychar = YYLEX) < 0) yychar = 0;
#if YYDEBUG
            if (yydebug)
            {
                yys = 0;
                if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
                if (!yys) yys = "illegal-symbol";
                printf("%sdebug: state %d, reading %d (%s)\n",
                        YYPREFIX, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == 0) goto yyaccept;
        goto yyloop;
    }
    if ((yyn = yygindex[yym]) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: after reduction, shifting from state %d \
to state %d\n", YYPREFIX, *yystack.s_mark, yystate);
#endif
    if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack))
    {
        goto yyoverflow;
    }
    *++yystack.s_mark = (short) yystate;
    *++yystack.l_mark = yyval;
    goto yyloop;

yyoverflow:
    yyerror("yacc stack overflow");

yyabort:
    yyfreestack(&yystack);
    return (1);

yyaccept:
    yyfreestack(&yystack);
    return (0);
}
