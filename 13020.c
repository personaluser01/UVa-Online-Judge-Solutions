/*
 * 13020. Landscaping
 * TOPIC: maxflow-mincut
 * status: Accepted
 */
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DIM 64
#define vc(x,y) (0<=(x)&&(x)<m&&0<=(y)&&(y)<n)
#define N DIM*DIM
#define MAXE (1<<20)
typedef long long i64;
#define enc(x,y) ((x)*n+(y))

i64 min( i64 x, i64 y ) {
	if ( x < y ) return x;
	return y;
}

char g[DIM][DIM];
int m,n,src,sink,last[N],next[MAXE],to[MAXE],E,seen[N],yes,visited[N],indeed,d[N],q[N],*head,*tail,
	dx[] = {-1,0,1,0},
	dy[] = {0,1,0,-1};
i64 A,B,cap[MAXE],flow[MAXE];

void add_arcs( int x, int y, i64 c ) {
	int i = E++, j = E++;
	to[i] = y, next[i] = last[x], last[x] = i, cap[i] = c, flow[i] = 0;
	to[j] = x, next[j] = last[y], last[y] = j, cap[j] = 0, flow[j] = 0;
}

int bfs() {
	int x,y,i;
	for ( head=tail=q, d[sink]=0, visited[*tail++=sink]=++indeed; head<tail; )
		for ( i = last[x = *head++]; i >= 0; i = next[i] )
			if ( flow[i^1] < cap[i^1] && visited[y=to[i]] != indeed ) 
				visited[y] = indeed, d[*tail++ = y] = d[x]+1;
	return visited[src] == indeed;
}

int dfs( int x, i64 df ) {
	int i,y;
	i64 dt;
	if ( x == sink ) return df;
	if ( seen[x] == yes ) return 0;
	for ( seen[x] = yes, i = last[x]; i >= 0; i = next[i] )
		if ( seen[y=to[i]] != yes && cap[i] > flow[i] && visited[y] == indeed && d[y]+1 == d[x] )
			if ( dt = dfs(y,min(cap[i]-flow[i],df)) ) {
				flow[i] += dt, flow[i^1] -= dt;
				return dt;
			}
	return 0;
}

i64 maxflow() {
	i64 T = 0,dt;
	for (;bfs();)
		for (;++yes && (dt = dfs(src,(1LL<<61)));  T += dt );
	return T;
}

int main() {
	int i,j,k,l,ni,nj;
#ifndef ONLINE_JUDGE
	freopen("13020.in","r",stdin);
#endif
	for ( ;4 == scanf("%d %d %lld %lld",&m,&n,&A,&B) && (m||n||A||B); ) {
		for ( i = 0; i < m; scanf("%s",g[i++]) );
		src = enc(m,0), sink = enc(m,1);
		last[src] = last[sink] = -1;
		for ( i = 0; i < m; ++i )
			for ( j = 0; j < n; ++j )
				last[enc(i,j)] = -1;
		for ( i = 0; i < m; ++i )
			for ( j = 0; j < n; ++j ) {
				if ( g[i][j] == '.' )
					add_arcs(src,enc(i,j),B);
				else add_arcs(enc(i,j),sink,B);
				for ( l = 0; l < 4; ++l ) {
					ni = i+dx[l], nj = j+dy[l];
					if ( !vc(ni,nj) ) continue ;
					add_arcs(enc(i,j),enc(ni,nj),A);
				}
			}
		printf("%lld\n",maxflow());
	}
	return 0;
}

