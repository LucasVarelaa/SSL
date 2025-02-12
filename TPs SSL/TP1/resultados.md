1) gcc *.c -o prog
   
2) tabla.c: In function 'imprimir_tabla':
    tabla.c:9:44: warning: implicit declaration of function 'nudos_a_kmh' [-Wimplicit-function-declaration]
        9 |         printf("|%10.2f  |%10.4f  |\n", i, nudos_a_kmh(i));
         |                                            ^~~~~~~~~~~
    main

Al no incluir "conversion.h" la funcion "nudos_a_kmh" deja de estar declarada por lo que se genera un error tipo warning el cual indica que 
existe un llamado a una funcion "nudos_a_kmh" a la cual no se le encuentra su previa declaracion. 
Este error es detectado en la linea 9 por el parser 

3) c:/mingw/bin/../lib/gcc/mingw32/9.2.0/../../../../mingw32/bin/ld.exe: C:\Users\Usuario\AppData\Local\Temp\ccszO8as.o:main.c:(.text+0xd2)  undefined reference to `imprimir_tabla'
collect2.exe: error: ld returned 1 exit status

Al no incluir "tabla.c" el compilador no encuentra referencia a “imprimir_tabla” en las bibliotecas o en los archivos objetos por lo que se produce el error de referencia indefinida durante el proceso de enlace. Este error es detectado en la línea 25 por el linker. 
 
4)	gcc -E conversion.c -o conversion.i 
