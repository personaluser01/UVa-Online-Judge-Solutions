/*
 * 11167. Monkeys in the Emei Mountain
 */
#include <algorithm>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <queue>
#include <set>
#define N 0x80
#define Q (N*N*2)
using namespace std;
#define T 50100
#define is_active(x) (x!=src&&x!=sink&&d[x]<4*V&&excess[x]>0)
#include <cassert>

int m,n,ts,a[N],b[N],sa[N],sb[N],
	litres[N],src,sink,
	V,E,L,cur[Q],
	vname[T],iname[Q],
	excess[Q],d[Q],
	A[Q],B[Q];

typedef struct edge {
	struct edge *back_edge;
	int x,y,capacity,flow;
}edge;
edge e[Q];
set<int> s;
queue<int> q;
vector<int> adj[Q],lst[T];
vector<pair<int,int> > vec[N],z[T];

void add_arcs( int x, int y, int c ) {
	int i,j;
	if ( c <= 0 ) {
		printf("Trying to add negative capacity from %d to %d, %d\n",x,y,c);
		assert(0);
	}
	e[i = E++].x = x, e[i].y = y, e[i].capacity = c, e[i].flow = 0;
	e[j = E++].x = y, e[j].y = x, e[j].capacity = 0, e[j].flow = 0;
	(e[i].back_edge = e+j)->back_edge = e+i;
}

int Push( int x ) {
	int i = adj[x][cur[x]],
		y = e[i].y,
		delta,pre,pos;
	if ( !is_active(x) ) return 0;
	if ( d[x] != d[y]+1 )
		return 0;
	if ( e[i].capacity == e[i].flow )
		return 0;
	delta = min(excess[x],e[i].capacity-e[i].flow);
	pre = is_active(y);
	excess[x] -= delta, excess[y] += delta;
	e[i].flow += delta, e[i].back_edge->flow -= delta;
	pos = is_active(y);
	if ( !pre && pos ) q.push(y);
	return 1;
}

int Relabel( int x ) {
	int i,j;
	if ( !is_active(x) )
		return 0;
	for ( d[x] = 4*V, i = 0; i < (int)adj[x].size(); ++i )
		if ( e[j = adj[x][i]].capacity > e[j = adj[x][i]].flow )
			d[x] = min(d[x],1+d[e[j].y]);
	return 1;
}

void push_relabel( int x ) {
	if ( !Push(x) )
		if ( ((++cur[x]),(cur[x]%=adj[x].size())) == 0 )
			Relabel(x);
}

int parent[Q],seen[Q],yes,Cnt[T];
edge *ee[Q];
int retrace( int x, int df ) {
	return (x==src)?df:retrace(parent[x],min(df,ee[x]->capacity-ee[x]->flow));
}
void update( int x, int df ) {
	if ( x != src )
		update(parent[x],df), ee[x]->flow += df, ee[x]->back_edge->flow -= df;
}
int bfs() {
	int i,j,x,y;
	for (q.push(src),seen[src]=++yes;!q.empty()&&seen[sink]!=yes;)
		for (x=q.front(),q.pop(),i=0;i<(int)adj[x].size();++i)
			if ( e[j = adj[x][i]].capacity > e[j = adj[x][i]].flow )
				if ( seen[y = e[j].y] != yes )
					seen[y] = yes, parent[y] = x, q.push(y), ee[y] = e+j;
	while(!q.empty())q.pop();
	return seen[sink] == yes;
}

int outflow( int x ) {
	int k = 0,i;
	for ( i = 0; i < E; ++i )
		if ( e[i].x == x )
			k += e[i].flow;
	return k;
}

int inflow( int x ) {
	int k = 0,i;
	for ( i = 0; i < E; ++i )
		if ( e[i].y == x )
			k += e[i].flow;
	return k;
}

