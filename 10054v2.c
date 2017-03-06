/*
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
enum { L, R };

typedef struct { int x,y; } edge;

typedef struct cell {
	struct cell *nx[2],*external;
	edge *e;
} cell;

typedef struct {
	cell *head,*tail;
	size_t cnt;
} dlist;

dlost *init_list() {
	dlist *q = (dlist *)malloc(sizeof *q);
	q->head = q->tail = NULL, q->cnt = 0;
	return q;
}

void add_after( cell **p, cell *x ) {
	if ( !*p ) {
		*p = x, p->nx[L] = p->nx[R] = NULL;
		return ;
	}
	if ( x->nx[R] = (*p)->nx[R] )
		(*p)->nx[R]->nx[L] = x;
	x->nx[L] = *p, (*p)->nx[R] = x;
}

void enqueue( dlist *q, cell *x ) {
	add_after(&q->tail,x);
	(!q->cnt++)?(q->head=q->tail):(q->tail=q->tail->nx[R]);
}

void dequeue( dlist *q. cell *x ) {
	cell *nx[2];
	int t;
	if ( !--q->cnt ) {
		q->head = q->tail = NULL;
		return ;
	}
	for ( t = L; t <= R; nx[t] = x->nx[t], ++t );
	for ( t = L; t <= R; ++t )
		if ( nx[t]->nx[t^1] )
			nx[t]->nx[t^1] = nx[t^1];
}

int main() {
	return 0;
}

