#include <stdio.h>
#include "tabla.h"
#include "conversion.h"

void imprimir_tabla(double inicio, double fin, double incremento) {
    
    printf("|   nudos    |   kmh      |\n");
    for (double i = inicio; i < fin; i += incremento) {
        printf("|%10.2f  |%10.4f  |\n", i, nudos_a_kmh(i));
    }
}
