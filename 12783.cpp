/*
 * 12783. Weak Links
 * TOPIC: bridges, graph theory, dfs
 * status: Accepted
 */
#include <iostream>
#include <vector>
#include <set>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 0x400
#define M (1<<15)
enum { W=0, G=1, B=2 };
using namespace std;

int n,m,last[N],to[M],next[M],h[N],d[N],color[N],E,p[N],is[N],yes;
set<pair<int,int> > w;

void add_arcs( int x, int y ) {
	int i = E++, j = E++;
	to[i]=y, next[i]=last[x],last[x]=i;
	to[j]=x, next[j]=last[y],last[y]=j;
}

void dfs( int x, int depth ) {
	int i,y;
	assert( color[x] == W );
	for ( color[x] = G, h[x] = d[x] = depth, i = last[x]; i >= 0; i = next[i] )
		if ( color[y = to[i]] == W ) {
			p[y]=x,dfs(y,depth+1);
			h[x]=min(h[x],h[y]);
			if ( h[y] >= depth+1 )
				w.insert(make_pair(min(x,y),max(x,y)));
		}
		else if ( color[y] == G ) {
			if ( p[x] == y ) continue ;
			h[x]=min(h[x],d[y]);
		}
	color[x] = B;
	if ( h[x] >= d[x] )
		is[x] = yes;
}

int main() {
	int i,j,k;
#ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
#endif
	for ( ;2 == scanf("%d %d",&n,&m) && (n||m); ) {
		for ( E = 0, i = 0; i < n; ++i )
			color[i] = W, last[i] = -1;
		for ( k = 0; k < m; ++k ) 
			scanf("%d %d",&i,&j), add_arcs(i,j);
		for ( k = 0, w.clear(), i = 0; i < n; ++i )
			if ( color[i] == W )
	  			dfs(i,0);
		printf("%lu",w.size());
		for ( set<pair<int,int> >::iterator it = w.begin(); it != w.end(); ++it ) 
			printf(" %d %d",it->first,it->second);
		putchar('\n');
	}
    return 0;
}

