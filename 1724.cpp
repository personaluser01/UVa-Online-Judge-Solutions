/*
 * 1724. Solitaire
 * TOPIC: bfs, meet-in-the-middle
 * status: Accepted
 */
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <set>
#include <map>
#include <queue>
#include <iostream>
#define BIT(k) (1ULL<<(k))
#define MASK(k) (BIT(k)-1ULL)
#define L(k) ((k)&((~(k))+1ULL))
#define vc(x,y) (0<=(x)&&(x)<8&&0<=(y)&&(y)<8)
#define oo 0xfffffffful
#define xchg(x,y) (((x)==(y))||((x)^=(y),(y)^=(x),(x)^=(y)))
#define SH 6
#define Q (((64*(64-1)*(64-2)*(64-3))/24)+0x400)
#define A(u,i) (((u)>>((i)*SH))&MASK(SH))
#define enc(x,y) ((x)|((y)<<3))
typedef unsigned long long u64;
typedef unsigned int state;
using namespace std;

int dx[] = {-1,0,1,0},
	dy[] = {0,1,0,-1};

state rinput() {
	int i,j,k;
	unsigned int v[4];
	for ( k = 0; k < 4; ++k ) {
		if ( 2 != scanf("%d %d",&i,&j) ) return 0;
		--i, --j, v[k] = enc(i,j);
	}
	for ( j = 1; j; )
		for ( i = j = 0; i < 3; ++i )
			if ( v[i] > v[i+1] )
				xchg(v[i],v[i+1]),++j;
	return v[0]|(v[1]<<6)|(v[2]<<12)|(v[3]<<18);
}

state normalize( state u ) {
	unsigned int v[4],w=A(u,3);
	int i,j,k;
	for ( i = 0; i < 4; ++i ) v[i] = A(u,i);
	for ( i = 0; i < 2; ++i )
		assert( v[i] < v[i+1] );
	for ( i = 3; i >= 1 && v[i] < v[i-1]; --i ) xchg(v[i],v[i-1]);
	/*
	for ( j = 1; j; )
		for ( i = j = 0; i < 3; ++i )
			if ( v[i] > v[i+1] )
				xchg(v[i],v[i+1]), ++j;*/
	for ( i = 0; i < 3; ++i )
		assert( v[i] < v[i+1] );
	return v[0]|(v[1]<<6)|(v[2]<<12)|(v[3]<<18);
}

state move( state u, int idx, const int dir ) {
	unsigned int w = A(u,idx),v;
	int x = (w&MASK(3)), y = (w>>3),
		nx = x+dx[dir], ny = y+dy[dir];
	if ( !vc(nx,ny) ) return +oo;
	v = enc(nx,ny);
	assert( v != w );
	if ( v > w ) {
		for ( int l = idx+1; l < 4; ++l )
			if ( A(u,l) == v ) {
				nx += dx[dir], ny += dy[dir];
				if ( !vc(nx,ny) ) return +oo;
				for ( int t = 0; t < 4; ++t )
					if ( A(u,t) == enc(nx,ny) )
						return +oo;
				v = enc(nx,ny);
				break ;
			}
	}
	else {
		for ( int l = idx-1; l >= 0; --l )
			if ( A(u,l) == v ) {
				nx += dx[dir], ny += dy[dir];
				if ( !vc(nx,ny) ) return +oo;
				for ( int t = 0; t < 4; ++t )
					if ( A(u,t) == enc(nx,ny) )
						return +oo;
				v = enc(nx,ny);
				break ;
			}
	}
	w = (u>>((idx+1)*6));
	u &= ~(MASK(24)<<(idx*6));
	assert( A(u,idx) == 0 );
	return normalize((u|(w<<(idx*6))|(v<<18))&MASK(24));
}

state q[Q],*head,*tail,dist;
set<state> m,s;

void bfs( state src ) {
	state u,v;
	int i,j,len;
	for ( m.clear(),dist=0,head=tail=q,m.insert(*tail++=src),len=tail-head; head<tail && dist<=4; ) {
		u = *head++;
		if ( dist == 4 ) goto nx01;
		for ( i=0; i<4; ++i ) 
			for ( j=0; j<4; ++j )
				if ( (v=move(u,i,j)) < +oo ) 
					if ( m.find(v)==m.end() )
						m.insert(*tail++=v);
nx01:
		if ( !--len ) ++dist, len=tail-head;
	}
}

int BFS( state src ) {
	state u,v;
	int i,j,len;
	for ( s.clear(),dist=0,head=tail=q,s.insert(*tail++=src),len=tail-head; head<tail && dist<=4; ) {
		u = *head++;
		if ( m.find(u) != m.end() ) return 1;
		if ( dist == 4 ) goto nx02;
		for ( i = 0; i < 4; ++i )
			for ( j = 0; j < 4; ++j )
				if ( (v=move(u,i,j)) < +oo )
					if ( s.find(v)==s.end() )
						s.insert(*tail++=v);
nx02:
		if ( !--len ) ++dist,len=tail-head;
	}
	return 0;
}

int main() {
	int i,j,k;
	state src,dst;
#ifndef ONLINE_JUDGE
	freopen("c.txt","r",stdin);
#endif
	for ( ;src = rinput(); ) {
		assert( dst = rinput() );
		m.clear(), bfs(src), puts(BFS(dst)?"YES":"NO");
	}
	return 0;
}

