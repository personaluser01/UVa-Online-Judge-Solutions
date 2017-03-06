/*
 * 1660. Cable TV Network
 * TOPIC: maxflow, menger's theorem, maxflow-mincut, vertex capacities, gomory-hu, all-pairs maxflow
 * status: Accepted
 */
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 0x400
#define MAXE (1<<16)
#define IN(x) (0|((x)<<1))
#define OUT(x) (1|((x)<<1))
#define oo (1<<29)

int min( int x, int y ) { if ( x < y ) return x; return y; }

int to[MAXE],next[MAXE],last[N],flow[MAXE],cap[MAXE],E,V,m,n,
	visited[N],yes,seen[N],indeed,d[N],src,sink,
	q[N],*head,*tail,is[N],forbidded[MAXE],aha,e[N];

void add_arcs( int x, int y, int c ) {
	int i = E++, j = E++;
	to[i] = y, next[i] = last[x], last[x] = i, cap[i] = c, flow[i] = 0;
	to[j] = x, next[j] = last[y], last[y] = j, cap[j] = 0, flow[j] = 0;
}

int bfs() {
	int i,x,y;
	for ( head=tail=q, visited[sink]=++indeed, d[*tail++=sink]=0; head < tail; )
		for ( i=last[x=*head++]; i >= 0 && (y=to[i])>=0; i = next[i] )
			if ( forbidded[i] != aha && forbidded[i^1] != aha )
			if ( visited[y] != indeed || d[y] > d[x]+1 )
				if ( flow[i^1] < cap[i^1] )
					d[*tail++ = y] = d[x]+1, visited[y] = indeed;
	return visited[src] == indeed; 
}

int dfs( int x, int df ) {
	int i,y,dt;
	if ( x == sink ) return df;
	if ( seen[x] == yes ) return 0;
	for ( seen[x] = yes, i = last[x]; i >= 0 && (y=to[i])>=0; i = next[i] )
		if ( forbidded[i] != aha && forbidded[i^1] != aha )
		if ( visited[y] == indeed && d[y]+1==d[x] && flow[i] < cap[i] )
			if ( dt = dfs(y,min(df,cap[i]-flow[i])) ) {
				flow[i] += dt, flow[i^1] -= dt;
				return dt;
			}
	return 0;
}

int maxflow() {
	int k = 0,t;
	for (;bfs();) for (++yes;t=dfs(src,+oo);k+=t);
	return k;
}

int main() {
	int i,j,k,w;
	char tmp1[0x20],tmp2[0x20],tmp3[0x20];
#ifndef ONLINE_JUDGE
	freopen("c.txt","r",stdin);
#endif
	for ( ;2 == scanf("%d %d",&n,&m);) {
		for ( w = +oo, E = 0, i = 0; i < 2*n+2; last[i++] = -1 );
		src = IN(n), sink = OUT(n);
		for ( ++yes, k = 0; k < m; ++k ) {
			scanf("%[^0-9] %d %[^0-9] %d %[^0-9 \t\n]",tmp1,&i,tmp2,&j,tmp3);
		   	add_arcs(OUT(i),IN(j),N), add_arcs(OUT(j),IN(i),N);;
		}
		for ( i = 0; i < n; ++i ) add_arcs(IN(i),OUT(i),1), e[i] = E-1;
		if ( n == 0 ) { puts("0"); continue ; }
		if ( n == 1 ) { puts("1"); continue ; }
		for ( i = 0; i < n; ++i )
			for ( j = i+1; j < n; ++j ) {
				for ( k = 0; k < E; flow[k++] = 0 );
				forbidded[e[i]] = forbidded[e[j]] = ++aha;
				src = OUT(i), sink = IN(j);
				w = min(w,maxflow());
			}
		printf("%d\n",min(n,w));
	}
	return 0;
}

