#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "problem4.h"


static void init_matrix(double *matrix, int number_of_nodes) {
    int i, j;
    int min = -100, max = 100;

    for(i = 0; i < number_of_nodes; ++i) {
        for(j = i+1; j < number_of_nodes; ++j) {
            // TODO fix this to the generation of double values
            // Print out linearized indices for testing
            // int index = index_calc(i, j, number_of_nodes);
            //printf("(%i, %i): ", i,j);
            //printf("%i\n", index);
            matrix[index_calc(i, j, number_of_nodes)] = randdouble(min, max);
        }
    }
}

//struct problem *newProblem(const char *filename) {
struct problem *newProblem(int n) {
    struct problem *p = NULL;
    //TODO get number of vertices
    if (n > 0) {
        p = (struct problem *) malloc(sizeof (struct problem));
        p->n = n;
        int matrix_size = n*(n-1)/2;
        p->matrix = (double *)malloc(matrix_size * sizeof(double));
        init_matrix(p->matrix, n);
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
    s->n = n;
    s->prob = p;
    s->data = (int *)malloc(n * sizeof (int));
    s->groups = (int **)malloc(n * sizeof (int *));
    s->group_sizes = (int *)malloc(n * sizeof(int));
    s->group_capacities = (int *)malloc(n * sizeof(int));
    // TODO alloc memory for groups
    // TODO choose a smaller initial capacity
    int initial_capacity = n;
    // int initial_capacity = n / 2;
    for(int i = 0; i < n; ++i) {
        // Start simple
        int * ptr = (int *)malloc(initial_capacity*sizeof(int));
        s->groups[i] = ptr;
        s->group_sizes[i] = 0;
        s->group_capacities[i] = n;
    }
    // TODO: alloc memory for rndSample and initialize with nodes
    s->sampleLim = n-1;
    s->rndSample = (int *)malloc(n * sizeof(int));
    for(int i = 0; i < n; ++i) {
        s->rndSample[i] = i;
    }
    for(int i = n - 1; i > 0; --i) {
        int j = randint(i);
        int tmp = s->rndSample[j];
        s->rndSample[j] = s->rndSample[i];
        s->rndSample[i] = tmp;
    }
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
    int n = s->n;
    free(s->data);
    for(int i = 0; i < n; ++i) {
        free(s->groups[i]);
    }
    free(s->groups);
    free(s->group_sizes);
    free(s->group_capacities);
    free(s->rndSample);
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
    int n = p->n;
    printf("  \t");
    for(int i = 0; i < n; ++i) {
        printf( "%i\t", i);
    }
    printf("\n");
    for(int i = 0; i < n; ++i) {
        printf("%i|\t", i);
        for(int j = 0; j < n; ++j) {
            //TODO for now cast to int for better readability
            if (j > i) {
                printf("%i\t", (int)(p->matrix[index_calc(i, j, n)]));
            }
            else {
                printf(" \t");
            }
        }
        printf("\n");
    }
}

void printSolution(struct solution *s) {
    int n = s->n;

    for(int i = 0; i < n; ++i) {
        printf("%i ", s->rndSample[i]);
    }
    printf("\n");
    //TODO print the rest
}

void printMove(struct move *v) {
    printf("%d-member community detection move: %d, %d\n", v->prob->n, v->data[0], v->data[1]);
}

