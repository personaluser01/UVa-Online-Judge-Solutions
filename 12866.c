/*
 * 12866. Combinations
 * TOPIC: combinatorics, dp, binary, lucas, binomial coefficients
 * status: Accepted
 */
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 63
typedef long long i64;
typedef unsigned long long u64;
enum { DIGL = 7, BASE = 10000000LL, LEN = 0x5 };

i64 *c[N][N],*deg[N],*ONE,*ZERO,low,high;

i64 *add( i64 *x, i64 *y ) {
	i64 *z = (i64 *)calloc(LEN, sizeof *z);
	int i;
	for ( i=0; i<LEN; ++i ) z[i]=x[i]+y[i];
	for ( i=0; i<LEN; ++i )
		if ( z[i] >= BASE )
			z[i+1] += z[i]/BASE, z[i] %= BASE;
	return z;
}

void print( i64 *x ) {
	int i;
	for ( i = LEN-1; i >= 0 && !x[i]; --i );
	if ( i < 0 ) { puts("0"); return ; }
	for ( printf("%lld",x[i]); --i >= 0; printf("%0*lld",DIGL,x[i]) );
	putchar('\n');
}

i64 *load( i64 n ) {
	int i = 0;
	i64 *d = (i64 *)calloc(LEN,sizeof *d);
	do { d[i++] = n%BASE; } while ( n /= BASE );
	return d;
}

i64 *mult( i64 *x, i64 *y ) {
	i64 *z = (i64 *)calloc(LEN, sizeof *z);
	int i,j;
	for ( i = 0; i < LEN; ++i )
		for ( j = 0; i+j < LEN; ++j )
			if ( (z[i+j] += x[i]*y[j]) >= BASE ) {
				z[i+j+1] += z[i+j]/BASE;
				z[i+j] %= BASE;
			}
	for ( i = 0; i < LEN; ++i )
		if ( z[i] >= BASE )
			z[i+1] += z[i]/BASE, z[i] %= BASE;
	return z;
}

i64 *f( i64 x ) {
	i64 y=x,m=0,n=0,pos[N],pref[N],d[N],i,j,k,*res,*a;
	if ( x < 0 ) return ZERO;
	if ( x == 0 ) return ONE;
	for(;y;d[n++]=(y&1),y>>=1);
	for(i=0,j=n-1;i<j;k=d[i],d[i]=d[j],d[j]=k,++i,--j);
	for(i=0;i<n;++i) if (d[i]) pos[m++]=i;
	for(pref[0]=0,i=1;i<=n;pref[i]=pref[i-1]+d[i-1],++i);
	for ( res=ZERO, k=0; k<=n; res=add(res,mult(a,deg[k++])) )
		for ( a=ZERO, i=0; i<m && k>=pref[pos[i]]; ++i )
			a=add(a,c[n-1-pos[i]][k-pref[pos[i]]]);
	res = add(res,deg[pref[n]]);
	return res;
}

int equal( i64 *x, i64 *y ) {
	int i;
	for ( i = 0; i < LEN; ++i )
		if ( x[i] != y[i] )
			return 0;
	return 1;
}

i64 *sub( i64 *x, i64 *y ) {
	i64 *z = (i64 *)calloc(LEN, sizeof *z);
	int i,j;
	for ( i = 0; i < LEN; ++i ) 
		z[i] = x[i]-y[i];
	for ( i = 0; i < LEN; ++i )
		for (;z[i] < 0; --z[i+1], z[i] += BASE );
	for ( i = 0; i < LEN; ++i ) {
		assert( 0 <= z[i] && z[i] < BASE );
	}
	assert( equal(add(z,y),x) );
	return z;
}

int main() {
	int i,j,k;
#ifndef ONLINE_JUDGE
	freopen("a.txt","r",stdin);
#endif
	ONE = load(1), ZERO = load(0);
	for ( i = 0; i < N; c[i++][0] = ONE );
	for ( j = 1; j < N; c[0][j++] = ZERO );
	for ( i = 1; i < N; ++i ) {
		for ( j = 1; j <= i; ++j ) 
			c[i][j] = add(c[i-1][j],c[i-1][j-1]);
		for ( j = i+1; j < N; ++j ) c[i][j] = ZERO;
	}
	for ( deg[0] = ONE, i = 1; i < N; ++i )
		deg[i] = add(deg[i-1],deg[i-1]);
	for (;2==scanf("%lld %lld",&low,&high) && (low||high); print(sub(f(high),f(low-1))) );
	return 0;
}

