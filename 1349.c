/*
 * 1349. Optimal Bus Route Design
 * TOPIC: mincost circulation/min weight bipartite matching, hungarian
 * status: Accepted
 */
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXV (N*2)
#define N 0x80
#define MAXE (1<<20)
#define IN(x) (0|((x)<<1))
#define OUT(x) (1|((x)<<1))
#define is_tight(x,y) (p[S][x]+p[T][y]==w[x][y])
#define oo (1<<29)
#define BIT(k) (1ULL<<(k))
#define L(k) ((k)&(~(k)+1ULL))
typedef unsigned long long u64;
enum { S, T };

u64 rev[2][(N>>6)+8];
char which[BIT(21)];

int who( u64 u ) {
	if ( u >= BIT(60) )
		return 60+which[u>>60];
	if ( u >= BIT(40) )
		return 40+which[u>>40];
	if ( u >= BIT(20) )
		return 20+which[u>>20];
	return which[u];
}

int max( int x, int y ) {
	if ( x < y ) return y;
	return x;
}

int min( int x, int y ) {
	if ( x > y ) return y;
	return x;
}

int n,adj[N][N+N+N],deg[N],w[N][N],mate[2][N],p[2][N],
	q[MAXV],head,tail,cnt,needs_revision[2][N],indeed,
	visited[MAXV],yes,df;

void add_arcs( int x, int y, int c ) { 
	if ( w[x][y] < c ) return ;
	w[x][y]=c;
}

int alt_path( int x, const int t ) {
	int i,y;
	if ( visited[x]==yes )
		return 0;
	for ( visited[x]=yes, i=0; i<deg[x]; ++i )
		if ( !t || is_tight(x,y=adj[x][i]) )
			if ( mate[T][y=adj[x][i]]==-1 || alt_path(mate[T][y],t) ) {
				mate[S][mate[T][y]=x]=y;
				return 1;
			}
	return 0;
}

int bpm( const int t ) {
	int x,k,flag;
	do {
		for ( flag=0,k=cnt,++yes; k--; ) {
			x=q[head++],--cnt,head&=(MAXV-1);
			if ( alt_path(x,t) ) flag=1;
			else q[tail++]=x,tail&=(MAXV-1),++cnt;
		}
	} while ( flag );
	return n-cnt;
}

void dfs( int x ) {
	int i,y;
	if ( visited[x]==yes )
		return ;
	for ( visited[x]=yes, rev[S][x>>6]|=BIT(x&63), i = 0; i < deg[x]; ++i ) 
		if ( is_tight(x,y=adj[x][i]) ) {
			assert( mate[T][y] != -1 );
			dfs(mate[T][y]);
			rev[T][y>>6]|=BIT(y&63);
		}
		else {
			assert( w[x][y]-p[S][x]-p[T][y] > 0 );
			df = min(df,w[x][y]-p[S][x]-p[T][y]);
		}
}

void hungarian() {
	int x,y,i,j,k,l,t;
	u64 u;
	for ( y = 0; y < n; p[T][y++] = 0 );
	for ( x = 0; x < n; ++x ) {
		for ( p[S][x] = +oo, i = 0; i < deg[x]; ++i )
			p[S][x] = min(p[S][x],w[x][adj[x][i]]);
		assert( p[S][x] < +oo );
	}
	for (head=tail=0,cnt=0,i=0;i<n;q[tail++]=i++,tail&=(MAXV-1),++cnt);
	for ( i = 0; i < n; mate[S][i] = mate[T][i] = -1, ++i );
	for (;bpm(1)<n;) {
		for ( ++yes, df = +oo, i=head, k=cnt; k--; dfs(q[i]), i = (i+1)&(MAXV-1) );
		assert( df > 0 );
		for ( t = S; t <= T; ++t )
			for ( i = 0; i <= (n>>6); rev[t][i++] = 0 )
				for ( u = rev[t][i]; u; u &= ~L(u) ) {
					x = (i<<6)+who(L(u));
					if ( t == S ) p[S][x] += df;
					else p[T][x] -= df;
				}
	}
	for(k=0,i=0;i<n;k+=w[i][mate[S][i]],++i);
	printf("%d\n",k);
}

int main() {
	int i,j,k,t;
#ifndef ONLINE_JUDGE
	freopen("c.txt","r",stdin);
#endif
	for ( i = 0; i < 21; which[BIT(i)] = i, ++i );
	for (;1==scanf("%d",&n)&&n>0;) {
		for ( i = 0; i < n; ++i )
			for ( j = 0; j < n; ++j )
				w[i][j] = +oo;
		for ( i = 0; i < n; deg[i++] = 0 );
		for ( i=0; i<n; ++i ) 
			for ( mate[S][i]=mate[T][i]=-1; 1==scanf("%d",&j) && --j>=0 && 1==scanf("%d",&k); add_arcs(i,j,k) );
		for ( i = 0; i < n; ++i )
			for ( j = 0; j < n; ++j )
				if ( w[i][j] < +oo )
					adj[i][deg[i]++] = j;
		for (head=tail=0,cnt=0,i=0;i<n;q[tail++]=i++,tail&=(MAXV-1),++cnt);
		if ( bpm(0) < n ) { puts("N"); continue ; }
		hungarian();
	}
	return 0;
};

