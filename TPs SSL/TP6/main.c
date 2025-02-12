#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include "semantic.h"

extern int yynerrs;
extern int errores_lexicos;
extern int errores_semanticos;

int main() {
    int resultado = yyparse();



    if (errores_lexicos != 0 || yynerrs != 0 || errores_semanticos != 0){
        printf("Errores sintacticos: %d - Errores lexicos: %d - Errores Semanticos: %d\n",yynerrs, errores_lexicos, errores_semanticos);
    }


    return resultado;
}