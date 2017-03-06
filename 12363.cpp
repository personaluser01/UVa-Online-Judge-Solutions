/*
 * 12363. Gedge Maze
 * TOPIC: graph theory, bridge, lca queries, dfs, bfs
 * status: Accepted
 */
#include <cassert>
#include <cstdio>
#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <cmath>
#include <vector>
#include <queue>
#define N (1<<14)
#include <set>
enum{ WHITE = 0, GRAY = 1, BLACK = 2 };
#define DB 0
#define K 15
using namespace std;

int n,m,qr,p[N],seen[N],yes,color[N],h[N],d[N],anc[N][K],rank[N],par[N];
queue<int> q;
vector<int> adj[N];
set<pair<int,int> > bridge;

void link( int x, int y ) {
	if ( rank[x] > rank[y] )
		par[y] = x;
	else {
		par[x] = y;
		if ( rank[x] == rank[y] ) ++rank[y];
	}
}

int find( int x ) { return par[x] = par[x]==x?x:find(par[x]); }

void merge( int x, int y ) { link(find(x),find(y)); }

void dfs( int x, int depth ) {
	int i,y;
	assert( color[x] == WHITE );
	h[x] = d[x] = depth, color[x] = GRAY, seen[x] = yes;
	for ( i = 0; i < (int)adj[x].size() && (y=adj[x][i]) >= 0; ++i ) {
		if ( color[y] == WHITE ) {
			DB && printf("%d-->%d\n",x+1,y+1);
			p[y] = x, dfs(y,depth+1);
			h[x] = min(h[x],h[y]);
			if ( h[y] >= d[x]+1 )
				bridge.insert(make_pair(x,y)), bridge.insert(make_pair(y,x));
		}
		else if ( color[y] == GRAY ) {
			if ( p[x] == y ) continue ;
			h[x] = min(h[x],d[y]);
		}
		else {
			DB && printf("[forward edge] Attempted from %d to %d\n",x+1,y+1);
			continue ;
		}
	} 
	DB && printf("d[%d] = %d, h[%d] = %d\n",x+1,d[x],x+1,h[x]);
	color[x] = BLACK;
}

void bfs( int src ) {
	int x,y,i,k;
	for ( d[x=src]=0,q.push(x),seen[x]=yes; !q.empty(); )
		for ( x=q.front(),q.pop(),i=0; i<(int)adj[x].size(); ++i )
			if ( seen[y=adj[x][i]]!=yes ) 
				for ( d[y]=d[x]+1, q.push(y), seen[y] = yes, anc[y][0] = x, k = 1; k < K; ++k )
					anc[y][k] = anc[anc[y][k-1]][k-1];
}

int up( int x, unsigned int k ) {
	int i;
	for ( i = 0; k; ++i, k >>= 1 )
		if ( k&1 ) x = anc[x][i];
	return x;
}

int lca( int x, int y ) {
	int k;
	if ( d[x] < d[y] )
		return lca(y,x);
	if ( d[x] > d[y] )
		return lca(up(x,d[x]-d[y]),y);
	assert( d[x] == d[y] );
	if ( x == y )
		return x;
	for ( k = K-1; k; --k ) {
		assert( anc[x][k] == anc[y][k] );
		if ( anc[x][k-1] != anc[y][k-1] )
			x = anc[x][k-1], y = anc[y][k-1];
	}
	assert( anc[x][0] == anc[y][0] );
	return anc[x][0];
}

bool test( int x, int parent ) {
	for (;x != parent; x = anc[x][0] )
		if ( bridge.find(make_pair(anc[x][0],x))==bridge.end() )
			return false;
	return true;
}

int main() {
	int i,j,k,l;
#ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
#endif
	for(;3 == scanf("%d %d %d",&n,&m,&qr) && (n||m||qr); puts("-") ) {
		for( i = 0; i < n; color[i] = 0, adj[i++].clear() );
		for ( i = 0; i < n; ++i ) rank[par[i] = i] = 0;
		for( ;m-- && 2 == scanf("%d %d",&i,&j); adj[i].push_back(j), adj[j].push_back(i) )
			if ( find(--i) != find(--j) )
				merge(i,j);
		for ( i = 0; DB && i < n; ++i )
			sort(adj[i].begin(),adj[i].end());
		for ( ++yes, bridge.clear(), i = 0; i < n; ++i )
			if ( seen[i] != yes ) p[i] = -1, dfs(i,0);
		for ( set<pair<int,int> >::iterator it = bridge.begin(); DB && it != bridge.end(); ++it )
			printf("%d %d\n",it->first+1, it->second+1);
		for ( i = 0; i < n; ++i )
			for ( k = 0; k < K; ++k )
				anc[i][k] = -1;
		for ( ++yes, i = 0; i < n; ++i )
			if ( seen[i] != yes ) 
				bfs(i);
		for(;qr-- && 2 == scanf("%d %d",&i,&j); ) {
			if ( find(--i) != find(--j) ) {
				puts("N");
				continue ;
			}
			k = lca(i,j);
			DB && printf("lca(%d,%d) = %d\n",i+1,j+1,k+1);
			if ( test(i,k) && test(j,k) ) puts("Y");
			else puts("N");
		}
	}
    return 0;
}


