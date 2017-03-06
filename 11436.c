/*
 * 11436. Cubes -- EXTREME!!!
 * TOPIC: maths, divisors, quadratic equations
 * status: Accepted
 */
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define tol 1e-13
typedef long long i64;

i64 n;

int find_xy( i64 a, i64 b, i64 *x, i64 *y ) {
	i64 d = a*a+4*b, s = (i64)(sqrt(d)+tol);
	if ( s*s != d ) return 0;
	if ( (a+s)&1 ) return 0;
	*x = (a+s)/2;
	if ( b%(*x) ) return 0;
	*y = b/(*x);
	return 1;
}

int main() {
	int i,j,k;
	i64 a,b,x,y,m,X,Y;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( ;1 == scanf("%lld",&n) && n > 0; ) {
		for ( Y = (1LL<<62), a = 1; a*a <= n/a; ++a ) {
			m = n-a*a*a;
			if ( (m%3) || ((m/3)%a) ) continue ;
			b = m/3/a;
			if ( find_xy(a,b,&x,&y) && y < Y ) X = x, Y = y;
		}
		if ( Y == (1LL<<62) )  {
			puts("No solution");
			continue ;
		}
		else printf("%lld %lld\n",X,Y);
	}
	return 0;
}

