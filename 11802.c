/*
 * 11802. All Your Bases Belong to Us
 * TOPIC: maths, combinatorics, neat
 * status: Accepted
 */
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MOD 1000000007LL
#define N (1LL<<15)
#define BIT(k) (1ULL<<(k))
#define SET(k) (a[(k)>>3] |= BIT((k)&7))
#define CLR(k) (a[(k)>>3] &= ~BIT((k)&7))
#define TST(k) (a[(k)>>3] & BIT((k)&7))
typedef long long i64;

unsigned char a[(N>>3)+8];
i64 *p,n,K;
int m;

i64 max( i64 x, i64 y ) {
	if ( x < y ) return y;
	return x;
}

void sieve() {
	i64 i,j,k;
	for ( SET(2), i = 3; i < N; i += 2 ) SET(i);
	for ( i = 3; i < N; i += 2 )
		if ( TST(i) )
			for ( j = i+i; j < N; j += i ) CLR(j);
	for ( i = 0; i < N; ++i )
		if ( TST(i) ) ++m;
	p = (i64 *)malloc(m*sizeof *p);
	for ( k = 0, i = 0; i < N; ++i )
		if ( TST(i) ) p[k++] = i;
	assert( k == m );
}

i64 D( i64 n, i64 p ) {
	i64 s = 0,q = p;
	for (;n>=q;s+=n/q,q*=p);
	return s;	
}

i64 F( i64 a, i64 b ) { return a/b; }
i64 C( i64 a, i64 b ) {
	if ( 0 == (a%b) )
		return a/b;
	return a/b+1LL;
}

int main() {
	int i,j,k,ts,cs = 0;
	i64 d,ax,bx;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( sieve(), scanf("%d",&ts); ts--; printf("Case %d: %lld\n",++cs,(ax-bx+MOD)%MOD) ) {
		scanf("%lld %lld",&n,&K);
		for ( ax = bx = 1LL, i = 0; i < m && p[i] <= n; ++i ) {
			d = D(n,p[i]);
			ax *= (F(d,K)+1LL), bx *= (F(d,K+1)+1);
			ax %= MOD, bx %= MOD;
		}
	}
	return 0;
}

