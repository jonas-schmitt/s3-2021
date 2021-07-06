#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "s3problem.h"


struct problem {
    double **matrix;
    int n;   /* number of nodes */
};

struct solution {
    struct problem *prob;
};

struct move {
    struct problem *prob;
};


int getNumObjectives(const struct problem *p) {
    return 1;
}