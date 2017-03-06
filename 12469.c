/*
 * 12469. Stones
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
#define N 0x400
#define M N
#define oo 0xfffffffful

unsigned int z[2][N][M];

int f( int n, int t, int m ) {
	int k;
	if ( z[t][n][m] < +oo )
		return z[t][n][m];
	for ( k = 1; k <= 2*m && k <= n; ++k )
		if ( f(n-k,t^1,k) == t )
			return z[t][n][m] = t;
	return z[t][n][m] = t^1;
}

int main() {
	int i,j,k,t,n;
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	memset(z,0xfful,sizeof(z));
	while ( 1 == scanf("%d",&n) && n > 0 ) {
		for ( k = 1; k <= n-1; ++k )
			if ( f(n-k,1,k) == 0 ) {
				puts("Alicia");
				goto next;
			}
		puts("Roberto");
next: continue ;
	}
	return 0;
}

