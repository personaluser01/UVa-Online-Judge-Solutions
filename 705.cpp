/*
 * 705. Slash Maze
 * status: Accepted
 */
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#define N 0x80
#define EI	(puts("There are no cycles.\n"))
#define KYLLA(x,y) (printf("%d Cycles; the longest has length %d.\n\n",x,y))
#define SH 7
#define M(k) ((1UL<<(k))-1UL)
#define enc(x,y,t) ((x) | ((y) << SH) | ((t) << (SH+SH)))
#include <queue>
#include <vector>
using namespace std;
typedef unsigned int state;;
#define Q (1UL << (SH+SH+2))
#define valid_cell(x,y) (0<=(x)&&(x)<m&&0<=(y)&&(y)<n)
enum { ONE, TWO, THREE, FOUR };
char direction[4][3] = {"NE","NW","SW","SE"};
#define oo 0xfffffffful

int m,n,ts,ax,V;
unsigned int d[Q],ML,anc[Q][SH+SH+2],MML;
char g[N][N];
vector<state> adj[Q];
queue<state> q;

void add_edge( state u, state v ) {
	if ( u < +oo && v < +oo )
		adj[u].push_back(v);
}

state promote( state u, unsigned int k ) {
	int i;
	for ( i = 0; (1UL << i) <= k; ++i );
	for (;i >= 0; --i )
		if ( (k >> i) & 1 )
			u = anc[u][i];
	return u;
}

state lca( state u, state v ) {
	int K;
	if ( d[u] < d[v] )
		return lca(v,u);
	if ( d[u] > d[v] ) 
		return lca(promote(u,d[u]-d[v]),v);
	assert( d[u] == d[v] );
	if ( u == v )
		return u;
	for ( K = 0; (1 << K) <= d[u]; ++K );
	assert( K );
	if ( anc[u][0] == anc[v][0] )
		return anc[u][0];
	assert( u != v );
	assert( anc[u][K] == anc[v][K] );
	for (;; u = anc[u][K], v = anc[v][K] ) {
		if ( anc[u][0] == anc[v][0] )
			return anc[u][0];
		for(;anc[u][K] == anc[v][K]; --K );
	}
	assert( anc[u][0] == anc[v][0] );
	assert( u != v );
	return anc[u][0];
}

char color[Q];
int papa[Q];
enum { WHITE = 0, GREY = 1, BLACK = 2 };

void dfs( state u, unsigned int depth ) {
	state v;
	int x,y,t,nx,ny,nt;
	assert( color[u] == WHITE );
	color[u] = GREY;
	d[u] = depth;
	for ( int i = 0; i < (int)adj[u].size(); ++i )
		if ( color[v = adj[u][i]] == WHITE )
			papa[v] = u, dfs( v, depth+1 );
		else if ( color[v] == GREY )
			if ( papa[u] != v ) {
				++ax;
				if ( ML < d[u]-d[v]+1 )
					ML = d[u]-d[v]+1;
			}
	color[u] = BLACK;
}

void bfs( state src ) {
	state u,v,z;
	unsigned int cycle_length;
	int i,j,k,t;
	assert( !q.size() );
	i = src & M(SH), j = (src >> SH) & M(SH), t = (src >> (SH+SH));
	for ( d[src] = 0, q.push(src); !q.empty(); )
		for ( u = q.front(), q.pop(), i = 0; i < (int)adj[u].size(); ++i )
			if ( d[v = adj[u][i]] > d[u] + 1 ) {
				for ( q.push(v),  d[v] = d[anc[v][0] = u] + 1, k = 1; (1 << k) <= d[v] ; ++k )
					anc[v][k] = anc[anc[u][k-1]][k-1];
			}
			else if ( d[v] < d[u]+1 ) {
				z = lca(u,v);
				assert( z < +oo );
				cycle_length = (d[u]-d[z]) + (d[v]-d[z]) + 1;
				if ( cycle_length > MML )
					MML = cycle_length;
			}
}

state names[Q];

void name_them( state u, state v ) {
	if ( names[u] == +oo && names[v] == +oo )
		names[u] = names[v] = V++;
	else if ( names[u] < +oo && names[v] == +oo )
		names[v] = names[u];
	else if ( names[u] == +oo && names[v] < +oo )
		names[u] = names[v];
	else {
		assert( names[u] == names[v] );
	}
}

int main() {
	int i,j,k,ii,jj;
	state u,v;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	while ( 2 == scanf("%d %d",&n,&m) && (m||n) ) {
		for ( i = 0; i < m; ++i )
			scanf("%s",g[i]);

		for ( i = 0; i < m; ++i )
			for ( j = 0; j < n; ++j )
				for ( k = ONE; k <= FOUR; ++k )
					names[enc(i,j,k)] = +oo; 

		for ( V = 0, i = 0; i < m; ++i )
			for ( j = 0; j < n; ++j ) {
					ii = i, jj = j+1;
					if ( valid_cell(ii,jj) ) {
						u = enc(i,j,ONE), v = enc(ii,jj,THREE);
						name_them(u,v);
					}
					ii = i+1, jj = j;
					if ( valid_cell(ii,jj) ) {
						u = enc(i,j,FOUR), v = enc(ii,jj,TWO);
						name_them(u,v);
					}
					ii = i, jj = j-1;
					if ( valid_cell(ii,jj) ) {
						u = enc(i,j,THREE), v = enc(ii,jj,ONE);
						name_them(u,v);
					}
					ii = i-1, jj = j;
					if ( valid_cell(ii,jj) ) {
						u = enc(i,j,TWO), v = enc(ii,jj,FOUR);
						name_them(u,v);
					}
			}
		for ( u = 0; u < V; ++u )
			adj[u].clear();
		for ( i = 0; i < m; ++i )
			for ( j = 0; j < n; ++j )
				if ( g[i][j] == '/' ) {
					u = names[enc(i,j,ONE)];
					v = names[enc(i,j,FOUR)];
					add_edge(u,v);
					add_edge(v,u);
					u = names[enc(i,j,TWO)];
					v = names[enc(i,j,THREE)];
					add_edge(u,v);
					add_edge(v,u);
				}
				else {
					u = names[enc(i,j,ONE)];
					v = names[enc(i,j,TWO)];
					add_edge(u,v);
					add_edge(v,u);
					u = names[enc(i,j,THREE)];
					v = names[enc(i,j,FOUR)];
					add_edge(u,v);
					add_edge(v,u);
				}
		MML = ML = 0, ax = 0;
		for ( u = 0; u < V; ++u )
			for ( d[u] = +oo, k = 0; (1 << k) <= V; ++k )
				anc[u][k] = +oo;
		for ( u = 0; u < V; ++u )
			if ( d[u] == +oo )
				bfs(u);
		for ( u = 0; u < V; color[u++] = WHITE );
		for ( u = 0; u < V; ++u )
			if ( color[u] == WHITE )
				dfs(u,0);
		printf("Maze #%d:\n",++ts);
		if ( ax && MML > 2 )
			KYLLA(ax,MML);
		else EI;
	}
	return 0;
}

