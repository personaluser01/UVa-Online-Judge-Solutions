/*
 * 1388. Graveyard
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <limits.h>
#include <float.h>
#define N 0x400*2
typedef long long i64;
#define pi (2*acos(0.0))

i64 m,n;
long double k,l,S,a[N],b[N];

long double f( long double x, long double y ) {
	if ( x > y )
		return f(y,x);
	assert( x <= y );
}

int main() {
	int i,j;
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	for ( S = 10000; 2 == scanf("%lld %lld",&n,&m); ) {
		if ( m == n ) {
			puts("0.0");
			continue ;
		}
		k = S/n, l = S/(m+n);
		for ( i = 0; i < n; ++i )
			x[i] = 2*pi*i/n;
		for ( j = 0; j < m+n; ++j )
			y[j] = 2*pi*j/(n+m);
	}
	return 0;
}

