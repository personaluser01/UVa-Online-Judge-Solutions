/*
 * 11632. Elias Gamma Coding
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
#define N 0x100
#define K 16
#define oo 0xfffffffful

int n,c[N],pref[N];
int sum( int i, int j ) { return pref[j]-pref[i-1]; }
unsigned int z[130][130],w;

int main() {
	int i,j,k,t;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for( ;1 == scanf("%d",&n) && n; ) {
		for ( i = 1; i <= n; ++i ) 
			scanf("%d",&c[i]), pref[i] = pref[i-1]+c[i];
		for ( i = 1; i <= n; ++i )
			for ( k = 0; k <= n; ++k )
				z[i][k] = +oo;
		for ( k = 0; k <= n; ++k ) z[0][k] = 0;
		for ( i = 1; i <= n; ++i )
			for ( k = 1; k <= i; ++k )
				for ( t = 0; t <= i-1; ++t )
					if ( z[i-t-1][k-1] < +oo )
						if ( z[i][k] > sum(i-t,i)*(k+i)+z[i-t-1][k-1] )
							z[i][k] = sum(i-t,i)*(k+i) + z[i-t-1][k-1];
		for ( w = +oo, k = 0; k <= n; ++k )
			if (w>z[n][k])
				w = z[n][k];
		printf("%u\n",w);
	}
	return 0;
}
