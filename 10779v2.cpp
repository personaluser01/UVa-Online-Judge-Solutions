/*
 * 10799. Collector's Problem
 * status: Accepted
 */
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>
#include <queue>
#define N 11
#define M 26
#define Q (5000)
using namespace std;
#define oo 0xfffffffful

typedef struct edge { struct edge *back_edge; int x,y,capacity,flow; } edge;
int n,m,ts,cs,Cnt[M][N],V,E,src[N],sink[N],u[M][N],v[M][N],p[Q];
vector<int> adj[Q];
edge e[Q],*ee[Q];
unsigned int d[Q];
queue<int> q;

void add_arcs( int x, int y, int c ) {
	int i,j;
	e[i = E].x = x, e[E].y = y, e[E].capacity = c, e[E].flow = 0, ++E;
	e[j = E].x = y, e[E].y = x, e[E].capacity = 0, e[E].flow = 0, ++E;
	e[i].back_edge = e+j, e[j].back_edge = e+i;
}

int bfs( int src, int dst ) {
	int i,j,k,x,y;
	for ( x = 0; x < V; ++x ) d[x] = +oo;
	for (q.push(src),d[src] = 0;!q.empty()&&d[dst]==+oo;)
		for ( x = q.front(), q.pop(), i = 0; i < (int)adj[x].size(); ++i )
			if ( e[j = adj[x][i]].capacity > e[j = adj[x][i]].flow )
				if ( d[y = e[j].y] > d[x]+1 )
					d[e[j].y]=d[x]+1,q.push(y),p[y]=x,ee[y]=e+j;
	while ( !q.empty() ) q.pop();
	return d[dst] < +oo;
}

int retrace( int src, int x, int df ) {
	if ( x != src )
		return retrace(src,p[x],min(df,ee[x]->capacity-ee[x]->flow));
	return df;
}

void update( int src, int x, int df ) {
	if ( x != src ) {
		ee[x]->flow+=df,ee[x]->back_edge->flow -= df;
		update(src,p[x],df);
	}
}

int main() {
	int i,j,k,l,t,x,y;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( scanf("%d",&ts); ts--; E = V = 0 ) {
		scanf("%d %d",&n,&m);
		for ( i = 0; i < m; ++i )
			for ( j = 0; j < n; ++j )
				Cnt[i][j] = 0;
		for ( j = 0; j < n; ++j ) 
			for ( scanf("%d",&l); l--; scanf("%d",&t), ++Cnt[--t][j] );
		for ( j = 0; j < n; ++j ) {
			src[j] = V++, sink[j] = V++;
			add_arcs(sink[j],src[j],m*m);
			for ( i = 0; i < m; ++i )
				u[i][j] = V++, v[i][j] = V++;
			for ( i = 0; i < m; ++i )
				if ( Cnt[i][j] >= 2 )
					add_arcs(src[j],v[i][j],Cnt[i][j]-1);
				else if ( !Cnt[i][j] )
					add_arcs(u[i][j],sink[j],1);
		}
		for ( j = 0; j < n; ++j )
			for ( k = 0; k < n; ++k )
				if ( k != j )
					for ( i = 0; i < m; ++i )
						add_arcs(v[i][j],u[i][k],1);
		for ( i = 0; i < V; ++i ) adj[i].clear();
		for ( i = 0; i < E; ++i )
			adj[e[i].x].push_back(i);
		for(;bfs(src[0],sink[0]);update(src[0],sink[0],retrace(0[src],sink[0],(1<<29))) );
		for ( k = 0, i = 0; i < E; ++i )
			if ( e[i].y == sink[0] )
				k += e[i].flow;
		for ( i = 0; i < m; ++i )
			if ( Cnt[i][0] && ++k );
		printf("Case #%d: %d\n",++cs,k);
	}
	return 0;
}
