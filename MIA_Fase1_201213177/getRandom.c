#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "getRandom.h"

int getRandom(){

    time_t t;

    srand((unsigned) time(&t));

    int r = rand() % 500;

    return r;
}