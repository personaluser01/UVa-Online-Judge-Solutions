/*
 * 11510. Erdos Unit Fractions
 * TOPIC: number theorey, diophantine equations
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef long long i64;

i64 max( i64 x, i64 y ) { return x<y?y:x; }

i64 gcd( i64 x, i64 y ) { return !y ? x:gcd(y,x%y); }

i64 n,x,y,z,p,q,r,ok,X,Y,Z;

int main() {
	while ( 1 == scanf("%lld",&n) && n > 0 ) {
		for ( ok = 0, x = (X = n/4); x <= 3*X+1 && !ok; ++x ) {
			if ( 4*x <= n || 4*x > 3*n ) continue ;
			for ( y = max((Y = (n*x)/(4*x-n)),x); y <= 2*Y+1 && !ok; ++y ) {
				p = 4*x*y-n*x-n*y;
				if ( p <= 0 ) continue ;
				q = n*x*y;
				r = gcd(p,q);
				p /= r, q /= r;
				if ( p == 1 ) { z = q; ok = 1; break; }
			}
			if ( ok ) break ;
		}
		printf("%lld %lld %lld\n",x,y,z);
	}
	return 0;
}

