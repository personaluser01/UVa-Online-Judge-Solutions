/*
 * 10480. Sabotage
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <limits.h>
#include <float.h>
#define N 64
#define M (1 << 16)
#define BIT(k) (1ull<<(k))
typedef unsigned long long u64;
#define SET(u,k) ((u)|=BIT(k))
#define TST(u,k) ((u)&BIT(k))
#define MASK(k) (BIT(k)-1ULL)
#define L(u) ((u) & ((~(u))+1ull))

int min( int x, int y ) { return x<y?x:y;}

int n,m,last[N],to[M],cap[M],flow[M],next[M],E,src,sink,
	seen[N],yes,visited[N],indeed,q[N],*head,*tail;
unsigned int d[N];
unsigned char bt[1 << 20];

int who( u64 u ) {
	if ( u < (1<<20) )
		return bt[u];
	if ( u < (1ull<<40) )
		return 20+bt[u>>20];
	return 40+bt[u>>40];
}

void add_arcs( int x, int y, int c ) {
	int i = E++, j = E++;
	assert( (i^1) == j );
	to[i]=y,cap[i]=c,flow[i]=0,next[i]=last[x],last[x]=i;
	to[j]=x,cap[j]=0,flow[j]=0,next[j]=last[y],last[y]=j;
}

int dfs( int x, int df ) {
	int i,y,t;
	if ( x == sink ) return df;
	for(seen[x]=yes,i=last[x];i>=0;i=next[i])
		if ( cap[i] > flow[i] && visited[y = to[i]] == indeed && d[y]+1 == d[x] )
			if ( seen[y] != yes )
				if ( t = dfs(y,min(df,cap[i]-flow[i])) ) {
					flow[i] += t, flow[i^1] -= t;
					return t;
				}
	return 0;
}

int bfs() {
	int i,j,k,x,y;

	head = tail = q;
	for(d[*tail++=sink]=0,visited[sink]=++indeed;head<tail;)
		for ( i = last[x = *head++]; i >= 0; i = next[i] )
			if ( cap[i^1] > flow[i^1] && visited[y = to[i]] != indeed )
				visited[*tail++=y] = indeed, d[y] = d[x]+1;
	return visited[src] == indeed;
}

void collect( int x, u64 *u ) {
	int i;
	if ( TST(*u,x) ) return ;
	for ( SET(*u,x), i = last[x]; i >= 0; i = next[i] )
		if ( cap[i] > flow[i] )
			if ( !TST(*u,to[i]) )
				collect(to[i],u);
}

int main() {
	int i,j,k,l,t,x,ax;
	u64 u,v;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( k = 0; k < 20; ++k )
		bt[1ull << k] = k;
	for(;2==scanf("%d %d",&n,&m)&&(n||m);putchar('\n')) {
		for ( i = 0; i < n; ++i ) last[i] = -1;
		for ( E = 0, l = 0; l < m; ++l ) 
			scanf("%d %d %d",&i,&j,&k), add_arcs(--i,--j,k), add_arcs(j,i,k);
		src = 0, sink = 1;
		for(ax = 0;bfs();)for(++yes;t = dfs(src,(1<<29)); ax += t );
		u = 0, collect(src,&u), v = (~u)&MASK(n);
		assert( u );
		assert( v );
		for (;u; u -= L(u) ) {
			for ( i = last[x = who(L(u))]; i >= 0; i = next[i] )
				if ( TST(v,to[i]) ) {
					assert( cap[i] == flow[i] );
					ax -= cap[i];
					if ( cap[i] )
						printf("%d %d\n",x+1,to[i]+1);
				}
		}
	}
	return 0;
}

