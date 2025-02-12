%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "scanner.h"
    #include "semantic.h"
    #include "symbol.h"
   
    int errores_lexicos = 0;
    void yyerror(const char *s);
    char* gen_binary_op(char* left, char op, char* right);
    char* gen_unary_op(char op, char* operand);
%}

%defines "parser.h"
%output "parser.c" 

%code provides {
    extern int errores_lexicos;
}

%union {
    char* str;
    int valor;
}

%token <str> IDENTIFICADOR
%token <valor> CONSTANTE
%token PROGRAMA FIN ENTERO LEER ESCRIBIR ASIGNACION

%define parse.error verbose

%left '+' '-'
%left '*' '/' '%'
%right NEG

%type <str> expresion

%%

inicio:
    PROGRAMA IDENTIFICADOR {
        iniciarPrograma();
    } lista_de_declaracion_o_sentencias FIN {
        finalizarPrograma();
        YYACCEPT;
    }
    ;

declaracion:
    ENTERO IDENTIFICADOR ';' {
        declararVariable($2);
        free($2);
    }
    | IDENTIFICADOR ';' {
        verificarVariable($1);
        free($1);
    }
    | ENTERO error ';'
    ;

sentencia:
    LEER '(' lista_identificadores ')' ';'
    | ESCRIBIR '(' lista_expresiones ')' ';'
    | IDENTIFICADOR ASIGNACION expresion ';' {
        generarAsignacion($1, $3);
        free($1);
        free($3);
    }
    | error ';'
    ;

lista_de_declaracion_o_sentencias:
    /* vacío */
    | sentencia lista_de_declaracion_o_sentencias
    | declaracion lista_de_declaracion_o_sentencias
    ;

lista_identificadores:
    IDENTIFICADOR {
        generarLectura($1);
        free($1);
    }
    | lista_identificadores ',' IDENTIFICADOR {
        generarLectura($3);
        free($3);
    }
    ;

lista_expresiones:
    expresion {
        generarEscritura($1);
        free($1);
    }
    | lista_expresiones ',' expresion {
        generarEscritura($3);
        free($3);
    }
    ;

expresion:
    expresion '+' expresion {
        $$ = gen_binary_op($1, '+', $3);
        free($1);
        free($3);
    }
    | expresion '-' expresion {
        $$ = gen_binary_op($1, '-', $3);
        free($1);
        free($3);
    }
    | expresion '*' expresion {
        $$ = gen_binary_op($1, '*', $3);
        free($1);
        free($3);
    }
    | expresion '/' expresion {
        $$ = gen_binary_op($1, '/', $3);
        free($1);
        free($3);
    }
    | expresion '%' expresion {
        $$ = gen_binary_op($1, '%', $3);
        free($1);
        free($3);
    }
    | '-' expresion %prec NEG {
        $$ = gen_unary_op('-', $2);
        free($2);
    }
    | CONSTANTE {
        char* temp = malloc(20);
        sprintf(temp, "%d", $1);
        $$ = temp;
    }
    | IDENTIFICADOR {
        if (isDeclared($1)) {
            $$ = strdup($1);
        } else {
            printf("Línea #%d: Error semántico: identificador %s NO declarado\n", yylineno, $1);
            errores_semanticos++;
            $$ = strdup("");  // No generará código
        }
        free($1);
    }
    | '(' expresion ')' {
        $$ = $2;
    }
    ;

%%

void yyerror(const char *s) {

    /*if (strstr(s, "syntax error, unexpected '*'") != NULL) {
        char*mensaje = malloc(100);
        sprintf(mensaje, "linea #%d: syntax error, unexpected '*', expecting :=\n", yylineno);
        insertar_linea_en_buffer(mensaje);
    }*/
    
    // Personalizar mensajes de error específicos
    if (strstr(s, "syntax error, unexpected ')'") != NULL) {
        printf("linea #%d: syntax error, unexpected ')', expecting ID\n", yylineno);
    } 
    else if (strstr(s, "syntax error, unexpected IDENTIFICADOR") != NULL) {
        printf("linea #%d: syntax error, unexpected ID, expecting :=\n", yylineno);
    }
    else {
        printf("linea #%d: %s\n", yylineno, s);
    }
}

char* gen_binary_op(char* left, char op, char* right) {
    char* temp = nuevoTemporal();
    char expr[256];
    sprintf(expr, "%s %c %s", left, op, right);
    generarAsignacion(temp, expr);
    return temp;
}

char* gen_unary_op(char op, char* operand) {
    char* temp = nuevoTemporal();
    char expr[256];
    sprintf(expr, "%c%s", op, operand);
    generarAsignacion(temp, expr);
    return temp;
}
