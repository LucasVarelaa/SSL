#include "conversion.h"

// relacion entre nudo y kmh: 1 nudo = 1.852 kmh
double nudos_a_kmh(double nudos){
    return nudos * NUDOS_A_KM;
}
