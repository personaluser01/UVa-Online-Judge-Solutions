/*
 * 11338. Minefield
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <limits.h>
#include <float.h>
#define tol 1e-9
#define N 10100
#define xchg(x,y) (((x)==(y))||((x)^=(y),(y)^=(x),(x)^=(y)))
#define bubble (xchg(pos[heap[i]],pos[heap[j]]),xchg(heap[i],heap[j]))
#define oo (DBL_MAX-1024)
#define MAXE (1 << 19)
#define S(x) ((x)*(x))

typedef struct { long double x,y; } cell;

cell c[N];
int n,width,height,pos[N],cnt,heap[2*N],
	next[MAXE],last[N],to[MAXE],E;
long double Limit,d[N],r[MAXE];

void push( int x ) {
	int i,j;
	if(pos[x]<0) pos[heap[cnt]=x]=cnt,++cnt;
	for(j=pos[x];j&&d[heap[i=(j-1)>>1]]>d[heap[j]];bubble,j=i);
}

void pop( int *x ) {
	int i,j;
	if ( x ) *x = *heap;
	if ( --cnt )
		pos[heap[0] = heap[cnt]] = 0;
	for ( j = 0; (i = j, j <<= 1, ++j) <= cnt-1; bubble ) {
		if ( j < cnt-1 && d[heap[j+1]] < d[heap[j]] ) ++j;
		if ( d[heap[i]] <= d[heap[j]] ) break ;
	}
}

long double dijkstra( int src, int dst ) {
	int i,x,y;
	for ( x = 0; x < n; ++x ) d[x] = +oo, pos[x] = -1;
	for ( cnt = 0, d[src] = 0, push(src); cnt && d[dst] > Limit; )
		for ( pop(&x), i = last[x]; i >= 0 && d[x] <= Limit; i = next[i] ) 
			if ( d[y = to[i]] > d[x]+r[i] )
				d[y] = d[x]+r[i], push(y);
	return d[dst];
}

int main() {
	int i,j,k,l,t;
	long double w;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for (;2 == scanf("%d %d",&width,&height);) {
		for ( scanf("%d",&n), i = 1; i <= n; ++i )
			scanf("%Lf %Lf",&c[i].x,&c[i].y);
		c[0].x = c[0].y = 0, c[n+1].x = width, c[n+1].y = height, n += 2;
		for ( i = 0; i < n; last[i++] = -1 );
		for ( E = 0, i = 0; i < n; ++i )
			for ( j = i+1; j < n; ++j ) {
				w = S(c[i].x-c[j].x)+S(c[i].y-c[j].y);
				if ( w <= 9.0/4.0 ) {
					to[k = E++] = j, to[t = E++] = i;
					r[k] = r[t] = sqrt(w);
					next[k] = last[i], next[t] = last[j];
					last[j] = t, last[i] = k;
				}
			}
		scanf("%Lf",&Limit),puts(dijkstra(0,n-1)<=Limit?"I am lucky!":"Boom!");
	}
	return 0;
}

