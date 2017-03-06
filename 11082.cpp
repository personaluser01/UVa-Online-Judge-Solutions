/*
 * 11082. Matrix Decompressing
 * status: Accepted
 */
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
#include <cassert>
#define N 32
#define Q (N*N)
using namespace std;
#define oo 0xfffffffful
typedef long long i64;

int ts,cs,src,sink,E,V,m,n,p[Q],g[N][N];
unsigned int d[Q];
i64 rsum[N],csum[N],row[N],col[N];
typedef struct edge { 
	struct edge *back_edge; 
	int x,y,capacity,flow; 
} edge;
edge e[Q],*ee[Q];
vector<int> adj[Q];
queue<int> q;

void add_arcs( int x, int y, int c ) {
	int i,j;
	e[i = E++].x = x, e[i].y = y, e[i].capacity = c, e[i].flow = 0;
	e[j = E++].x = y, e[j].y = x, e[j].capacity = 0, e[j].flow = 0;
	(e[i].back_edge = e+j)->back_edge = e+i;
}

int retrace( int x, int df ) { return x==src?df:retrace(p[x],min(df,ee[x]->capacity-ee[x]->flow)); }
void update( int x, int df ) { if ( x != src ) ee[x]->flow += df, ee[x]->back_edge->flow -= df, update(p[x],df); }
int bfs() {
	int i,j,x,y;
	for ( x = 0; x < V; ++x ) d[x] = +oo;
	for ( q.push(src), d[src] = 0; !q.empty() && d[sink] == +oo;)
		for ( x = q.front(), q.pop(), i = 0; i < (int)adj[x].size(); ++i )
			if ( e[j = adj[x][i]].capacity > e[j = adj[x][i]].flow )
				if ( d[y = e[j].y] > d[x]+1 )
					d[y] = d[x]+1, q.push(y), p[y] = x, ee[y] = e+j;
	for(;!q.empty();q.pop());
	return d[sink]<+oo;
}

int main() {
	int i,j,k;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( scanf("%d",&ts); ts-- && 2 == scanf("%d %d",&m,&n) && printf("Matrix %d\n",++cs);) {
		for ( i = 1; i <= m; ++i ) scanf("%lld",rsum+i), row[i] = rsum[i]-rsum[i-1], row[i] -= n;
		for ( i = 1; i <= n; ++i ) scanf("%lld",csum+i), col[i] = csum[i]-csum[i-1], col[i] -= m;
		for ( E = 0, src = 0, sink = m+n+1, V = m+n+2, i = 1; i <= m; ++i )
			add_arcs(src,i,row[i]);
		for ( i = 1; i <= m; ++i )
			for ( j = 1; j <= n; ++j )
				add_arcs(i,j+m,19);
		for ( j = 1; j <= n; ++j )
			add_arcs(j+m,sink,col[j]);
		for ( i = 0; i < V; ++i ) adj[i].clear();
		for ( i = 0; i < E; ++i )
			adj[e[i].x].push_back(i);
		for(;bfs();update(sink,retrace(sink,(1<<29))) );
		for ( k = 0; k < E; ++k ) {
			i = e[k].x, j = e[k].y;
			if ( 1 <= i && i <= m )
				if ( m+1 <= j && j <= m+n ) {
					/*assert( e[k].flow >= 0 );*/
					g[i-1][j-m-1] = e[k].flow+1;
				}
		}
		for ( i = 0; i < m; printf("%d\n",g[i++][j]) )
			for ( j = 0; j < n-1; ++j )
				printf("%d ",g[i][j]);
		putchar('\n');
	}
	return 0;
}
