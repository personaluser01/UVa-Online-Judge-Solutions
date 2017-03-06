/*
 * 11930. Rectangles
 * TOPIC: scc, 2-sat
 * status:
 */
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define var(i) ((i)<<1)
#define neg(i) (var(i)|1)
typedef long long i64;
typedef struct { i64 x,y; } cell;
#define MAXE (1<<18)
#define N 0x400
enum { D, T };

cell c[N][4];
int n,to[2][MAXE],next[2][MAXE],last[2][N],E[2];

void add_arcs( int x, int y ) {
	int i = E[0]++, j = E[1]++;
	to[D][i] = y, next[D][i] = last[D][x], last[D][x] = i;
	to[T][j] = x, next[T][j] = last[T][y], last[T][y] = j;
}

int intersect( cell a, cell b, cell p, cell q ) {
	cell m,n;
	i64 det,dt,dtau;
	m.x = b.x-a.x, m.y = b.y-a.y;
	n.x = q.x-p.x, n.y = q.y-p.y;

	det = -m.x*n.y+n.x*m.y;
}

int main() {
	int i,j,k;
#ifndef ONLINE_JUDGE
	freopen("11930.in","r",stdin);
#endif
	for ( ;1==scanf("%d",&n) && n>0; ) {
		for ( i = 0; i < n; ++i ) 
			for ( j = 0; j < 4; ++j )
				scanf("%lld %lld",&c[i][j].x,&c[i][j].y);
		for ( E[D]=E[T]=0, i=0; i<n; ++i ) {
			k = var(i), last[D][k] = last[T][k] = -1;
			k = neg(i), last[D][k] = last[T][k] = -1;
		}
		for ( i = 0; i < n; ++i )
			for ( j = 0; j < n; ++j ) {
				if ( i == j ) continue ;
				if ( intersect(c[i][0],c[i][2],c[j][0],c[j][2]) )
					add_arcs(var(i),neg(j));
				if ( intersect(c[i][1],c[i][3],c[j][0],c[j][2]) )
					add_arcs(neg(i),neg(j));
				if ( intersect(c[i][0],c[i][2],c[j][1],c[j][3]) )
					add_arcs(var(i),var(j));
				if ( intersect(c[i][1],c[i][3],c[j][1],c[j][3]) )
					add_arcs(neg(i),var(j));
			}
	}
	return 0;
}

