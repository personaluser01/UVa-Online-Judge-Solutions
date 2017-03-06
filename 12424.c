/*
 * 12424. Answering Queries on a Tree
 * TOPIC: lca, jumping on powers of two, dp, preorder traversal, interval tree, lazy propagation, segment tree
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXN (1<<17)
#define N MAXN
#define MAXE (1<<21)
#define K 17
#define oo (1<<29)
#define MAXC 10
int max( int x, int y ) { return x<y?y:x; }

int last[MAXN],next[MAXE],to[MAXE],col[MAXN],p[MAXN],anc[N][K],q[MAXN],*head,*tail,d[MAXN],
	name[MAXN],pos[N],h[N],cur,E,m,n,
	tr[N<<1][MAXC],val[N][MAXC],
	bucket[MAXN<<1][MAXC];

int up( int x, unsigned int k ) {
	int i;
	for ( i = 0; i < K; ++i )
		if ( (k&(1UL<<i)) ) x = anc[x][i];
	return x;
}

int lca( int x, int y ) {
	int k;
	if ( d[x] < d[y] ) 
		return lca(y,x);
	if ( d[x] > d[y] )
		return lca(up(x,d[x]-d[y]),y);
	assert( d[x] == d[y] );
	if ( x == y ) return x;
	for ( k = K-1; k; --k )
		if ( anc[x][k-1] != anc[y][k-1] )
			x = anc[x][k-1], y = anc[y][k-1];
	return anc[x][0];
}

void add_arc( int x, int y ) {
	int i = E++;
	to[i] = y, next[i] = last[x], last[x] = i;
}

int calc_h( int x ) {
	int i,y;
	if ( h[x] < +oo )
		return h[x];
	for ( h[x] = 1, pos[x] = cur++, i = last[x]; i >= 0; i = next[i] )
		if ( (y=to[i]) != p[x] && h[y] == +oo ) 
			h[x] += calc_h(y);
	return h[x];
}

void fill_array( int x, int cnt, const int ch ) {
	int i,y;
	if ( val[pos[x]][ch] < +oo )
		return ;
	for ( val[pos[x]][ch] = cnt+(ch==col[x]?1:0), i = last[x]; i >= 0; i = next[i] )
		if ( (y=to[i]) != p[x] )
			fill_array(y,val[pos[x]][ch],ch);
}

int build_tree( int r, int i, int j, const int ch ) {
	int k = (i+j)/2;
	bucket[r][ch] = 0;
	if ( i == j ) 
		return tr[r][ch] = val[i][ch];
	return tr[r][ch] = build_tree(2*r,i,k,ch)+build_tree(2*r+1,k+1,j,ch);
}

void update( int r, int i, int j, int qi, int qj, int dt, const int ch ) {
	int k = (i+j)/2;
	assert( i <= j );
	if ( i > qj || j < qi ) 
		return ;
	if ( qi <= i && j <= qj ) {
		bucket[r][ch] += (j-i+1)*dt;
		return ;
	}
	update(2*r,i,k,qi,qj,dt,ch), update(2*r+1,k+1,j,qi,qj,dt,ch);
}

int f( int r, int i, int j, int qi, int qj, const int ch ) {
	int k = (i+j)/2;
	assert( i <= j );
	if ( i > qj || qi > j )
		return 0;
	if ( qi <= i && j <= qj ) {
		if ( bucket[r][ch] )
			tr[r][ch] += bucket[r][ch], bucket[r][ch] = 0;
		return tr[r][ch];
	}
	assert( k < j );
	if ( bucket[r][ch] ) 
		bucket[2*r][ch] += bucket[r][ch]/(j-i+1)*(k-i+1), bucket[2*r+1][ch] += bucket[r][ch]/(j-i+1)*(j-k), bucket[r][ch] = 0;
	return f(2*r,i,k,qi,qj,ch)+f(2*r+1,k+1,j,qi,qj,ch);
}

int answer_query( int u, int v ) {
	int z = lca(u,v),k,t = p[z], ans = 0;
	for ( k = 0; k < MAXC; ++k ) 
		ans = max(ans,f(1,0,n-1,pos[u],pos[u],k)+f(1,0,n-1,pos[v],pos[v],k)-f(1,0,n-1,pos[z],pos[z],k)-(t==-1?0:f(1,0,n-1,pos[t],pos[t],k)));
	return ans;
}

int main() {
	int i,j,k,ts,cs,x,y,old_color;
#ifndef ONLINE_JUDGE
	freopen("12424.in","r",stdin);
#endif
	for ( scanf("%d",&ts); ts--; ) {
		for ( scanf("%d %d",&n,&m), i = 0; i < n; last[i++] = -1 );
		for ( i = 0; i < n; h[i] = d[i] = +oo, p[i] = last[i] = -1, scanf("%d",&col[i++]), --col[i-1] );
		for ( i = 0; i < N; ++i )
			for ( k = 0; k < MAXC; val[i][k++] = +oo );
		for ( i = 0; i < n; ++i )
			for ( k = 0; k < K; anc[i][k++] = -1 );
		for ( E = 0, k = 0; k < n-1; ++k, scanf("%d %d",&i,&j), --i, --j, add_arc(i,j), add_arc(j,i) );
		for ( p[0]=-1, head=tail=q, d[*tail++=0]=0; head<tail; )
			for ( i=last[x=*head++]; i>=0; i=next[i] )
				if ( d[y=to[i]]>d[x]+1 ) 
					for ( p[*tail++=y]=x, d[y]=d[x]+1, anc[y][0]=x, k=1; anc[y][k-1] >= 0; anc[y][k]=anc[anc[y][k-1]][k-1], ++k );
		cur = 0;
		assert( calc_h(0) == n );
		assert( cur == n );
		for ( k = 0; k < MAXC; fill_array(0,0,k++) );
		for ( k = 0; k < MAXC; build_tree(1,0,n-1,k++) );
		for (;m-- && 3==scanf("%d %d %d",&k,&i,&j);) {
			--i, --j;
			switch ( k ) {
				case 0: old_color = col[i], col[i] = j;
						update(1,0,n-1,pos[i],pos[i]+h[i]-1,-1,old_color);
						update(1,0,n-1,pos[i],pos[i]+h[i]-1,1,col[i]);
						break ;
				case 1: printf("%d\n",answer_query(i,j));
						break ;
				default: assert( 0 );
			}
		}
	}
	return 0;
}

