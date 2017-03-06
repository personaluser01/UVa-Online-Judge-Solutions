/*
 * 12846. Daisy Puzzle Game
 * TOPIC: sprague-grundy
 * status: Accepted
 */
#include <bits/stdc++.h>
#include <set>
#define N 21
#define BIT(k) (1ULL<<(k))
#define MASK(k) (BIT(k)-1ULL)
#define TST(u,k) (((u)>>(k))&1ULL)
#define oo 0xfffffffful
using namespace std;
typedef unsigned int state;

int m,n;
char bts[BIT(N)];
unsigned int z[BIT(N)];

unsigned int calc_z( const state u ) {
	int i,j,k,m;
	state w[N];
	if ( z[u] < +oo ) return z[u];
	if ( !u ) return z[u] = 0;
	set<unsigned int> s;
	for ( m=0, i=0; BIT(i)<=u; i=++j ) {
		for ( j=i; BIT(j)<=u && !TST(u,j); ++j );
		for ( w[m]=0, k=0; BIT(j)<=u && TST(u,j); w[m]|=BIT(k++), ++j );
		if ( w[m] ) ++m;
	}
	assert( m >= 1 );
	if ( m == 1 ) {
		for ( s.clear(), j = 0; j < bts[w[0]]; s.insert( calc_z(w[0]&~BIT(j++)) ) );
		for ( j=0; j<bts[w[0]]-1; ++j )
			s.insert( calc_z(w[0]&~(MASK(2)<<j)) );
		auto &ret = z[u];
		for ( ret=0; s.count(ret); ++ret );
		assert( s.find(ret) == s.end() );
		assert( ret == z[u] );
		return z[u];
	}
	for ( z[u]=0, i=0; i<m; z[u]^=calc_z(w[i++]) );
	return z[u];
};

int main() {
	int i,j,k,cs = 0,ts;
	state u,v,w[N];
#ifndef ONLINE_JUDGE
	freopen("12846.in","r",stdin);
#endif
	for ( u = 0; u < BIT(N); bts[u] = bts[u>>1]+(u&1), ++u );
	for ( memset(z,0xff,sizeof z), scanf("%d",&ts); ts--; printf("Case %d: %s\n",++cs,calc_z(u)?"yes":"no") ) {
		for ( scanf("%d %d",&n,&m), u=MASK(n); m-- && 1==scanf("%d",&k); u&=~BIT(k-1) );
		for ( m = 0, i = 0; i < n; i = ++j ) {
			for ( j = i; j < n && !TST(u,j); ++j );
			for ( w[m] = 0, k = 0; j < n && TST(u,j); w[m] |= BIT(k++), ++j );
			if ( w[m] ) ++m;
		}
		if ( m >= 2 && TST(u,0) && TST(u,n-1) )
			k = bts[w[0]], w[0] |= (w[--m]<<k);
		for ( u = 0, k = 0, i = 0; i < m; u |= (w[i] << k), k += bts[w[i++]]+1 );
	}
	return 0;
}

