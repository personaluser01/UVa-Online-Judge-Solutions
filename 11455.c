/*
 * 11455. Behold My Quadranlge
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

typedef long long i64;
i64 x[4];
int ts;

int main() {
	i64 i,j,k,t,l;
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	for ( scanf("%d",&ts); ts--; ) {
		assert( 4 == scanf("%lld %lld %lld %lld",&i,&j,&k,&l) );
		x[0] = i, x[1] = j, x[2] = k, x[3] = l;
		for ( j = 1; j; )
			for ( j = i = 0; i < 3; ++i )
				if ( x[i] > x[i+1] )
					k = x[i], x[i] = x[i+1], x[i+1] = k, ++j;
		if ( x[0] == x[1] && x[1] == x[2] && x[2] == x[3] )
			puts("square");
		else if ( x[0] == x[1] && x[2] == x[3] )
			puts("rectangle");
		else if ( x[0]+x[1]+x[2] <= x[3] )
			puts("banana");
		else puts("quadrangle");
	}
	return 0;
}

