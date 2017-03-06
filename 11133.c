/*
 * 11133. Eigensequences
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define M 45
typedef long long i64;

int divisor[M][M*M],*ptr[M];
i64 z[M][M][M+8];

int main() {
	int i,j,k,ts,cs,t,l;
	i64 ax,a,b,n;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( n = 1; n < M; ++n )
		for ( ptr[n] = divisor[n], k = 1; k <= n; ++k )
			if ( !(n % k) && (*ptr[n]++ = k) );
	for ( i = 0; i < M; ++i )
		for ( j = i+1; j < M; ++j )
			if ( !(j % (j-i)) )
				z[i][j][2] = 1;
	for ( n = 3; n < M+8; ++n )
		for ( i = 0; i < M; ++i )
			for ( j = i+1; j < M; ++j )
				for ( l = 0; l < ptr[j]-divisor[j]; ++l )
					t = j-divisor[j][l], z[i][j][n] += z[i][t][n-1];
	while ( 2 == scanf("%lld %lld",&a,&b) && (a < b) ) {
		assert( 0 <= a );
		assert( b <= 44 );
		for ( ax = 0, n = 2; n <= b-a+1; ++n )
			ax += z[a][b][n];
		printf("%lld %lld %lld\n",a,b,ax);
	}
	return 0;
}

