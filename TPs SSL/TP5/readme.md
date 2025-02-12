# TP5 - Parser para Lenguaje Mini

## Descripción

Este proyecto implementa un parser para el lenguaje mini utilizando las herramientas Flex y Bison. El parser es capaz de reconocer y procesar declaraciones, sentencias de lectura, escritura y asignación, así como expresiones aritméticas. El objetivo es analizar el código fuente del lenguaje mini y generar una salida que indique el tipo de sentencias y operaciones encontradas, además de reportar errores léxicos y sintácticos.

## Estructura del Proyecto

- `main.c`: Punto de entrada del programa. Llama al parser y muestra el informe final de la ejecución.
- `scanner.l`: Definición del escáner utilizando Flex. Se encarga de la tokenización del código fuente.
- `parser.y`: Definición del parser utilizando Bison. Se encarga de analizar la estructura gramatical del código fuente.
- `makefile`: Instrucciones para compilar el proyecto utilizando `make`.

## Compilación y Ejecución en Windows
```sh
# Compilar el proyecto
make

# Ejecutar el programa con el archivo de entrada correcto y redirigir la salida a un archivo
Get-Content entradaok.txt | .\programa.exe | Set-Content salidaok.txt

# Ejecutar el programa con el archivo de entrada con errores y redirigir la salida a un archivo
Get-Content entradaerr.txt | .\programa.exe | Set-Content salidaerr.txt