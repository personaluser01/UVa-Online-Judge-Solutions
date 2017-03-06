/*
 * 1515. Pool Construction
 * TOPIC: network flow, maxflow, mincut, very very neat, could not have though myself
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define H (0x40)
#define N H
#define MAXV (1<<12)
#define MAXE (1<<21)
#define oo (1LL<<60)
#define vc(x,y) (0<=(x) && (x)<m && 0<=(y) && (y)<n)
typedef long long i64;

i64 min( i64 x, i64 y ) { return x<y?x:y; }

int m,n,dig,fill,boundary,src,sink,to[MAXE],next[MAXE],last[MAXV],V,E,visited[MAXV],yes,seen[MAXV],indeed,*tail,*head,q[MAXV],
	di[] = {-1,0,1,0},
	dj[] = {0,1,0,-1};
char g[N][N];
i64 flow[MAXE],cap[MAXE],d[MAXV];

void add_arcs( int x, int y, i64 c ) {
	int i = E++, j = E++;
	to[i] = y, next[i] = last[x], last[x] = i, cap[i] = c, flow[i] = 0;
	to[j] = x, next[j] = last[y], last[y] = j, cap[j] = 0, flow[j] = 0;
}

int bfs() {
	int x,y,i;
	for ( head = tail = q, d[*tail++ = sink] = 0, visited[sink] = ++indeed; head < tail; )
		for ( i = last[x = *head++]; i >= 0; i = next[i] )
			if ( cap[i^1] > flow[i^1] && visited[y = to[i]] != indeed ) 
				visited[y] = indeed, d[*tail++ = y] = d[x]+1;
	return visited[src] == indeed;
}

i64 dfs( int x, i64 df ) {
	i64 dt;
	int i,y;
	if ( x == sink ) return df;
	if ( seen[x] == yes ) return 0;
	for ( seen[x] = yes, i = last[x]; i >= 0; i = next[i] )
		if ( flow[i] < cap[i] && visited[y = to[i]] == indeed && d[y]+1 == d[x] )
			if ( dt = dfs(y,min(df,cap[i]-flow[i])) ) {
				flow[i] += dt, flow[i^1] -= dt;
				return dt;
			}
	return 0;
}

i64 maxflow() {
	i64 T = 0, t = 0;
	for(;bfs();)
		for (;++yes&&(t=dfs(src,+oo));T+=t);
	return T;
}

int main() {
	int i,j,k,l,ts,ni,nj;
	i64 ans;
#ifndef ONLINE_JUDGE
	freopen("1515.in","r",stdin);
#endif
	for ( scanf("%d",&ts); ts-- && 2 == scanf("%d %d",&n,&m); ) {
		scanf("%d %d %d",&dig,&fill,&boundary);
		for ( i = 0; i < m; scanf("%s",g[i++]) );
		for ( ans = 0, V = m*n+5, src = m*n, sink = m*n+1, E = 0, i = 0; i < V; last[i++] = -1 );
		for ( i = 0; i < m; ++i )
			for ( j = 0; j < n; ++j ) {
				if ( i == 0 || i == m-1 || j == 0 || j == n-1 ) {
					if ( g[i][j] == '.' ) 
						ans += fill, g[i][j] = '#';
					add_arcs(src,i*n+j,+oo);
				}
				else if ( g[i][j] == '#' )
					add_arcs(src,i*n+j,dig);
				else if ( g[i][j] == '.' )
					add_arcs(i*n+j,sink,fill);
				for ( l = 0; l < 4; ++l )
					if ( vc(ni = i+di[l],nj = j+dj[l]) )
						add_arcs(i*n+j,ni*n+nj,boundary);
			}
		printf("%lld\n",ans+maxflow());
	}
	return 0;
}

