/*
 * 1317. Concert Hall Scheduling
 * TOPIC: mincost circulation, cycle cancellation
 * status: Accepted
 */
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define MAXN (1<<15)
#define MAXE (1<<20)
#define oo (1LL<<43)
typedef long long i64;
i64 min( i64 x, i64 y ) { return x<y?x:y; }

int last[MAXN],to[MAXE],cap[MAXE],flow[MAXE],next[MAXE],E,V,src,sink,n,p[MAXN];
i64 d[MAXN],cost[MAXE];

void add_arcs( int x, int y, int c, int w ) {
	int i = E++, j = E++;
	to[i] = y, next[i] = last[x], last[x] = i, cap[i] = c, cost[i] = w;
	to[j] = x, next[j] = last[y], last[y] = j, cap[j] = 0, cost[j] = -w;
	flow[i] = flow[j] = 0;
}

int neg_cycle_exists( int *t ) {
	int i,j,x,y;
	static int visited[MAXN] = {0}, indeed = 0;

	for ( d[src] = 0, visited[src] = ++indeed, i = 0; i < V; ++i )
		for ( j = 0; j < E; ++j ) 
			if ( visited[x=to[j^1]]==indeed && cap[j]>flow[j] && (visited[y=to[j]]!=indeed || d[y]>d[x]+cost[j]) )
				d[y] = d[x]+cost[p[y]=j], visited[y] = indeed;
	for ( i = 0; i < E; ++i ) 
		if ( visited[x=to[i^1]]==indeed && cap[i]>flow[i] && (visited[y=to[i]]!=indeed || d[y]>d[x]+cost[i]) ) {
			d[y] = d[x]+cost[p[y]=i];
			visited[y] = indeed;
			return (*t = y)+1;
		}
	return 0;
}

i64 mincost_circulation() {
	int x,y,i,j,k,v,df;
	static int used[MAXN] = {0}, yes = 0;
	i64 T = 0,cc;

	while ( neg_cycle_exists(&x) ) {
		for ( used[x] = ++yes, v = to[p[x]^1]; used[v] != yes; used[v] = yes, v = to[p[v]^1] );
		for ( x = v, df = cap[p[x]]-flow[p[x]], v = to[p[x]^1]; v != x; df = min(df,cap[p[v]]-flow[p[v]]), v = to[p[v]^1] );
		assert( df >= 1 );
		for ( cc = 0, flow[p[v]] += df, cc += df*cost[p[v]], flow[p[v]^1] -= df, v = to[p[v]^1]; v != x; flow[p[v]] += df, flow[p[v]^1] -= df, cc += cost[p[v]], v = to[p[v]^1] );
		assert( cc < 0 );
	}
	for ( i = 0; i < E; ++i )
		T += cost[i]*flow[i];
	return T;
}

int main() {
	int i,j,k,l;
#ifndef ONLINE_JUDGE
	freopen("1317.in","r",stdin);
#endif
	while ( 1 == scanf("%d",&n) && n > 0 ) {
		for ( E = 0, V = 2*367, src = V-1, i = 0; i < V; last[i++] = -1 );
		for ( l = 0; l < n; ++l ) {
			scanf("%d %d %d",&i,&j,&k), --i, --j;
			add_arcs(j+366,i,1,-k);
		}
		for ( i = 0; i < 365; ++i ) {
			add_arcs(i,i+366,2,0);
			add_arcs(i+366,i+1,2,0);
		}
		for ( i = 0; i < 365; ++i )
			add_arcs(src,i,1,0);
		printf("%lld\n",-mincost_circulation()/2);
	}
	return 0;
}

