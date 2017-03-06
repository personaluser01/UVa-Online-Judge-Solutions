/*
 * 10951. Polynomial GCD
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 0x100
typedef long long i64;

i64 MOD;

void ext_euclid( i64 x, i64 y, i64 *a, i64 *b, i64 *d ) {
	i64 na,nb;
	if ( !y ) {
		*a = 1, *b = 0, *d = x;
		return ;
	}
	ext_euclid(y,x%y,&na,&nb,d);
	*b = na - (*a = nb)*(x/y);
}

i64 modinv( i64 x, i64 p ) {
	i64 a,b,d;
	assert( p );
	assert( (x % p) != 0 );
	ext_euclid(x,p,&a,&b,&d);
	assert( a*x + b*p == d );
	while ( a < 0 ) a += p;
	a %= p;
	assert( ((x*a) % p) == 1 );
	return a;
}

i64 c[2][N],n[2],res[N],deg;

void printout( i64 *c, i64 n ) {
	i64 i;
	for ( i = n; i; --i )
		printf("%lldx^%lld + ",c[i],i);
	printf("%lldx^%lld\n",c[i],i);
}

void divide_poly( i64 *x, i64 *n, i64 *y, i64 *m ) {
	i64 q[N],i,j,k;

	assert( *n >= *m );
	for ( k = (*n)-(*m); k >= 0; --k ) {
		assert( (y[*m] %= MOD) );
		q[k] = (modinv(y[*m],MOD)*x[k+*m]) % MOD;
		for ( i = *m; i >= 0; x[i+k] %= MOD, --i ) 
			for ( x[i+k] -= q[k]*y[i]; x[i+k] < 0; x[i+k] += MOD );
		assert( x[k+*m] == 0 );
	}
	for (;*n >= 0 && !(x[*n] %= MOD); --(*n) );
	if ( *n < 0 ) *n = 1;
	for (;*m >= 0 && !(y[*m] %= MOD); --(*m) );
	if ( *m < 0 ) *m = 1;
}

void gcd( i64 *x, i64 *n, i64 *y, i64 *m ) {
	i64 i,k;
	assert( *m <= *n );

	divide_poly(x,n,y,m);
	if ( *n == 1 && x[*n-1] == 0 ) {
		for ( deg = *m, k = modinv(y[*m],MOD), i = *m; i >= 0; res[i] = (y[i] *= k), res[i] %= MOD, --i );
		for ( ;deg >= 0 && !res[deg]; --deg );
		return ;
	}
	if ( *n >= *m )
		return gcd(x,n,y,m);
	else return gcd(y,m,x,n);
}

int main() {
	int i,j,k,t,cs = 0;
	i64 ax;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	while ( 1 == scanf("%lld",&MOD) && (MOD) ) {
		for ( t = 0; t <= 1; ++t ) { 
			for ( scanf("%lld",n+t), i = 0; i <= n[t]; c[t][n[t]-i] %= MOD, ++i )
				for ( scanf("%lld",c[t]+n[t]-i); c[t][n[t]-i] < 0; c[t][n[t]-i] += MOD );
			for (;n[t] && !c[t][n[t]]; --n[t] );
			if ( n[t] < 0 ) 
				continue ;
			assert( n[t] >= 0 );
			for ( ax = modinv(c[t][n[t]],MOD), i = 0; i <= n[t]; ++i )
				c[t][i] *= ax, c[t][i] %= MOD;
			assert( c[t][n[t]] == 1 );
		}
		printf("Case %d: ",++cs);
		if ( n[0] < 0 && n[1] < 0 ) {
			assert( 0 );
		}
		else if ( n[0] < 0 ) {
			for ( deg = n[1], i = 0; i <= deg; ++i )
				res[i] = c[1][i];
			goto pr;
		}
		else if ( n[1] < 0 ) {
			for ( deg = n[0], i = 0; i <= deg; ++i )
				res[i] = c[0][i];
			goto pr;
		}
		if ( n[0] < n[1] ) t = 1;
		else t = 0;
		gcd(c[t],n+t,c[1-t],n+1-t);
		pr :
		for ( printf("%lld",deg), i = deg; i >= 0; printf(" %lld",res[i--]) );
		putchar('\n');
	}
	return 0;
}

