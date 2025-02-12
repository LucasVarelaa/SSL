#include "scanner.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Tabla de transición
static Estado tablaTransicion[NUM_ESTADOS][NUM_COLUMNAS] = {

                    // Letra,                   Dígito,               Operador,         Puntuación,         Espacio,           ':',                    '=',                        Otro,                   EOF
/*ESTADO_INICIAL*/   { ESTADO_ID,               ESTADO_CONSTANTE,     ESTADO_OPERADOR,  ESTADO_PUNTUACION,  ESTADO_INICIAL, ESTADO_ASIGNACION_INICIO,   ESTADO_ERROR_ASIGNACION,   ESTADO_ERROR_GENERAL,  ESTADO_EOF },  // ESTADO_INICIAL
/*ESTADO_ID*/        { ESTADO_ID,               ESTADO_ID,            ESTADO_INICIAL,   ESTADO_INICIAL,     ESTADO_INICIAL, ESTADO_INICIAL,             ESTADO_INICIAL,            ESTADO_ERROR_GENERAL,  ESTADO_INICIAL },  // ESTADO_ID
/*ESTADO_CONSTANTE*/ { ESTADO_INICIAL,          ESTADO_CONSTANTE,     ESTADO_INICIAL,   ESTADO_INICIAL,     ESTADO_INICIAL, ESTADO_INICIAL,             ESTADO_INICIAL,            ESTADO_ERROR_GENERAL,  ESTADO_INICIAL },  // ESTADO_CONSTANTE
/*ESTADO_OPERADOR*/  { ESTADO_INICIAL,          ESTADO_INICIAL,       ESTADO_INICIAL,   ESTADO_INICIAL,     ESTADO_INICIAL, ESTADO_INICIAL,             ESTADO_INICIAL,            ESTADO_ERROR_GENERAL,  ESTADO_INICIAL },  // ESTADO_OPERADOR
/*ESTADO_PUNTUACION*/{ ESTADO_INICIAL,          ESTADO_INICIAL,       ESTADO_INICIAL,   ESTADO_INICIAL,     ESTADO_INICIAL, ESTADO_INICIAL,             ESTADO_INICIAL,            ESTADO_ERROR_GENERAL,  ESTADO_INICIAL },  // ESTADO_PUNTUACION
/*ASIGNACION_INICIO*/{ ESTADO_ERROR_ASIGNACION,ESTADO_ERROR_ASIGNACION,ESTADO_ERROR_ASIGNACION,ESTADO_ERROR_ASIGNACION,ESTADO_ERROR_ASIGNACION,ESTADO_ERROR_ASIGNACION,ESTADO_ASIGNACION_FINAL,ESTADO_ASIGNACION_FINAL,ESTADO_ASIGNACION_FINAL},  // ESTADO_ASIGNACION_INICIO
/*ASIGNACION FINAL*/ { ESTADO_INICIAL,          ESTADO_INICIAL,       ESTADO_INICIAL,   ESTADO_INICIAL,     ESTADO_INICIAL, ESTADO_INICIAL,             ESTADO_INICIAL,             ESTADO_ERROR_GENERAL, ESTADO_INICIAL },  // ESTADO_ASIGNACION_FINAL
/*ERROR GENERAL*/    { ESTADO_ERROR_GENERAL,    ESTADO_ERROR_GENERAL, ESTADO_ERROR_GENERAL,ESTADO_ERROR_GENERAL, ESTADO_ERROR_GENERAL, ESTADO_ERROR_GENERAL, ESTADO_ERROR_GENERAL, ESTADO_ERROR_GENERAL,  ESTADO_INICIAL },  // ESTADO_ERROR_GENERAL
/*ERROR_ASIGNACION*/ { ESTADO_INICIAL,          ESTADO_INICIAL,ESTADO_INICIAL,ESTADO_INICIAL,ESTADO_INICIAL,ESTADO_INICIAL,ESTADO_INICIAL,ESTADO_INICIAL,ESTADO_EOF} // ESTADO_EOF
};



// Funciones auxiliares
int esLetra(char c) {
    return isalpha(c);
}

int esDigito(char c) {
    return isdigit(c);
}

int esEspacio(char c) {
    return isspace(c);
}

int esOperador(char c) {
    return strchr("+-*/%%", c) != NULL;
}

int esPuntuacion(char c) {
    return strchr(";,()", c) != NULL;
}

int esDospuntos(char c) {
    return c == ':';
}

int esIgual(char c) {
    return c == '=';
}

