/*
 * 1510. Neon Signs
 * TOPIC: combinatorics, counting strategies, dp
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef long long i64;
#define N 0x400
enum { SOLID, DASHED };
enum { LESS, GREATER };

int g[N][N],n;
i64 c[N][2][2],ans;

int main() {
	int i,j,k,l,t,ts;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( scanf("%d",&ts); ts-- && 1 == scanf("%d",&n); ) {
		for ( i = 0; i < n-1; ++i ) 
			for ( j = i+1; j < n; ++j )
				scanf("%d",&g[i][j]), g[j][i] = g[i][j];
		for ( i = 0; i < n; ++i )
			for ( t = 0; t < 2; ++t )
				for ( k = 0; k < 2; ++k )
					c[i][t][k] = 0;
		for ( i = 0; i < n; ++i ) {
			for ( j = 0; j < i; ++j )
				++c[i][g[i][j]][0];
			for ( j = i+1; j < n; ++j )
				++c[i][g[i][j]][1];
		}
		for ( ans = 0, i = 0; i < n; ++i )
			ans += (c[i][SOLID][GREATER]*(c[i][SOLID][GREATER]-1))/2;
		for ( i = 0; i < n; ++i )
			ans += (c[i][DASHED][GREATER]*(c[i][DASHED][GREATER]-1))/2;
		for ( k = 0; k < n; ++k )
			ans += (c[k][DASHED][LESS]*(c[k][DASHED][LESS]-1))/2;
		for ( k = 0; k < n; ++k )
			ans += (c[k][SOLID][LESS]*(c[k][SOLID][LESS]-1))/2;
		for ( j = 0; j < n; ++j )
			ans -= c[j][DASHED][GREATER]*c[j][SOLID][LESS];
		for ( j = 0; j < n; ++j )
			ans -= c[j][SOLID][GREATER]*c[j][DASHED][LESS];
		printf("%lld\n",ans/2);
	}
	return 0;
}

