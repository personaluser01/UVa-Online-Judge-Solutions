/*
 * 10302. Summation of Polynomials
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
enum { BASE = 100000LL, DIGL = 5 };
typedef long long i64;

i64 max( i64 x, i64 y ) {
	return x < y ? y : x;
}

void print( i64 *x ) {
	int i;
	for ( i = *x; i && !x[i]; --i );
	if ( !i ) {
		puts("0");
		return ;
	}
	for ( printf("%lld",x[i]); --i; printf("%0*lld",DIGL,x[i]) );
	putchar('\n');
}

i64 *mult( i64 *x, i64 *y ) {
	i64 *z = (i64 *)calloc(*x+*y+3, sizeof *z);
	int i,j;
	for ( i = 1; i <= *x; ++i )
		for ( j = 1; j <= *y; ++j )
			z[i+j-1] += x[i]*y[j];
	for ( i = 1; i <= *x+*y+1; ++i )
		if ( z[i] >= BASE )
			z[i+1] += z[i]/BASE, z[i] %= BASE;
	for ( *z = *x+*y+1, i = *z; i && !z[i]; --i );
	if ( !i ) *z = 1;
	else *z = i;
	return z;
}

i64 *add( i64 *x, i64 *y ) {
	i64 *z = (i64 *)calloc(max(*x,*y)+2, sizeof *z);
	int i;
	for ( i = 1; i <= *x; ++i )
		z[i] += x[i];
	for ( i = 1; i <= *y; ++i )
		z[i] += y[i];
	for ( *z = max(*x,*y)+1, i = 1; i <= *z; ++i )
		if ( z[i] >= BASE )
			z[i+1] += z[i]/BASE, z[i] %= BASE;
	for ( i = *z; i && !z[i]; --i );
	if ( !i ) *z = 1;
	else *z = i;
	return z;
}

i64 *load( i64 n ) {
	i64 *x = (i64 *)calloc(4, sizeof *x);
	int i = 0;
	do {
		x[++i] = n % BASE, n /= BASE;
	} while(n);
	*x = i;
	return x;
}

void div2( i64 *z ) {
	i64 i,j,k,r;
	for ( i = *z; i && !z[i]; --i );
	if ( !i ) return ;
	for ( k = 0; i; k = r, --i ) {
		r = (BASE*k+z[i]) & 1;
		z[i] = (BASE*k+z[i]) >> 1;
	}
}

int main() {
	i64 *x,*y,*z,n;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	while ( 1 == scanf("%lld",&n) ) {
		x = load(n), y = mult(x,x), z = add(y,x);
		div2(z);
		x = mult(z,z);
		print(x);
	}
	return 0;
}