int esOtro(char c) {
    return !esLetra(c) && !esDigito(c) && !esOperador(c) && !esPuntuacion(c) && !esEspacio(c) && !esDospuntos(c) && !esIgual(c);
}

Columna obtenerColumna(char c) {
    if (esLetra(c)) return COL_LETRA;
    if (esDigito(c)) return COL_DIGITO;
    if (esOperador(c)) return COL_OPERADOR;
    if (esPuntuacion(c)) return COL_PUNTUACION;
    if (esEspacio(c)) return COL_ESPACIO;
    if (esDospuntos(c)) return COL_DOSPUNTOS;
    if (esIgual(c)) return COL_IGUAL;
    if (c == EOF) return COL_EOF;
    return COL_OTRO;
}


Token obtenerToken() {
    Token token = {TOKEN_ERROR_GENERAL, {0}};
    Estado estadoActual = ESTADO_INICIAL;
    char c;
    int pos = 0;

    int cont = 0;
    char aux;
    while (1) {
        
        //aux = c;
        c = getchar();

        
        
        Columna col = obtenerColumna(c);
        Estado nuevoEstado = tablaTransicion[estadoActual][col];

        if (nuevoEstado == ESTADO_INICIAL) {
            if (estadoActual != ESTADO_INICIAL) {
                ungetc(c, stdin);
                token.lexema[pos] = '\0';

                switch (estadoActual) {
                    case ESTADO_ID: token.tipo = TOKEN_IDENTIFICADOR; break;
                    case ESTADO_CONSTANTE: token.tipo = TOKEN_CONSTANTE; break;
                    case ESTADO_OPERADOR: token.tipo = TOKEN_OPERADOR; break;
                    case ESTADO_PUNTUACION: token.tipo = TOKEN_PUNTUACION; break;
                    case ESTADO_ASIGNACION_FINAL: token.tipo = TOKEN_ASIGNACION; break;
                    case ESTADO_ERROR_GENERAL: token.tipo = TOKEN_ERROR_GENERAL; break;
                    case ESTADO_ERROR_ASIGNACION: token.tipo = TOKEN_ERROR_ASIGNACION; break;
                    
                }

                return token;
            }
            continue;
        }

        if (nuevoEstado == ESTADO_ASIGNACION_FINAL) {
            token.lexema[pos++] = c;
            token.lexema[pos] = '\0';
            token.tipo = TOKEN_ASIGNACION;
            return token;
        }

        if (nuevoEstado == ESTADO_ERROR_GENERAL) {
            
                while (c!='\n'){  // Si hay error general, esto te lee la linea actual entera
                    token.lexema[pos++] = c;
                    token.tipo = TOKEN_ERROR_GENERAL;
                    c=getchar();


                }
            
            token.lexema[pos] = '\0';
            return token;
        }

        if (nuevoEstado == ESTADO_ERROR_ASIGNACION)
        {
            token.tipo = TOKEN_ERROR_ASIGNACION;
            while (c != '\n' && c != EOF)
            {
                token.lexema[pos++] = c;
                c = getchar();
            }
            token.lexema[pos] = '\0';
            return token;
        }

        if (nuevoEstado == ESTADO_EOF) {
            token.tipo = TOKEN_EOF;
            token.lexema[0] = '\0';
            return token;
        }


        token.lexema[pos++] = c;
        estadoActual = nuevoEstado;
        aux = c;
    }
}


bool strings_iguales(char * s1, char* s2){
    if (strcmp(s1,s2)==0)
        return true;
    
    return false;
}

char* clasificarPuntuacion(char lexema[100]){
    if (strings_iguales(lexema,";")) return "Punto y coma";
    if (strings_iguales(lexema,")")) return "Paréntesis que cierra";
    if (strings_iguales(lexema,"(")) return "Paréntesis que abre";
    if (strings_iguales(lexema,",")) return "Coma";
}

char* clasificarOperador(char lexema[100]){
    if (strings_iguales(lexema,"+")) return "Más";
    if (strings_iguales(lexema,"-")) return "Menos";
    if (strings_iguales(lexema,"*")) return "Multiplicación";
    if (strings_iguales(lexema,"/")) return "División";
    if (strings_iguales(lexema,"%%")) return "Módulo";
}

char* clasificarErrorAsignacion(char lexema[100]){
    if (strings_iguales(lexema,":")) return "Error en asignación por : solo";
    if (strings_iguales(lexema,"=")) return "Error en asignación por = solo";
}

// gcc *.c -o programa
// Get-Content entrada.txt | ./programa.exe > salida.txt
