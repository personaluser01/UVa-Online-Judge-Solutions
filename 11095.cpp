/*
 * 11095. Tabriz City
 * TOPIC: min vertex cover
 * status:
 */
#include <algorithm>
#include <iostream>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <cctype>
#define N 31
#define BIT(k)   (1ULL << (k))
#define MASK(k)  (BIT(k)-1ULL)
#define L(u)     ((u)&((~(u))+1ULL))
#define TST(x,y) ((u[x]>>(y))&1)
typedef unsigned long long u64;
using namespace std;

u64 u[N],best;
char which[BIT(21)],bts[BIT(21)];
int ans,n,m,g[N][N],yes;

int Bits( u64 u ) { return bts[u>>40]+bts[(u>>20)&MASK(20)]+bts[u&MASK(20)]; }

int who( u64 u ) {
	if ( u >= BIT(20) )
		return 20+which[u>>20];
	return which[u];
}

void f( int covered, int cost, u64 mp, int pos ) {
	int i,j,k,*top,st[N],dc = 0,np = i+1;
	u64 v,w = 0;
	if ( covered == m ) 
		if ( cost < ans ) 
			ans = cost, best = mp;
	if ( cost >= ans ) return ;
	assert( covered < m );
	for ( i = pos; i < n; ++i ) {
		for ( top = st, k = 0, v = u[i]; v; v &= ~L(v) )
			if ( g[i][j=who(L(v))] != yes ) {
				++k, *++top = j;
				g[i][j] = g[j][i] = yes;
			}
		f(covered+k,cost+1,mp|BIT(i),i+1);
		for (;top > st; j = *top--, g[i][j] = g[j][i] = 0 );

		for ( dc = 0, top = st, k = 0, v = u[i]; v; v &= ~L(v) )
			if ( g[i][j=who(L(v))] != yes ) {
				++k, *++top = j;
				g[i][j] = g[j][i] = yes;
				w |= BIT(j), ++dc;
				if ( j > np ) np = j;
			}
		f(covered+k,cost+dc,mp|w);
		for (;top > st; j = *top--, g[i][j] = g[j][i] = 0 );
	}
}

int main() {
	int i,j,k,ts,cs = 0;
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	for ( k = 0; k < BIT(21); ++k ) bts[k] = bts[k>>1]+(k&1);
	for ( k = 0; k < 21; ++k ) which[BIT(k)] = k;
	for ( scanf("%d",&ts); ts-- && 2 == scanf("%d %d",&n,&m); ) {
		printf("Case #%d: ",++cs);
		for ( i = 0; i < n; u[i++] = 0 );
		for ( k = 0; k < m; ++k )
			scanf("%d %d",&i,&j), u[i] |= BIT(j), u[j] |= BIT(i);
		for ( m = 0, i = 0; i < n; ++i )
			m += Bits(u[i]);
		assert( !(m&1) );
		m >>= 1, ans = BIT(29);
		if ( ans == BIT(29) ) {
			puts("\n\n");
			continue ;
		}
	}
	return 0;
}

