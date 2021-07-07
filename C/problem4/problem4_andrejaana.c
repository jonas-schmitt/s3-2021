//
// Created by jonas on 07.07.2021.
//
#include <string.h>
#include "problem4.h"
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
