/*
 * 1233. USHER
 * TOPIC: cycles, floyd-warshall, greedy
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define N 0x200
#define oo (1LL<<43)
typedef long long i64;

int n;
i64 d[N][N],B,c;

int main() {
	int i,j,k,ts;
#ifndef ONLINE_JUDGE
	freopen("1233.in","r",stdin);
#endif
	for ( scanf("%d",&ts); ts-- && 2 == scanf("%lld %d",&B,&n); ) {
		for ( ++n, i = 0; i < n; ++i )
			for ( j = 0; j < n; d[i][j++] = +oo );
		for ( scanf("%d",&k); k-- && 1 == scanf("%d",&i); d[0][i] = 0 );
		for ( i = 1; i < n; ++i ) 
			for ( scanf("%d",&k); k-- && 2 == scanf("%lld %d",&c,&j); d[i][j]=(i==j?+oo:d[i][j]>c?c:d[i][j]) );
		for ( k = 0; k < n; ++k )
			for ( i = 0; i < n; ++i )
				for ( j = 0; j < n; ++j )
					if ( d[i][k] < +oo && d[k][j] < +oo ) 
						if ( d[i][k]+d[k][j] < d[i][j] )
							d[i][j] = d[i][k]+d[k][j];
		if ( (c = d[0][0]) >= B ) {
			puts("0");
			continue ;
		}
		assert( c >= 2 );
		printf("%lld\n",(i64)ceil((B-c+0.00)/(c-1)));
	}
	return 0;
}

