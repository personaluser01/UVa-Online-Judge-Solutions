/*
 * 1224. Tile Codes
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
typedef unsigned long long u64;
#define N 0x20
#define oo 0xffffffffffffffffull

int ts,n;
u64 z[N][3][3],w,c[N];

u64 calc_z( int n, int i, int j ) {
	int k;
	if ( z[n][i][j] < +oo )
		return z[n][i][j];
	if ( n == 1 ) {
		if ( !(i == j && i == 0) )
			return z[n][i][j] = 0;
		return z[n][i][j] = 1;
	}
	if ( n == 2 ) {
		if ( i == 0 && j == 0 )
			return z[n][i][j] = 1;
		if ( i == 2 && j == 2 )
			return z[n][i][j] = 1;
		if ( i == 1 && j == 1 )
			return z[n][i][j] = 1;
		return z[n][i][j] = 0;
	}
	assert( n >= 3 );
	if ( i == 0 ) {
		for ( z[n][i][j] = 0, k = 0; k < 3; ++k )
			z[n][i][j] += calc_z(n-1,k,j);
		return z[n][i][j];
	}
	if ( i == 1 ) {
		for ( z[n][i][j] = 0, k = 0; k < 3; ++k )
			z[n][i][j] += calc_z(n-2,k,j);
		return z[n][i][j];
	}
	if ( i == 2 ) {
		for ( z[n][i][j] = 0, k = 0; k < 3; ++k )
			z[n][i][j] += calc_z(n-2,k,j);
		return z[n][i][j];
	}
	assert( 0 );
}

u64 f( int n ) {
	int i,j;
	u64 w = 0;
	if ( n == 0 )
		return c[n] = 1;
	if ( n == 1 )
		return c[n] = 1;
	if ( n == 2 )
		return c[n] = 3;
	if ( n < 0 )
		return 0;
	if ( c[n] < +oo )
		return c[n];
	for ( i = 0; i < 3; ++i )
		for ( j = i+1; j < 3; ++j )
			w += calc_z(n,i,j);
	w += f(n-2), w += f(n-4), w += f(n-4);
	return c[n] = w;
}

int main() {
	int i,j,k;
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	memset(z,0xffull,sizeof(z));
	memset(c,0xffull,sizeof(c));
	for ( scanf("%d",&ts); ts-- && 1 == scanf("%d",&n); ) {
		printf("%llu\n",f(n));
	}
	return 0;
}

