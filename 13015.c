/*
 * 13015. Promotions
 * TOPIC: DAG, bfs, dfs, dp
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 5003
#define MAXN N
#define MAXE (1<<17)
enum { D, T };
enum { WHITE, GREY, BLACK };

int max( int x, int y ) { if ( x < y ) return y; return x; }

int m,n,A,B,to[2][MAXE],next[2][MAXE],last[2][MAXN],E[2],indeg[N],src,d[N+N],visited[N],yes,q[N],*tail,*head,c[N+N],total,
	st[N+N],*top,color[N],v[N],len,succ[N],pred[N];

void add_arcs( int x, int y ) {
	int i = E[D]++, j = E[T]++;
	to[D][i] = y, next[D][i] = last[D][x], last[D][x] = i;
	to[T][j] = x, next[T][j] = last[T][y], last[T][y] = j;
	++indeg[y];
}

void dfs( int x ) {
	int i,y;
	assert( color[x] == WHITE );
	for ( color[x] = GREY, i = last[D][x]; i >= 0; i = next[D][i] )
		if ( color[y = to[D][i]] == WHITE )
			dfs(y);
		else assert( color[y] == BLACK );
	color[*++top = x] = BLACK;
};

int DFS( int x, int t ) {
	int i,y,ret = 0;
	assert( visited[x] != yes );
	for ( ++ret, visited[x] = yes, i = last[t][x]; i >= 0; i = next[t][i] )
		if ( visited[y = to[t][i]] != yes )
			ret += DFS(y,t);
	return ret;
}

int main() {
	int i,j,k,cur,ans,x,y,on_border;
#ifndef ONLINE_JUDGE
	/*freopen("test11in.txt","r",stdin);*/
	freopen("in.txt","r",stdin);
#endif
	for (;4==scanf("%d %d %d %d",&A,&B,&n,&m) && (A||B||n||m);) {
		for ( E[D]=E[T]=0, i=0; i<=n; last[D][i]=last[T][i]=-1, color[i] = WHITE, indeg[i++]=0 );
		for ( src=n, k=0; k<m && 2 == scanf("%d %d",&i,&j); add_arcs(i,j),++k );
		for ( top = st, i = 0; i < n; ++i )
			if ( color[i] == WHITE )
				dfs(i);
		for ( len = 0; top > st; v[len++] = *top-- );
		assert( len == n );
		for ( i = 0; i < n; ++i ) 
			++yes, succ[v[i]] = DFS(v[i],D), ++yes, pred[v[i]] = DFS(v[i],T);
		for ( i = 0, j = 0, k = 0, x = 0; x < n; ++x )
			if ( succ[x] >= n-A+1 ) 
				++i;
		for ( x = 0; x < n; ++x )
			if ( succ[x] >= n-B+1 )
				++j;
		for ( x = 0; x < n; ++x )
			if ( pred[x] >= B+1 )
				++k;
		printf("%d\n%d\n%d\n",i,j,k);
	}
	return 0;
}

