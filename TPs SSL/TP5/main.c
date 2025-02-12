#include <stdio.h>
#include <stdlib.h>
#include "parser.h"

extern int yynerrs;
extern int errores_lexicos;

int main() {
    yyparse(); // Ejecuta el parser
    printf("Errores sintácticos: %d - Errores léxicos: %d\n", yynerrs, errores_lexicos);
    //fprintf(stderr, "Se detectaron %d errores sintácticos - Errores léxicos: %d.\n", yynerrs, errores_lexicos);
    return EXIT_SUCCESS;
}
