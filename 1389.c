/*
 * 1389. Hard Life
 * TOPIC: maxmimum density subgraph, maxflow mincut, goldberg
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXN 0x80
#define MAXE (1<<20)
#define oo (1LL<<43)
typedef long long i64;
double min(double x, double y) {return x<y?x:y;}

int to[MAXE],next[MAXE],last[MAXN],V,E,n,visited[MAXN],yes,seen[MAXN],indeed,src,sink,m,u[0x400],v[0x400],deg[MAXN],q[MAXN],*head,*tail,
	*ptr,o[MAXN],len,vx[MAXN];
double cap[MAXE],flow[MAXE];
i64 d[MAXN];

void add_arcs( int x, int y, double c ) {
	int i = E++, j = E++;
	to[i] = y, next[i] = last[x], last[x] = i, cap[i] = c;
	to[j] = x, next[j] = last[y], last[y] = j, cap[j] = 0;
	assert( c >= 0 );
	flow[i] = flow[j] = 0;
}

void init( double g ) {
	int i,j,k,x,y;
	for ( E = 0, V = n+2, src = V-2, sink = V-1, x = 0; x < V; last[x++] = -1 );
	for ( i = 0; i < m; ++i )
		add_arcs(u[i],v[i],1), add_arcs(v[i],u[i],1);
	for ( x = 0; x < n; ++x )
		add_arcs(src,x,m), add_arcs(x,sink,m+2*g-deg[x]);
}

int bfs() {
	int i,j,k,x,y;
	for ( head=tail=q, d[*tail++ = sink] = 0, visited[sink] = ++yes; head < tail; )
		for ( i=last[x=*head++]; i >= 0; i = next[i] )
			if ( cap[i^1] > flow[i^1] && visited[y = to[i]] != yes )
				visited[*tail++ = y] = yes, d[y] = d[x]+1;
	return visited[src] == yes;
}

double dfs( int x, double df ) {
	int y,i;
	double dt;
	if ( x == sink ) return df;
	if ( seen[x] == indeed )
		return 0;
	for ( seen[x] = indeed, i = last[x]; i >= 0; i = next[i] )
		if ( cap[i] > flow[i] && visited[y = to[i]] == yes && d[y]+1 == d[x] ) 
			if ( dt = dfs(y,min(df,cap[i]-flow[i])) ) {
				flow[i] += dt, flow[i^1] -= dt;
				return dt;
			}
	return 0;
}

void maxflow() {
	for(;bfs();)for(;++indeed&&dfs(src,+oo););
}

void find_mincut() {
	int x,y,i;
	for ( maxflow(), head=tail=q, seen[*tail++=src]=++indeed; head < tail; )
		for ( i = last[x = *head++]; i >= 0; i = next[i] )
			if ( cap[i] > flow[i] && seen[y = to[i]] != indeed )
				seen[*tail++ = y] = indeed;
	for ( ptr = o, x = 0; x < V; ++x )
		if ( seen[x] == indeed )
			*ptr++ = x;
}

void goldberg() {
	double low,high,mid;
	int i,j,k,flag = 0;
	if ( n == 1 || m == 0 ) {
		len = 1, vx[0] = 0;
		goto nx;
	}
	for ( low = 0, high = m; (high-low)*n*(n-1) >= 1; ) {
		init(mid=(low+high)/2.00);
		find_mincut();
		if ( ptr-o == 1 ) {
			assert( *(ptr-1) == src );
			high = mid;
		}
		else {
			low = mid, len = ptr-o-1, ++flag;
			for ( j = 0, i = 0; i < ptr-o; ++i )
				if ( o[i] != src )
					vx[j++] = o[i];
		}
	}
	if ( !flag ) {
		puts("1\n1");
		return ;
	}
	for ( j = 1; j; )
		for ( j = 0, i = 0; i < len-1; ++i )
			if ( vx[i] > vx[i+1] )
				k = vx[i], vx[i] = vx[i+1], vx[i+1] = k, ++j;
nx:
	for ( printf("%d\n",len), i = 0; i < len; printf("%d\n",vx[i++]+1) );
}

int main() {
	int i,j,k,ts = 0;
#ifndef ONLINE_JUDGE
	freopen("1389.in","r",stdin);
#endif
	for (;2 == scanf("%d %d",&n,&m); goldberg() ) {
		for ( memset(deg,0,sizeof deg), i = 0; i < m; scanf("%d %d",u+i,v+i), ++deg[--v[i]], ++deg[--u[i]], ++i );
		if ( ts++ ) putchar('\n');
	}
	return 0;
}

