#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "problem4.h"


static void init_matrix(double *matrix, int number_of_nodes) {
    int i, j;

    for(i = 0; i < number_of_nodes; ++i) {
        for(j = i+1; j < number_of_nodes; ++j) {
            // TODO fix this to the generation of double values
            matrix[index_calc(i, j, number_of_nodes)] = randint(i);
        }
    }
}

struct problem *newProblem(const char *filename) {
    struct problem *p = NULL;
    //TODO get number of vertices
    int n = 0;
    if (n > 0) {
        p = (struct problem *) malloc(sizeof (struct problem));
        p->n = n;
        //TODO handle uneven numbers
        p->matrix = (double *)malloc((n * n / 2 - n) * sizeof(double));
        init_matrix(p->matrix, n);
        //TODO initialize
    } else
        fprintf(stderr, "problem4: Invalid number of vertices: %d\n", n);
    return p;
}

int getNumObjectives(const struct problem *p) {
    return 1;
}

/*****************************/
/* ----- API functions ----- */
/*****************************/

/* Memory management */

/*
 * Allocate memory for a solution
 * Status: CHECK
 */
struct solution *allocSolution(struct problem *p) {
    int n = p->n;
    struct solution *s = (struct solution *)malloc(sizeof (struct solution));
    s->prob = p;
    s->data = (int *)malloc(n * sizeof (int));
    s->groups = (int **)malloc(n * sizeof (int *));
    // TODO alloc memory for groups
    s->group_sizes = (int *)malloc(n * sizeof(int));
    s->group_capacities = (int *)malloc(n * sizeof(int));
    s->n = n;
    return s;
}

/*
 * Allocate memory for a move
 * Status: FINAL
 */
struct move *allocMove(struct problem *p) {
    struct move *v = malloc(sizeof (struct move));
    v->prob = p;
    return v;
}

/*
 * Free the memory used by a problem
 * Status: FINAL
 */
void freeProblem(struct problem *p) {
    free(p->matrix);
    free(p);
}

/*
 * Free the memory used by a solution
 * Status: FINAL
 */
void freeSolution(struct solution *s) {
    free(s->data);
    // TODO free individual groups
    free(s->groups);
    free(s->group_sizes);
    free(s->group_capacities);
    free(s);
}

/*
 * Free the memory used by a move
 * Status: FINAL
 */
void freeMove(struct move *v) {
    free(v);
}

/* I/O  */
void printProblem(struct problem *p) {
    //TODO
}

void printSolution(struct solution *s) {
    //TODO
}

void printMove(struct move *v) {
    printf("%d-member community detection move: %d, %d\n", v->prob->n, v->data[0], v->data[1]);
}

