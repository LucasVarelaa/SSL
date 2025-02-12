%{
    #include <stdio.h>
    #include "scanner.h"
   
    int errores_lexicos = 0;
    int errores_sintacticos = 0;
    void yyerror(const char *s);
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
%right '='

%type <valor> expresion 

%%

inicio:
    PROGRAMA IDENTIFICADOR {
        printf("programa: %s\n", $2);
    } lista_de_declaracion_o_sentencias FIN {
        printf("Fin del programa\n");
        if (yynerrs || errores_lexicos) YYABORT; else YYACCEPT;
    }
    ;

declaracion:
    ENTERO IDENTIFICADOR ';' {
        printf("Sentencia declaración: %s\n", $2);
    }
    | IDENTIFICADOR ';'
    | ENTERO error ';'
    ;

sentencia:
    LEER '(' lista_identificadores ')' ';' {
        printf("Sentencia leer\n");
    }
    | ESCRIBIR '(' lista_expresiones ')' ';' {
        printf("Sentencia escribir\n");
    }
    | IDENTIFICADOR ASIGNACION expresion ';' {
        printf("Sentencia asignación\n");
    }
    | error ';' {
        yyerror;
    }
    ;

lista_de_declaracion_o_sentencias:
    /* vacío */
    | sentencia lista_de_declaracion_o_sentencias
    | declaracion lista_de_declaracion_o_sentencias
    ;

lista_identificadores:
    IDENTIFICADOR{
        // Acción para un solo identificador
    }
    | lista_identificadores ',' IDENTIFICADOR {
        // Acción para una lista de identificadores
    }
    ;

lista_expresiones:
    expresion
    | lista_expresiones ',' expresion
    ;
/*
expresion : 	          valor                   {$$=$1;                   }
                        | '-'valor %prec NEG      {$$ = invertir($2);       }
                        | '('expresion')'         {$$ = $2;                 }
                        | expresion '+' expresion {$$ = sumar($1, $3);      }
                        | expresion '-' expresion {$$ = restar($1, $3);     }
                        | expresion '*' expresion {$$ = multiplicar($1, $3);}
                        | expresion '/' expresion {$$ = dividir($1, $3);    }
						| '(' error ')';

valor : 		  		  identificador
                        | CONSTANTE;

identificador :         IDENTIFICADOR {if(!existe($1)){mostrarError($1,1); YYERROR;}else $$ = $1;};

*/
expresion:
    expresion '+' expresion {
        printf("suma\n");
        $$ = $1 + $3;
    }
    | expresion '-' expresion {
        printf("resta\n");
        $$ = $1 - $3;
    }
    | expresion '*' expresion {
        printf("multiplicación\n");
        $$ = $1 * $3;}
    | expresion '/' expresion {
        printf("división\n");
        $$ = $1 / $3;    }
    | expresion '%' expresion {
        printf("módulo\n");
        $$ = $1 % $3;}
    |CONSTANTE {
        $$ = $1;
    }
    | IDENTIFICADOR {
        // Aquí deberías buscar el valor del identificador
        $$ = 0; // Placeholder
    }
    | '-' expresion %prec NEG {
        printf("inversión\n");
        $$ = -$2;
    }
    | '('{printf("abre paréntesis\n");}
        expresion
        ')'{
        printf("Cierra paréntesis\n");
        }
    
    ;


%%

void yyerror(const char *s){
    printf("Línea # %d: %s\n", yylineno, s);
    return;
}