/*
 * 12199. Lights
 * TOPIC: combinatorics, dp, binary, very neat, recurrence, modulo, lucas theorem
 * status: Accepted
 */
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MOD 10567201LL
#define N 0x400
#define oo (1LL<<59)
typedef long long i64;

int m,n,v;
i64 F[MOD+1],z[N],d[N],G[MOD+1],g[N];

i64 mpow( i64 x, i64 n ) {
	i64 ax = 1LL;
	for (;n;n >>= 1, x*=x, x%=MOD )
		if ( n&1 ) ax*=x, ax%=MOD;
	return ax;
}

i64 inv( i64 x, i64 p ) { return mpow(x,p-2); };

i64 calc_z( int m ) {
	i64 a,b;
	if ( z[m] < +oo ) return z[m];
	if ( m == 0 ) {
		if ( v == 0 )
			return z[0] = 1;
		return z[0] = 0;
	}
	if ( m == 1 ) 
		return z[m] = 1LL;
	assert( m >= 2 );
	if ( d[n] < m-1 ) {
		a = (((d[n]-m+2+MOD)%MOD)*calc_z(m-2))%MOD;
		return z[m] = (g[m]*(MOD-a))%MOD;
	}
	a = (((F[d[n]]*G[m-1])%MOD)*G[d[n]-m+1])%MOD;
    b =	(((d[n]-m+2+MOD)%MOD)*calc_z(m-2))%MOD;
	return z[m] = (g[m]*(a-b+MOD))%MOD;
}

int main() {
	i64 i,j,k;
#ifndef ONLINE_JUDGE
	freopen("12199.in","r",stdin);
#endif
	for ( F[0] = 1LL, i = 1; i < MOD; ++i )
		F[i] = ((F[i-1]*i)%MOD);
	for ( i = 0; i < MOD; ++i ) 
		G[i] = inv(F[i],MOD);
	for ( d[0] = 1LL, i = 1; i < N; ++i )
		d[i] = ((d[i-1]<<1)%MOD), g[i] = inv(i,MOD);
	for ( ;3 == scanf("%d %d %d",&n,&m,&v) && (n||m||v); ) {
		for ( i = 0; i <= m; z[i++] = +oo );
		printf("%lld\n",calc_z(m));
	}
	return 0;
}

