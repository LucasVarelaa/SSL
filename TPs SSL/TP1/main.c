#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "tabla.h"

int main(int argc, char const *argv[])
{

    if (argc < 3) {
        printf("Uso: %s <inicio> <fin> [incremento]\n", argv[0]);
        return 1;
    }

    double inicio = atof(argv[1]);
    double fin = atof(argv[2]);

    // Valor predeterminado
    double incremento = 1;
    if (argc >= 4) {
        incremento = atof(argv[3]);
    }

    if (incremento <= 0) {
        printf("El incremento no es válido, se establecerá en 1 por defecto.\n");
        incremento = 1;
    }

    assert(inicio < fin);

    imprimir_tabla(inicio, fin, incremento);

    return 0;
}
