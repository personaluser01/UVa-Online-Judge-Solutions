/*
 * 12277. Locks and Keys
 * TOPIC: trees, lca, swerc2010
 * status: Accepted
 */
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXK 14
#define N (1<<12)
#define MAXE (1<<21)
#define Q (1<<22)
enum { D, T };
enum { WHITE, GREY, BLACK };

int n,m,src,dst,key_location[N],next[MAXE],to[MAXE],last[N],E,V,door[MAXE],
	anc[N][MAXK],q[N],*head,*tail,seen[N],yes,d[N],target[N],
	adj[2][N][N],deg[2][N],*qtr,out[Q],is_open[N],K,
	path[Q],*ptr,parent[N],visited[N],indeed,o[N],len,
	tin[N],tout[N],tick;
char color[N];

void dfstimer( int x ) {
	int i,y,k;
	assert( color[x] == WHITE );
	for ( color[x]=GREY, tin[x]=++tick, i=last[x]; i>=0; i=next[i] )
		if ( color[y=to[i]]==WHITE ) {
			for ( d[y] = d[x]+1, anc[y][0] = x, k = 1; anc[y][k-1] >= 0; anc[y][k] = anc[anc[y][k-1]][k-1], ++k );
			dfstimer(y);
		}
		else if ( color[y]==GREY ) {
			assert( anc[x][0] == y );
		}
	color[x]=BLACK, tout[x]=++tick;
}

void add_arc( int x, int y, int col ) {
	int i = E++, j = E++;
	assert( j < MAXE );
	to[i] = y, next[i] = last[x], last[x] = i;
	to[j] = x, next[j] = last[y], last[y] = j;
	door[i] = door[j] = col;
};

int up( int x, int n ) {
	int k = 0;
	for ( ;n; n >>= 1, ++k )
		if ( n&1 )
			x = anc[x][k];
	assert( x >= 0 );
	return x;
}

int lca( int x, int y ) {
	int k;
	if ( x == y ) return x;
	if ( tin[x] <= tin[y] && tout[y] <= tout[x] )
		return x;
	if ( tin[y] <= tin[x] && tout[x] <= tout[y] )
		return y;
	if ( d[y] > d[x] )
		return lca(y,x);
	if ( d[y] < d[x] )
		return lca(up(x,d[x]-d[y]),y);
	assert(d[x]==d[y]);
	if ( x < 0 || y < 0 || anc[x][K-1] != anc[y][K-1] ) 
		printf("[K = %d] %d %d %d %d, depth = %d\n",K,x,y,anc[x][K-1],anc[y][K-1],d[x]);
	assert( x >= 0 && y >= 0 && anc[x][k=K-1]==anc[y][k=K-1] );
	for(;k--;) {
		if (anc[x][k]!=anc[y][k])
			x = anc[x][k], y = anc[y][k];
		assert( anc[x][k+1] == anc[y][k+1] );
	}
	assert( x != y ); assert( anc[x][0] == anc[y][0] );
	return anc[x][0];
}

int dfs_detect_cycle( int x ) {
	int i,y;
	assert( color[x] == WHITE );
	for ( color[x] = GREY, i = 0; i < deg[T][x]; ++i )
		if ( color[y = adj[T][x][i]] == WHITE ) {
			if ( dfs_detect_cycle(y) )
				return 1;
		}
		else {
			if ( color[y] == GREY ) 
				return 1;
		}
	color[x] = BLACK;
	return 0;
}

int descending( int x, int y ) {
	return tin[x] <= tin[y] && tout[y] <= tout[x];
}

void find_path( int src, int dst, int w ) {
	int z = lca(src,dst),t,i,x,y,
		*head,*tail,q[N];
	char used[N];
	assert( z != -1 );
	/*printf("[n = %d, m = %d] src = %d, dst = %d\n",n,m,src,dst);*/
	if ( src == dst ) { *ptr++ = src; return ; }
	if ( src == z ) {
		assert( ptr-path < Q );
		memset(used,0,sizeof used);
		for(*ptr++=src,head=tail=q,used[*tail++=src]=1;head<tail&&*(ptr-1)!=dst;)
			for ( i=last[x=*head++]; i>=0; i=next[i] )
				/*if ( !used[y=to[i]] && lca(y,dst)==y ) {*/
				if ( !used[y=to[i]] && descending(x,y) && tin[y]<=tin[dst] && tout[dst]<=tout[y] ) {
					/*printf("[%*d [%d %d] %d]\n",w,tin[y],tin[dst],tout[dst],tout[y]);*/
					used[*tail++=y]=1;
					if ( (t=door[i])>=0 && !is_open[t] )
						find_path(x,key_location[t],w+4),find_path(key_location[t],x,w+4),is_open[t]=1;
					assert( ptr-path < Q );
					*ptr++=y;
					break ;
				}
		assert( *(ptr-1) == dst );
		return ;
	}
	assert( ptr-path<Q );
	for ( *ptr++=(t=src); (t=anc[t][0])!=z && t != -1; *ptr++=t );
	assert( t!=-1 );
	find_path(z,dst,w+4);
}

