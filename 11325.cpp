/*
 * 11325. This Means War
 * TOPIC: backtracking
 * status: Accepted
 */
#include <iostream>
#include <algorithm>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <set>
#define A 52
#define N A
#define M 0x40
#define oo 0xfffffffful
#define L(u) ((u)&((~(u))+1ULL))
typedef unsigned long long u64;
#define BIT(k)  (1ULL<<(k))
#define MASK(k) (BIT(k)-1ULL)
#define val(u) ((u)&15ULL)
#define how_much_left(k) (A/2-1-(k))
#define enc(i,j) ((i)|((j)<<4))
#define MM MASK(16)
using namespace std;

int m,ts,is[0x400],yes,c[M];
unsigned int a[N],b[N],available,adr[M],g[0x400],tail[N];
char which[BIT(21)],bts[BIT(21)];

set<u64> deadend[N][MM+1];

unsigned int f( char ch ) {
	if ( isdigit(ch) )
		return ch-'2';
	if ( ch == 'T' ) return 8;
	if ( ch == 'J' ) return 9;
	if ( ch == 'Q' ) return 10;
	if ( ch == 'K' ) return 11;
	assert( ch == 'A' );
	return 12;
}

int who( const u64 u ) {
	if ( u >= BIT(40) )
		return 40+which[u>>40];
	if ( u >= BIT(20) )
		return 20+which[u>>20];
	return which[u];
}

unsigned int get_smallest( const unsigned int u ) { return who(L(u)); }

unsigned int paritet( const unsigned int u ) {
	if ( !((available>>val(u))&1ULL) )
		return +oo;
	return val(u);
}

int conv( const char *s ) { return enc(f(0[s]),g[1[s]]); }

int bitsize( u64 u ) { return bts[u&MASK(20)]+bts[(u>>20)&MASK(20)]+bts[u>>40]; }

int hall_marriage( int k ) {
	u64 u,w,V = 0,adj[N],x,y;
	int i,j;
	for ( w = available; w; w &= ~L(w) )
		for ( j = c[who(L(w))]; j--; )
			for ( adj[x=V++] = 0, i = k; i < A/2; ++i )
				if ( val(a[i]) <= who(L(w)) )
					adj[x] |= BIT(i-k);
	for ( u = 0; u < (1<<V); ++u ) {
		for ( w = 0, i = 0; i < V; ++i )
			if ( (u>>i)&1 )
				w |= adj[i];
		if ( bitsize(w) < bitsize(u) )
			return 0;
	}
	return 1;
}

int can_arrange( int k ) {
	unsigned int u,v[3],w,i,ignored_weights;
	u64 e = 0;

#define del(u)     { if ( 0 == (--c[u]) ) available &=~BIT(u); }
#define restore(u) { if((++c[u]) == 1)    available |= BIT(u); }

	if ( k == A/2 ) return 1;
	assert( k < A/2 );

	for ( i = 0; i <= 12; e|=(((u64)c[i])<<(3*i)), ++i );
	// e |= ((u64)k)<<(3*i);

	if ( deadend[k][e&MM].find(e) != deadend[k][e&MM].end() )
		return 0;

	if ( how_much_left(k)==0 ) goto next;

	if ( (u=paritet(a[k]))<+oo ) {
		assert( u==val(a[k]) );
		del(u);
		if ( how_much_left(k) == 1 ) {
			if ( can_arrange(k+1) ) return 1;
			restore(u);
			goto next;
		}
		assert( how_much_left(k)>=2 );
		//v[0] = get_smallest(available);
		//del(v[0]);
		if ( how_much_left(k+1)==1  ) {
			if ( can_arrange(k+2) ) return 1;
			restore(u);
			//restore(v[0]);
			goto next;
		}
		assert( how_much_left(k+1) >= 2 );
		//v[1] = get_smallest(available);
		//del(v[1]);
		if ( how_much_left(k+2) == 1 ) {
			if ( can_arrange(k+3) ) return 1;
			restore(u);
			//restore(v[0]);
			//restore(v[1]);
			goto next;
		}
		assert( how_much_left(k+2) >= 2 );
		//v[2] = get_smallest(available);
		//del(v[2]);
		if ( can_arrange(k+4) ) return 1;
		restore(u);
		//restore(v[0]);
		//restore(v[1]);
		//restore(v[2]);
	}
next:
	for ( w = available, ignored_weights = 0; w && (ignored_weights&tail[k+1])==ignored_weights; w &= ~L(w) )
		if ( (u=get_smallest(w)) > val(a[k]) ) {
			del(u); 
			if ( can_arrange(k+1) ) return 1;
			restore(u);
			ignored_weights |= BIT(u);
		}
	deadend[k][e&MM].insert(e);
	return 0;
}

int main() {
	int i,j,k;
	char tmp[0x80];
#ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
#endif
	for ( i = 0; i < 21; ++i ) which[BIT(i)] = i;
	for ( k = 0; k < BIT(21); ++k )
		bts[k] = bts[k>>1]+(k&1);
	g['H'] = 0, g['C'] = 1, g['D'] = 2, g['S'] = 3;
	for ( scanf("%d",&ts); ts-- && ++yes; ) {
		/*for ( i = A/2-1; i >= 0; scanf("%s",tmp), is[a[i--]=conv(tmp)]=yes );*/
		for ( i = 0; i < A/2; ) {
			scanf("%s",tmp), a[i++]=conv(tmp);
			// assert( is[a[i-1]] != yes );
			is[a[i-1]] = yes;
		}
		for ( m = 0, i = 0; i <= 3; ++i )
			for ( j = 0; j <= 12; ++j)
				if ( is[k=enc(j,i)]!=yes && (b[m++]=k)>=0 );
		assert( m == A/2 );
		memset(c,0,sizeof c);
		for ( i = 0; i < m; ++i ) ++c[val(b[i])];
		for ( available = 0, i = 0; i <= 12; ++i ) {
			if ( c[i] ) available |= BIT(i);
			assert( 0 <= c[i] && c[i] <= 4 );
		}
		for ( k = 0; k < A/2; ++k )
			for ( i = 0; i <= MM; ++i )
				deadend[k][i].clear();
		puts(can_arrange(0)?"yes":"no");
		//printf("%lu\n",deadend.size());
	}
    return 0;
}


