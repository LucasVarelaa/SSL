#include "parser.h"


Token token_actual;

static bool debo_escanear = true;



char* textoDelToki[]={
    "TOKEN_IDENTIFICADOR",
    "TOKEN_CONSTANTE",
    "TOKEN_OPERADOR",
    "TOKEN_PUNTUACION",
    "TOKEN_ASIGNACION",
    "TOKEN_ERROR_GENERAL",
    "TOKEN_ERROR_ASIGNACION",
    "TOKEN_EOF",
    "TOKEN_PROGRAMA",
    "TOKEN_ENTERO",
    "TOKEN_LEER",
    "TOKEN_ESCRIBIR",
    "TOKEN_FIN",
    "TOKEN_PUNTO_Y_COMA",
    "TOKEN_COMA",
    "TOKEN_PARENTESIS_ABRE",
    "TOKEN_PARENTESIS_CIERRA",
    "TOKEN_ERROR"
};

void parser(void) {
    programa();
    Match(TOKEN_EOF);
    printf("fin\n");
}

void programa(void) {
    Match(TOKEN_PROGRAMA); 
    Match(TOKEN_IDENTIFICADOR); 
    printf("Programa: %s\n",token_actual.lexema);
    listaSentencias();
    Match(TOKEN_FIN); 
}


void listaSentencias(void) {
    do{
        sentencia();
    }while(token_actual.tipo != TOKEN_FIN);
}


void sentencia(void) {
    token_actual = prox_token();
    switch(token_actual.tipo)
    {
        case TOKEN_ENTERO:  
            Match(TOKEN_ENTERO);
            Match(TOKEN_IDENTIFICADOR);
            if(token_actual.tipo == TOKEN_IDENTIFICADOR){
                printf("Sentencia declaracion\n");
            }
            break;

        case TOKEN_LEER: 
            Match(TOKEN_LEER);
            if(token_actual.tipo == TOKEN_LEER){
                printf("Sentencia leer\n");
            }
            Match(TOKEN_PARENTESIS_ABRE);
            listaIdentificadores();
            Match(TOKEN_PARENTESIS_CIERRA);
            break;

        case TOKEN_ESCRIBIR: 
            Match(TOKEN_ESCRIBIR);
            if(token_actual.tipo == TOKEN_ESCRIBIR){
                printf("Sentencia escribir\n");
            }
            Match(TOKEN_PARENTESIS_ABRE);
            listaExpresiones();
            Match(TOKEN_PARENTESIS_CIERRA);
            break;

        case TOKEN_IDENTIFICADOR: 
            Match(TOKEN_IDENTIFICADOR);
            Match(TOKEN_ASIGNACION);
            if(token_actual.tipo == TOKEN_ASIGNACION){
                printf("Sentencia asignacion\n");
            }
            expresion();
            break;

        case TOKEN_FIN:
            break;

        default:
            if(!es_error(token_actual.tipo) && !strings_iguales(token_actual.lexema,"fin")){
               
                error_sintactico(token_actual);
            }
            break;
    }

    if(token_actual.tipo != TOKEN_FIN)
        Match(TOKEN_PUNTO_Y_COMA);
}


void listaIdentificadores(void) {
    Match(TOKEN_IDENTIFICADOR);
    token_actual = prox_token();
    while(token_actual.tipo == TOKEN_COMA){ 
        Match(TOKEN_COMA);
        Match(TOKEN_IDENTIFICADOR);
    }
}

void listaExpresiones(void) {
    expresion();
    token_actual = prox_token();
    while(token_actual.tipo == TOKEN_COMA){ 
        Match(token_actual.tipo);
        expresion();
    }
}

void expresion(void) {
    termino();
    token_actual = prox_token();
    while(token_actual.tipo == TOKEN_OPERADOR && (strings_iguales(token_actual.lexema,"+") || strings_iguales(token_actual.lexema,"-"))){
        Match(token_actual.tipo); 
        termino();
    }
}

void termino(void) {
    primaria();
    token_actual = prox_token();
    while(token_actual.tipo == TOKEN_OPERADOR && (strings_iguales(token_actual.lexema,"/") || strings_iguales(token_actual.lexema,"*") || strings_iguales(token_actual.lexema,"%"))){
        Match(token_actual.tipo);
        primaria();
    } 
}

void primaria(void) {
    token_actual = prox_token();
    switch (token_actual.tipo)
    {
        case TOKEN_IDENTIFICADOR: 
            Match(TOKEN_IDENTIFICADOR);
            break;
        case TOKEN_CONSTANTE:
            Match(TOKEN_CONSTANTE);
            break;
        case TOKEN_PARENTESIS_ABRE:
            Match(TOKEN_PARENTESIS_ABRE); 
            expresion(); 
            Match(TOKEN_PARENTESIS_CIERRA);
            break;
        case TOKEN_OPERADOR:
            if (strings_iguales(token_actual.lexema, "-"))
            {
                Match(TOKEN_OPERADOR); 
                expresion();
            }
            else {error_sintactico(token_actual);}
        break;
         
        default:
            if(!es_error(token_actual.tipo))
                error_sintactico(token_actual);
            break;
    }
}


Token prox_token(void)
{
	if (debo_escanear) {
		token_actual = obtenerToken();
        if (token_actual.tipo == TOKEN_IDENTIFICADOR || token_actual.tipo == TOKEN_PUNTUACION) {
            token_actual.tipo=esReservada(token_actual.lexema);
        }   

		debo_escanear = false;
	}

	return token_actual;
}

void Match(TokenTipo tok)
{
    Token auxiliar = prox_token();
    if (tok!= auxiliar.tipo)
		error_sintactico(auxiliar);
	debo_escanear = true;
}

TokenTipo esReservada(char *tok) {
    if (strcmp(tok, "programa")==0) {return TOKEN_PROGRAMA;}
    else {if (strcmp(tok, "entero")==0) {return TOKEN_ENTERO;}
    else {if (strcmp(tok, "leer")==0) {return TOKEN_LEER;}
    else {if (strcmp(tok, "escribir")==0) {return TOKEN_ESCRIBIR;}
    else {if (strcmp(tok, "fin")==0) {return TOKEN_FIN;}
    else {if (strcmp(tok, ";")==0) {return TOKEN_PUNTO_Y_COMA;}
    else {if (strcmp(tok, ",")==0) {return TOKEN_COMA;}
    else {if (strcmp(tok, "(")==0) {return TOKEN_PARENTESIS_ABRE;}
    else {if (strcmp(tok, ")")==0) {return TOKEN_PARENTESIS_CIERRA;}
    else {return TOKEN_IDENTIFICADOR;}}}}}}}}}
}


void error_sintactico(Token token){
    switch (token.tipo)
    {
    case TOKEN_ERROR_GENERAL:
        printf("Error general: '%s'\n", token.lexema);
        break;
    
    case TOKEN_ERROR_ASIGNACION:
        printf("%s\n",clasificarErrorAsignacion(token.lexema));
        break;
    default:
        printf("Error Sintactico, no se esperaba el token %s ('%s')\n",textoDelToki[token_actual.tipo],token.lexema);
        break;
    }
}


bool es_error(TokenTipo token) {
    return (token == TOKEN_ERROR_GENERAL || token == TOKEN_ERROR_ASIGNACION);
}


// gcc *.c -o programa
// Get-Content entradaerr.txt | ./programa.exe > salidaerr.txt