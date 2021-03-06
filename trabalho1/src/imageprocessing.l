
%{
#include <stdlib.h>
#include <string.h>
void yyerror(char *);

#include "y.tab.h"
%}



%%

[a-z]  {
        yylval.ival = yytext[0] - 'a';
        return VAR;
       }


\" { return ASPA; }

[0-9\.]+ {
    for (int i = 0; i < yyleng; i++ )
      yylval.strval[i] = yytext[i];
    yylval.strval[yyleng] = '\0';
    return NUMERO;
}

[a-zA-Z0-9\.]+  {
        for (int i = 0; i < yyleng; i++ )
          yylval.strval[i] = yytext[i];

        yylval.strval[yyleng] = '\0';
        printf ("Achei nome: %s\n", yylval.strval);
        return STRING;
       }
\[  {
        return COLCHETE_ESQ;
    }
\]  {
        return COLCHETE_DIR;
    }

[=]     {
          return IGUAL;
        }

\n   {
         return EOL;
       }

[*] {
        return VEZES;
    }

[/] {
        return DIVIDIDO;
    }

[ \t]+ ;

.     {printf("**%s**\n", yytext);
yyerror("Token nao reconhecido!\n");}

%%

int  yywrap() {
  return 1;
}
