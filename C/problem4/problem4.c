#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "s3problem.h"


#include <gsl/gsl_rng.h>
extern gsl_rng *rng;    /* The single rng instance used by the whole code */

static int randint(int n_max) {
    return gsl_rng_uniform_int(rng, n_max+1);
}


struct edge {
    int index;
    int weight;
}

struct problem {
    struct edge *edge_list;
    int number_of_nodes;
};

struct solution {
    struct problem *prob;
    int n;
    int objvalue;
    int number_of_groups;
};

struct move {
    struct problem *prob;
    int exchange_group[2];
};


struct problem *newProblem(int n) {
    struct problem *p = NULL;
    if (n > 0) {
        p = (struct problem *) malloc(sizeof (struct problem));
        p->number_of_nodes = n;
        p->edge_list = (struct edge *) malloc(n*(n+1)/2 * sizeof(struct edge));
        init_table(p->edge_list, n);
    } else
        fprintf(stderr, "problem4: Invalid number of nodes: %d\n", n);
    return p;
}

static int index_calc(int a, int b) {
    return a + 10*b;
}

static void init_table(struct edge *edge_list, int number_of_nodes) {
    int i, j, k = 0;
    
    for(i = 0; i < number_of_nodes; ++i) {
        for(j = i+1; j < number_of_nodes; ++j) {
            edge_list[k].index = index_calc(i,j);
            edge_list[k].weight = randint(i);

            ++k;
        }
    }
}

int getNumObjectives(const struct problem *p) {
    return 1;
}

void freeProblem(struct problem *p) {
    free(p->edge_list);
    free(p);
}