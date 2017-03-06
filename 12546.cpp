/*
 * 12546. LCM Pair Sum
 * TOPIC: number theory
 * status: in progress
 */
#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>
#define MOD 1000000007LL
#define N 16
#define TST(u,i) (((u)>>(i))&1)
using namespace std;
typedef long long i64;

int ts,cs,n,d[N];
i64 v[N],V,p[N];

i64 modpow( i64 x, i64 n ) {
	i64 ax=1LL;
	for (;n;n>>=1,x*=x,x%=MOD)
		if(n&1)ax*=x,ax%=MOD;
	return ax;
}

const i64 inv2 = modpow(2LL,MOD-2);

i64 f00( unsigned int t ) {
	i64 res = V;
	for ( int i = 0; i < n; ++i )
		res *= (modpow(p[i],(1-TST(t,i))*d[i]+1)-1), res %= MOD;
	return res;
}

i64 f01( unsigned int t ) {
	i64 res = 1LL;
	for ( int i = 0; i < n; ++i )
		res *= modpow(p[i],TST(t,i)*d[i]), res %= MOD;
	return res;
}

i64 f04( unsigned int t ) {
	i64 res = 1LL;
	for ( int i = 0; i < n; ++i )
		res *= (d[i]*(1-TST(t,i))+1), res %= MOD;
	return res;
}

int main() {
	int i,j,k;
	i64 SODN,res;
	assert( ((inv2*2)%MOD) == 1 );
	for ( scanf("%d",&ts); ts-- && 1==scanf("%d",&n);) {
		for ( i = 0; i < n; ++i ) {
			scanf("%lld %d",&p[i],&d[i]);
		   	v[i] = modpow(p[i]-1,MOD-2);
			assert( (((p[i]-1)*v[i])%MOD) == 1 );
		}
		for ( res = 0, V = 1LL, i = 0; i < n; V *= v[i++], V %= MOD );
		for ( SODN = V, i = 0; i < n; ++i )
			SODN *= (modpow(p[i],d[i]+1)-1), SODN %= MOD;
		for ( unsigned int t = 0; t < (1<<n); ++t )
			res += (f00(~t)*f01(~t)*f04(t)+f00(t)*f01(t)), res %= MOD;
		printf("Case %d: %lld\n",++cs,(inv2*res)%MOD);
	}
	return 0;
}

