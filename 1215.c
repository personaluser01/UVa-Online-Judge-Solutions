/*
 * 1215. String Cutting
 * TOPIC: deque, bitmasks, xor
 * status: Accepted
 */
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 0x400
#define M (1<<16)
#define BIT(k) (1ULL<<(k))
#define MASK(k) (BIT(k)-1ULL)
enum { L, R };

int m,n,c[N];
char s[M],bts[1<<21];

int Bits( unsigned int u ) {
	return bts[u>>20]+bts[u&MASK(20)];
}

typedef struct cell {
	struct cell *nx[2];
	int i,j;
} cell ;

cell pool[M],*ptr = pool;

cell *init( int i, int j ) {
	cell *x = ptr++;
	x->i = i, x->j = j, x->nx[L] = x->nx[R] = NULL;
	return x;
}

void add_after( cell **item, int i, int j ) {
	cell *p = init(i,j);
	if ( !*item )
		*item = p;
	else {
		if ( (*item)->nx[R] )
			(*item)->nx[R]->nx[L] = p, p->nx[R] = (*item)->nx[R];
		(*item)->nx[R] = p, p->nx[L] = *item;
	}
}

typedef struct {
	cell *head,*tail;
	size_t cnt;
} queue;

queue *init_queue() {
	queue *q = (queue *)malloc(sizeof *q);
	q->head = q->tail = NULL, q->cnt = 0;
	return q;
}

void push( queue *q, int i, int j ) {
	add_after(&q->tail,i,j);
	if ( !q->cnt++ )
		q->head = q->tail;
	else q->tail = q->tail->nx[R];
}

int insert( queue *q, int k ) {
	cell *qtr;
	int l = q->cnt,t,cost = 0;
	cell *x,*y,*prev,*next;
	unsigned int u=0,v=0;
	for ( qtr = q->head; l-- && qtr; qtr = qtr->nx[R] ) {
		if ( qtr->i <= k && k < qtr->j ) {
			for ( t = qtr->i; t <= k; ++t )
				u |= BIT(s[t]-'a');
			for ( t = k+1; t <= qtr->j; ++t )
				v |= BIT(s[t]-'a');
			cost += Bits(u^v);
			x = init(qtr->i,k), y = init(k+1,qtr->j);
			prev = qtr->nx[L], next = qtr->nx[R];
			if ( prev ) 
				prev->nx[R] = x, x->nx[L] = prev, x->nx[R] = y, y->nx[L] = x;
			else 
				q->head = x, x->nx[R] = y, y->nx[L] = x;
			if ( next )
				y->nx[R] = next, next->nx[L] = y;
			else 
				q->tail = y;
			++q->cnt;
			return cost;
		}
	}
	assert( 0 );
}

queue *q;

int main() {
	int i,j,k,ts;
#ifndef ONLINE_JUDGE
	freopen("c.txt","r",stdin);
#endif
	for ( k = 0; k < (1<<21); bts[k]=bts[k>>1]+(k&1), ++k );
	for ( scanf("%d\n",&ts); ts--; printf("%d\n",k) ) {
		for ( scanf("%d\n",&n), i = 0; i < n; scanf("%d\n",&c[i++]) );
		scanf("%[^\n]\n",s+1), m = strlen(s+1);
		for ( k=0,q=init_queue(),push(q,1,m),i = 0; i < n; k += insert(q,c[i++]) );
	}
	return 0;
}

