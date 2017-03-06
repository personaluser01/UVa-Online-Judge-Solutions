/*
 * 12546. LCM Pair Sum
 * TOPIC: combinatorics, dp, bitmasks
 * status: Accepted
 */
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MOD 1000000007LL
#define N 16
#define BIT(k) (1ULL<<(k))
#define MASK(k) (BIT(k)-1ULL)
#define T(t,i) (((t)>>(i))&1)
#define L(k) ((k) & ((~(k))+1ULL))
#define oo (1LL<<61)
typedef long long i64;

i64 p[N],ip[N],U[1<<N],R[1<<N][2],sod[1<<N][2],nod[1<<N][2],g[1<<N],f[1<<N];
int d[N],n;
char who[1<<N],bts[1<<N];

int max( int x, int y ) { if(x<y) return y; return x; }

i64 modpow( i64 x, i64 n ) {
	i64 ax = 1LL;
	for (;n;n>>=1,x*=x,x%=MOD)
		if (n&1) ax*=x,ax%=MOD;
	return ax;
}

i64 iSOD( unsigned int t, int shift ) {
	i64 res = U[t],i;
	for (;t&&(i=who[L(t)])>=0; t&=~L(t), res %= MOD )
		if ( shift )
			res *= (modpow(p[i],max(d[i]-1,0)+1)-1);
		else res *= (modpow(p[i],d[i]+1)-1);
	return res%MOD;
}

i64 iNOD( unsigned int t, int shift ) {
	i64 res = 1LL,i;
	for (;t&&(i=who[L(t)])>=0; t &= ~L(t), res %= MOD )
		if ( shift )
			res *= d[i];
		else res *= (d[i]+1);
	return res;
}

i64 rec( unsigned int t, int shift ) {
	i64 res = 1LL,i;
	for (;t&&(i=who[L(t)])>=0; t&=~L(t), res %= MOD )
		if ( shift )
			res *= modpow(p[i],max(d[i]-1,0));
		else res *= modpow(p[i],d[i]);
	return res;
}

i64 G( int l, unsigned int u ) {
	i64 res = 0,m=bts[u],pref = who[L(u)];
	unsigned int t,tt,s,v;

	assert( (u>>who[L(u)]) == MASK(m) );
	if ( g[v = (u&~(MASK(m)<<(pref+l+1)))] < +oo ) 
		return g[v];
	for ( tt=0; tt<(1<<(m-l-1)); ++tt ) {
		t = ((1<<(pref+l))|(tt<<(pref+l+1)))&MASK(n);
		s = ((~t)&MASK(n)), s >>= pref, s <<= pref;
		res += (((nod[t][0]*R[t][0])%MOD)*sod[s][1])%MOD;
		res += (((nod[s][1]*R[s][0])%MOD)*sod[t][0])%MOD;
		res %= MOD;
	}
	return g[v] = res;
}

i64 F( unsigned int t, int sh ) {
	i64 res,l,m=bts[t];
	if ( !(t&(t-1)) ) {
		assert( who[t] == n-1 );
		res = sod[t][0]+R[t][0]*nod[t][0];
		return res%MOD;
	}
	assert( m >= 2 );
	assert( (t>>who[L(t)]) == MASK(m) );
	if ( f[t] < +oo ) 
		return f[t];
	res = (R[BIT(who[L(t)])][0]*F(t&~L(t),sh+4)%MOD);
	for ( l = 1; l <= m-1; ++l )
		res += G(l,t), res %= MOD;
	l = (sod[t][1]+R[t][0]*nod[t][1])%MOD, res += l, res %= MOD;
	return f[t] = res;
}

int main() {
	int i,j,k,cs = 0,ts;
	unsigned int u,v;
#ifndef ONLINE_JUDGE
	freopen("12546.in","r",stdin);
#endif
	for ( i = 0; i < N; who[BIT(i)] = i, ++i );
	for ( u = 0; u < (1<<N); ++u )
		bts[u] = bts[u>>1]+(u&1);
	for ( scanf("%d",&ts); ts-- && 1 == scanf("%d",&n); ) {
		for ( i = 0; i < n; ++i )
			scanf("%lld %d",p+i,d+i);
		for ( u = 0; u < (1<<n); g[u++] = +oo );
		for ( i = 0; i < n; ++i )
			ip[i] = modpow(p[i]-1,MOD-2);
		for ( R[0][0] = R[0][1] = 1LL, U[0] = 1LL, u = 1; u < (1<<n); ++u ) {
			i = who[L(u)];
			R[u][0] = R[u&~L(u)][0]*modpow(p[i],d[i]), R[u][0] %= MOD;
			R[u][1] = R[u&~L(u)][1]*modpow(p[i],max(d[i]-1,0)), R[u][1] %= MOD;
			U[u] = U[u&~L(u)]*ip[i], U[u] %= MOD;
		}
		for ( u=0,nod[u][0]=nod[u][1]=sod[u][0]=sod[u][1]=1LL, u = 1; u < (1<<n); ++u ) {
			i = who[L(u)];
			nod[u][0] = nod[u&~L(u)][0]*(1+d[i]), nod[u][1] = nod[u&~L(u)][1]*(d[i]);
			nod[u][0] %= MOD, nod[u][1] %= MOD;
			sod[u][0] = ((sod[u&~L(u)][0]*(modpow(p[i],d[i]+1)-1))%MOD)*ip[i], sod[u][0]%=MOD;
			sod[u][1] = ((sod[u&~L(u)][1]*(modpow(p[i],max(d[i]-1,0)+1)-1))%MOD)*ip[i], sod[u][1]%=MOD;
		}
		for ( u = 0; u < (1<<n); f[u++] = +oo );
		for ( k = 1; k <= n; ++k )
			F(MASK(k)<<(n-k),0);
		printf("Case %d: %lld\n",++cs,F(MASK(n),0));
	}
	return 0;
}

