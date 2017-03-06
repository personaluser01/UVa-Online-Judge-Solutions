 /*
 * 812. Trade on Verweggistan
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <limits.h>
#include <float.h>
#define N 64
typedef long long i64;

int m,n[N],c[N][N],cs,adj[N][N],deg[N];
i64 z[N][N],w[N],*ptr,s[1 << 19];

void rec( int k, i64 num ) {
	int i;
	while ( k <= m && !deg[k] ) ++k;
	if ( k == m+1 ) {
		*ptr++ = num;
		return ;
	}
	for ( i = 0; i < deg[k]; ++i )
		rec(k+1,num+adj[k][i]);
}

int cmp( const void *a, const void *b ) {
	int *x = (int *)a,
		*y = (int *)b;
	if ( *x == *y )
		return 0;
	return *x < *y ? -1:1;
}

int main() {
	i64 i,j,k,profit;
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	for (;1 == scanf("%d",&m) && m;) {
		if ( cs ) putchar('\n');
		for ( profit = 0, i = 1; i <= m; ++i ) {
			scanf("%d",n+i);
			for ( j = 1; j <= n[i]; ++j )
				scanf("%d",&c[i][j]);
			for ( j = 1; j <= n[i]; ++j )
				z[i][j] = z[i][j-1]+(10-c[i][j]);
			for ( k = -(1<<29), j = 1; j <= n[i]; ++j )
				if ( z[i][j] > k )
					k = z[i][j];
			deg[i] = 0;
			if ( (w[i] = k) < 0 ) 
				continue ;
			for ( j = 1; j <= n[i]; ++j )
				if ( z[i][j] == k )
					adj[i][deg[i]++] = j;
			profit += w[i];
		}
		printf("Workyards %d\n",++cs);
		printf("Maximum profit is %lld.\n",profit);
		printf("Number of pruls to buy:");
		ptr = s, rec(1,0);
		assert( ptr>s );
		qsort(s,ptr-s,sizeof *s,cmp);
		for ( j = 0, k = -1, i = 0; i < ptr-s && j < 10; ++i )
			if ( s[i] != k ) printf(" %lld",s[i]), k = s[i], ++j;
		putchar('\n');
	}
	return 0;
}

