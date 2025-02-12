# TP6 - Compilador para Lenguaje Mini

## Descripción
Este proyecto consiste en crear un compilador tipo transpiler para el lenguaje mini plus, que genere código en lenguaje C. El objetivo principal es afianzar el conocimiento del analizador semántico y la generación de código. Además de las funcionalidades del TP5, el compilador incluirá rutinas semánticas de control y generación de código, asegurando que las variables sean correctamente declaradas y utilizadas, y reportando errores léxicos, sintácticos y semánticos.

## Estructura del Proyecto
- `main.c:` Punto de entrada del programa. Llama al parser y muestra el informe final de la ejecución.
- `scanner.l:` Definición del escáner utilizando Flex. Se encarga de la tokenización del código fuente.
- `parser.y:` Definición del parser utilizando Bison. Se encarga de analizar la estructura gramatical del código fuente.
- `semantic.c` y `semantic.h:` Rutinas semánticas para el control y generación de código.
- `symbol.c` y `symbol.h:` Implementación del diccionario de símbolos, que gestiona las declaraciones y usos de variables.
- `makefile:` Instrucciones para compilar todo el proyecto utilizando make.