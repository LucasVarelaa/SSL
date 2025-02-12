#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "semantic.h"
#include "symbol.h"
int errores_semanticos = 0;
static int temp_counter = 0;
static FILE* output = NULL;

void iniciarPrograma() {
    output = stdout;

    printf("#include <stdio.h>\n\n");
    printf("int main(void) {\n");

    initSymbolTable();
    temp_counter = 0;
    errores_semanticos = 0;
}

void finalizarPrograma() {
    
    printf("\treturn 0;\n}\n");
    freeSymbolTable();
}

void declararVariable(const char* nombre) {
    if (isDeclared(nombre)) {
        printf("linea #%d: Error semantico: identificador %s ya declarado\n", yylineno, nombre);
        errores_semanticos++;
    } else {
        if (addSymbol(nombre)) {
            printf("\tint %s;\n", nombre);
        }
    }
}

void verificarVariable(const char* nombre) {
    if (!isDeclared(nombre)) {
        printf("linea #%d: Error semantico: identificador %s NO declarado\n", yylineno, nombre);
        errores_semanticos++;
    }
}

void generarLectura(const char* nombre) {
    verificarVariable(nombre);
    printf("\tscanf(\"%%d\", &%s);\n", nombre);
}

void generarEscritura(const char* expresion) {
    if (expresion && *expresion) {  // Solo si la expresión no está vacía
        fprintf(output, "\tprintf(\"%%d\\n\", %s);\n", expresion); // ????
        //fprintf(output, "\tprintf(\"%%d\\n\", %s);\n", expresion);
    }
}


void generarAsignacion(const char* destino, const char* expresion) {
    verificarVariable(destino);
    printf("\t%s = %s;\n", destino, expresion);
}

char* nuevoTemporal() {
    char* temp = malloc(20);
    sprintf(temp, "_Temp%d", ++temp_counter);
    
    // Declarar la variable temporal en la tabla de símbolos
    
    
    printf("\tint %s;\n", temp);

    addSymbol(temp);  // Agregar a la tabla de símbolos
    
    return temp;
}

void liberarTemporales() {
    temp_counter = 0;
}
