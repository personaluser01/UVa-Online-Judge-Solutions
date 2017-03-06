/*
 * 991. Safe Salutations
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
#define N 0x40
typedef long long i64;

int n;
i64 c[N][N],v[2*N];

int main() {
	int i,j,k,l,t,cs = 0;
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	for ( i = 0; i < N; c[i++][0] = 1 );
	for ( i = 1; i < N; ++i )
		for ( j = 1; j < N; ++j )
			c[i][j] = c[i-1][j]+c[i-1][j-1];
	for ( v[0] = 1, v[2] = 1, n = 2; n < N; ++n )
		for ( i = 0; 2*i+2 <= 2*n; ++i )
			v[2*n] += v[2*i]*v[2*n-2*i-2];
	while ( 1 == scanf("%d",&n) ) {
		if ( ++cs > 1 ) putchar('\n');
		printf("%lld\n",v[2*n]);
	}
	return 0;
}

