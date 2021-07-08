#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <gsl/gsl_rng.h>
#include "s3problem.h"
#include "ils.h"

gsl_rng *rng;    /* The single rng instance used by the whole code */

int main(int argc, char **argv) {
    struct problem *p;
    int max_iter, i;
    double cost, mincost;

    if (argc < 3) {
        fprintf(stderr, "Usage: %s <num nodes> <max iter>\n", argv[0]);
        return 0;
    }

    /* Set up random number generation */
    rng = gsl_rng_alloc(gsl_rng_mt19937); 
    gsl_rng_set(rng, time(0));

    /* Input arguments */
    max_iter = atoi(argv[2]);

    /* Problem and solver instantiation */
    p = newProblem(argv[1]);
    if (p != NULL) {
        printProblem(p);

        /* Clean up */
    }
    struct solution *s = allocSolution(p);
    if (s != NULL) {
        randomSolution(s);
        printSolution(s);
    }
    freeProblem(p);
    freeSolution(s);
    gsl_rng_free(rng);
    return 0;
}