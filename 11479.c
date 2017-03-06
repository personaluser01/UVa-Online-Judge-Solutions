/*
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

i64 c[3];
int cs;

int main() {
	int i,j,k,ts;
	i64 t;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( scanf("%d",&ts); ts--; ) {
		scanf("%lld %lld %lld",c,c+1,c+2);
		printf("Case %d: ",++cs);
		for ( j = 1;j;)
			for ( i = j= 0; i < 2; ++i )
				if ( c[i] > c[i+1] )
					t = c[i], c[i] = c[i+1], c[i+1] = t, ++j;
		if ( c[0] == c[1] && c[1] == c[2] && c[0] > 0 ) {
			puts("Equilateral");
			continue ;
		}
		if ( c[0] <= 0 || c[2]>=c[1]+c[0] ) {
			puts("Invalid");
			continue ;
		}
		if ( c[0] == c[1]||c[1]==c[2] ) {
			puts("Isosceles");
			continue ;
		}
		puts("Scalene");
	}
	return 0;
}
