/*
 * 11380. Down Went the Titanic
 * status: Accepted
 */
#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <set>
#include <cstring>
#include <queue>
#include <iostream>
#include <vector>
#define DIM 0x30
#define vc(x,y) (0<=(x)&&(x)<m&&0<=(y)&&(y)<n)
#define v(x,y) (((x)*n+(y))+2)
#define IN(u) ((u)<<1)
#define OUT(u) (1|((u)<<1))
using namespace std;
#define Q (1 << 17)
#define is_active(x) (x != src && x != sink && d[x] < 3*V && excess[x] > 0)
#define oo (1 << 29)

typedef struct edge { struct edge *back_edge; int x,y; int capacity, flow; } edge;

char g[DIM][DIM],
	 dx[]={-1,0,1,0},
	 dy[]={0,1,0,-1};
unsigned int dist[Q];
int m,n,cap,src = 0,sink = 1,D,M,
	excess[Q],d[Q],V,cur[Q],parent[Q];
vector<pair<int,int> > ihmiset;
queue<int> q;
edge e[Q],*ee[Q];
set<int> s;
vector<int> adj[Q];

void add_arcs( int x, int y, int cap ) {
	int i,j,k;
	e[i = M].x = x, e[M].y = y, e[M].capacity = cap, e[M].flow = 0, ++M;
	e[j = M].x = y, e[M].y = x, e[M].capacity = 0,   e[M].flow = 0, ++M;
	e[i].back_edge = e+j, e[j].back_edge = e+i;
	s.insert(x), s.insert(y);
}

int Push( edge *e ) {
	int x = e->x,
		y = e->y,
		delta,pre,pos;
	if ( !is_active(x) )  return 0;
	if ( d[x] != d[y]+1 ) return 0;
	if ( e->capacity == e->flow )
		return 0;
	delta = min(e->capacity-e->flow,excess[x]);
	assert( delta > 0 );
	pre = is_active(y);
	excess[x]-=delta, excess[y]+=delta;
	e->flow += delta, e->back_edge->flow -= delta;
	pos = is_active(y);
	if ( !pre && pos )
		q.push(y);
	return 1;
}

int Relabel( int x ) {
	int w = +oo,i,j,y;
	if ( !is_active(x) )
		return 0;
	for ( i = 0; i < (int)adj[x].size(); ++i ) {
		y = e[j = adj[x][i]].y;
		if ( e[j].capacity > e[j].flow ) {
			assert( d[x] <= d[y] );
			w = min(w,1+d[y]);
		}
	}
	d[x] = (w == +oo?3*V:w);
	return 1;
}

void discharge( int x ) {
	if ( !Push(e+adj[x][cur[x]]) )
		if ( ((++cur[x]),(cur[x]%=adj[x].size())) == 0 )
			Relabel(x);
}

int retrace( int x, int df ) {
	if ( x != src )
		return retrace(parent[x],min(df,ee[x]->capacity-ee[x]->flow));
	return df;
}

void update( int x, int df ) {
	if ( x != src ) {
		ee[x]->flow += df, ee[x]->back_edge->flow -= df;
		update(parent[x],df);
	}
}

int bfs() {
	int i,x,y,k;
	memset(dist,0xff,sizeof(dist));
	for ( parent[src] = -1, dist[src] = 0, q.push(src); !q.empty();) {
		x = q.front(), q.pop();
		for ( i = 0; i < (int)adj[x].size(); ++i ) {
			k=adj[x][i],y=e[k].y;
			if ( e[k].capacity == e[k].flow )
				continue ;
			if ( dist[y] > dist[x]+1 )
				dist[y] = dist[x]+1, q.push(y), parent[y] = x, ee[y] = e+k;
		}
	}
	return dist[sink]<0xfffffffful;
}

int main() {
	int i,j,k,ni,nj,l,t,x,y;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	while ( 3 == scanf("%d %d %d",&m,&n,&cap) ) {
		for ( i = 0; i < m; scanf("%s",g[i++]) );
		ihmiset.clear(), s.clear(), M = 0;
		for ( i = 0; i < m; ++i )
			for ( j = 0; j < n; ++j )
				if ( g[i][j] == '*' )
					ihmiset.push_back(make_pair(i,j));
		D = ihmiset.size();
		if ( !D ) {
			puts("0");
			continue ;
		}
		for ( l = 0; l < (int)ihmiset.size(); ++l ) {
			i = ihmiset[l].first, j = ihmiset[l].second;
			add_arcs(src,IN(v(i,j)),1);
		}
		for ( i = 0; i < m; ++i )
			for ( j = 0; j < n; ++j )  
				if ( g[i][j] != '~' ) {
					if ( g[i][j] == '*'||g[i][j] == '.' )
						add_arcs(IN(v(i,j)),OUT(v(i,j)),1);
					else 
						add_arcs(IN(v(i,j)),OUT(v(i,j)),+oo);
					for ( l = 0; l < 4; ++l ) {
						ni = i+dx[l], nj = j+dy[l];
						if ( !vc(ni,nj) )
							continue ;
						if ( g[ni][nj] == '~'||g[ni][nj] == '*' )
							continue ;
						add_arcs(OUT(v(i,j)),IN(v(ni,nj)),+oo);
					}
				}
		for ( i = 0; i < m; ++i )
			for ( j = 0; j < n; ++j )
				if ( g[i][j] == '#' ) 
					add_arcs(OUT(v(i,j)),sink,cap);
		for ( set<int>::iterator it = s.begin(); it != s.end(); adj[*it++].clear() );
		for ( i = 0; i < M; adj[e[i].x].push_back(i), ++i );
		V = s.size();
		for ( set<int>::iterator it = s.begin(); it != s.end(); ++it )
			d[*it]=0, excess[*it]=0;
		/*
		for ( d[src] = V, i = 0; i < (int)adj[src].size(); ++i ) {
			x = e[k = adj[src][i]].y;
			excess[x] += e[k].capacity, e[k].flow = e[k].capacity;
			e[k].back_edge->flow -= e[k].capacity;
		}
		for ( set<int>::iterator it = s.begin(); it != s.end(); ++it ) {
			cur[*it]=0;
			if ( is_active(*it) )
				q.push(*it);
		}
		while ( !q.empty() ) {
			for ( x = q.front(), q.pop(), k = d[x]; excess[x] > 0 && k == d[x]; discharge(x) );
			if ( is_active(x) ) q.push(x);
		}
		printf("%d\n",excess[sink]);
		*/
		for (;bfs();update(sink,retrace(sink,D)));
		for ( k = 0, i = 0; i < M; ++i )
			if ( e[i].y == sink )
				k += e[i].flow;
		printf("%d\n",k);
	}
	return 0;
}

