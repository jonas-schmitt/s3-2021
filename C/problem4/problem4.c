#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "problem.h"
#include "problem4.h"


#include <gsl/gsl_rng.h>
extern gsl_rng *rng;    /* The single rng instance used by the whole code */

static int randint(int n_max) {
    return gsl_rng_uniform_int(rng, n_max+1);
}


struct problem {
    double **edge_list;
    int number_of_nodes;
};

struct solution {
    struct problem *prob;
    int n;
    int *data;
    int objvalue;
    int number_of_groups;
};

struct move {
    struct problem *prob;
    int exchange_group[2];
};


static int index_calc(int a, int b) {
    return a + 10*b;
}

static void init_matrix(double **edge_list, int number_of_nodes) {
    int i, j;
    
    for(i = 0; i < number_of_nodes; ++i) {
        for(j = i+1; j < number_of_nodes; ++j) {
            edge_list[i][j-1] = randint(i);
        }
    }
}

struct problem *newProblem(int n) {
    struct problem *p = NULL;
    int i, j;

    if (n > 0) {
        p = (struct problem *) malloc(sizeof (struct problem));
        p->number_of_nodes = n;
        p->edge_list = (double **) malloc(n * sizeof(double *)); // total size = ((n+1)*(n/2)-n)

        for(i = 0; i < n; ++i) {
            for(j = i; j < n; ++j) {
                p->edge_list[i] = (double *) malloc((n-1-i) * sizeof(double));
            }
        }

        init_matrix(p->edge_list, n);
    } else
        fprintf(stderr, "problem4: Invalid number of nodes: %d\n", n);
    return p;
}

int getNumObjectives(const struct problem *p) {
    return 1;
}

void printProblem(struct problem *p) {
    int i, j;

    for(i = 0; i < p->number_of_nodes; ++i) {
        for(j = i+1; j < p->number_of_nodes; ++j) {
            printf("(%d,%d) = %lf\n", i, j, p->edge_list[i][j-1]);
        }
    }
}

void freeProblem(struct problem *p) {
    int i;

    for(i = 0; i < p->number_of_nodes; ++i) {
        free(p->edge_list[i]);
    }

    free(p->edge_list);
    free(p);
}


/* TODO */

struct solution *allocSolution(struct problem *p);
struct move *allocMove(struct problem *p);

void freeSolution(struct solution *s);
void freeMove(struct move *v);


struct solution *randomSolution(struct solution *s);
struct solution *copySolution(struct solution *dest, const struct solution *src);
double *getObjectiveVector(double *objv, struct solution *s);
struct solution *applyMove(struct solution *s, const struct move *v);
int getNeighbourhoodSize(struct solution *s);
struct solution *resetRandomMoveWOR(struct solution *s);

struct move *randomMove(struct move *v, const struct solution *s);
struct move *copyMove(struct move *dest, const struct move *src);
double *getObjectiveIncrement(double *obji, struct move *v, struct solution *s);
struct move *randomMoveWOR(struct move *v, struct solution *s);