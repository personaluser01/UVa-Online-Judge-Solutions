/*
 * 11478. Halum
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
#define N 0x200
#define M (1 << 20)
#define oo (DBL_MAX-1024)
typedef long long i64;
#define tol 1e-9

int n,E,V,last[N],next[M],to[M],cost[M],m,seen[N][N],yes;
i64 dist[N][N];
double MU,mu;

void add_arcs( int x, int y, int c ) {
	int i = E++,j = E++;
	to[i] = y, next[i] = last[x], last[x] = i, cost[i] = c;
	to[j] = x, next[j] = last[y], last[y] = j, cost[j] = -c;
}

int main() {
	int i,j,k,l,t,x,y;
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	while ( 2 == scanf("%d %d",&n,&m) ) {
		for ( i = 0; i <= n; ++i ) last[i] = -1;
		for ( E = 0, l = 0; l < m; ++l ) {
			scanf("%d %d %d",&i,&j,&k);
			add_arcs(i,j,k);
		}
		for ( i = 1; i <= n; ++i )
			add_arcs(0,i,0);
		for ( seen[0][0] = ++yes, dist[0][0] = 0, k = 1; k <= n+1; ++k )
			for ( i = 0; i < E; i += 2 ) {
				y = to[i], x = to[i^1];
				if ( seen[x][k-1] != yes )
					continue ;
				if ( seen[y][k] != yes || dist[y][k] > dist[x][k-1]+cost[i] )
					seen[y][k] = yes, dist[y][k] = dist[x][k-1]+cost[i];
			}
		for ( mu = +oo, x = 1; x <= n; ++x )
			if ( seen[x][n+1] == yes ) {
				for ( MU = -oo, k = 0; k <= n; ++k )
					if ( seen[x][k] == yes )
						if ( (dist[x][n+1]-dist[x][k]+0.0)/(n+1-k) > MU )
							MU = (dist[x][n+1]-dist[x][k]+0.0)/(n+1-k);
				if ( MU < mu ) mu = MU;
			}
		if ( fabs(mu-oo) < tol )
			puts("Infinite");
		else if ( mu < 1 )
			puts("No Solution");
		else {
			printf("%lld\n",(i64)(mu+tol));
		}
	}
	return 0;
}