int cycle_reachable( int x ) {
	memset(color,WHITE,sizeof color);
	return dfs_detect_cycle(x);
}

int main() {
	int i,j,k,t,l,x,y,cur,ok,ll;
#ifndef ONLINE_JUDGE
	freopen("12277.in","r",stdin);
	/*freopen("in.txt","r",stdin);*/
#endif
	for ( ;4 == scanf("%d %d %d %d",&n,&m,&src,&dst) && (n||m||src||dst); ) {
		for ( i = 0; i < n; last[i++] = -1 );
		for ( K = 0; (1<<K) <= n; ++K );
		for ( i = 0; i < m; ++i ) for ( k = D; k <= T; deg[k++][i] = 0 );
		for ( E = 0, i = 0; i < m; target[i] = -1, scanf("%d",&key_location[i++]) );
		for ( k = 0; k < n-1; scanf("%d %d %d",&i,&j,&l), add_arc(i,j,l), ++k );

		for ( i = 0; i < n; ++i ) for ( k = 0; k < K; anc[i][k++] = -1 );
		memset(is_open,0,sizeof is_open), memset(color,WHITE,sizeof color), tick = 0, d[src] = 0, dfstimer(src);

		/* build depdendency graph: x-->y iff for unlocking y the door x has to be unlocked, too */
		for ( k = 0; k < m; ++k ) 
			for ( head=tail=q, seen[*tail++=src]=++yes; head<tail && seen[key_location[k]] != yes;)
				for ( i = last[x=*head++]; i >= 0; i = next[i] ) 
					/*if ( seen[y=to[i]]!=yes && lca(key_location[k],y)==y ) {*/
					if ( seen[y=to[i]]!=yes && tin[y] <= tin[key_location[k]] && tout[key_location[k]] <= tout[y] ) {
						seen[*tail++=y]=yes;
						if ( (t=door[i]) >= 0 ) {
							adj[D][t][deg[D][t]++] = k, adj[T][k][deg[T][k]++] = t;
						}
						break ;
					}
		for ( k = 0; k < m; ++k ) 
			for ( head=tail=q, seen[*tail++=src]=++yes; head<tail && seen[target[k]] != yes;)
				for ( i = last[x=*head++]; i >= 0; i = next[i] ) 
					/*if ( seen[y=to[i]]!=yes && lca(target[k],y)==y ) {*/
					if ( seen[y=to[i]]!=yes && tin[y] <= tin[target[k]] && tout[target[k]] <= tout[y] ) {
						seen[*tail++=y]=yes;
						if ( (t=door[i]) >= 0 && t != k ) 
							adj[D][t][deg[D][t]++] = k, adj[T][k][deg[T][k]++] = t;
						break ;
					}
		/* all the doors on the path src-->dst */
		for ( len = 0, head = tail = q, seen[*tail++ = src] = ++yes; head < tail && seen[dst] != yes; )
			for ( i = last[x = *head++]; i >= 0; i = next[i] )
				/*if ( seen[y = to[i]] != yes && lca(y,dst) == y ) {*/
				if ( seen[y = to[i]] != yes && descending(x,y) && tin[y] <= tin[dst] && tout[dst] <= tout[y] ) {
					seen[*tail++ = y] = yes;
					if ( (t=door[i]) >= 0 )
						o[len++] = t;
					break ;
				}

		for ( ok = 1, i = 0; i < len && ok; ok &= !cycle_reachable(o[i++]) );
		if ( !ok ) { puts("Impossible"); continue ; }
		ptr = path, find_path(src,dst,0);
		for ( qtr = out, i = 0; i < ptr-path; *qtr++ = path[i], i = j )
			for ( j = i+1; j < ptr-path && path[i] == path[j]; ++j );
		assert( qtr-out <= 4*(m+1)*n );
		for ( printf("%lu:",qtr-out-1), i = 0; i < qtr-out; printf(" %d",out[i++]) );
		putchar('\n');
	}
	return 0;
}

