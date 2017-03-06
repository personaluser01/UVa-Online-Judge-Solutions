/*
 * 11167. Monkeys in the Emei Mountain
 */
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <cstring>
#include <vector>
#include <algorithm>
#include <map>
#include <queue>
#define N 0x80
#define T 50001
#define Q (N+T)
#define oo 0xfffffffful
using namespace std;
#define is_active(x) (src!=x&&sink!=x&&excess[x]>0&&d[x]<5*V)

typedef struct edge{struct edge *back_edge;int x,y,capacity,flow;}edge;
int m,n,Low,High,src,sink,beg[N],ed[N],must_drink[N],v[T],V,E,d[Q],cur[Q],iv[Q],excess[Q];
edge e[5000001+T+N];
queue<int> q;
vector<int> adj[Q],lst[T];
vector<pair<int,int> > vec[N];
void add_arcs( int x, int y, int c ) {
	int i,j;
	e[i = E++].x = x, e[i].y = y, e[i].capacity = c, e[i].flow = 0;
	e[j = E++].x = y, e[j].y = x, e[j].capacity = 0, e[j].flow = 0;
	(e[i].back_edge = e+j)->back_edge = e+i;
}

int Push( int x ) {
	int i = adj[x][cur[x]],
		y = e[i].y,
		pre,pos,delta;
	if( !is_active(x) )
		return 0;
	if ( e[i].flow == e[i].capacity )
		return 0;
	if ( d[x] != d[y]+1 )
		return 0;
	pre = is_active(y);
	delta = min(excess[x],e[i].capacity-e[i].flow);
	excess[x] -= delta, e[i].flow += delta, e[i].back_edge->flow -= delta, excess[y] += delta;
	pos = is_active(y);
	if ( !pre && pos ) q.push(y);
	return 1;
}

int Relabel( int x ) {
	int i,k,y,w = 5*V;
	if ( !is_active(x) )
		return 0;
	for ( i = 0; i < (int)adj[x].size(); ++i ) {
		k = adj[x][i], y = e[k].y;
		if ( e[k].capacity == e[k].flow )
			continue ;
		w = min(w,1+d[y]);
	}
	d[x] = w;
	return 1;
}

void push_relabel( int x ) {
	if ( !is_active(x) )
		return ;
	if ( !Push(x) )
		if ( ((++cur[x]),(cur[x] %= adj[x].size())) == 0 )
			Relabel(x);
}

edge *ee[Q];
int p[Q],seen[Q],yes;

int bfs() {
	int i,j,x,y;
	for (seen[src]=++yes,q.push(src);!q.empty();)
		for(x=q.front(),q.pop(),i=0;i<(int)adj[x].size();++i)
			if ( e[j = adj[x][i]].capacity > e[j = adj[x][i]].flow )
				if ( seen[y = e[j].y] != yes )
					seen[y]=yes,q.push(y),p[y]=x,ee[y]=e+j;
	// while(!q.empty()) q.pop();
	return seen[sink] == yes;
}

int retrace( int x, int df ) {
	return (x==src)?df:retrace(p[x],min(df,ee[x]->capacity-ee[x]->flow));
}
void update( int x, int df ) {
	if ( x != src )
		ee[x]->flow += df, ee[x]->back_edge->flow -= df, update(p[x],df);
}

int dfs( int x, int df ) {
	int i,y;
}

int main() {
	int i,j,k,l,t,cs = 0,x,y,Total;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for(;2 == scanf("%d %d",&n,&m) && printf("Case %d: ",++cs);) {
		Low = (1<<29), High = -(1<<29), Total = 0;
		for ( i = 0; i < T; ++i ) v[i] = -1;
		V = 1 + n;
		for ( i = 0; i < n; ++i ) {
			scanf("%d %d %d",&l,&k,&t), Total += l;
			Low = min(Low,k);
			High = max(High,t);
			beg[i+1] = k, ed[i+1] = t, must_drink[i+1] = l;
			for ( k = beg[i+1]; k <= ed[i+1]-1; ++k )
				if ( v[k] == -1 )
					iv[v[k] = V++] = k;
		}
		for ( sink = V++, E = 0, src = 0, i = 1; i <= n; ++i ) {
			add_arcs(src,i,must_drink[i]);
			for ( k = beg[i]; k <= ed[i]-1; ++k )
				add_arcs(i,v[k],1);
		}
		for ( k = Low; k <= High; ++k )
			if ( v[k] != -1 )
				add_arcs(v[k],sink,m);
		for ( k = 0; k < V; ++k ) d[k] = excess[k] = 0;
		d[src] = V;
		for ( i = 0; i < V; ++i ) adj[i].clear(), cur[i] = 0;
		for ( i = 0; i < E; ++i ) adj[e[i].x].push_back(i);
		/*
		for ( i = 0; i < (int)adj[src].size(); ++i ) {
			j = adj[src][i], y = e[j].y;
			excess[y] += e[j].capacity, e[j].flow += e[j].capacity;
			e[j].back_edge->flow -= e[j].capacity;
		}
		for ( x = 0; x < V; ++x )
			if ( is_active(x) ) q.push(x);
		while (!q.empty())  {
			for ( x = q.front(), q.pop(), k = d[x]; k == d[x] && excess[x] > 0; push_relabel(x) );
			if ( is_active(x) ) q.push(x);
		}
		if ( excess[sink] != Total ) {
			puts("No");
			continue ;
		}
		*/
		for(;bfs();update(sink,retrace(sink,(1<<29))) );
		for ( k = 0, i = 0; i < E; ++i )
			if ( e[i].y == sink )
				k += e[i].flow;
		if ( k < Total ) {
			puts("No");
			continue ;
		}
		puts("Yes");
		for ( i = Low; i <= High; ++i ) lst[i].clear();
		for ( i = 0; i < E; ++i ) {
			x = e[i].x, y = e[i].y;
			if ( e[i].flow <= 0 )
				continue ;
			if ( 1 <= x && x <= n )
				if ( 1+n <= y && y != sink && y != src ) 
					lst[iv[y]].push_back(x);
		}
		for ( i = 1; i <= n; ++i ) vec[i].clear();
		for ( k = Low; k <= High; ++k )
			for ( i = 0; i < (int)lst[k].size(); ++i ) {
				x = lst[k][i];
				if ( vec[x].size() == 0||vec[x][vec[x].size()-1].second < k )
					vec[x].push_back(make_pair(k,k+1));
				else vec[x][vec[x].size()-1].second = k+1;
			}
		for ( x = 1; x <= n; ++x ) {
			printf("%d",(int)vec[x].size());
			for ( i = 0; i < (int)vec[x].size(); ++i )
				printf(" (%d,%d)",vec[x][i].first,vec[x][i].second);
			putchar('\n');
		}
	}
	return 0;
}

