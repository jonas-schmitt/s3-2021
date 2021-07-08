//
// Created by jonas on 07.07.2021.
//
#include "problem4.h"
/*
 * Apply a move to a solution
 * Status: FINAL
 */
struct solution *applyMove(struct solution *s, const struct move *v) {
    int i, j;
    i = v->data[0];
    j = v->data[1];
    s->data[i] = j;
    int k = s->data[i];
    for(int l = 0; l < s->group_sizes[k]; ++l) {
        if(s->groups[k][l] == i) {
            s->group_sizes[k] -= 1;
            s->groups[k][l] = s->groups[k][s->group_sizes[k]];
            break;
        }
    }
    s->groups[j][s->group_sizes[j]] = i;
    s->group_sizes[j]++;
    return s;
}
