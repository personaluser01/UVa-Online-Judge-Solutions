/*
 * 11161. Help My Brother (II)
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
enum { DIGL = 4, BASE = 10000LL, LEN = 0x80 };
#define N 1501

int ts,n;

void print( i64 *x ) {
	int i;
	for ( i = LEN-1; i >= 0 && !x[i]; --i );
	if ( i < 0 ) {
		putchar('0');
		return ;
	}
	for ( printf("%lld",x[i]); --i >= 0; printf("%0*lld",DIGL,x[i]) );
}

void norm( i64 *x ) {
	int i;
	for ( i = 0; i < LEN; ++i )
		if ( x[i] >= BASE )
			x[i+1] += x[i]/BASE, x[i] %= BASE;
}

i64 *add( i64 *x, i64 *y ) {
	i64 *z = (i64 *)calloc(LEN, sizeof *z);
	int i;
	for ( i = 0; i < LEN; ++i )
		z[i] = x[i]+y[i];
	norm(z);
	return z;
}

i64 *mult( i64 *x, i64 *y ) {
	i64 *z = (i64 *)calloc(LEN, sizeof *z);
	int i,j;
	for ( i = 0; i < LEN; ++i )
		for ( j = 0; j+i < LEN; ++j )
			z[i+j] += x[i]*y[j];
	norm(z);
	return z;
}

void div2( i64 *x ) {
	i64 rem = 0,tmp,i;
	for ( i = LEN-1; i >= 0; --i ) {
		tmp  = (rem*BASE+x[i])&1;
		x[i] = (rem*BASE+x[i])>>1;
		rem = tmp;
	}
	norm(x);
}

i64 *load( i64 n ) {
	i64 *x = (i64 *)calloc(LEN, sizeof *x),i = 0;
	do { x[i++] = n%BASE; } while ( n /= BASE );
	return x;
}

i64 *F[N],*pref[N],*z,*ONE,*ZERO;

void dec( i64 *x ) {
	int i;
	for ( --x[0], i = 1; i < LEN; ++i )
		if ( x[i] < 0 )
			x[i] += BASE, --x[i+1];
	norm(x);
}

void inc( i64 *x ) {
	++x[0];
	norm(x);
}

int main() {
	i64 *x;

#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif

	F[0] = load(0);
	F[1] = F[2] = load(1);
	ONE = load(1), ZERO = load(0);
	for ( n = 3; n < N; ++n )
		F[n] = add(F[n-1],F[n-2]);
	for ( pref[0] = load(0), n = 1; n < N; ++n )
		pref[n] = add(pref[n-1],F[n]);

	while ( 1 == scanf("%d",&n) && n > 0 ) {
		printf("Set %d:\n",++ts);
		if ( F[n][0]&1 )
			x = add(F[n],ONE), div2(x);
		else
			x = add(F[n],ZERO), div2(x);
		z = add(x,pref[n-1]), dec(z);
		print(z), puts("");
	}
	return 0;
}

