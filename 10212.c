/*
 * 10212. The Last Non-Zero Digit
 * blinkovua@info.sgu.ru
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define Q (1 << 24)
typedef long long i64;

i64 n,m,q,ax,L;

i64 deg( i64 n, i64 p ) {
	i64 q = p,ax = 0;
	for (;p <= n; ax += n/p, p *= q );
	return ax;
}

i64 mypow( i64 x, i64 n, i64 p ) {
	i64 ax = 1;
	while ( n ) {
		if ( n & 1 )
			ax *= x, ax %= p;
		x *= x,  n >>= 1, x %= p;
	}
	return ax;
}

unsigned char a[Q];
#define SET(k,x)  ( a[(k)>>2] |= ((x) << (2*((k) & 3))) )
#define TST(k)  ( (a[(k)>>2] >> (2*((k) & 3))) & 3 )

i64 f( i64 r ) {
	while ( !(r & 1) ) r /= 2;
	while ( !(r % 5) ) r /= 5;
	return r % 5;
}

int main() {
	i64 i,j,k,t,res,r;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( SET(1,0), n = 2; (n >> 2) < Q; ++n ) {
		for ( m = n; !(m % 2); m >>= 1 );
		for ( ; !(m % 5); m /= 5 );
		m %= 5;
		k = (TST(n-1)+1)*m, k %= 5;
		assert( k != 0 );
		SET(n,k-1);
	}
	L = n;
	while ( 2 == scanf("%lld %lld",&n,&m) ) {
		if ( n == m ) {
			i = deg(n,2), j = deg(n,5);
			if ( i < j ) j -= i, i = 0;
			else i -= j, j = 0;
			if ( n < L )
				k = TST(n)+1;
			else {
				for ( k = TST(L-1)+1, r = L; r <= n; ++r )
					k *= f(r), k %= 5;
			}
			ax = (6*k+5) % 10;
		}
		else {
			i = deg(n,2) - deg(n-m,2);
			j = deg(n,5) - deg(n-m,5);
			if ( i < j ) j -= i, i = 0;
			else i -= j, j = 0;
			if ( n < L )
				k = TST(n)+1;
			else {
				for ( k = TST(L-1)+1, r = L; r <= n; ++r )
					k *= f(r), k %= 5;
			}
			if ( n-m < L )
				t = TST(n-m)+1;
			else {
				for ( t = TST(L-1)+1, r = L; r <= n-m; ++r )
					t *= f(r), t %= 5;
			}
			if ( t == 1 ) t = 1;
			else if ( t == 2 ) t = 3;
			else if ( t == 3 ) t = 2;
			else
				assert( t == 4 );
			ax = (t*k*6+5) % 10;
		}
		if ( i + j == 0 )
			printf("%lld\n",ax);
		else if ( i == 0 )
			printf("%lld\n",(ax*5) % 10 );
		else {
			i %= 4;
			if ( i == 1 )
				printf("%lld\n",(ax*2) % 10 );
			else if ( i == 2 )
				printf("%lld\n",(ax*4) % 10 );
			else if ( i == 3 )
				printf("%lld\n",(ax*8) % 10 );
			else printf("%lld\n",(ax*6) % 10 );
		}
	}
	return 0;
}
