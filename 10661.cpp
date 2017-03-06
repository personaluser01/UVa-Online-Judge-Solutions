/*
 * 10661. The Perspectographer
 * TOPIC: chromatic number, graphs
 * status: Accepted
 */
#include <algorithm>
#include <iostream>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#define N 		21
#define A 		26
#define BIT(k)  (1ULL<<(k))
#define MASK(k) (BIT(k)-1ULL)
#define L(u)    ((u)&((~(u))+1ULL))
using namespace std;

int n,m,best_size,C;
char bts[BIT(N)],who[BIT(N)],c[N];
unsigned int adj[N],V,col[N];

int is_clique( const unsigned int u ) {
	int q[N],*head=q,*tail=q,i,j;
	unsigned int v = u;
	for(;v; *tail++ = who[L(v)], v &= ~L(v) );
	for ( i = 0; i < tail-head; ++i )
		for ( j = i+1; j < tail-head; ++j )
			if ( !(adj[i]&BIT(j)) )
				return 0;
	return 1;
}

int f( unsigned int u ) {
	unsigned int v,i,j,forbidden = 0, available;
	if ( u == 0 ) return 1;
	for ( v = adj[i = who[L(u)]]; v && bts[forbidden] < C; v &= ~L(v) )
		if ( (j=who[L(v)]) < i )
			forbidden |= BIT(c[j]);
	if ( bts[forbidden] == C ) return 0;
	available = ~forbidden & MASK(C);
	for ( v = available; v; v &= ~L(v) ) {
		c[i] = who[L(v)];
		if ( f(u&~L(u)) )
			return 1;
	}
	return 0;
}

int main() {
	int i,j,k,ts,l;
	char aa[N],bb[N];
	unsigned int u,v,INITIAL;
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	for ( k = 0; k < BIT(N); ++k )
		bts[k] = bts[k>>1]+(k&1);
	for ( k = 0; k < N; ++k )
		who[BIT(k)] = k;
	for(scanf("%d",&ts);ts--&&2==scanf("%d %d",&n,&m);) {
		for ( i = 0; i < A; ++i ) adj[i] = 0;
		for ( V = 0, l = 0; l < m; ++l ) {
			scanf("%s %s",aa,bb), i=0[aa]-'A', j=0[bb]-'A', adj[i]|=BIT(j), adj[j]|=BIT(i);
			V |= BIT(i), V |= BIT(j);
		}
		for ( best_size = 0, v=V; v; v=(v-1)&V ) 
			if ( bts[v] > best_size && is_clique(v) ) 
				best_size = bts[v];
		for ( C = best_size; C <= n && !f(MASK(n)); ++C );
		printf("%d\n",C);
	}
	return 0;
}


