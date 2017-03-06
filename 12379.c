/*
 * 12379. Central Post Office
 * TOPIC: tree diameter, eulerian path
 * status: Accepted
 */
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <iostream>
using namespace std;
#define N (1<<17)
#define M (N+N)
#define oo (1<<29)

int next[M],last[N],to[M],E,q[M],*head,*tail,n,m,d[N],yes,seen[N];
vector<int> adj[N];

void add_arcs( int x, int y ) {
	adj[x].push_back(y);
	/*to[j] = x, next[j] = last[y], last[y] = j;*/
}

int bfs( int src, int *furthest ) {
	int i,j,k,x,y;
	for ( *furthest=-1, head=tail=q, x = 0; x < n; d[x++] = +oo );
	for ( d[*tail++=src]=0; head<tail; )
		for ( x=*head++, i = 0; i < (int)adj[x].size(); ++i )
			if ( d[y=adj[x][i]] > d[x]+1 )
				d[*tail++=y]=d[x]+1;
	for ( x = 0; x < n; ++x )
		assert( d[x] < +oo );
	for ( k = 0, x = 0; x < n; ++x )
		if ( d[x] >= k )
			k=d[*furthest=x];
	assert( *furthest != -1 );
	return k;
}

void dfs( int x ) {
	int i,y;
	for ( seen[x] = yes, i = 0; i < (int)adj[x].size(); ++i )
		if ( seen[y=adj[x][i]] != yes ) 
			d[y] = d[x]+1, dfs(y);
}

int main() {
	int i,j,k,ts,cs;
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	for ( scanf("%d",&ts); ts-- && 1 == scanf("%d",&n); ) {
		for ( E = i = 0; i < n; adj[i].clear(), last[i++] = -1 );
		for ( k = 0; k < n; ++k ) 
			for ( scanf("%d",&i); i-- && 1 == scanf("%d",&j); add_arcs(k,j-1) );
		for ( ++yes, k = 0, d[0] = 0, dfs(0), i = 0; i < n; ++i )
			if ( d[i] >= k ) k = d[j = i];
		for ( ++yes, k = 0, d[j] = 0, dfs(j), i = 0; i < n; ++i )
			if ( d[i] > k ) k = d[i];
		//printf("%d\n",(2*n-2)-k);
		bfs(0,&i), printf("%d\n",2*(n-1)-bfs(i,&j));
	}
	return 0;
}

