#ifndef PARSER_H
#define PARSER_H

#include "scanner.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


void parser(void);
void programa(void);
extern Token token_actual;
Token prox_token(void);
TokenTipo esReservada(char* textoDelTokenActual);
void Match(TokenTipo tok);
void listaSentencias(void);
void sentencia(void);
void listaIdentificadores(void);
void listaExpresiones(void);
void expresion(void);
void termino(void);
void primaria(void);
bool es_error(TokenTipo token);
void error_sintactico(Token token);

#endif 