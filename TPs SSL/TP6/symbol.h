#ifndef SYMBOL_H
#define SYMBOL_H

// Estructura para almacenar información de símbolos
typedef struct {
    char* name;
    int declared;    // 1 si está declarada, 0 si no
    int initialized; // 1 si está inicializada, 0 si no
} Symbol;

// Funciones del diccionario de símbolos
void initSymbolTable();
int addSymbol(const char* name);
int isDeclared(const char* name);
void freeSymbolTable();

#endif
