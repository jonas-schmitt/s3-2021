//
// Created by jonas on 07.07.2021.
//
#include <string.h>
#include "problem4.h"

/* Move generation */

/*
 * Generate moves uniformly at random
 * Status: TENTATIVE, NEEDS_TESTING
 * Notes:
 *   Move (i,j) such that i != j. Order is irrelevant and not enforced.
 */
/* old code template

struct move *randomMove(struct move *v, const struct solution *s) {
    int n = s->n;
    do {
        v->data[0] = randint(n-1);
        v->data[1] = randint(n-1);
    } while(!is_valid_move(v, s));
    return v;
}*/

static int is_valid_move(struct move *m, const struct solution *s) {
    //TODO
    if(m->data[0] == m->data[1]){
        return 0;
    }

    return 1;
} 

struct move *randomMove(struct move *m, const struct solution *s) {
    /* move v must have been allocated with allocMove() */
    int n;

    n = s->n;
    m->data[0] = randint(n-1);

    do{
        m->data[1] = randint(n-1);
    }while(!is_valid_move(m, s));

    printf("%d, %d", m->data[0], m->data[1]);

    return m;
}

static void swap(int i, int sampleLim, int *rndSample){
    int temp;

    temp = s->rndSample[i];
    s->rndSample[temp] = s->rndSample[s->sampleLim];
    s->rndSample[s->sampleLim] = temp;
}

struct move *randomMoveWOR(struct move *m, struct solution *s) {
    int r;

    if(s->sampleLim <= 1) 
        return NULL;

    r = randint(--s->sampleLim);
    m->data[0] = s->rndSample[r];
    swap(r, s->sampleLim, s->rndSample);

    --s->sampleLim;
    
    do{
        r = randint(s->sampleLim);
        m->data[1] = s->rndSample[r];
    }while(!is_valid_move(m,s));

    swap(r, s->sampleLim, s->rndSample);
    
    return m;
}

double *getObjectiveIncrement(double *obji, struct move *m, struct solution *s) {
    int i,j;

    if (m->data[0] < m->data[1]) {   
        i = m->data[0];
        j = m->data[1];
    } else {
        i = m->data[1];
        j = m->data[0];
    }
    
    return NULL;
}
struct move *copyMove(struct move *dest, const struct move *src){
    //TODO I think you just have to copy the pointer, but not the whole problem - Jonas
    memcpy(dest->prob, src->prob, sizeof(dest->prob));
    memcpy(dest->data, src->data, sizeof(dest->data));

    return dest;
}
