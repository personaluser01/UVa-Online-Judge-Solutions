/*
 * 1306. The K-League
 * TOPIC: baseball elimination problem, maxflow
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 0x40
#define MAXN (0x400)
#define MAXE (1<<20)
#define oo (1LL<<43)
typedef long long i64;
i64 min( i64 x, i64 y ) { return x<y?x:y; }

int a[N][N],m[N],to[MAXE],next[MAXE],last[MAXN],E,V,n,wins[N],defeats[N],id[N][N],ww[N],src,sink,
	q[MAXN],*head,*tail,visited[MAXN],yes,seen[MAXN],indeed;
i64 flow[MAXE],cap[MAXE],Total,d[MAXN];

void add_arcs( int x, int y, i64 c ) {
	int i = E++, j = E++;
	to[i] = y, next[i] = last[x], last[x] = i, cap[i] = c;
	to[j] = x, next[j] = last[y], last[y] = j, cap[j] = 0;
	flow[i] = flow[j] = 0;
}

void init( const int idx ) {
	int i,j,k = 0;
	for ( E = 0, V = (n-1)*(n-2)/2+(n-1)+2, src = V-2, sink = V-1, i = 0; i < V; last[i++] = -1 );
	for ( i = 0; i < n; ++i )
		for ( j = i+1; i != idx && j < n; ++j )
			if ( j != idx )
				id[i][j] = k++;
	assert( k == ((n-1)*(n-2))/2 );
	for ( i = 0; i < n; ++i )
		if ( i != idx )
			ww[i] = k++;
	for ( i = 0; i < n; ++i )
		for ( j = i+1; j < n && i != idx; ++j )
			if ( j != idx )
				add_arcs(src,id[i][j],a[i][j]);
	for ( i = 0; i < n; ++i )
		for ( j = i+1; j < n && i != idx; ++j )
			if ( j != idx ) 
				add_arcs(id[i][j],ww[i],a[i][j]), add_arcs(id[i][j],ww[j],a[i][j]);
	for ( i = 0; i < n; ++i )
		if ( i != idx )
			add_arcs(ww[i],sink,wins[idx]+m[idx]-wins[i]);
	for ( Total = 0, i = 0; i < n; ++i )
		for ( j = i+1; j < n && i != idx; ++j )
			if ( j != idx )
				Total += a[i][j];
}

int bfs() {
	int x,y,i;
	for ( head=tail=q, visited[*tail++ = sink] = ++yes, d[sink] = 0; head < tail; )
		for ( i = last[x=*head++]; i >= 0; i = next[i] )
			if ( cap[i^1]>flow[i^1] && visited[y=to[i]]!=yes )
				visited[*tail++=y]=yes,d[y]=d[x]+1;
	return visited[src] == yes;
}

i64 dfs( int x, i64 df ) {
	i64 dt,i,y;
	if ( x == sink ) 
		return df;
	if ( seen[x] == indeed )
		return 0;
	for ( seen[x] = indeed, i = last[x]; i >= 0; i = next[i] )
		if ( visited[y=to[i]] == yes && cap[i]>flow[i] && d[y]+1 == d[x] )
			if ( dt = dfs(y,min(df,cap[i]-flow[i])) ) {
				flow[i] += dt, flow[i^1] -= dt;
				return dt;
			}
	return 0;
}

int maxflow( const int idx ) {
	i64 T = 0, dt, i;
	for ( init(idx), i = 0; i < E; ++i )
		if ( cap[i] < 0 )
			return 0;
	for ( ;bfs(); )
		for ( ;++indeed && (dt=dfs(src,+oo)); T += dt );
	return Total == T;
}

int main() {
	int i,j,k,ts;
#ifndef ONLINE_JUDGE
	freopen("1306.in","r",stdin);
#endif
	for ( scanf("%d",&ts); ts-- && 1 == scanf("%d",&n); putchar('\n') ) {
		for ( i = 0; i < n; ++i ) scanf("%d %d",wins+i,defeats+i);
		for ( i = 0; i < n; ++i )
			for ( m[i] = 0, j = 0; j < n; ++j )
				scanf("%d",&a[i][j]), m[i] += a[i][j];
		for ( k = 0, i = 0; i < n; ++i )
			if ( maxflow(i) ) {
				if ( k++ ) putchar(' ');
				printf("%d",i+1);
			}
	}
	return 0;
}

