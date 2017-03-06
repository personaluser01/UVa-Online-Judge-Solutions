/*
 * 1173. The Finest Chef
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <limits.h>
#include <float.h>
#define    excess(x,y)     (w[x][y]-pi[S][x]-pi[T][y])
#define    is_tight(x,y)   (!excess(x,y))
enum { S, T };
#define N 0x200
#define Q 0x400

int min( int x, int y ) { return x<y?x:y; }

int n[2],pi[2][N],w[N][N],mate[2][N],seen[N],yes,df,
	deg[2][N],adj[2][N][N],q[Q],head,tail,cnt,visited[2][N];

int pop() {
	int r=q[head];
	head=(head+1)&(Q-1),--cnt;
	return r;
}
void push( int x ) { q[tail]=x,tail=(tail+1)&(Q-1),++cnt; }

int alt_path( int x ) {
	int y,i;
	if ( seen[x] == yes ) return 0;
	for ( seen[x] = yes, i = 0; i < deg[S][x]; ++i )
		if ( is_tight(x,y=adj[S][x][i]) )
			if ( mate[T][y]==-1||alt_path(mate[T][y]) ) {
				mate[S][mate[T][y] = x] = y;
				return 1;
			}
	return 0;
}

int bpm() {
	int x,flag,k;
	for(flag=1;flag;)
		for(++yes,k=cnt,flag=0;k--;alt_path(x=pop())?(flag=1):push(x));
	return n[S]-cnt;
}

void dfs( int x ) {
	int i,y;
	if ( visited[S][x] == yes )
		return ;
	visited[S][x] = yes;
	for ( i = 0; i < deg[S][x]; ++i ) {
		y = adj[S][x][i];
		assert( excess(x,y) >= 0 );
		if ( is_tight(x,y) ) {
			assert( mate[T][y] >= 0 );
			visited[T][y] = yes;
			dfs( mate[T][y] );
		}
		else
			df = min(df,excess(x,y));
	}
}

void kuhn() {
	int x,y,weight,k,i;
	while ( bpm() < n[S] ) {
		for ( df = (1<<29), ++yes, k = cnt; k--; )
			dfs(x = pop()), push(x);
		assert( df > 0 );
		for ( x = 0; x < n[S]; ++x )
			if ( visited[S][x] == yes )
				pi[S][x] += df;
		for ( y = 0; y < n[T]; ++y )
			if ( visited[T][y] == yes )
				pi[T][y] -= df;
	}
	for ( weight = 0, x = 0; x < n[S]; ++x )
		weight += w[x][mate[S][x]];
	printf("%d\n",weight);
}

int main() {
	int i,j,k,l,ts,x,y;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( scanf("%d",&ts); ts-- && 2 == scanf("%d %d",n+S,n+T);) {
		for ( i = 0; i < n[S]; ++i )
			for ( j = 0; j < n[T]; ++j )
				w[i][j] = (1<<29), mate[S][i] = mate[T][j] = -1;
		for ( scanf("%d",&l); l-- && 3 == scanf("%d %d %d",&i,&j,&k); ) {
			assert( 0 <= i && i < n[S] );
			assert( 0 <= j && j < n[T] );
			w[i][j] = min(w[i][j],k);
		}
		memset(deg,0,sizeof(deg));
		for ( x = 0; x < n[S]; ++x )
			for ( y = 0; y < n[T]; ++y )
				if ( w[x][y] < (1<<29) )
					adj[S][x][deg[S][x]++] = y, adj[T][y][deg[T][y]++] = x;
		memset(pi,0,sizeof(pi));
		for ( x = 0; x < n[S]; ++x )
			for ( pi[S][x] = (1<<29), i = 0; i < deg[S][x]; ++i )
				pi[S][x] = min(pi[S][x],w[x][adj[S][x][i]]);
		for ( head = tail = 0, cnt = 0, x = 0; x < n[S]; push(x++) );
		kuhn();
		if ( ts ) putchar('\n');
	}
	return 0;
}

