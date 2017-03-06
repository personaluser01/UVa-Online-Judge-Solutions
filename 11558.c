/*
 * 11558. Dinner
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <limits.h>
#include <float.h>
#define N 512
#define LIM ((2.00*n)/3.00)
#define enc(x,y) ((x)|((y)<<9))
#define M(k) ((1UL<<(k))-1UL)
#define oo (1 << 29)

int n,m,yes,deg[N],mi,ma,fe[N][N],g[N][N];
unsigned int adj[N][N];

int cmp( const void *a, const void *B ) {
	unsigned int x = *(unsigned int *)a,
				 y = *(unsigned int *)b;
	if ( x == y ) return 0;
	return x<y?-1:1;
}

int main() {
	int i,j,k,l;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for (;2 == scanf("%d %d",&n,&m) && ++yes;) {
		for ( i = 0; i < n; deg[i++] = 0 );
		mi = +oo, ma = -oo;
		for ( l = 0; l < m; ++l ) {
			scanf("%d %d %d",&i,&j,&k), --i, --j;
			adj[i][deg[i]++] = enc(j,k);
			adj[j][deg[j]++] = enc(i,k);
			if ( mi > k ) mi = k;
			if ( ma < k ) ma = k;
			g[i][j] = g[j][i] = yes;
			fe[i][j] = fe[j][i] = k;
		}
		for ( i = 0; i < n; ++i )
			for ( j = i+1; j < n; ++j )
				if ( g[i][j] != yes ) {
					adj[i][deg[i]++] = enc(j,2008); 
					adj[j][deg[j]++] = enc(i,2008);
					fe[i][j] = fe[j][i] = 2008;					
					g[i][j] = g[j][i] = yes;
				}
		for ( i = 0; i < n; ++i )
			qsort(adj[i],deg[i],sizeof *adj[i],cmp);
		for ( k = mi; k <= ma; ++k ) {
		}
	}
	return 0;
}
