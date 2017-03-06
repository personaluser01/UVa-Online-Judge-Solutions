/*
 * 12125. March of the Penguins
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
#define N 0x80
#define MAXV (2*N)
#define M (1 << 19)
#define S(x) ((x)*(x))

int min( int x, int y ) { return x < y ? x : y; }

int ts,cs,n,kap[N],pen[N],src,sink,V,
	to[M],next[M],last[MAXV],E,cur_x,
	visited[MAXV],indeed,seen[MAXV],yes,
	q[MAXV],*head,*tail,d[MAXV];
short cap[M],flow[M];
long double D,xx[N],yy[N];

void add_arcs( int x, int y, int c ) {
	int i = E++, j = E++;
	to[i] = y, next[i] = last[x], last[x] = i;
	to[j] = x, next[j] = last[y], last[y] = j;
	cap[i] = c, cap[j] = 0;
	flow[i] = flow[j] = 0;
}

int forbidden( int x, int y ) {
	return (y==sink&&1<=x&&x<=n&&x!=cur_x)||(x==sink&&1<=y&&y<=n&&y!=cur_x);
}

int dfs( int x, int df ) {
	int i,y,t;
	if ( x == sink )
		return df;
	for ( seen[x] = yes, i = last[x]; i >= 0; i = next[i] )
		if ( visited[y = to[i]] == indeed && d[y = to[i]]+1 == d[x] )
			if ( seen[y] != yes && cap[i] > flow[i] )
				if ( !forbidden(x,y) )
					if ( t = dfs(y,min(df,cap[i]-flow[i])) ) {
						flow[i] += t, flow[i^1] -= t;
						return t;
					}
	return 0;
}

int bfs() {
	int i,x,y;
	head = tail = q, d[sink] = 0;
	for ( visited[*tail++ = sink] = ++indeed; head < tail;)
		for ( i = last[x = *head++]; i >= 0; i = next[i] )
			if ( cap[i^1] > flow[i^1] && visited[y = to[i]] != indeed )
				if ( !forbidden(x,y) )
					visited[y] = indeed, d[*tail++ = y] = d[x]+1;
	return visited[src]==indeed;
}

int maxflow() {
	int T = 0,t,i;
	memset(flow,0,E*sizeof 0[flow]);
	for(;bfs();)for(++yes;t=dfs(src,1<<29);T+=t);
	return T;
}

int main() {
	int i,j,k,l,t,T,Total,out[N],*ptr;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( scanf("%d",&ts); ts--; ) {
		assert( 2 == scanf("%d %Lf",&n,&D) );
		for ( Total = 0, i = 1; i <= n; ++i )
			scanf("%Lf %Lf %d %d",xx+i,yy+i,pen+i,kap+i), Total += pen[i];
		src = 0, sink = 2*n+1, V = 2*n+2, E = 0;
		for ( i = 0; i < V; ++i ) last[i] = -1;
		for ( i = 1; i <= n; ++i ) {
			add_arcs(src,i,pen[i]);
			add_arcs(i,i+n,kap[i]);
			add_arcs(i,sink,Total);
		}
		for ( i = 1; i <= n; ++i )
			for ( j = 1; j <= n; ++j )
				if ( i != j && sqrt(S(xx[i]-xx[j])+S(yy[i]-yy[j])) <= D )
					add_arcs(i+n,j,kap[i]);
		for ( ptr = out, cur_x = 1; cur_x <= n; ++cur_x )
			if ( (t = maxflow()) == Total )
				*ptr++ = cur_x;
		if ( ptr == out ) puts("-1");
		else {
			for ( i = 0; i < ptr-out-1; ++i )
				printf("%d ",out[i]-1);
			printf("%d\n",out[i]-1);
		}
	}
	return 0;
}

