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
    int group = s->data[m->data[0]];
    int new_group = s->data[m->data[1]];

    if(s->group_sizes[group] <= 1 && s->group_sizes[new_group] <= 1){
        return 0;
    }

    return 1;
} 

struct move *randomMove(struct move *m, const struct solution *s) {
    /* move v must have been allocated with allocMove() */
    int n;

    n = s->n;

    do{
        m->data[0] = randint(n-1);
        m->data[1] = randint(n-1);
    }while(!is_valid_move(m, s));

    return m;
}

static void swap(int i, int sampleLim, int *rndSample){
    int temp;

    temp = rndSample[i];
    rndSample[temp] = rndSample[sampleLim];
    rndSample[sampleLim] = temp;
}

struct move *randomMoveWOR(struct move *m, struct solution *s) {
    int r1, r2;

    if(s->sampleLim <= 1 || s->sampleLimGroup <= 1) 
        return NULL;

    --s->sampleLim;
    --s->sampleLimGroup;
    
    do{
        r1 = randint(s->sampleLim);
        m->data[0] = s->rndSample[r1];

        r2 = randint(s->sampleLimGroup);
        m->data[1] = s->rndSampleGroup[r2];
    }while(!is_valid_move(m,s));

    swap(r1, s->sampleLim, s->rndSample);
    swap(r2, s->sampleLimGroup, s->rndSampleGroup);
    
    return m;
}

struct solution *resetRandomMoveWOR(struct solution *s){
    s->sampleLim = s->n-1;
    return s;
}

static double calc_weight(struct solution *s, int group1, int group2, int node1) {
    int j;
    double weight = 0.0;
    int index = 0;

    for(j = 0; j < s->group_sizes[group1]; ++j) {
        if(s->groups[group1][j] != node1){
            if(node1 < s->groups[group1][j])
                index = index_calc(node1, s->groups[group1][j], s->prob->n);
            else
                index = index_calc(s->groups[group1][j], node1, s->prob->n);

            weight += s->prob->matrix[index];
        }
    }

    for(j = 0; j < s->group_sizes[group2]; ++j) {
        if(s->groups[group2][j] != node1){
            if(node1 < s->groups[group2][j])
                index = index_calc(node1, s->groups[group2][j], s->prob->n);
            else
                index = index_calc(s->groups[group2][j], node1, s->prob->n);
            
            weight += s->prob->matrix[index];
        }
    }

    return weight;
}

double *getObjectiveIncrement(double *obji, struct move *m, struct solution *s) {
    int group1,group2;
    double weight1, weight2;

    group1 = s->data[m->data[0]];
    group2 = m->data[1];

    /* 
       first it is calculated the current weight value of both groups
       next it is calculated the weight after the move occurs
       the difference between both corresponds to the improvement/decrease of the obj function
    */
    weight1 = calc_weight(s, group1, group2, m->data[0]);
    weight2 = calc_weight(s, group2, group1, m->data[0]);
    
    // TO CHECK: only return this?
    *obji = (double)(m->incrvalue = (weight2-weight1));
    return obji;
}
struct move *copyMove(struct move *dest, const struct move *src){
    dest->prob = src->prob;
    dest->data[0] = src->data[0];
    dest->data[1] = src->data[1];
    dest->incrvalue = src->incrvalue;

    return dest;
}

int getNeighbourhoodSize(struct solution *s){
    /* not sure if the neighbor is the number of nodes or number of groups */
    
    //return s->n;

    int n_groups = 0;

    for(int i = 0; i < s->n; ++i){
        if(s->group_sizes[i] > 0){
            ++n_groups;
        }
    }

    return n_groups;
}

double *getObjectiveVector(double *objv, struct solution *s){
    *objv = (double)getObjectiveValue(s);
    return objv;
}
