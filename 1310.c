/*
 * 1310.
 * TOPIC: dfs tree anatomy, back edges, forward edges, cross edges
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 2048
#define BIT(k)  (1UL<<(k))
#define MASK(k) (BIT(k)-1UL)
#define M (1<<21)
#define SET(a,k) (a[(k)>>3]|=BIT((k)&7))
#define TST(a,k) (a[(k)>>3]&BIT((k)&7))
#define CLR(a,k) (a[(k)>>3]&=~BIT((k)&7))
#define mem(a) (memset(a,0,sizeof a))
enum { WHITE, GREY, BLACK };
int min( int x, int y ) { return x<y?x:y; }
int max( int x, int y ) { return x>y?x:y; }

int n,h[N],d[N],from[M],to[M],last[N],next[M],E,parent[N],lowest[N],m,paired[M],in[N],out[N],tick;
char color[N];
unsigned char to_remove[M>>3],is_bridge[M>>3],in_tree[M>>3],is_undirected[M>>3],processed[M>>3];

void add_arc( int x, int y ) {
	int i = E++;
	to[i] = y, from[i] = x, next[i] = last[x], last[x] = i, CLR(is_undirected,i);
}

void add_arcs( int x, int y ) {
	int i = E++, j = E++;
	to[i] = y, from[i] = x, next[i] = last[x], last[x] = i;
	to[j] = x, from[j] = y, next[j] = last[y], last[y] = j;
	SET(is_undirected,i), SET(is_undirected,j);
	paired[paired[i] = j] = i;
}

void f( int x, int depth ) {
	int i,y,black_vertex_reachable = 0;

	assert( color[x] == WHITE );

	for ( in[x] = ++tick, color[x]=GREY, h[x]=d[x]=depth,i=last[x];i>=0&&(y=to[i])>=0;i=next[i] )
		if ( color[y] == WHITE ) 
			parent[y] = x, f(y,depth+1), h[x] = min(h[x],h[y]);
		else if ( color[y] == GREY ) {
			if ( parent[x] != y ) 
				h[x] = min(h[x],d[y]);
		}
		else {
			if ( !(in[x] < in[y] && out[y] < out[x]) ) 
				black_vertex_reachable = 1;
		}
	if ( black_vertex_reachable ) lowest[x] = -1;
	else {
		for ( lowest[x] = h[x], i = last[x]; i >= 0 && (y = to[i]) >= 0; i = next[i] )
			if ( parent[y] == x )
				lowest[x] = max(lowest[x],lowest[y]);
	}
	color[x] = BLACK, out[x] = ++tick;
}

void dfs( int x ) {
	int i,y;
	assert( color[x] == WHITE );
	for ( color[x] = GREY, i = last[x]; i >= 0 && (y = to[i]) >= 0; i = next[i] ) {
		if ( color[y] == WHITE ) 
			SET(in_tree,i), dfs(y);
		else if ( color[y] == GREY ) {
			if ( parent[x] == y ) {
				if ( TST(is_undirected,i) && lowest[x] < d[x] ) { /* i is not a bridge */
					assert( TST(in_tree,paired[i]) );
					SET(to_remove,i);
				}
			}
			else {
				if ( TST(is_undirected,i) ) {
					assert( !TST(in_tree,paired[i]) );
					SET(to_remove,paired[i]); /* paired[i] is a forward edge, i is a back edge */
				}
			}
		}
		else {
			/*assert( !TST(is_undirected,i) );*/
		}
	}
	color[x] = BLACK;
}

void init() {
	int i,j,k;
	mem(to_remove), mem(is_bridge), mem(in_tree), mem(processed), mem(is_undirected);
	for ( tick = -1, E = 0, i = 0; i < n; last[i++] = -1 );
}

void output_results() {
	int i,j;
	for ( i = 0; i < E; ++i ) {
		if ( !TST(is_undirected,i) || TST(processed,i) ) continue ;
		j = paired[i];
		if ( TST(to_remove,i) ) 
			printf("%d %d 1\n",1+from[j],1+to[j]);
		else if ( TST(to_remove,j) ) 
			printf("%d %d 1\n",1+from[i],1+to[i]);
		else 
			printf("%d %d 2\n",1+from[i],1+to[i]);
		SET(processed,i), SET(processed,j);
	}
}

int main() {
	int i,j,k,l,t;
#ifndef ONLINE_JUDGE
	freopen("1310.in","r",stdin);
#endif
	while ( 2 == scanf("%d %d",&n,&m) ) {
		for ( init(), t = 0, l = 0; l < m; ++l ) {
			scanf("%d %d %d",&i,&j,&k), --i, --j;
			if ( k == 2 ) add_arcs(i,j), ++t;
			else add_arc(i,j);
		}
		mem(color), f(0,0), mem(color), dfs(0), output_results();
	}
	return 0;
}

