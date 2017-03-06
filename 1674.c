/*
 * 1674. Lightning Energy Report
 * TOPIC: lca, dp, lazy updates, tree updates
 * status: Accepted
 */
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BIT(k) (1ULL<<(k))
#define N BIT(16)
#define MAXE BIT(20)
#define L(k) ((k)&((~(k))+1ULL))
#define K 17
#define MAXV N
#define oo BIT(29)

int V,E,n,to[MAXE],next[MAXE],last[N],anc[N][K],
	q[MAXV],*head,*tail,d[N],m,weight[N],extra[N];

int up( int x, unsigned int k ) {
	int i = 0,y=x,l=k;
	for (;k; k>>=1, ++i )
		if ( k&1 ) 
			x=anc[x][i];
	assert ( d[x]+l== d[y] );
	return x;
}

int lca( int x, int y ) {
	int k;
	if ( d[x] < d[y] )
		return lca(y,x);
	assert( d[x] >= d[y] );
	if ( d[x] > d[y] )
		return lca(up(x,d[x]-d[y]),y);
	assert( d[x] == d[y] );
	if ( x == y ) return x;
	for ( k = m; k; --k ) 
		if ( anc[x][k-1] != anc[y][k-1] )
			x = anc[x][k-1], y = anc[y][k-1];
	assert( anc[x][0] == anc[y][0] );
	return anc[x][0];
}

void add_arcs( int x, int y ) {
	int i = E++, j = E++;
	to[i] = y, next[i] = last[x], last[x] = i;
	to[j] = x, next[j] = last[y], last[y] = j;
}

void bfs() {
	int i,k,x,y;
	for ( x = 0; x < n; ++x )
		for ( d[x] = +oo, k = 0; k <= m; anc[x][k++] = -1 );
	for ( head = tail = q, d[*tail++ = 0] = 0; head < tail; )
		for ( i=last[x=*head++]; i>=0; i=next[i] )
			if ( d[y=to[i]]>d[x]+1 ) 
				for ( d[*tail++=y]=d[anc[y][0]=x]+1, k=1; k<=m && anc[y][k-1]!=-1; anc[y][k]=anc[anc[y][k-1]][k-1], ++k ) ;
}

int dfs( int x ) {
	int i,y,sum = weight[x];
	for ( i = last[x]; i >= 0; i = next[i] )
		if ( (y = to[i]) != anc[x][0] ) 
			sum += dfs(y);
	return weight[x] = sum;
}

int main() {
	int qr,i,j,k,l,t,ts,cs=0;
#ifndef ONLINE_JUDGE
	freopen("c.txt","r",stdin);
#endif
	for ( scanf("%d",&ts); ts-- && printf("Case #%d:\n",++cs) && 1 == scanf("%d",&n); ) {
		for ( E = 0, V = n, i = 0; i < n; last[i++] = -1 );
		for ( k = 0; k < n-1; scanf("%d %d",&i,&j), add_arcs(i,j), ++k );
		for ( m = 0; BIT(m) < n; ++m );
		for ( i = 0; i < n; weight[i] = extra[i] = 0, ++i );
		for ( bfs(), scanf("%d",&qr); qr--; ) {
			scanf("%d %d %d",&i,&j,&k), t = lca(i,j);
			extra[t] += k, weight[i] += k, weight[j] += k, weight[t] -= 2*k;
		}
		for ( dfs(0), i = 0; i < n; printf("%d\n",weight[i]+extra[i]), ++i );
	}
	return 0;
}

