/*
 * Huge Mods
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 128
typedef long long i64;

i64 f( i64 x, const i64 a, const i64 m ) {
	return (a*x) % m;
}

i64 find_period( const i64 a, const i64 m ) {
	i64 x = a,lambda,mu,i,
		y = f(x,a,m),period;
	if ( x == y )
		return 1;
	assert( x != y );
	for ( lambda = 1; x != y; y = f(f(y,a,m),a,m), x = f(x,a,m), ++lambda );
	assert( x == y );
	printf("Here %lld\n",lambda);
	for ( i = lambda, x = a, y = a; i--; y = f(y,a,m) );
	assert( x == y );
	/*for ( *pre_period = 0; x != y; x = f(x,a,m), y = f(y,a,m), ++(*pre_period) );*/
	for ( period = 1, x = f(x,a,m); x != y; x = f(x,a,m), ++period );
	return period;
}

i64 mypow( i64 a, i64 n, i64 p ) {
	i64 x = 1;
	while ( n ) {
		if ( n & 1 )
			x *= a, x %= p;
		n >>= 1, x *= x, x %= p;
	}
	return x;
}

i64 rec( i64 *d, int n, i64 m ) {
	0[d] %= m;
	if ( n == 1 || !0[d] )
		return 0[d];
	assert( n > 1 );
	return mypow(0[d],rec(d+1,n-1,find_period(0[d],m)),m);
}

int main() {
	int ts = 0,n;
	i64 a[N],M,i,j,k,m;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	while ( 1 == scanf("%lld",&M) ) {
		scanf("%d",&n);
		for ( i = 0; i < n; scanf("%lld",a+i), ++i );
		printf("Case #%d: ",++ts);
		printf("%lld\n",rec(a,n,M));
	}
	return 0;
}
