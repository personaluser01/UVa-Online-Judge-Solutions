/*
 * 10827. Maximum Sum on a Torus
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 512
#define oo (1 << 29)
#define el(k) (colsum[k][l]-colsum[k][i-1])
#define valid_cell(x,y) (1 <= (x) && (x) <= m && 1 <= (y) && (y) <= n)

int n,c[N][N],colsum[N][N],z[N][N];

int g( int i, int j, int l, int k ) {
	return z[l][k]-z[i-1][k]-z[l][j-1]+z[i-1][j-1];
}

int max( int x, int y ) {
	if ( x < y ) return y;
	return x;
}

int f( int m, int n, int L ) {
	int i,j,k,l,t,s,
		a = -oo, 
		b = -oo,
		maxsum = 0;
	for ( j = 1; j <= n; ++j )
		for ( i = 1; i <= m; ++i )
			colsum[j][i] = colsum[j][i-1] + c[i][j];
	for ( i = 1; i <= m; ++i )
		for ( j = 1; j <= n; ++j )
			z[i][j] = z[i-1][j]+z[i][j-1]-z[i-1][j-1]+c[i][j];

	for ( t = 1; t <= L; ++t )
		for ( i = 1; (l = i+t-1) <= m; ++i ) {
			for (a = -oo, k = 1; k <= n;) 
				for ( s = 0; s >= 0 && k <= n; a = max(a,s+=el(k)), ++k );
			for (b = -oo, k = 1; k <= n;)
				for ( s = 0; s >= 0 && k <= n; b = max(b,s-=el(k)), ++k );
			maxsum = max(maxsum,max(a,g(i,1,l,n)+b));
		}
	return maxsum;
}

int main() {
	int i,j,l,k,t,s,maxsum,ts;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( scanf("%d",&ts); ts--; ) {
		for ( scanf("%d",&n), i = 1; i <= n; ++i )
			for ( j = 1; j <= n; ++j )
				scanf("%d",c[i]+j);
		for ( i = n+1; i <= 2*n; ++i )
			for ( j = 1; j <= n; ++j )
				c[i][j] = c[i-n][j];
		printf("%d\n",f(2*n,n,n));
	}
	return 0;
}
