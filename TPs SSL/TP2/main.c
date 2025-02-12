#include "scanner.h"
#include "string.h"
#include <stdio.h>

int main() {
    Token token;
    do {
        token = obtenerToken();
        if (token.tipo == TOKEN_EOF) break;

        printf("%s '%s'\n", 
            token.tipo == TOKEN_IDENTIFICADOR ? "Identificador" :
            token.tipo == TOKEN_CONSTANTE ? "Constante" :
            token.tipo == TOKEN_OPERADOR ? clasificarOperador(token.lexema) :
            token.tipo == TOKEN_PUNTUACION ? clasificarPuntuacion(token.lexema) :
            token.tipo == TOKEN_ASIGNACION ? "Asignación" :
            token.tipo == TOKEN_ERROR_GENERAL ? "Error General" :
            token.tipo == TOKEN_ERROR_ASIGNACION ? clasificarErrorAsignacion(token.lexema) :
            token.tipo == TOKEN_EOF ? "EOF" : "Desconocido", token.lexema);

            
        }   while (token.tipo != TOKEN_EOF);
        
        return 0;
        
} 