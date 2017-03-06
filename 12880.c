/*
 * 12880. Bookc Club
 * TOPIC: maxflow
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N (1<<14)
#define MAXV (N+N)
#define MAXE (1<<21)

int m,n,visited[MAXV],indeed,seen[MAXV],yes,to[MAXE],next[MAXE],cap[MAXE],flow[MAXE],
	E,V,src,sink,last[MAXV],q[MAXV],*head,*tail,d[MAXV];

void add_arcs( int x, int y, int c ) {
	int i = E++, j = E++;
	to[i] = y, next[i] = last[x], last[x] = i, cap[i] = c, flow[i] = 0;
	to[j] = x, next[j] = last[y], last[y] = j, cap[j] = 0, flow[j] = 0;
}

int dfs( int x, int df ) {
	int i,y,dt;
	if ( x == sink ) return df ;
	if ( seen[x] == yes || !df ) return 0;
	for ( seen[x] = yes, i = last[x]; i >= 0; i = next[i] )
		if ( flow[i] < cap[i] && visited[y=to[i]] == indeed && d[y]+1 == d[x] )
			if ( (dt = dfs(y,cap[i]-flow[i]<df?cap[i]-flow[i]:df)) ) {
				flow[i] += dt, flow[i^1] -= dt;
				return dt;
			}
	return 0;
}

int bfs() {
	int x,y,i;
	for ( head=tail=q,seen[*tail++=sink]=++yes,d[sink]=0; head<tail; )
		for ( i=last[x=*head++]; i>=0; i=next[i] )
			if ( flow[i^1]<cap[i^1] && seen[y=to[i]]!=yes )
				d[*tail++=y]=d[x]+1, seen[y]=yes;
	return seen[src]==yes;
}

void maxflow() {
	int dt,t=0;
	for(;bfs();)for(;++yes&&(dt=dfs(src,1<<29));t+=dt);
	puts(t==n?"YES":"NO");
}

int main() {
	int i,j,k;
#ifndef ONLINE_JUDGE
	freopen("12880.in","r",stdin);
#endif
	for ( ;2==scanf("%d %d",&n,&m); maxflow() ) {
		for ( src = n+n, sink = src+1, V = sink+1, E = 0, i = 0; i < V; last[i++] = -1 );
		for ( ;m-- && 2 == scanf("%d %d",&i,&j); add_arcs(i,n+j,1) );
		for ( i = 0; i < n; add_arcs(src,i,1), add_arcs(i+n,sink,1), ++i );
	}
	return 0;
}

