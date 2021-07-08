//
// Created by jonas on 07.07.2021.
//
#include <string.h>
#include <limits.h>
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
        int rand_range = randint(n-1);
        int groupID = randint(rand_range);
        s->data[i] = groupID;
        // assign vertices to groups
        s->groups[groupID][s->group_sizes[groupID]] = s->data[i];
        s->group_sizes[groupID] += 1;
    }
    s->objvalue = getObjectiveValue(s);
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
    // TODO I think this must be changed to getObjectiveVector, sorry for the confusion
    // TODO check whether the objective has been already computed in the solution
    int n = s->n;
    for(int i = 0; i < n; ++i) {
        int groupObjVal = 0;
        for(int j = 0; j < s->group_sizes[i]; ++j) {
            for(int k = j+1; k < s->group_sizes[i]; ++k) {
                // TODO You can just use the index_calc function in problem4.h instead of the code below
                if (j>k) {
                    int tmp = j;
                    j = k;
                    k = tmp;
                }
                groupObjVal += s->prob->matrix[j*(s->n-1-j)+k-j];
            }
        }
        s->objvalue += groupObjVal/2;

    }
    return s->objvalue;
}

/* Operations on solutions*/
struct solution *copySolution(struct solution *dest, const struct solution *src) {
    dest->prob = src->prob;
    dest->n = src->n;
    memcpy(dest->data, src->data, src->n * sizeof (int));
    for(int i = 0; i < src->n; ++i) {
        memcpy(dest->groups[i], src->groups[i], src->group_capacities[i] * sizeof (int));
        dest->group_sizes[i] = src->group_sizes[i];
        dest->group_capacities[i] = src->group_capacities[i];
    }
    dest->objvalue = src->objvalue;
    return dest;
}
