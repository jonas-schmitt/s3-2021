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

#include "problem.h"


/* Problem instantiation and inspection */
struct problem *newProblem(const char *filename);

int getNumObjectives(const struct problem *p);


/* Memory Management */
struct solution *allocSolution(struct problem *p);
struct move *allocMove(struct problem *p);

void freeProblem(struct problem *p);
void freeSolution(struct solution *s);
void freeMove(struct move *v);


/* Reporting */
void printProblem(struct problem *p);
void printSolution(struct solution *s);
void printMove(struct move *v);


/* Operations on solutions */
struct solution *randomSolution(struct solution *s);
struct solution *copySolution(struct solution *dest, const struct solution *src);
double *getObjectiveVector(double *objv, struct solution *s);
struct solution *applyMove(struct solution *s, const struct move *v);
int getNeighbourhoodSize(struct solution *s);
struct solution *resetRandomMoveWOR(struct solution *s);


/* Operations on moves */
struct move *randomMove(struct move *v, const struct solution *s);
struct move *copyMove(struct move *dest, const struct move *src);
double *getObjectiveIncrement(double *obji, struct move *v, struct solution *s);
struct move *randomMoveWOR(struct move *v, struct solution *s);