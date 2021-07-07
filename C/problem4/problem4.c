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
    double *edge_list;
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
    int data[2];
};


static int index_calc(int i, int j, int n) {
    return i*(n-1-i) + j-i;
}

static void init_matrix(double *edge_list, int number_of_nodes) {
    int i, j;
    
    for(i = 0; i < number_of_nodes; ++i) {
        for(j = i+1; j < number_of_nodes; ++j) {
            *(edge_list + index_calc(i,j, number_of_nodes)) = randint(i);
        }
    }
}

struct problem *newProblem(int n) {
    struct problem *p = NULL;
    int i;

    if (n > 0) {
        p = (struct problem *) malloc(sizeof (struct problem));
        p->number_of_nodes = n;
        p->edge_list = (double *) malloc(((n+1)*(n/2)-n) * sizeof(double)); //upper triangular matrix without diagonal

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
    double *list = p->edge_list;

    for(i = 0; i < p->number_of_nodes; ++i) {
        for(j = i+1; j < p->number_of_nodes; ++j) {
            printf("(%d,%d) = %lf\n", i, j, *(list + index_calc(i,j,p->number_of_nodes)));
        }
    }
}

void freeProblem(struct problem *p) {
    int i;

    free(p->edge_list);
    free(p);
}

struct move *randomMove(struct move *m, const struct solution *s) {
    /* move v must have been allocated with allocMove() */
    int n;

    n = s->n;
    m->data[0] = randint(n-1);
    
    do{
        m->data[1] = randint(n-1);

        if(m->data[0] != m->data[1]){
            break;
        }
    }while(1);

    printf("%d, %d", m->data[0], m->data[1]);

    return m;
}


/* TODO */

struct solution *allocSolution(struct problem *p){
    return NULL;
}

struct move *allocMove(struct problem *p){
    return NULL;
}

void freeSolution(struct solution *s){
    return;
}

void freeMove(struct move *v){
    return;
}

void printSolution(struct solution *s){
    return;
}

void printMove(struct move *v){
    return;
}


struct solution *randomSolution(struct solution *s){
    return NULL;
}

struct solution *copySolution(struct solution *dest, const struct solution *src){
    return NULL;
}

double *getObjectiveVector(double *objv, struct solution *s){
    return NULL;
}

struct solution *applyMove(struct solution *s, const struct move *v){
    return NULL;
}

int getNeighbourhoodSize(struct solution *s){
    return 0;
}

struct solution *resetRandomMoveWOR(struct solution *s){
    return NULL;
}

struct move *copyMove(struct move *dest, const struct move *src){
    return NULL;
}

double *getObjectiveIncrement(double *obji, struct move *v, struct solution *s){
    return NULL;
}

struct move *randomMoveWOR(struct move *v, struct solution *s){
    return NULL;
}


/* Compiler says this is undefined, not sure if needed */
struct solution *randomNeighbour(struct solution *s, int d){
    return NULL;
}