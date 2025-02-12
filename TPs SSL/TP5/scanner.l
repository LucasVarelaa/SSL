%{
    #include <stdio.h>
    #include "parser.h"
    char msg[120];
    void yyerror(const char *s);

%}

%option header-file="scanner.h"
%option outfile="scanner.c"
%option noinput
%option nounput
%option noyywrap
%option yylineno

Letra                                                        [[:alpha:]]
Digito                                                       [0-9]
Letra_Digito                                                 [[:alnum:]]
Espacio                                                      [[:space:]]
OperadorAsignacion                                           ":="
Otros														 [[:punct:]]{-}[();,+\-*/]
Comentario                                                   "//".*

%%
programa                                                     { return PROGRAMA; }
"fin"                                                        { return FIN; }
"entero"                                                     { return ENTERO; }
"leer"                                                       { return LEER; }
"escribir"                                                   { return ESCRIBIR; }
{Letra}{Letra_Digito}*                                       { yylval.str = strdup(yytext); return IDENTIFICADOR; } /* quite el .str */
{Digito}+                                                    { yylval.valor = atoi(yytext); return CONSTANTE; }
"("                                                          { return '('; }
")"                                                          { return ')'; }
","                                                          { return ','; }
"+"                                                          { return '+'; }
"-"                                                          { return '-'; }
"*"                                                          { return '*'; }
"/"                                                          { return '/'; }
"%"                                                          { return '%'; }
";"                                                          { return ';'; }
{OperadorAsignacion}                                         { return ASIGNACION; }
{Comentario}                                                 { /* Ignorar comentario    */ }
{Espacio}+                                                   { /* Ignorar espacio       */ }
{Otros}+                                                     { errores_lexicos++; sprintf(msg, "Error léxico: cadena desconocida: %s", yytext); yyerror(msg); }
%%


