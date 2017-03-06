/*
 * 10329. Combinatorial Expression
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
#define Q 8000
typedef long long i64;
enum { DIGL = 5, BASE = 100000LL };

unsigned char is[Q>>3];
#define SET(k) (is[(k)>>3]|=(1UL<<((k)&7)))
#define CLR(k) (is[(k)>>3]&= ~(1UL<<((k)&7)))
#define TST(k) (is[(k)>>3]&(1UL<<((k)&7)))
int num[Q],m,n,denom[Q],K,*p;

void sieve() {
	int i,j,k;
	for ( SET(2), i = 3; i < Q; i += 2 ) SET(i);
	for ( i = 3; i < Q; i += 2 )
		for ( j = i+i; TST(i) && j < Q; CLR(j), j += i );
	for ( m = 0, i = 0; i < Q; ++i )
		if ( TST(i) && ++m );
	p = (int *)malloc(m*sizeof *p);
	for ( k = i = 0; i < Q; ++i )
		if ( TST(i) && (p[k++] = i) );
}

void profile( int n, int r, int *prof ) {
	int i,j,k,ax,w;
	assert( n >= r );
	if ( n == r || r == 0 )
		return ;
	for ( i = 0; p[i] <= n; ++i ) 
		for ( w = n, ax = p[i]; ax <= w; prof[i] += w/ax, ax *= p[i] );
	for ( i = 0; p[i] <= r; ++i ) 
		for ( w = r, ax = p[i]; ax <= w; prof[i] -= w/ax, ax *= p[i] );
	for ( i = 0; p[i] <= n-r; ++i ) 
		for ( w = n-r, ax = p[i]; ax <= w; prof[i] -= w/ax, ax *= p[i] );
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

i64 *load( i64 n ) {
	i64 *x = (i64 *)calloc(4,sizeof *x);
	do x[++(*x)]=n%BASE;while(n/=BASE);
	return x;
}

i64 *mult( i64 *x, i64 *y ) {
	i64 *z = (i64 *)calloc(*x+*y+4,sizeof *z),i,j,k;
	for ( i = 1; i <= *x; ++i )
		for ( j = 1; j <= *y; ++j )
			z[i+j-1] += x[i]*y[j];
	for ( *z = *x+*y+2, i = 1; i <= *z; ++i )
		if ( z[i] >= BASE )
			z[i+1] += z[i]/BASE, z[i] %= BASE;
	for ( i = *z; i && !z[i]; --i );
	*z = !i ? 1 : i;
	return z;
}

i64 *pw( i64 *x, int m ) {
	i64 *ax = load(1LL);
	while ( m ) {
		if ( m & 1 )
			ax = mult(ax,x);
		x = mult(x,x), m >>= 1;
	}
	return ax;
}

int digs( i64 *x ) {
	int i,k = 0;
	char str[0x400];
	for ( i = *x; i && !x[i]; --i );
	if ( !i ) return 1;
	*x = !i ? 1 : i;
	k = DIGL*((*x)-1);
	assert( x[*x] );
	sprintf(str,"%lld",x[*x]);
	k += strlen(str);
	return k;
}

int main() {
	int i,j,k;
	i64 *x;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( sieve(); 2 == scanf("%d %d",&n,&m); ) {
		for ( i = 0; p[i] <= 5000; ++i )
			num[i] = denom[i] = 0;
		for ( i = 0; i < n; ++i ) {
			scanf("%d %d",&k,&j);
			profile(k,j,num);
		}
		for ( i = 0; i < m; ++i ) {
			scanf("%d %d",&k,&j);
			profile(k,j,denom);
		}
		for ( i = 0; p[i] <= 5000; ++i )
			if ( denom[i] > num[i] ) {
				puts("0");
				goto next;
			}
		x = load(1LL);
		for ( i = 0; p[i] <= 5000; ++i )
			if ( num[i] != denom[i] ) {
				assert( num[i] > denom[i] );
				x = mult(x,pw(load((i64)p[i]),num[i]-denom[i]));
				if ( digs(x) >= 101 )
					goto nx;
			}
		assert( digs(x) < 101 );
		print(x);
		next: continue ;
		nx: puts("-1");
	}
	return 0;
}
