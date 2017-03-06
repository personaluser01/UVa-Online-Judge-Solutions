/*
 * 10271. Chopsticks
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
#define K 0x400
#define N 5001
#define oo 0xfffffffful
#define SQ(x) ((x)*(x))

int m,n,c[N];
unsigned int z[K][N][2],w;

unsigned int min( unsigned int x, unsigned int y ) { return x < y ? x : y; }

int main() {
	int ts,i,j,k;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( scanf("%d",&ts); ts-- && scanf("%d %d",&m,&n) == 2; ) {
		for ( m += 8, i = 1; i <= n; scanf("%d",&c[i++]) );
		for ( i = 1, j = n; i < j; ++i, --j )
			k = c[i], c[i] = c[j], c[j] = k;
		for ( i = 1; i <= n-1; ++i )
			assert( c[i] >= c[i+1] );
		memset(z,0xffull,sizeof(z));
		for ( i = 0; i <= n; z[0][i++][0] = 0 );
		for ( i = 2; i <= n; ++i ) 
			for ( k = 1; k <= m; ++k ) {
				z[k][i][0] = min(z[k][i-1][0],z[k][i-1][1]);
				if ( (w = min(z[k-1][i-2][0],z[k-1][i-2][1])) < +oo && i-2*k >= k  )
					z[k][i][1] = SQ(c[i]-c[i-1]) + w;
			}
		printf("%u\n",min(z[m][n][0],z[m][n][1]));
	}
	return 0;
}
