/*
 * 10779. Collector's Problem
 */
#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>
#include <queue>
#define N 16
#define M 32
#define Bob 0
#define Q 500
using namespace std;
#define oo 0xfffffffful

typedef struct edge { struct edge *back_edge; int x,y; int capacity, flow; } edge;
int ts,cs,n,m,Cnt[N][M],src,sink,V,E,v[N][M],parent[Q];
unsigned int dist[Q];
edge e[Q*Q],*ee[Q];
vector<int> adj[Q],u[M];
queue <int> q;

void add_arcs( int x, int y, int c ) {
	int i,j;
	e[i = E].x = x, e[E].y = y, e[E].capacity = c, e[E].flow = 0, ++E;
	e[j = E].x = y, e[E].y = x, e[E].capacity = 0, e[E].flow = 0, ++E;
	e[i].back_edge = e+j, e[j].back_edge = e+i;
}

int bfs() {
	int x,y,i,j;
	for ( x = 0; x < V; ++x ) dist[x] = +oo;
	for ( parent[src] = -1, dist[src] = 0, q.push(src); !q.empty() && dist[sink] == +oo;)
		for ( x = q.front(), q.pop(), i = 0; i < (int)adj[x].size(); ++i )
			if ( e[j = adj[x][i]].capacity > e[j = adj[x][i]].flow )
				if ( dist[y = e[j].y] > dist[x] + 1 )
					dist[y]=dist[parent[y]=x]+1,q.push(y),ee[y]=e+j;
	while ( !q.empty() ) q.pop();
	return dist[sink] < +oo;
}

int retrace( int x, int df ) {
	assert( x >= 0 );
	if ( x != src ) 
		return retrace(parent[x],min(df,ee[x]->capacity-ee[x]->flow));
	return df;
}

void update_flow( int x, int df ) {
	assert( df > 0 );
	assert( x >= 0 );
	if ( x != src ) 
		ee[x]->flow += df, ee[x]->back_edge->flow -= df, update_flow(parent[x],df);
}

int main() {
	int i,j,k,l,t,x,y;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( scanf("%d",&ts); ts--; ) {
		printf("Case #%d: ",++cs), scanf("%d %d",&n,&m);
		for ( i = 0; i < m; ++i )
			for ( j = 0; j < n; Cnt[j++][i] = 0 );
		for ( i = 0; i < n; ++i ) 
			for ( scanf("%d",&l); l--; scanf("%d",&t), ++Cnt[i][--t] );
		src = 0, sink = m+1, V = m+2, E = 0;
		for ( i = 0; i < m; u[i++].clear() );
		for ( i = 0; i < m; ++i ) 
			if ( (v[Bob][i] = V++), Cnt[Bob][i] )
				add_arcs(src,v[Bob][i],Cnt[Bob][i]);
		for ( i = 0; i < m; ++i )
			for ( j = 1; j < n; ++j ) {
				u[i].push_back(k = V++);
				if ( Cnt[Bob][i] >= 2 )
					add_arcs(v[Bob][i],k,1);
			}
		for ( j = 1; j < n; ++j ) 
			for ( i = 0; i < m; ++i )
				if ( Cnt[j][i] >= 2 ) 
					v[j][i] = V++, add_arcs(v[j][i],v[Bob][i],Cnt[j][i]-1);
		for ( j = 1; j < n; ++j )
			for ( i = 0; i < m; ++i )
				if ( !Cnt[j][i] )
					for ( k = 0; k < m; ++k )
						if ( Cnt[j][k] >= 2 )
							add_arcs(u[i][j-1],v[j][k],1);
		for ( i = 0; i < m; ++i )  add_arcs(v[Bob][i],i+1,1);
		for ( i = 1; i <= m; ++i ) add_arcs(i,sink,1);
		for ( i = 0; i < V; ++i ) adj[i].clear();
		for ( i = 0; i < E; ++i ) adj[e[i].x].push_back(i);
		for (;bfs();update_flow(sink,retrace(sink,(1<<29))));
		for ( k = 0, i = 1; i <= m; ++i )
			for ( j = 0; j < (int)adj[i].size(); ++j )
				if ( e[adj[i][j]].y == sink )
					k += e[adj[i][j]].flow;
		printf("%d\n",k);
	}
	return 0;
}

