/*
 * 10254. The PRiest Mathematician
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
enum { DIGL = 6, BASE = 1000000LL };
#define DBG(x) (1)
#define N 10001

i64 max( i64 x, i64 y ) { return x < y ? y : x; }
i64 min( i64 x, i64 y ) { return x < y ? x : y; }

i64 *load( i64 n ) {
	i64 *x = (i64 *)calloc(4,sizeof *x);
	do x[++(*x)] = n%BASE; while (n /= BASE );
	return x;
}

void print( i64 *x ) {
	int i;
	for ( i = *x; i && !x[i]; --i );
	if ( !i ) { puts("0"); return ; }
	for ( printf("%lld",x[i]); --i; printf("%0*lld",DIGL,x[i]) );
	putchar('\n');
}

i64 *add( i64 *x, i64 *y, i64 *r ) {
	i64 *z,i;
	if ( r ) 
		for ( i = 0; i <= max(*x,*y)+2; r[i++] = 0 );
	z = !r?(i64 *)calloc(max(*x,*y)+3,sizeof *z):r;
	for ( i = 1; i <= *x; ++i ) z[i] += x[i];
	for ( i = 1; i <= *y; ++i ) z[i] += y[i];
	for ( *z = max(*x,*y)+2, i = 1; i <= *z; ++i )
		if ( z[i] >= BASE )
			z[i+1] += z[i]/BASE, z[i] %= BASE;
	for ( i = *z; i && !z[i]; --i );
	*z = !i?1:i;
	return z;
}

int is_less( i64 *x, i64 *y ) {
	int i,j,k;
	for ( i = *x; i && !x[i]; --i );
	for ( j = *y; j && !y[j]; --j );
	if ( i == j ) {
		for ( k = i; k; --k )
			if ( x[k] != y[k] )
				return x[k] < y[k];
		return 0;
	}
	return i < j;
}

void dec( i64 *x ) {
	int i;
	for ( --x[1], i = 1; i <= *x; ++i )
		if ( x[i] < 0 )
			x[i] += BASE, --x[i+1];
	for ( i = *x; i && !x[i]; --i );
	*x = !i? 1:i;
}

i64 n,m,*kaks[N],*c[N],*A,*B,z[N];

int main() {
	int i,j,k;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( kaks[0] = load(1LL), n = 1; n < N; ++n ) 
		kaks[n] = add(kaks[n-1],kaks[n-1],NULL);
	A = (i64 *)calloc(*kaks[N-1]+*kaks[N-1], sizeof *A);
	c[0] = load(0), c[1] = load(1), c[2] = load(3LL);
	for ( n = 3; n < N; c[n] = add(c[n],c[n],NULL), dec(c[n]), DBG(printf("z[%lld] = %lld\n",n,z[n])), ++n )
		for ( c[n] = NULL, k = z[n-1]; k <= min(z[n-1]+5,n-1); ++k ) {
			B = add(c[k],kaks[n-k-1],NULL);
			if ( !c[n]||is_less(B,c[n]) ) {
				if ( c[n] ) free(c[n]);
				c[n] = B, z[n] = k;
			}
		}
	for(;1==scanf("%lld",&n);print(c[n]));
	return 0;
}
