/*
 * 11544. Recruiter's Problem
 * TOPIC: maxflow
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef long long i64;
#define N 0x80
#define MAXE (N*N+N+N)

typedef struct edge {
	struct edge *r;
	int x,y,cap,flow;
} edge;

edge e[MAXE];
int ts,cs,m,n,seen[N],visited[N],indeed,yes,adj[N][N],deg[N],src,sink,outlaw[N],E,V,aha,
	q[N],*tail,*head,d[N],req[N],f[MAXE],a[N];

void add_arcs( int x, int y, int c ) {
	int i = E++, j = E++;
	e[i].x = x, e[i].y = y, e[i].cap = c, e[i].flow = 0;
	e[j].x = y, e[j].y = x, e[j].cap = 0, e[j].flow = 0;
	e[i].r = &e[j], e[j].r = &e[i];
}

int dfs( int x ) {
	int i,y,k;
	if ( x == sink )
		return 1;
	if ( seen[x] == yes )
		return 0;
	for ( seen[x] = yes, i = 0; i < deg[x]; ++i ) 
		if ( outlaw[y=e[k=adj[x][i]].y]!=aha && e[k].flow < e[k].cap && visited[y] == indeed && d[y]+1 == d[x] && dfs(y) ) {
			++e[k].flow, --e[k].r->flow;
			return 1;
		}
	return 0;
}

int bfs() {
	int i,k,x,y;
	for ( head = tail = q, visited[*tail++ = sink] = ++indeed, d[sink] = 0; head < tail; )
		for ( x = *head++, i = 0; i < deg[x]; ++i ) 
			if ( outlaw[y=e[k=adj[x][i]].y] != aha && (visited[y] != indeed || d[y] > d[x]+1) && e[k].r->flow < e[k].r->cap ) 
				visited[*tail++ = y] = indeed, d[y] = d[x]+1;
	return visited[src] == indeed;
}

void restore_flow() {
	int i;
	for ( i = 0;i < E; ++i ) e[i].flow = f[i];
}

void init_flow() {
	int i;
	for ( i = 0; i < E; ++i ) f[i] = e[i].flow, e[i].flow = 0;
}

int maxflow() {
	int T = 0;
	for(;bfs();)
		for(;++yes && dfs(src) && ++T;);
	return T;
}

void dec_req( int y, int dt ) {
	int i;
	for ( i = 0; i < deg[y]; ++i )
		if ( e[adj[y][i]].y == sink ) {
			e[adj[y][i]].cap += dt;
			assert( e[adj[y][i]].cap >= 0 );
			return ;
		}
	assert( 0 );
}

int main() {
	int i,j,k,T,x,y,ans;
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	for ( scanf("%d",&ts); ts-- && ++aha; ) {
		printf("Case #%d:\n",++cs);
		scanf("%d %d",&m,&n);
		for ( i = 1; i <= n; ++i ) 
			scanf("%d",req+i);
		for ( E = 0, src = 0, sink = m+n+1, V = m+n+2, i = 1; i <= m; ++i ) 
			for ( scanf("%d",&k); k-- && 1 == scanf("%d",&j); add_arcs(i,j+m,1) ) ;
		for ( i = 1; i <= m; add_arcs(src,i++,1) );
		for ( j = 1; j <= n; add_arcs(j+m,sink,req[j]), ++j );
		for ( x = src; x <= sink; ++x ) a[x] = -1, deg[x] = 0;
		for ( i = 0; i < E; ++i )
			adj[e[i].x][deg[e[i].x]++] = i;
		for ( ans = T = maxflow(), i = 0; i < E; i += 2 ) {
			x = e[i].x, y = e[i].y;
			if ( x == src || y == src || x == sink || y == sink || x >= m+1 || outlaw[x] == aha )
				continue ;
			assert( 1 <= x && x <= m && 1+m <= y && y <= m+n );
			if ( e[i].flow > 0 && x <= m && y >= m+1 && req[y-m] >= 1 ) {
				a[x] = (y-m);
				outlaw[x] = aha, --T, --req[y-m];
				dec_req(y,-1);
				continue ;
			}
			if ( !req[y-m] ) continue ;
			outlaw[x] = aha, init_flow(), dec_req(y,-1), --req[y-m];
			if ( (k=maxflow())==T-1 ) {
				a[x] = (y-m), T = k;
				continue ;
			}
			outlaw[x] = 0, dec_req(y,1), ++req[y-m];
		}
		printf("%d applicant(s) can be hired.\n",ans);
		for ( i = 1; i <= m; ++i )
			if ( a[i] != -1 )
				printf("%d %d\n",i,a[i]);
	}
	return 0;
}

