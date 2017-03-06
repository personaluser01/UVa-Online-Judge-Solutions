/*
 * 12022. Ordering T-Shirts
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
#define N 0x10
typedef unsigned long long u64;
typedef long long i64;

int n;
i64 C[N][N],deg[N][N],ax;

int main() {
	int i,j,k,ts,m;
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	for ( n = 0; n < N; ++n ) C[n][0] = 1;
	for ( n = 1; n < N; ++n )
		for ( i = 1; i <= n; ++i )
			C[n][i] = C[n-1][i] + C[n-1][i-1];
	for ( k = 1; k < N; ++k )
		for ( deg[k][0] = 1, i = 1; i < N; ++i )
			deg[k][i] = deg[k][i-1]*k;
	for ( scanf("%d",&ts); ts--; ) {
		scanf("%d",&n), ax = 0;
		for ( m = 1; m <= n; ++m )
			for ( k = 0; k <= m; ++k )
				if ( k & 1 )
					ax -= C[m][k]*deg[m-k][n];
				else
					ax += C[m][k]*deg[m-k][n];
		printf("%lld\n",ax);
	}
	return 0;
}

