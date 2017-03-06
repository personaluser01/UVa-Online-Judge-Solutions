/*
 * 11720. How Many Ways
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define M 64
#define MOD 1000000007LL

typedef long long i64;
i64 n,K,A[M][M],V,v[M],R[M][M],tmp[M][M];

int main() {
	int i,j,k,l,t,ts,x,y;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( scanf("%d",&ts); ts--; ) {
		scanf("%lld %lld",&K,&n), memset(A,0,sizeof(A));
		V = 0, k = 1, v[k] = i = V, j = V+1;
		A[v[k]][j] = A[j][v[k]] = 1, V = ++j;
		A[j-1][V] = A[v[k]][V] = 1;
		for ( k = 2; k <= K; A[v[k++]][V = ++j] = 1 ) 
			for ( v[k] = i = V, j = i+k-1, A[j][i] = 1, l = 0; l < k-1; ++l ) 
				A[i+l][i+l+1] = 1;
		memset(R,0,sizeof(R));
		for ( i = 0; i <= V; ++i ) R[i][i] = 1;
		for ( n -= K*(K+1)/2, n += K; n > 0; n >>= 1 ) {
			if ( n & 1 ) {
				for ( i = 0; i <= V; ++i )
					for ( j = 0; j <= V; ++j )
						for ( tmp[i][j] = 0, k = 0; k <= V; ++k )
							tmp[i][j] += (R[i][k]*A[k][j]) % MOD, tmp[i][j] %= MOD;
				for ( i = 0; i <= V; ++i )
					for ( j = 0; j <= V; ++j )
						R[i][j] = tmp[i][j];
			}
			for ( i = 0; i <= V; ++i )
				for ( j = 0; j <= V; ++j )
					for ( tmp[i][j] = 0, k = 0; k <= V; ++k )
						tmp[i][j] += (A[i][k]*A[k][j]) % MOD, tmp[i][j] %= MOD;
			for ( i = 0; i <= V; ++i )
				for ( j = 0; j <= V; ++j )
					A[i][j] = tmp[i][j];
		}
		printf("%lld\n",R[0][V] % MOD);
	}
	return 0;
}