int main() {
	int i,j,k,x,y,Total,low,high,l,right,left;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for (;2 == scanf("%d %d",&n,&m) && n > 0 && printf("Case %d: ",++ts);) {
		low = (1<<29), high = -(1<<29);
		src = 0, V = n+1, E = 0, s.clear(), L = 0, Total = 0;
		for ( i = 1; i <= n; ++i ) {
			scanf("%d %d %d",litres+i,a+i,b+i);
			low = min(a[i],low), high = max(high,b[i]);
			Total += litres[i];
			if ( s.find(a[i]) == s.end() )
				s.insert(a[i]);
			if ( s.find(b[i]) == s.end() )
				s.insert(b[i]);
			if ( litres[i] ) add_arcs(src,i,litres[i]);
		}
		for ( set<int>::iterator it = s.begin(); it != s.end(); iname[vname[*it] = ++L] = *it, ++it );
		for ( i = 1; i <= n; ++i ) {
			sa[i] = vname[a[i]], sb[i] = vname[b[i]];
			for ( k = sa[i]; k < sb[i]; ++k )
				add_arcs(i,n+k,(iname[k+1]-iname[k]));
		}
		sink = L+n, V = L+n+1;
		for ( k = 1; k < L; ++k )
			add_arcs(k+n,sink,m*(iname[k+1]-iname[k]));
		for (x=0;x<V;++x)d[x]=excess[x]=0,cur[x]=0,adj[x].clear();
		for ( i = 0; i < E; ++i ) adj[e[i].x].push_back(i);
#if 1
		d[src] = V;
		for ( i = 0; i < (int)adj[src].size(); ++i ) {
			k = e[j = adj[src][i]].y;
			e[j].flow += e[j].capacity, e[j].back_edge->flow -= e[j].capacity;
			excess[k] += e[j].flow;
		}
		for ( i = 0; i < V; ++i )
			if ( is_active(i) )
				q.push(i);
		while ( !q.empty() ) {
			for ( x = q.front(), q.pop(), k = d[x]; k == d[x] && excess[x] > 0; push_relabel(x) );
			if ( is_active(x) ) q.push(x);
		}
		if ( excess[sink] != Total ) {
			puts("No");
			continue ;
		}
#else
		for ( ;bfs();update(sink,retrace(sink,(1<<29))) );
		if ( inflow(sink) != Total ) {
			puts("No");
			continue ;
		}
#endif
		puts("Yes");
		for ( k = low; k <= high; ++k ) lst[k].clear(),Cnt[k]=0;
		for ( y = 1; y <= L; ++y ) z[y].clear();
		for ( i = 0; i < E; ++i ) {
			if ( (k = e[i].flow) <= 0 )
				continue ;
			x = e[i].x, y = e[i].y;
			if ( !(1 <= x && x <= n) )
				continue ;
			if ( !(1+n <= y && y <= (L-1)+n) )
				continue ;
			z[y-n].push_back(make_pair(x,k));
		}
		for ( y = 1; y < L; ++y ) {
			for ( k = 0, i = 0; i < (int)z[y].size(); ++i )
				k += z[y][i].second;
			assert( k <= (iname[y+1]-iname[y])*m );
		}
		for ( y = 1; y < L; ++y ) {
			for ( l = iname[y]; l < iname[y+1]; ++l ) {
				assert( !lst[l].size() );
				assert( !Cnt[l] );
			}
			for ( k = 0, i = 0; i < (int)z[y].size(); ++i ) {
				k += z[y][i].second;
				assert( z[y][i].second <= (iname[y+1]-iname[y]) );
			}
			assert( k <= (iname[y+1]-iname[y])*m );
			for ( i = 0; i < (int)z[y].size(); ++i ) {
				k = z[y][i].second; x = z[y][i].first;
				for ( l = iname[y]; l < iname[y+1] && k > 0; ++l )
					if ( Cnt[l] < m ) 
						lst[l].push_back(x), --k, ++Cnt[l];
				assert( k <= 0 );
			}
		}
		for ( j = low; j <= high; ++j )
			if ( lst[j].size() )
				sort(lst[j].begin(),lst[j].end());
		for ( i = 1; i <= n; ++i ) vec[i].clear();
		for ( i = low; i <= high; ++i )
			for ( l = 0; l < (int)lst[i].size(); ++l ) {
				x = lst[i][l];
				vec[x].push_back(make_pair(i,i+1));
			}
		for ( m = 0, i = 1; i <= n; ++i ) {
			if ( !litres[i] ) {
				puts("0");
				continue ;
			}
			assert( vec[i].size() > 0 );
			sort(vec[i].begin(),vec[i].end());
			left = vec[i][0].first, right = vec[i][0].second;
			for ( m = 0, j = 1; j < (int)vec[i].size(); ++j ) {
				if ( vec[i][j].first > right )
					A[m] = left, B[m++] = right, left = vec[i][j].first;
				right = vec[i][j].second;
			}
			A[m] = left, B[m++] = right;
			for ( printf("%d",m), j = 0; j < m; ++j )
				printf(" (%d,%d)",A[j],B[j]);
			putchar('\n');
		}
	}
	return 0;
}

