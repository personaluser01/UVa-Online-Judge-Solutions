/*
 * 1146. Now or later
 * TOPIC: 2-sat
 * status: Accepted
 */
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N (0x400*2)
typedef long long i64;
#define MAXV (2*N)
#define MAXE (1<<20)
#define enc(t,x) ((t)|((x)<<1))
#define oo (1<<29)
enum { S, T };

typedef struct { int x,y; } seg;
seg c[N];
int last[2][MAXV],next[2][MAXE],to[2][MAXE],V,E[2],n,st[MAXV],*top,seen[2][MAXV],yes[2],scc[MAXV],mark;

void add_arc( int x, int y ) {
	int i = E[S]++, j = E[T]++;
	to[S][i] = y, next[S][i] = last[S][x], last[S][x] = i;
	to[T][j] = x, next[T][j] = last[T][y], last[T][y] = j;
}

void dfs( int t, int x ) {
	int i,y;
	for ( seen[t][x] = yes[t], i = last[t][x]; i >= 0; i = next[t][i] )
		if ( seen[t][y=to[t][i]] != yes[t] ) 
			dfs(t,y);
	if ( t == T ) *++top = x;
	else scc[x] = mark;
}

int f( const int gap ) {
	int i,j,k;
	for ( V=2*n, i = 0; i < V; ++i )
		for ( j = S; j <= T; last[j++][i] = -1 );
	for ( E[S]=E[T]=0, i=0; i<n; ++i )
		for ( j=i+1; j<n; ++j ) {
			if ( abs(c[i].x-c[j].x) < gap && abs(c[i].x-c[j].y) < gap &&\
			   	 abs(c[i].y-c[j].x) < gap && abs(c[i].y-c[j].y) < gap )
				return 0;
			if ( abs(c[i].x-c[j].x) < gap ) { /* both i and j can not be early */
				add_arc(enc(0,i),enc(1,j));
				add_arc(enc(0,j),enc(1,i));
			}
			if ( abs(c[i].y-c[j].y) < gap ) { /* both i and j can not be late */
				add_arc(enc(1,i),enc(0,j));
				add_arc(enc(1,j),enc(0,i));
			}
			if ( abs(c[i].x-c[j].y) < gap ) {
				add_arc(enc(0,i),enc(0,j));
				add_arc(enc(1,j),enc(1,i));
			}
			if ( abs(c[i].y-c[j].x) < gap ) {
				add_arc(enc(1,i),enc(1,j));
				add_arc(enc(0,j),enc(0,i));
			}
		}
	for ( top = st, ++yes[T], i = 0; i < V; ++i )
		if ( seen[T][i] != yes[T] )
			dfs(T,i);
	for ( mark=0, ++yes[S]; top > st; )
		if ( seen[S][i=*top--] != yes[S] ) 
			++mark, dfs(S,i);
	for ( i = 0; i < n; ++i )
		if ( scc[enc(S,i)] == scc[enc(T,i)] )
			return 0;
	return 1;
}

int main() {
	int i,j,k,good,bad,mid;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for (;1==scanf("%d",&n) && n; printf("%d\n",good) ) {
		for ( i = 0; i < n; scanf("%d %d",&c[i].x,&c[i].y), ++i );
		assert ( !f(+oo) );
		for ( good=0,bad=+oo; good+1<bad;)
			if ( f(mid=(good+bad)/2) )
				good = mid;
			else bad = mid;
	}
	return 0;
}

