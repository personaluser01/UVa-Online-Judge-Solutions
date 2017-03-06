/*
 * 13057. Prove them all
 * TOPIC: scc, dag
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N (1<<14)
#define M (1<<18)
enum { D, T };

int m,n,to[2][M],next[2][M],last[2][N],E[2],scc[N],st[N],*top,visited[2][N],yes[2],mark,indeg[N],seen[N],indeed,queue[N],*tail,*head;

void add_arcs( int x, int y ) {
	int i = E[D]++, j = E[T]++;
	to[D][i] = y, next[D][i] = last[D][x], last[D][x] = i;
	to[T][j] = x, next[T][j] = last[T][y], last[T][y] = j;
}

void dfs( int t, int x ) {
	int i,y;
	if ( visited[t][x] == yes[t] ) return ;
	for ( visited[t][x] = yes[t], i = last[t][x]; i >= 0; i = next[t][i] )
		if ( visited[t][y=to[t][i]] != yes[t] )
			dfs(t,y);
	if ( t == T ) *++top = x;
	else scc[x] = mark;
}

void DFS( int x ) {
	int i,y;
	if ( seen[x] == indeed ) return ;
	for ( seen[x]=indeed, i=last[D][x]; i>=0; DFS(y), i=next[D][i] ) 
		if ( scc[x]!=scc[y=to[D][i]] ) 
			++indeg[scc[y]];
}

int main() {
	int i,j,k,ts,cs = 0,t,l;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( scanf("%d",&ts); ts--&&2==scanf("%d %d",&n,&m); ) {
		for ( t = D; t <= T; ++t )
			for ( ++yes[t], E[t] = 0, i = 0; i <= n; last[t][i++] = -1 );
		for ( l = m; l--; scanf("%d %d",&i,&j), add_arcs(--i,--j) );
		for ( top = st, i = 0; i < n; ++i )
			if ( visited[T][i] != yes[T] )
				dfs(T,i);
		for ( mark = -1; top > st; )
			if ( visited[D][i = *top--] != yes[D] )
				indeg[++mark] = 0, dfs(D,i);
		for ( ++indeed, i = 0; i < n; DFS(i++) );
		for ( k = 0, i = 0; i <= mark; ++i )
			if ( !indeg[i] ) ++k;
		printf("Case %d: %d\n",++cs,k);
	}
	return 0;
}


