/*
 * 10688. The Poor Giant
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 512
#define oo 0xfffffffful

unsigned int min( unsigned int x, unsigned int y ) {
	if ( x < y ) return x;
	return y;
}

int n,K;
unsigned int z[N][N],weight[N];

int main() {
	int i,j,k,ts,cs = 0,l,t;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( scanf("%d",&ts); ts--;) {
		printf("Case %d: ",++cs);
		scanf("%d %d",&n,&K);
		for ( i = 1; i <= n; ++i )
			weight[i] = i+K;
		for ( i = 0; i <= n+2; ++i )
			for ( j = 0; j <= n+2; ++j )
				z[i][j] = +oo;
		for ( i = 1; i <= n; ++i )
			z[i][i] = 0;
		for ( i = 1; i+1 <= n; ++i )
			z[i][i+1] = 2*weight[i];
		for ( i = 0; i <= n+2; ++i )
			for ( j = 0; j < i; ++j )
				z[i][j] = 0;
		for ( k = 3; k <= n; ++k )
			for ( i = 1; (j = i+k-1) <= n; ++i )
				for ( t = i; t <= j; ++t )
					if ( z[i][t-1] < +oo && z[t+1][j] < +oo )
						z[i][j] = min(z[i][j],weight[t]*k+z[i][t-1]+z[t+1][j]);
		printf("%u\n",z[1][n]);
	}
	return 0;
}

