/*
 * 12272. Fake Scoreboard
 * TOPIC: maxflow, lexicographically smallest, bipartite matching
 * status: Accepted
 */
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 0x80
#define MAXV (1<<14)
#define MAXE (1<<20)

int min( int x, int y ) { if ( x < y ) return x; return y; }

typedef struct arc {
	int y,flow,cap;
	struct arc *rev;
} arc;

int m,n,inflow[N],outflow[N],Total,src,sink,V,E,deg[MAXV],visited[MAXV],seen[MAXV],indeed,yes,d[MAXV],q[MAXV],*head,*tail,
	idx[N][N];
arc e[MAXE],*adj[MAXV][MAXV>>7];
char g[N][N];

int forbidden( int x, int y, int u, int v ) {
	return 1 <= x && x <= m && m+1 <= y && y <= m+n && (x<u||x==u&&y<=v) || 1 <= y && y <= m && m+1 <= x && x <= m+n && (y<u||y==u&&x<=v);
}

void add_arcs( int x, int y, int c ) {
	arc *a = &e[E++], *b = &e[E++];
	a->y = y, b->y = x, a->flow = b->flow = 0, a->cap = c, b->cap = 0;
	a->rev = b, b->rev = a;
	adj[x][deg[x]++] = a, adj[y][deg[y]++] = b;
}

int bfs( int u, int v ) {
	int x,y,i;
	for ( head=tail=q,d[*tail++=sink]=0,visited[sink]=++indeed; head<tail;)
		for ( x=*head++, i = 0; i < deg[x]; ++i )
			if ( adj[x][i]->rev->flow < adj[x][i]->rev->cap )
				if ( visited[y=adj[x][i]->y] != indeed && !forbidden(x,y,u,v) )
					visited[*tail++=y]=indeed, d[y]=d[x]+1;
	return visited[src] == indeed;
}

int dfs( int x, int df, int u, int v ) {
	int dt,i,y;
	if ( x == sink ) return df;
	if ( seen[x] == yes ) return 0;
	for ( seen[x] = yes, i = 0; i < deg[x]; ++i ) 
		if ( adj[x][i]->flow < adj[x][i]->cap && seen[y = adj[x][i]->y] != yes )
			if ( !forbidden(x,y,u,v) && visited[y] == indeed && d[y]+1 == d[x] )
				if ( dt = dfs(y,min(df,adj[x][i]->cap-adj[x][i]->flow),u,v) ) {
					adj[x][i]->flow += dt;
					adj[x][i]->rev->flow -= dt;
					return dt;
				}
	return 0;
}

int maxflow( int u, int v ) {
	int dt,t = 0;
	for(;bfs(u,v);)
		for (;++yes&&(dt=dfs(src,1<<29,u,v));t+=dt);
	return t;
}

int find_way_around( int u, int v ) {
	int l,t;
	l = idx[u][v-m];
	if ( adj[u][l]->flow == 0 )
		return 1;
	assert( adj[u][l]->y == v );
	assert( adj[u][l]->flow == 1 );

	l = deg[u]-1;
	assert( adj[u][l]->y == src );
	assert( adj[u][l]->rev->flow == outflow[u] );
	--adj[u][l]->rev->flow, ++adj[u][l]->flow;
	l = 0;
	assert ( adj[v][l]->y == sink );
	assert( adj[v][l]->flow == inflow[v-m] );
	--adj[v][l]->flow, ++adj[v][l]->rev->flow;
	l = idx[u][v-m];
	--adj[u][l]->flow, ++adj[u][l]->rev->flow;
	if ( !(t = maxflow(u,v)) ) {
		l = deg[u]-1;
		assert( adj[u][l]->y == src );
		++adj[u][l]->rev->flow, --adj[u][l]->flow;
		l = 0;
		assert( adj[v][l]->y == sink );
		++adj[v][l]->flow, --adj[v][l]->rev->flow;
		l = idx[u][v-m];
		++adj[u][l]->flow, --adj[u][l]->rev->flow;
	}
	else 
		assert( t == 1 );
	return t;
}

int main() {
	int i,j,k,cs = 0,T,flag,l;
	arc *tmp;
#ifndef ONLINE_JUDGE
	freopen("12272.in","r",stdin);
#endif
	for ( ;2==scanf("%d %d",&m,&n) && (m||n); ) {
		if ( ++cs > 1 ) putchar('\n');
		Total = 0, V = 1+m+n+1, src = 0, sink = V-1, E = 0;
		for ( i = 1; i <= m; ++i ) scanf("%d",&outflow[i]), Total += outflow[i];
		for ( T = Total, j = 1; j <= n; ++j ) scanf("%d",&inflow[j]), Total -= inflow[j];
		if ( Total ) {
			nx: puts("Impossible");
			continue ;
		}
		for ( i = src; i <= sink; deg[i++] = 0 );
		for ( i = 1; i <= m; ++i ) 
			add_arcs(src,i,outflow[i]);
		for ( i = 1; i <= m; ++i )
			for ( j = 1; j <= n; ++j )
				add_arcs(i,j+m,1);
		for ( j = 1; j <= n; ++j )
			add_arcs(j+m,sink,inflow[j]);
		for ( i = 1; i <= m+n; ++i ) 
			for ( flag = 1; flag; )
				for ( flag = 0, j = 0; j < deg[i]-1; ++j )
					if ( adj[i][j]->y < adj[i][j+1]->y ) 
						flag = 1, tmp = adj[i][j], adj[i][j] = adj[i][j+1], adj[i][j+1] = tmp;
		if ( (k = maxflow(-1,-1)) != T ) goto nx;
		for ( i = src; i <= sink; ++i ) {
			for ( l = 0; l < deg[i]; ++l ) {
				assert( adj[i][l]->flow <= adj[i][l]->cap );
				assert( adj[i][l]->rev->y == i );
				assert( adj[i][l]->flow+adj[i][l]->rev->flow == 0 );
			}
		}
		for ( i = 1; i <= m; ++i )
			for ( l = 0; l < deg[i]; ++l ) 
				if ( adj[i][l]->y != src && adj[i][l]->y != sink )
					j = adj[i][l]->y, idx[i][j-m] = l;
		for ( i = 1; i <= m; ++i )
			for ( j = 1; j <= n; ++j ) {
				l = idx[i][j];
				assert( adj[i][l]->y == j+m );
				if ( adj[i][l]->flow ) {
					assert( adj[i][l]->flow == 1 );
					if ( find_way_around(i,j+m) ) {
						/*printf("(%d,%d)\n",i,j);*/
						assert( adj[i][l]->flow == 0 );
					}
				}
			}
		for ( i = 1; i <= m; ++i )
			for ( j = 1; j <= n; ++j )
				if ( adj[i][l = idx[i][j]]->flow == 1 )
					g[i][j] = 'Y';
				else g[i][j] = 'N';
		for ( i = 1; i <= m; g[i][n+1] = '\0', puts(g[i++]+1) );
	}
	return 0;
}

