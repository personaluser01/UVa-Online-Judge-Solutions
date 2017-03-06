/*
 * 11267. ``Hire-a-Coder'' Business Model
 * TOPIC: bipartite graph, mst, kruskal
 * status: Accepted
 */
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define oo (1<<29)
#define N 0x100
#define M (1<<21)
enum { S, T };
enum { UNDEF = -1, WHITE = 0, BLACK = 1 };

int n[2],m,g[N][N],color[N],ok,v[2][N],rank[N],p[N],
	x[M],y[M],w[M],id[M];

int dfs( int x, int c ) {
	int y;
	for ( color[x] = c, y = 0; y < m; ++y )
		if ( g[x][y] < +oo ) {
			if ( color[y] == UNDEF && !dfs(y,c^1) ) return 0;
			else if ( color[y] == c ) return 0;
		}
	return 1;
}

int cmp( const void *a, const void *b ) {
	int *i = (int *)a,
		*j = (int *)b;
	if ( w[*i] == w[*j] ) 
		return 0;
	return w[*i]<w[*j]?-1:1;
}

int link( int x, int y ) {
	if ( x == y ) return ;
	if ( rank[x] > rank[y] ) 
		p[y] = x;
	else {
		p[x] = y;
		if ( rank[x] == rank[y] )
			++rank[y];
	}
}

void merge( int x, int y ) { link(find(x),find(y)); }

int find( int x ) { return p[x]=(p[x]==x?x:find(p[x])); }

int main() {
	int i,j,k,l,ans;
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	for(;1==scanf("%d",&m) && m && 1 == scanf("%d",&k); ) {
		for ( i = 0; i < m; ++i ) for ( color[i]=UNDEF,j = 0; j < m; g[i][j++] = +oo );
		for(;k--&&3==scanf("%d %d %d",&i,&j,&l);--i,--j,g[i][j]=g[j][i]=l);
		for ( ok = 1, i = 0; i < m && ok; ++i )
			if ( color[i] == UNDEF && !dfs(i,WHITE) ) ok = 0;
		if ( !ok ) { puts("Invalid data, Idiot!"); continue ; }
		for ( n[S]=n[T]=0, i = 0; i < m; ++i )
			v[color[i]][n[color[i]]++] = i;
		assert( n[S]+n[T] == m );
		for ( i = 0; i < m; ++i ) rank[p[i]=i]=0;
		for ( k = 0, i = 0; i < m; ++i )
			for ( j = i+1; j < m; ++j )
				if ( g[i][j] < +oo )
					x[k] = i, y[k] = j, w[k++] = g[i][j];
		for ( i = 0; i < k; ++i ) id[i] = i;
		qsort( id, k, sizeof *id, cmp );
		for ( i = 0; i < k-1; ++i )
			assert( w[id[i]] <= w[id[i+1]] );
		for ( ans = 0, i = 0; i < k; ++i ) 
			if ( find(x[id[i]]) != find(y[id[i]]) || w[id[i]] < 0 ) 
				ans += w[id[i]], merge(x[id[i]],y[id[i]]);
		printf("%d\n",ans);
	}
	return 0;
}

