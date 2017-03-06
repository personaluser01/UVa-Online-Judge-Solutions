/*
 * 911. Multinomial Coefficients
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 0x80
typedef unsigned long long i64;

i64 n,K,m[N],c[N][N];

i64 multinom( i64 k, i64 n ) {
	assert( k >= 1 );
	if ( k == 1 ) {
		assert( m[0] == n );
		return 1;
	}
	if ( k == 2 ) {
		assert( m[0]+m[1] == n );
		return c[n][m[0]];
	}
	return c[n][m[k-1]]*multinom(k-1,n-m[k-1]);
}

int main() {
	i64 i,j,k;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( i = 0; i < N; ++i )
		c[i][0] = 1;
	for ( i = 1; i < N; ++i )
		for ( j = 1; j <= i; ++j )
			c[i][j] = c[i-1][j] + c[i-1][j-1];
	while ( 2 == scanf("%llu %llu",&n,&K) ) {
		for ( k = 0, i = 0; i < K; ++i )
			scanf("%llu",m+i), k += m[i];
		assert( k == n );
		printf("%llu\n",multinom(K,n));
	}
	return 0;
}

