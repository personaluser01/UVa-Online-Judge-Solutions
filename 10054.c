/*
 * 10054. Necklace
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 64
#define M (1 << 13)
#define EDGE_ID(e) (((e)-(E))>>1)
#define oo 0xfffffffful

int n,color[N],m,deg[N],v[N],E[M],anc[N][32],ok,K,tr[N],*ptr,soln[M],*qtr,ori[N],
	queue[N],*tail,*head,yes,active[M],in_cycle[M],ts,cs,*adj[N][M];
unsigned int d[N];

int up( int x, unsigned int dh ) {
	int k = 0;
	for (;dh; ++k, dh >>= 1 )
		if ( dh & 1 ) x = anc[x][k];
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
	if ( x != y ) {
		assert( anc[x][0] == anc[y][0] );
		x = anc[x][0], y = anc[y][0];
	}
	assert( x == y );
	return x;
}

void mark_cycle( int x, int z ) {
	if ( x != z )
		mark_cycle(anc[x][0],z), in_cycle[tr[x]] = yes;
}

void bfs( int t ) {
	int x,y,i,j,k,z;

	for ( i = 0; i < n; d[v[i++]] = +oo );
	for ( i = 0; i < n; ++i )
		for ( k = 0; k <= K; ++k )
			anc[v[i]][k] = -1;
	for ( ++yes, head = tail = queue, d[*tail++=v[0]]=0; head < tail; ) {
		for ( x = *head++, i = 0; i < deg[x]; ++i ) {
			if(!active[EDGE_ID(adj[x][i])])
				continue ;
			if ( d[y = *adj[x][i]] <= d[x]+1 ) {
				if ( !t ) continue ;
				if (EDGE_ID(adj[x][i])==tr[x])
					continue ;
				assert( (z = lca(x,y)) != -1 );
				mark_cycle(x,z), mark_cycle(y,z), in_cycle[EDGE_ID(adj[x][i])] = yes;
			}
			else {
				for(d[*tail++=y]=d[x]+1,tr[y]=EDGE_ID(adj[x][i]),\
					anc[y][0]=x,k=1;(1UL<<k)<=d[y];++k)
					anc[y][k]=anc[anc[y][k-1]][k-1];
			}
		}
	}
	if ( !t ) {
		for ( i = 0; i < n; ++i )
			if ( d[v[i]] == +oo ) {
				ok = 0;
				return ;
			}
	}
}

void euler_tour( int x ) {
	int i;

	for ( i = 0; i < deg[x]; ++i ) {
		if ( !active[EDGE_ID(adj[x][i])] || in_cycle[EDGE_ID(adj[x][i])] != yes )
			continue ;
		active[*ptr++ = EDGE_ID(adj[x][i])] = 0, *qtr++ = (adj[x][i]-E) & 1, bfs(1);
		euler_tour(*adj[x][i]);
		return ;
	}
	for ( i = 0; i < deg[x]; ++i ) {
		if ( !active[EDGE_ID(adj[x][i])] )
			continue ;
		active[*ptr++ = EDGE_ID(adj[x][i])] = 0, *qtr++ = (adj[x][i]-E) & 1, bfs(1);
		euler_tour(*adj[x][i]);
		return ;
	}
}

int main() {
	int i,j,k,x,y,prev;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( scanf("%d",&ts); ts--; ) {
		if ( cs >= 1 ) putchar('\n');
		printf("Case #%d\n",++cs);
		scanf("%d",&n);
		for ( x = 0; x < N; deg[x++] = 0 );
		for ( m = 0, k = 0; k < n; ++k ) {
			scanf("%d %d",&x,&y), --x, --y;
			E[2*m] = y, E[2*m+1] = x;
			adj[x][deg[x]++] = E+2*m, adj[y][deg[y]++] = E+2*m+1;
			active[m++] = 1;
		}
		for ( n = 0, x = 0; x < N; ++x )
			if ( deg[x] && (v[n++] = x) );
		for ( i = 0; i < n; ++i )
			if ( deg[v[i]] & 1 ) 
				goto nx;
		for ( K = 0; (1 << K) <= n; ++K );
		ok = 1, bfs(0);
		if ( !ok ) goto nx;
		qtr = ori, ptr = soln, euler_tour(v[0]);
		for ( prev = -1, i = 0; i < ptr-soln; ++i ) {
			k = soln[i];
			x = E[2*k], y = E[2*k+1];
			if ( !ori[i] )
				j = x, x = y, y = j;
			printf("%d %d\n",x+1,y+1);
		}
		continue ;
		nx: puts("some beads may be lost");
	}
	return 0;
}

