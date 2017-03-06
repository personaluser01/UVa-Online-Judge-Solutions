/*
 * 11170. Cos(NA)
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
#define N 0x40
typedef long long i64;
enum { DIGL = 6, BASE = 1000000LL, LEN = 0x10 };

int is_neg( i64 *x ) { return x[LEN-1] >= BASE/2; }

void negate( i64 *x ) {
	int i;
	for ( i = 0; i < LEN; x[i] = BASE-1-x[i], ++i );
	for ( i = 0; i < LEN && x[i] == BASE-1; x[i++] = 0 );
	++x[i];
}

i64 *load( i64 n ) {
	i64 *x = (i64 *)calloc(LEN, sizeof *x), i = 0, s = 1;
	if ( n < 0 ) s = -1, n = -n;
	do { x[i++] = n%BASE; } while ( n /= BASE );
	if ( s == -1 ) negate(x);
	return x;
}

i64 *add( i64 *x, i64 *y ) {
	int i;
	for ( i = 0; i < LEN; ++i )
		x[i] += y[i];
	for ( i = 0; i < LEN; ++i )
		if ( x[i] >= BASE )
			x[i+1] += x[i]/BASE, x[i] %= BASE;
}

i64 *sub( i64 *x, i64 *y ) {
	negate(y), add(x,y), negate(y);
}

void print( i64 *x ) {
	int i;
	if ( is_neg(x) ) {
		putchar('-'), negate(x), print(x), negate(x);
		return ;
	}
	for ( i = LEN-1; i >= 0 && !x[i]; --i );
	if ( i < 0 ) {
		putchar('0');
		return ;
	}
	for ( printf("%lld",x[i]); (--i) >= 0; printf("%0*lld",DIGL,x[i]) );
}

int n,m,pr;
i64 *C[N][N],*coeff,*ONE,*ZERO,*MONE;

int sig( int k ) {
	return (k&1)?-1:1;
}

void SIGN( char ch ) {
	if ( pr++ )
		putchar(ch);
}

int equal( i64 *x, i64 *y ) {
	int i;
	for ( i = 0; i < LEN; ++i )
		if ( x[i] != y[i] )
			return 0;
	return 1;
}

i64 *mult( i64 *x, i64 *y ) {
	i64 *z = (i64 *)calloc(LEN, sizeof *z),i,j;
	for ( i = 0; i < LEN; ++i )
		for ( j = 0; j+i < LEN; ++j )
			z[i+j] += x[i]*y[j];
	for ( i = 0; i < LEN; ++i )
		if ( z[i] >= BASE )
			z[i+1] += z[i]/BASE, z[i] %= BASE;
	return z;
}

int main() {
	int i,j,k,t;
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	ZERO = load(0);
	for ( i = 0; i < N; ++i )
		C[i][0] = load(1LL);
	for ( i = 0; i < N; ++i )
		for ( j = i+1; j < N; ++j )
			C[i][j] = ZERO;
	for ( i = 1; i < N; ++i )
		for ( j = 1; j <= i; ++j ) 
			C[i][j] = load(0), add(C[i][j],C[i-1][j]), add(C[i][j],C[i-1][j-1]);
	ONE = load(1), MONE = load(1), negate(MONE);

	while ( 1 == scanf("%d",&n) && n > 0 ) {
		pr = 0,	m = (n>>1);
		if ( n == 1 ) {
			puts("Cos(A)");
			continue ;
		}
		for ( j = 0; j <= m; ++j ) {
			for ( coeff = load(0), k = (n&1); k <= n-2*j; k += 2 ) {
				if ( sig((n-k)/2-j+(((n-k)>>1)&1)) == -1 )
					sub(coeff,mult(C[n][k],C[(n-k)>>1][j]));
				else
					add(coeff,mult(C[n][k],C[(n-k)>>1][j]));
			}
			if ( equal(coeff,ZERO) ) continue ;
			if ( equal(coeff,ONE) ) {
				SIGN('+');
				if ( n-2*j > 0 )
					printf("Cos");
				if ( n-2*j > 1 )
					printf("^%d",n-2*j);
				if ( n-2*j == 0 )
					putchar('1');
				if ( n-2*j > 0 )
					putchar('A');
			}
			else if ( equal(coeff,MONE) ) {
				SIGN('-');
				if ( n-2*j > 0 )
					printf("Cos");
				if ( n-2*j > 1 )
					printf("^%d",n-2*j);
				if ( n-2*j > 0 )
					printf("(A)");
				if ( n-2*j == 0 )
					putchar('1');
			}
			else {
				if ( !is_neg(coeff) )
					SIGN('+');
				else
					SIGN('-');
				if ( is_neg(coeff) ) negate(coeff);
				print(coeff);
				if ( n-2*j > 0 )
					printf("Cos");
				if ( n-2*j > 1 )
					printf("^%d",n-2*j);
				if ( n-2*j > 0 )
					printf("(A)");
			}
		}
		putchar('\n');
	}
	return 0;
}
