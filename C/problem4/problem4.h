/* s3problem.h
 *
 * (C) 2021 Carlos M. Fonseca <cmfonsec@dei.uc.pt>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or (at
 * your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */

/* SIGEVO Summer School modifications to the nasf4nio API*/


/**********************************/
/* ----- Utility functions ----- */
/**********************************/

#ifndef PROBLEM4_H
#define PROBLEM4_H
#include "s3problem.h"

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

static double randdouble(int n_min, int n_max){
    return gsl_rng_uniform(rng)*(n_max-n_min)+n_min;
}
#endif

struct problem {
    double *matrix;
    int n;
};

struct solution {
    struct problem *prob;
    int *data;
    int **groups;
    int *group_sizes;
    int *group_capacities;
    int n;
    double objvalue;
    int *rndSample;
    int sampleLim;
};

struct move {
    struct problem *prob;
    int data[2];
    double incrvalue;
};

int index_calc(int i, int j, int n) {
    if (i > j) {
        int tmp = i;
        i = j;
        j = tmp;
    }
    int index = 0;
    for(int k = 1; k < i+1; ++k) {
        index += n - k;
    }
    index += j - i - 1;
    //return i*(n-1-i) + j-i;
    return index;
}
#endif
