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
    // TODO update groups
    return s;
}
