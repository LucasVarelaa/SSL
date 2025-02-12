#ifndef SEMANTIC_H
#define SEMANTIC_H

extern int errores_semanticos;
extern int yylineno;


// Funciones semÃ¡nticas
void iniciarPrograma();
void finalizarPrograma();
void declararVariable(const char* nombre);
void verificarVariable(const char* nombre);
void generarLectura(const char* nombre);
void generarEscritura(const char* expresion);
void generarAsignacion(const char* destino, const char* expresion);
char* nuevoTemporal();
void liberarTemporales();

#endif