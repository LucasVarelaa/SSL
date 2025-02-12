%top{
    #include <stdio.h>
    #include "parser.h"
    extern int errores_lexicos;
}

%option header-file="scanner.h"
%option outfile="scanner.c"
%option noinput
%option nounput
%option noyywrap
%option yylineno

Letra                           [[:alpha:]]
Digito                          [0-9]
Letra_Digito                    [[:alnum:]]
Espacio                         [[:space:]]
OperadorAsignacion             ":="
Comentario                      "//".*
Fin                            "fin"
Otros                          [[:punct:]]{-}[();,+\-*/%]

%%
programa                                                    { return PROGRAMA; }
{Fin}                                                       { return FIN; }
entero                                                      { return ENTERO; }
leer                                                        { return LEER; }
escribir                                                    { return ESCRIBIR; }
{Letra}{Letra_Digito}*                                      { yylval.str = strdup(yytext); return IDENTIFICADOR; }
{Digito}+                                                   { yylval.valor = atoi(yytext); return CONSTANTE; }
"("                                                         { return '('; }
")"                                                         { return ')'; }
","                                                         { return ','; }
"+"                                                         { return '+'; }
"-"                                                         { return '-'; }
"*"                                                         { return '*'; }
"/"                                                         { return '/'; }
"%"                                                         { return '%'; }
";"                                                         { return ';'; }
{OperadorAsignacion}                                        { return ASIGNACION; }
{Otros}+                                                    {printf("linea #%d: Error lexico: asignacion mal formada: %s\n", yylineno, yytext);
                                                             errores_lexicos++;}
{Letra}{Letra_Digito}*{Otros}+({Letra_Digito}|{Otros})*     {printf("linea #%d: Error lexico: identificador invalido: %s\n", yylineno, yytext);
                                                             errores_lexicos++;}
{Digito}+{Letra}+{Letra_Digito}*                            {printf("linea #%d: Error lexico: constante invalida: %s\n", yylineno, yytext);
                                                             errores_lexicos++;}
{Espacio}+                                                  |
{Comentario}                                                ;
%%