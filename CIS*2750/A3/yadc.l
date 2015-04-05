%{
#include <stdio.h>
#include "y.tab.h"
%}
%%
[^=;{},\n\t "]+			{yylval.str = strdup(yytext); return WORD;}
\=						return EQUALSIGN;
\;						return SEMICOLON;
#(.*)					/* ignore comments */;
\n						/* ignore end of line */;
\{						return OBRACE;
\}						return EBRACE;
\,						return COMMA;
\"						/* ignore quotations */;
[ \t]+					/* ignore whitespace */;
%%
