/*
 * 610. Street Directions
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 0x400
#define oo 0xfffffffful
enum { S, T };
#define is_bridge(x,y) (in_cycle[min(x,y)][max(x,y)] != indeed)

int max( int x, int y ) {
	return x < y ? y : x;
} 

int min( int x, int y ) {
	return x < y ? x : y;
}

int n,m,cs,adj[N][16],deg[N],anc[N][16],
	seen[N],yes,*head,*tail,queue[N],p[N],
	in_cycle[N][N],indeed,K,num[N],cnt,orient[N][N];
unsigned int d[N];

int up( int x, unsigned int dh ) {
	int k = 0;
	for(;dh;++k,dh>>=1)
		if(dh&1)
			x=anc[x][k];
	return x;
}

int lca( int x, int y ) {
	int k;
	if ( x == y )
		return x;
	if ( d[x] < d[y] )
		return lca(y,x);
	if ( d[x] > d[y] )
		return lca(up(x,d[x]-d[y]),y);
	assert( d[x] == d[y] );
	for ( k = K; k--; )
		if ( anc[x][k] != anc[y][k] )
			x = anc[x][k], y = anc[y][k];
	if ( x != y ) 
		x = anc[x][0], y = anc[y][0];
	assert( x == y );
	return x;
}

void mark_cycle( int x, int z ) {
	if(x!=z)
		in_cycle[min(x,anc[x][0])][max(x,anc[x][0])]=indeed,mark_cycle(anc[x][0],z);
}

void dfs( int x ) {
	int i,y;

	assert( seen[x] != yes );
	for ( seen[x] = yes, num[x] = ++cnt, i = 0; i < deg[x]; ++i )
		if ( seen[y = adj[x][i]] != yes ) {
			if ( !is_bridge(x,y) )
				orient[x][y]=yes;
			p[y] = x, dfs(y);
		}
		else if ( p[x] != y ) {
			if ( num[x]<num[y] )
				orient[y][x]=yes;
			else orient[x][y]=yes;
		}
}

int main() {
	int i,j,k,l,x,y,z;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for (;2 == scanf("%d %d",&n,&m) && (n||m); puts("#") ) {
		printf("%d\n\n",++cs);
		for ( i = 0; i < n; deg[i] = 0, d[i++] = +oo );
		for ( K = 0; (1 << K) <= n; ++K );
		for ( x = 0; x < n; ++x )
			for ( k = 0; k <= K; ++k )
				anc[x][k] = -1;
		for ( k = 0; k < m; ++k ) {
			scanf("%d %d",&i,&j), --i, --j;
			adj[j][deg[adj[i][deg[i]++] = j]++] = i;
		}
		for ( ++indeed, head = tail = queue, d[*tail++ = 0] = 0; head < tail; )
			for ( x = *head++, i = 0; i < deg[x]; ++i )
				if ( d[y = adj[x][i]] > d[x] + 1 ) {
					for ( d[*tail++=y]=d[anc[y][0]=x]+1, k=1; (1UL<<k)<=d[y]; ++k )
						anc[y][k]=anc[anc[y][k-1]][k-1];
				}
				else if ( anc[x][0] != y ) {
					assert( (z = lca(x,y)) != -1 );
					mark_cycle(x,z), mark_cycle(y,z), in_cycle[min(x,y)][max(x,y)] = indeed;
				}
		/*
		 */
		for ( x = 0; x < n; ++x )
			for ( i = 0; i < deg[x]; ++i ) 
				if ( x < (y = adj[x][i]) )
					if ( is_bridge(x,y) )
						printf("%d %d\n%d %d\n",x+1,y+1,y+1,x+1);
		cnt = 0, ++yes, dfs( 0 );
		for ( x = 0; x < n; ++x )
			for ( y = 0; y < n; ++y )
				if ( orient[x][y] == yes )
					if ( !is_bridge(x,y) )
						printf("%d %d\n",x+1,y+1);

	}
	return 0;
}
