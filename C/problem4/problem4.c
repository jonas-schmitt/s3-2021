
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "s3include.h"

struct problem {
    double *matrix;
    int n;
};

struct solution {
    struct problem *prob;
    int *data;
    int **groups;
    int *groupsizes;
    int n;
    int objvalue;
};

struct move {
    struct problem *prob;
    int data[2];
};



/**********************************/
/* ----- Utility functions ----- */
/**********************************/

#if 0
/*
 * Random integer x such that 0 <= x <= n_max
 * Status: FINAL
 */
static int randint(int n_max) {
    int x;
    if (n_max < 1)
        return 0;
    div_t y = div(-RAND_MAX-1, -n_max-1);
    do
        x = random();
    while (x > RAND_MAX + y.rem);
    return x / y.quot;
}
#else
#include <gsl/gsl_rng.h>
extern gsl_rng *rng;    /* The single rng instance used by the whole code */

static int randint(int n_max) {
    return gsl_rng_uniform_int(rng, n_max+1);
}
#endif


/**********************************************/
/* ----- Problem-specific instantiation ----- */
/**********************************************/

struct problem *newProblem(const char *filename) {
    struct problem *p = NULL;
    //TODO get number of vertices
    int n = 0;
    if (n > 0) {
        p = (struct problem *) malloc(sizeof (struct problem));
        p->n = n;
        p->matrix = (double *)malloc((n * n / 2 - n) * sizeof(double));
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
    s->groupsizes = (int *)malloc(n * sizeof(int));
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
    free(s->groupsizes);
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

/* Solution generation */

/*
 * Generate solutions uniformly at random
 * Status: CHECK
 */
struct solution *randomSolution(struct solution *s) {
    /* solution s must have been allocated with allocSolution() */
    int n = s->n;
    for(int i = 0; i < n; ++i) {
        s->data[i] = randint(n-1);
    }
    // TODO assign vertices to groups
    return s;
}


/* Solution inspection */

/*
 * Solution evaluation
 * Status: INTERIM
 * Notes:
 *   Implements incremental evaluation for multiple moves
 */
double getObjectiveValue(struct solution *s) {
    //TODO
    return 0.0;
}

/* Operations on solutions*/
struct solution *copySolution(struct solution *dest, const struct solution *src) {
    dest->prob = src->prob;
    dest->n = src->n;
    memcpy(dest->data, src->data, src->n * sizeof (int));
    // TODO copy group data
    dest->objvalue = src->objvalue;
    return dest;
}

/*
 * Apply a move to a solution
 * Status: FINAL
 */
struct solution *applyMove(struct solution *s, const struct move *v) {
    int i, j;
    i = v->data[0];
    j = v->data[1];
    s->data[i] = j;
    // TODO update groups
    return s;
}

/* Move generation */

/*
 * Generate moves uniformly at random
 * Status: TENTATIVE, NEEDS_TESTING
 * Notes:
 *   Move (i,j) such that i != j. Order is irrelevant and not enforced.
 */
static int is_valid_move(struct move *v, const struct solution *s) {
    //TODO
    return true;

}
struct move *randomMove(struct move *v, const struct solution *s) {
    /* move v must have been allocated with allocMove() */
    int n = s->n;
    do {
        v->data[0] = randint(n-1);
        v->data[1] = randint(n-1);
    } while(!is_valid_move(v, s));
    return v;
}

struct move *randomMoveWOR(struct move *v, struct solution *s) {
    //TODO
    return NULL;
}

double *getObjectiveIncrement(double *obji, struct move *v, struct solution *s) {
    //TODO
    return NULL;
}