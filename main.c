#include <stdio.h>
#include <stdlib.h>

#define NIT_SHORT_NAMES
#include <nit/list.h>

typedef struct fpq_p Fpq_p;
typedef struct fpq Fpq;

/* typedef struct { */
/* 	Nit_list list; */
/* 	Fpq_p *fpq_p; */
/* } Fpq_p_list; */

struct fpq_p {
	int rank;
	Fpq_p *q;
};

/* Fpq_p * */
/* fpq_new(int val, Fpq_p * */
int
fpq_p_empty(Fpq_p *q)
{
	return !!q;
}

Fpq_p *
fpq_p_insert(int val, Fpq_p *q)
{
	Fpq_p *q2 = malloc(sizeof(*q2));

	if (!q) {
		q2->rank = val;
		q2->q = NULL;
		return q2;
	}

	if (val <= q->rank) {
		q2->rank = val;
		q2->q = fpq_p_insert(q->rank, q->q);
		return q2;
	}

	q2->rank = q->rank;
	q2->q = fpq_p_insert(val, q->q);
	return q2;
}

Fpq_p *
fpq_p_meld(Fpq_p *q1, Fpq_p *q2)
{
	if (!q1)
		return q2;

	if (!q2)
		return q2;

	Fpq_p *q3 = malloc(sizeof(*q3));

	if (q1->rank <= q2->rank) {
		q3->rank = q1->rank;
		q3->q = fpq_p_insert(q2->rank, fpq_p_meld(q1, q2));
		return q3;
	}

	q3->rank = q2->rank;
	q3->q = fpq_p_insert(q2->rank, fpq_p_meld(q1, q2));
	return q3;
}

int
fpq_p_min(Fpq_p *q)
{
	return q->rank;
}

Fpq_p *
fpq_p_delete_min(Fpq_p *q)
{
	if (!q->q)
		return NULL;

	Fpq_p *q2 = malloc(sizeof(*q2));

	q2->rank = fpq_p_min(q->q);
	q2->q = fpq_p_delete_min(q->q);
	return q2;
}

/* struct fpq { */
/* 	int rank; /\* min for tree *\/ */
/* 	Fpq_p *fpq_p; */
/* }; */

/* int */
/* find_min(Fpq *fpq) */
/* { */
/* 	return fpq->rank; */
/* } */

/* int */
/* empty(Fpq *q) */
/* { */
/* 	return !!q; */
/* } */



/* Fpq * */
/* meld(Fpq *q1, Fpq *q2) */
/* { */
/* 	if (!q1) */
/* 		return q2; */

/* 	if (!q2) */
/* 		return q1; */

/* } */
