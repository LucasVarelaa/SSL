#include "scanner.h"
#include "parser.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main() {
    setvbuf(stdout, NULL, _IONBF, 0);
    parser();
    return 0;
}