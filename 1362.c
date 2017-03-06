/*
 * 1362. Exploring Pyramids
 * TOPIC: dp, tree traversal, stacks, dfs
 * status: Accepted
 */
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MOD (1000000000LL)
#define N 0x200
typedef long long i64;

char s[N];
int n;
i64 z[N][N];

int main() {
	int i,j,k,t;
#ifndef ONLINE_JUDGE
	freopen("c.txt","r",stdin);
#endif
	for (;fgets(s+1,sizeof s,stdin); printf("%lld\n",z[1][n]) ) {
		for ( n = 0; s[n+1] && s[n+1] != '\n'; ++n );
		for ( i = 0; i <= n; ++i ) for ( j = 0; j <= n; z[i][j++] = 0 );
		for ( i = 1; i <= n; z[i][i] = 1LL, ++i );
		for ( k = 2; k <= n; ++k )
			for ( i = 1; (j=(i+k-1)) <= n; ++i )
				for ( t = i+1; t <= j; ++t )
					if ( s[i] == s[t] )
						if ( (z[i][j] += z[i+1][t-1]*z[t][j]) >= MOD )
							z[i][j] %= MOD;
	}
	return 0;
}

