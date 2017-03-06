/*
 * 12264. Risk
 * TOPIC: maxflow, binary search, not-my-idea
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 0x80
#define MAXV (N*2)
#define MAXE (1<<21)
#define oo (1<<29)
int min( int x, int y ) { return x<y?x:y; }

int V,E,to[MAXE],last[MAXV],next[MAXE],flow[MAXE],cap[MAXE],visited[MAXV],indeed,seen[MAXV],yes,d[MAXV],q[MAXV],*head,*tail,src,sink,a[N],n,
	inner,outer;
char is_border[N],g[N][N];

void add_arcs( int x, int y, int c ) {
	int i = E++, j = E++;
	to[i] = y, next[i] = last[x], last[x] = i, flow[i] = 0, cap[i] = c;
	to[j] = x, next[j] = last[y], last[y] = j, flow[j] = 0, cap[j] = 0;
}

int bfs() {
	int i,x,y;
	for ( head = tail = q, d[*tail++ = sink] = 0, visited[sink] = ++indeed; head < tail; )
		for ( i = last[x = *head++]; i >= 0; i = next[i] )
			if ( flow[i^1] < cap[i^1] && visited[y = to[i]] != indeed )
				visited[*tail++ = y] = indeed, d[y] = d[x]+1;
	return visited[src] == indeed;
}

int dfs( int x, int df ) {
	int dt,i,y;
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

int maxflow() {
	int T = 0,t;
	for(;bfs();)
		for(;++yes&&(t=dfs(src,+oo));T+=t);
	return T;
}

void build_graph( int limit ) {
	int i,j;
	for ( V = 2*n+2, src = V-2, sink = V-1, E = 0, i = 0; i < V; last[i++] = -1 );
	for ( i = 0; i < n; ++i ) {
		if ( !a[i] ) continue ;
		add_arcs(i,i+n,a[i]), add_arcs(src,i,a[i]);
		for ( j = 0; j < n; ++j )
			if ( g[i][j] == 'Y' && a[j] )
				add_arcs(i+n,j,a[i]);
		if ( is_border[i] )
			add_arcs(i,sink,limit);
		else add_arcs(i,sink,1);
	}
}

int main() {
	int i,j,k,ts,good,bad,mid;
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	for ( scanf("%d",&ts); ts--; printf("%d\n",good) ) {
		for ( scanf("%d",&n), i = 0; i < n; is_border[i] = 0, scanf("%d",&a[i++]) );
		for ( i = 0; i < n; scanf("%s",g[i++]) );
		for ( i = 0; i < n; ++i )
			for ( j = 0; j < n && a[i] && !is_border[i]; ++j )
				if ( g[i][j] == 'Y' && !a[j] ) is_border[i] = 1;
		for ( inner = outer = 0, i = 0; i < n; ++i )
			if ( a[i] ) {
				if ( is_border[i] ) ++outer;
				else ++inner;
			}
		for ( good = 0, bad = +oo; good+1 < bad; ) {
			build_graph(mid = (good+bad)/2);
			if ( (k = maxflow()) == mid*outer+inner ) good = mid;
			else bad = mid;
		}
	}
	return 0;
}

