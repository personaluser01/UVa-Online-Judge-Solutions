/*
 * 701. Archeologist's Dilemma
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
#define N (1 << 14)
#define tol 1e-9

i64 *load( i64 n ) {
	i64 *x = (i64 *)calloc(4,sizeof *x);
	do x[++(*x)] = n%BASE; while ( n/= BASE );
	return x;
}

i64 *add( i64 *x, i64 *y ) {
	i64 *z = (i64 *)calloc(*x+2,sizeof *z),i,j;
	for ( i = 1; i <= *x; ++i ) z[i] += x[i];
	for ( i = 1; i <= *y; ++i ) z[i] += y[i];
	for ( *z = *x+1, i = 1; i <= *z; ++i )
		if ( z[i] >= BASE )
			z[i+1] += z[i]/BASE, z[i] %= BASE;
	for ( i = *z; i && !z[i]; --i );
	*z = !i ? 1 : i;
	return z;
}

i64 *d[N],len[N];

i64 diglen( i64 *x ) {
	int i,k = 0;
	char tmp[0x30];
	for ( i = *x; i && !x[i]; --i );
	if ( !i ) return 1;
	sprintf(tmp,"%lld",x[i]), k += strlen(tmp), k += (i-1)*DIGL;
	return k;
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

long double LG( i64 k ) {
	return log((double )k)/log(10.00);
}

int main() {
	i64 i,j,k,*x,l,E,n;
	char s[0x400],tmp[0x400];
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( d[1] = load(2LL), k = 2; k < N; ++k )
		d[k] = add(d[k-1],d[k-1]);
	for ( k = 1; k < N; ++k )
		len[k] = diglen(d[k]);
	while ( 1 == scanf("%lld",&k) ) {
		sprintf(s,"%lld",k), i = strlen(s);
		for ( n = i+1; ; ++n ) {
			E = (i64)((n+LG(k))/LG(k)+tol);
		}
		puts("no power of 2");
		ok: continue ;
	}
	return 0;
}
