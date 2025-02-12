#include "scanner.h"
int TOKEN;
char *token_names[] = {"Fin de archivo", "Fin", "Programa", "Entero", "Leer", "Escribir", "Asignacion", "Identificador", "Constante"};

int main()
{
do
	{
		TOKEN = yylex();
		if(0 <= TOKEN && TOKEN <= ASIGNACION){
			// Muestro el TOKEN correspondiente a la gramatica
			printf("Token: %s\n",token_names[TOKEN]);
		}
		else if(TOKEN == IDENTIFICADOR || TOKEN == CONSTANTE){
			// Ademas del TOKEN , aca muestro el lexema que corresponde
			printf("Token: %s	lexema: %s\n",token_names[TOKEN],yytext);
		}
		else{
			// Si es solo un caracter el TOKEN, muestro ese caracter
			printf("Token: \'%c\'\n",TOKEN);
		}
	} while(TOKEN != FDT);

	return EXIT_SUCCESS;
}
