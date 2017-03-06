#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 8
#define M 128
typedef long long i64;

i64 n,k,W,
	C[M][M],
	cut[N+1][2][2*(N+1)];

void rec( i64 n, i64 k, int idx, i64 w, int t ) {
	int i;
	if ( k ) {
		for ( i = idx; i <= 2*n-2; ++i )
			rec(n,k-1,i+1,w*cut[n][t][i],t);
	}
	else W += w;
}

int main() {
	i64 i,j;
	for ( i = 0; i < M; C[i++][0] = 1 );
	for ( i = 1; i < M; ++i )
		for ( j = 1; j <= i; ++j )
			C[i][j] = C[i-1][j] + C[i-1][j-1];

	for ( n = 1; n <= N; ++n )
		for ( i = 0; i <= 2*n-2; ++i )
			for ( j = 0; j <= 2*n-2; ++j )
				if ( i+j >= n-1 )
					if ( j-i <= n-1 )
						if ( (i+j-n-1) % 2 == 0 )
							if ( (i-j+n-1) % 2 == 0 )
								++cut[n][((i+j)&1)][i];

	while ( 2 == scanf("%lld %lld",&n,&k) && (n||k) ) {
		W = 0, rec(n,k,0,1,1-(n&1));
		for ( i = 0; i <= 2*n-2; ++i )
			printf("%lld ",cut[n][1-(n&1)][i]);
		puts("");
		printf("%lld\n",W);
	}
	return 0;
}

