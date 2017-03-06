/*
 * 1599. Ideal Path
 * TOPIC: bfs, neat
 * status: Accepted
 */
#include <cassert>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <set>
using namespace std;
#define N (1<<17)
#define oo (1LL<<30)

int seen[N],yes,m,n,q[N],*head,*tail;

struct edge {
	int from,to;
	long long color;
	edge() {};
	edge( int from, int to, long long color ) {
		this->to = to, this->from = from, this->color = color;
	}
	int operator [] ( int i ) const {
		if ( i == 0 ) return from;
		return to;
	}
};

edge *parent[N],*path[N],**top = path;

struct comp {
	bool operator () ( const edge *a, const edge *b ) {
		if ( a->color == b->color ) 
			return a->to-b->to;
		return a->color-b->color;
	}
};

set<edge *,comp> adj[N];
long long ans[N],D[N],min_color,dist;

void dump( int x ) {
	if ( x ) dump(parent[x]->from), *++top = parent[x];
}

int main() {
	int i,j,k,l,x,y;
	bool flag,equality_broken;
#ifndef ONLINE_JUDGE
	freopen("1599.in","r",stdin);
#endif
	for (;2 == scanf("%d %d",&n,&m) && ++yes;) {
		for ( i = 0; i < n; D[i] = +oo, adj[i++].clear() );
		for ( l = 0; l < m; ++l ) 
			scanf("%d %d %d",&i,&j,&k), --i, --j, adj[i].insert(new edge(i,j,k)), adj[j].insert(new edge(j,i,k));

		for ( D[n-1]=0, head=tail=q, seen[*tail++ = n-1] = yes; head < tail; ) 
			for ( set<edge *,comp>::iterator it = adj[x = *head++].begin(); it != adj[x].end(); ++it ) 
				if ( seen[y=(*it)->to] != yes ) 
					seen[*tail++=y]=yes, D[y]=D[x]+1;
		assert( (dist = D[0]) < +oo );
		for ( i = 0; i <= dist; ans[i++] = +oo );
		for ( head=tail=q, seen[*tail++=0]=++yes; head < tail; ) {
			min_color = +oo;
			for ( set<edge *,comp> :: iterator it = adj[x = *head++].begin(); it != adj[x].end(); ++it ) 
				if ( D[y = (*it)->to] < +oo && D[x] == D[y]+1 ) 
					min_color = min(min_color,(*it)->color);
			if ( min_color < +oo ) {
				long long t = D[0]-D[x]+1;
				ans[t] = min(ans[t],min_color);
			}
			for ( set<edge *,comp> :: iterator it = adj[x].begin(); min_color < +oo && it != adj[x].end(); ++it )
				if ( D[y = (*it)->to] < +oo && D[y]+1 == D[x] ) 
					if ( (*it)->color == min_color ) 
						if ( seen[y] != yes || 0&&parent[y]->color > (*it)->color )
							seen[y] = yes, parent[*tail++ = y] = (*it);
		}
		printf("%lld\n",dist);
		for ( i = 1; i <= dist; ++i )
			if ( i > 1 ) printf(" %lld",ans[i]);
			else printf("%lld",ans[i]);
		putchar('\n');
	}
	return 0;
}


