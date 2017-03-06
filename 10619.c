/*
 * 10619. Advanced Causal MEasurements
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <limits.h>
#include <float.h>
#define N 100100
#define SH 1000000
#define is_cause_for(i,j) (c[i].t>=c[j].t+abs(c[i].x-c[j].x))

int n,m;
typedef struct { int x,t; } cell;

cell c[N];

int cmp( const void *a, const void *B ) {
	cell *A = (cell *)a,
		 *B = (cell *)b;
	return A->x - B->x;
}

int main() {
	int i,j,k;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( ;2 == scanf("%d %d",&n,&m); ) {
		for ( i = 0; i < n; ++i )
			scanf("%d %d",&c[i].t,&c[i].x), c[i].t += SH;
		qsort(c,n,sizeof *c,cmp);
	}
	return 0;
}
