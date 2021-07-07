//
// Created by jonas on 07.07.2021.
//
#include "problem4.h"

/* Move generation */

/*
 * Generate moves uniformly at random
 * Status: TENTATIVE, NEEDS_TESTING
 * Notes:
 *   Move (i,j) such that i != j. Order is irrelevant and not enforced.
 */
/* old code template
static int is_valid_move(struct move *v, const struct solution *s) {
    //TODO
    return true;

}
struct move *randomMove(struct move *v, const struct solution *s) {
    int n = s->n;
    do {
        v->data[0] = randint(n-1);
        v->data[1] = randint(n-1);
    } while(!is_valid_move(v, s));
    return v;
}*/
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

struct move *randomMoveWOR(struct move *v, struct solution *s) {
    //TODO
    return NULL;
}

double *getObjectiveIncrement(double *obji, struct move *v, struct solution *s) {
    //TODO
    return NULL;
}
