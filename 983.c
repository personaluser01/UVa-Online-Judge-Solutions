/*
 * 983. Localized Summing for Blurring
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
#define N 0x400
typedef long long i64;

i64 m,n,g[N][N],z[N][N],r[N][N];

i64 area( int a, int b, int c, int d ) {
	return z[c][d]-z[a-1][d]-z[c][b-1]+z[a-1][b-1];
}

int main() {
	int i,j,k,l,t,cs = 0;
	i64 sum;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	while ( 2 == scanf("%lld %lld",&n,&m) ) {
		if ( ++cs > 1 ) putchar('\n');
		for ( i = n; i >= 1; --i )
			for ( j = 1; j <= n; ++j )
				scanf("%lld",&g[i][j]);
		for ( i = 1; i <= n; ++i )
			for ( j = 1; j <= n; ++j )
				z[i][j] = z[i-1][j]+z[i][j-1]-z[i-1][j-1]+g[i][j];
		for ( k = 1, i = 1; i <= n-m+1; ++i, ++k )
			for ( t = 1, j = m; j <= n; ++j, ++t )
				r[k][t] = area(i,j-m+1,i+m-1,j);
		for ( sum = 0, i = k-1; i >= 1; --i )
			for ( j = 1; j < t; ++j )
				printf("%lld\n",r[i][j]), sum += r[i][j];
		printf("%lld\n",sum);
	}
	return 0;
}
