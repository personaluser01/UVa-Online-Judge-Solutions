/*
 * 302. John's Trip
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define M 2014
#define N 64
#define xchg(x,y) (((x)==(y))||((x)^=(y),(y)^=(x),(x)^=(y)))
#define oo 0xfffffffful
enum { WHITE, GREY, BLACK };

typedef struct {
	int x,y;
	int id;
} edge;

edge e[M << 1],*adj[N][M<<1];
int m,n,v[N],deg[N],queue[N],*tail,*head,src,ok,K,
	anc[N][256],in_cycle[M],yes,active[M],lst[M],
	soln[M],*ptr,tr[N];
unsigned int depth[N];

int cmp( const void *a, const void *b ) {
	edge *m = (edge *)a,
		 *n = (edge *)b;
	return (m->id)-(n->id);
}

int read_block() {
	int x,y,i,j,k;
	edge *tmp;

	for ( k = 0; k < M; active[k++] = 0 );
	for ( ok = 1, x = 0; x < N; deg[x++] = 0 );
	for ( m = 0; 2 == scanf("%d %d",&x,&y) && (x||y); ++m ) {
		scanf("%d",&k), active[k] = 1;
		if ( x > y ) xchg(x,y);
		assert( x <= y );
		if ( !m ) src = x;
		e[2*m].x   = x, e[2*m].y   = y, e[2*m].id   = k;
		e[2*m+1].x = y, e[2*m+1].y = x, e[2*m+1].id = k;
		adj[x][deg[x]++] = e+2*m;
		adj[y][deg[y]++] = e+2*m+1;
	}
	if ( !m ) return 0;
	for ( n = 0, x = 0; x < N; ++x ) 
		if ( deg[x] ) {
			if ( deg[x] & 1 ) {
				ok = 0;
				return m;
			}
			v[n++] = x;
		}
	for ( i = 0; i < n; ++i )
		if ( v[i] == src )
			src = i;
	for ( i = 0; i < n; ++i ) {
		for ( j = 1; j;)
			for ( j = 0, k = 0; k < deg[v[i]]-1; ++k )
				if ( cmp(adj[v[i]][k],adj[v[i]][k+1]) > 0 && ++j )
					tmp = adj[v[i]][k], adj[v[i]][k] = adj[v[i]][k+1], adj[v[i]][k+1] = tmp;
		for ( j = 0; j < deg[v[i]]-1; ++j )
			assert( adj[v[i]][j]->id <= adj[v[i]][j+1]->id );
	}
	for ( K = 0; (1 << K) < n; ++K );
	return m;
}

int up( int x, unsigned int d ) {
	int k = 0;
	for (;d; d >>= 1, ++k )
		if ( d & 1 )
			x = anc[x][k];
	return x;
}

int lca( int x, int y ) {
	int k;
	if ( x == y )
		return x;
	if ( depth[x] < depth[y] )
		return lca(y,x);
	if ( depth[x] > depth[y] )
		return lca(up(x,depth[x]-depth[y]),y);
	assert( depth[x] == depth[y] && x != y );
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

void mark_path( int x, int z ) {
	if ( x != z )
		in_cycle[tr[x]] = yes, mark_path(anc[x][0],z);
}

void bfs( int t ) {
	int x,y,i,j,k,z;

	head = tail = queue;
	memset(depth,0xff,sizeof(depth));
	for ( i = 0; i < n; ++i )
		for ( k = 0; k <= K; ++k )
			anc[v[i]][k] = -1;
	for (++yes,depth[*tail++=v[src]]=0, tr[v[src]] = -1;head<tail;) {
		for ( x = *head++, i = 0; i < deg[x]; ++i ) {
			if ( !active[adj[x][i]->id] )
				continue ;
			if ( depth[y = adj[x][i]->y] <= depth[x]+1 ) {
				if ( !t ) continue ;
				if ( tr[x] == adj[x][i]->id )
					continue ;
				if ( x == y ) {
					in_cycle[adj[x][i]->id] = yes;
					continue ;
				}
				assert( (z = lca(x,y)) != -1 );
				mark_path(x,z),mark_path(y,z),in_cycle[adj[x][i]->id]=yes;
				continue ;
			}
			for(tr[y]=adj[x][i]->id,depth[*tail++=y]=depth[x]+1,anc[y][0]=x,k=1;\
				(1UL<<k)<=depth[y];++k)
				anc[y][k] = anc[anc[y][k-1]][k-1];
		}
	}
	if ( !t ) {
		for ( i = 0; i < n; ++i )
			if ( depth[v[i]] == +oo ) {
				ok = 0;
				return ;
			}
	}
}

int eligible( edge *a ) {
	if ( !active[a->id] )
		return 0;
	return in_cycle[a->id] == yes;
}

void euler_tour( int x ) {
	int i;

	for ( i = 0; i < deg[x]; ++i ) {
		if ( !eligible(adj[x][i]) )
			continue ;
		active[adj[x][i]->id] = 0, bfs(1);
		*ptr++ = adj[x][i]->id;
		euler_tour(adj[x][i]->y);
		return ;
	}
	for ( i = 0; i < deg[x]; ++i ) {
		if ( !active[adj[x][i]->id] )
			continue ;
		assert( in_cycle[adj[x][i]->id] != yes );
		active[adj[x][i]->id] = 0, bfs(1);
		*ptr++ = adj[x][i]->id;
		euler_tour(adj[x][i]->y);
		return ;
	}
}

int main() {
	int i,j,k,x,y;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for (;read_block(); putchar('\n') ) {
		if ( !ok ) {
			epaonnistu:
				puts("Round trip does not exist.");
			continue ;
		}
		bfs( 0 );
		if ( !ok ) goto epaonnistu;
		ptr = soln, euler_tour( v[src] );
		for ( i = 0; i < ptr-soln-1; ++i )
			printf("%d ",soln[i]);
		printf("%d\n",soln[i]);
	}
	return 0;
}
