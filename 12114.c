/*
 * 12114. Bachelor Arithmetic
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
long double p,q;

i64 m,n;

int main() {
	int cs = 0;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	while ( 2 == scanf("%lld %lld",&m,&n) && (m||n) ) {
		printf("Case %d: ",++cs);
		if ( m == 1 ) {
			puts(":-\\");
			continue ;
		}
		if ( n == 1 ) {
			puts(":-(");
			continue ;
		}
		if ( n >= m ) {
			puts(":-|");
			continue ;
		}
		puts(":-(");
	}
	return 0;
}
