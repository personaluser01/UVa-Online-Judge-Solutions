/*
 * 11183. Teen Girls Squad
 * TOPIC: Chu-Liu-Edmonds Algorithms, mincost arborescence, graph contraction, recursion, cycles
 * status: Accepted
 */
#include <cassert>
#include <cstdio>
#include <algorithm>
#include <map>
#include <cstdlib>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <cmath>
#include <vector>
#include <queue>
#include <set>
using namespace std;
#define N 0x400
typedef long long i64;
#define oo (1L<<29)

class graph {
	public:
		int V,E,n,m,*to,*from,*next,*last,*weight,*pi;
		map<int,int> h;
	graph( int n, int m, int V ) {
		this->n = n, this->m = m, this->V = V, E = 0;
		to = (int *)malloc(m*sizeof *to);
		from = (int *)malloc(m*sizeof *from);
		next = (int *)malloc(m*sizeof *next);
		weight = (int *)malloc(m*sizeof *weight);
		last = (int *)malloc(n*sizeof *last);
		pi = (int *)malloc(n*sizeof *pi);
		for ( int i = 0; i < n; pi[i] = -1, last[i++] = -1 );
	}
	~graph() { free(to), free(next), free(last), free(weight), free(pi), free(from); }
	int add_edge( int x, int y, int w, int parent_id ) {
		int i = E++;
		from[i] = x, to[i] = y, next[i] = last[x], weight[last[x] = i] = w, pi[y] = i;
		h[i] = parent_id;
		return i;
	}
	void set_mapping( int x, int y ) { h[x] = y; }
	int get_mapping( int x ) { return h[x]; }
};

bool bfs( const graph *g ) {
	queue<int> q;
	bool *seen = new bool[g->n];
	int i,j,k,x,y;
	for ( i = 0; i < g->n; seen[i++] = false );
	for ( q.push(0), seen[0] = true; !q.empty();)
		for ( i = g->last[x=q.front()], q.pop(); i >= 0; i = g->next[i] )
			if ( !seen[y = g->to[i]] )
				seen[y] = true, q.push(y);
	for ( k = 0, i = 0; i < g->n; ++i )
		if ( seen[i] ) ++k;
	return k == g->V;
}

bool dfs( const graph *g, int x, vector<int> &v, int *color, int *cost ) {
	int i,j,k,y;
	assert( color[x] == 0 );
	for ( color[x] = 1, i = g->last[x]; i >= 0; i = g->next[i] )
		if ( color[y=g->to[i]]==0 ) {
			g->pi[y]=i;
			if ( dfs(g,y,v,color,cost) )
				return true;
		}
		else if ( color[y] == 1 ) {
			// printf("Attempting %d-->%d\n",x,y);
			for ( j=i,*cost=g->weight[i],v.clear(),i=x,v.push_back(i),*cost+=g->weight[g->pi[i]],i=g->from[g->pi[i]]; i!=y; v.push_back(i),*cost+=g->weight[g->pi[i]],i=g->from[g->pi[i]] );
			v.push_back(y), g->pi[y]=j;
			return true;
		}
	color[x] = 2;
	return false;
}

bool has_cycle( const graph *g, vector<int> &v, int *color, int *cost ) {
	bool *seen = new bool[g->n];
	int i,j;
	for ( i = 0; i < g->n; seen[i++] = false );
	for ( i = 0; i < g->n; ++i )
		if ( !seen[i] ) {
			for ( j = 0; j < g->n; color[j++] = 0 );
			if ( dfs(g,i,v,color,cost) ) 
				return true;
			for ( j = 0; j < g->n; ++j )
				if ( color[j] == 2 )
					seen[j] = true;
		}
	return false;
}

