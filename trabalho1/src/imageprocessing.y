%{
#include <stdio.h>
#include "imageprocessing.h"
#include <FreeImage.h>
#include <stdlib.h>

void yyerror(char *c);
int yylex(void);

%}
%union {
  char    strval[50];
  int     ival;
}
%token <strval> STRING NUMERO
%token <ival> VAR IGUAL EOL ASPA VEZES DIVIDIDO
%left SOMA

%%

PROGRAMA:
        PROGRAMA EXPRESSAO EOL
        |
        ;

EXPRESSAO:
    | STRING IGUAL STRING VEZES NUMERO{
        printf("Multiplicando o brilho da imagem %s por %s\n", $3, $5);
        imagem I = abrir_imagem($3);
        aplicar_brilho(&I, atof($5));
        salvar_imagem($1, &I);
        liberar_imagem(&I);
    }

    | STRING IGUAL STRING DIVIDIDO NUMERO{
        printf("Dividindo o brilho da imagem %s por %s\n", $3, $5);
        imagem I = abrir_imagem($3);
        aplicar_brilho(&I, 1/atof($5));
        salvar_imagem($1, &I);
        liberar_imagem(&I);
    }

    | STRING IGUAL STRING {
        printf("Copiando %s para %s\n", $3, $1);
        imagem I = abrir_imagem($3);
        printf("Li imagem %d por %d\n", I.width, I.height);
        salvar_imagem($1, &I);
        liberar_imagem(&I);
                          }
    ;

%%

void yyerror(char *s) {
    fprintf(stderr, "%s\n", s);
}

int main() {
  FreeImage_Initialise(0);
  yyparse();
  return 0;

}
