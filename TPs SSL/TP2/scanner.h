#ifndef SCANNER_H
#define SCANNER_H

#define NUM_ESTADOS 9
#define NUM_COLUMNAS 9

#include <stdbool.h>
#include <stdlib.h>

// Definición de los tipos de tokens
typedef enum {
    TOKEN_IDENTIFICADOR,
    TOKEN_CONSTANTE,
    TOKEN_OPERADOR,
    TOKEN_PUNTUACION,
    TOKEN_ASIGNACION,
    TOKEN_ERROR_GENERAL,
    TOKEN_ERROR_ASIGNACION,
    TOKEN_EOF
} TokenTipo;

// Definición de las columnas para la tabla de transición
typedef enum {
    COL_LETRA,
    COL_DIGITO,
    COL_OPERADOR,
    COL_PUNTUACION,
    COL_ESPACIO,
    COL_DOSPUNTOS,
    COL_IGUAL,
    COL_OTRO,
    COL_EOF
} Columna;

// Definición de los estados
typedef enum {
    ESTADO_INICIAL,
    ESTADO_ID,
    ESTADO_CONSTANTE,
    ESTADO_OPERADOR,
    ESTADO_PUNTUACION,
    ESTADO_ASIGNACION_INICIO,
    ESTADO_ASIGNACION_FINAL,
    ESTADO_ERROR_GENERAL,
    ESTADO_EOF,
    ESTADO_ERROR_ASIGNACION,
} Estado;

// Estructura de un token
typedef struct {
    TokenTipo tipo;
    char lexema[100];
} Token;

// Funciones del scanner
Token obtenerToken();
Columna obtenerColumna(char c);
bool error_asignacion(char char_ant, char c, bool* dos_puntos_sin_igual);
bool strings_iguales(char * s1, char* s2);
char* clasificarPuntuacion(char lexema[100]);
char* clasificarOperador(char lexema[100]);
char* clasificarErrorAsignacion(char lexema[100]);

#endif