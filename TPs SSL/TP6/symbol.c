#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symbol.h"

#define MAX_SYMBOLS 100

static Symbol symbolTable[MAX_SYMBOLS];
static int symbolCount = 0;

void initSymbolTable() {
    symbolCount = 0;
}

int addSymbol(const char* name) {
    // Verificar si el símbolo ya existe
    for (int i = 0; i < symbolCount; i++) {
        if (strcmp(symbolTable[i].name, name) == 0) {
            return 0; // Símbolo ya declarado
        }
    }
    
    // Agregar nuevo símbolo
    if (symbolCount < MAX_SYMBOLS) {
        symbolTable[symbolCount].name = strdup(name);
        symbolTable[symbolCount].declared = 1;
        symbolTable[symbolCount].initialized = 0;
        symbolCount++;
        return 1;
    }
    return 0;
}

int isDeclared(const char* name) {
    for (int i = 0; i < symbolCount; i++) {
        if (strcmp(symbolTable[i].name, name) == 0) {
            return 1;
        }
    }
    return 0;
}

void freeSymbolTable() {
    for (int i = 0; i < symbolCount; i++) {
        free(symbolTable[i].name);
    }
    symbolCount = 0;
}