i64 cle( const graph *g, int shift ) {
	graph *ng;
	i64 ax = 0;

	if ( g->V <= 1 ) return 0LL;

	int *cheapest_edge = new int[g->n],i,j,k,l,t,x,y,cost = 0,n = g->n,
		*to = g->to, *last = g->last, *next = g->next, *weight = g->weight,
		*from = g->from;

	for ( i = 0; i < g->n; ++i )
		cheapest_edge[i] = -1;

	for ( i = 0; i < g->E; ++i )
		if ( (j=cheapest_edge[y=to[i]])==-1||weight[i]<weight[j] )
			g->pi[y]=i, cheapest_edge[y]=i;

	assert( cheapest_edge[0] == -1 );

	for ( k = 0, i = 0; i < g->n; ++i )
		if ( cheapest_edge[i] != -1 && ++k );

	ng = new graph(n,k,n);
	for ( x = 0; x < g->n; ++x )
		if ( (j=cheapest_edge[x]) != -1 ) {
			assert( to[j] == x );
			l = ng->add_edge(from[j],x,weight[j],j), ax += weight[j];
		}

	vector<int> v;

	int *color = new int[n];

	if ( !has_cycle(ng,v,color,&cost) ) {
		delete ng; delete cheapest_edge; delete color;
		return ax;
	}

	int *p = new int[n];
	for ( x = 0; x < n; ++x )
		p[x] = ng->get_mapping(ng->pi[x]);

	delete ng; delete color;

	set<int> s(v.begin(),v.end());

	/*
	puts("Cycle:");
	for ( set<int>::iterator it = s.begin(); it != s.end(); ++it ) {
		printf("%d ",*it);
		if ( s.find(from[p[*it]]) == s.end() )
			printf("This one cannot be found: %d-->%d\n",from[p[*it]],*it);
		assert( s.find(from[p[*it]]) != s.end() );
	}
	printf("Cost of cycle: %d\n",cost);
	*/

	set<int>::iterator it = s.begin();
	bool x_in_s, y_in_s;

	ng = new graph(n,g->E-v.size(),g->V+1-v.size());

	for ( t = *it, i = 0; i < g->E; ++i ) {
		x = from[i], y = to[i];
		x_in_s = (s.find(x)!=s.end());
		y_in_s = (s.find(y)!=s.end());
		if ( !x_in_s && !y_in_s ) {
			ng->add_edge(x,y,weight[i],i);
			continue ;
		}
		if ( x_in_s && !y_in_s ) {
			ng->add_edge(t,y,weight[i],i);
			continue ;
		}
		if ( !x_in_s && y_in_s ) {
			ng->add_edge(x,t,weight[i]-weight[cheapest_edge[y]],i);
			// ng->add_edge(x,t,weight[i],i);
			continue ;
		}
	}

	k = cle(ng,shift+4);
	int xx=-1,yy=-1;

	l = ng->get_mapping(ng->pi[t]);
	xx = from[l], yy = to[l];
	assert( s.find(xx) == s.end() );
	assert( s.find(yy) != s.end() );
	
	assert( xx != -1 );
	delete ng; 

	i64 ans;

	assert( cheapest_edge[yy] >= 0 );

	ans = k+cost+weight[cheapest_edge[yy]]-weight[p[yy]];

	delete p; delete cheapest_edge;

	return ans;

}

int main() {
	int i,j,k,m,n,ts,cs = 0;
	int g[N][N];
	graph *G;
#ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
#endif
	for ( scanf("%d",&ts); ts-- && 2 == scanf("%d %d",&n,&m); ) {
		printf("Case #%d: ",++cs);
		for ( i = 0; i < n; ++i )
			for ( j = 0; j < n; g[i][j++] = +oo );
		for (;m-- && 3 == scanf("%d %d %d",&i,&j,&k); g[i][j]=min(g[i][j],k) );
		for ( m = 0, i = 0; i < n; ++i )
			for ( j = 1; j < n; ++j )
				if ( g[i][j] < +oo && ++m );
		G = new graph(n,m,n);
		for ( i = 0; i < n; ++i )
			for ( j = 1; j < n; ++j )
				if ( g[i][j] < +oo )
					G->add_edge(i,j,g[i][j],-1);
		if(!bfs(G)){puts("Possums!");continue;}
		printf("%lld\n",cle(G,0));
	}
    return 0;
}

