/*
 * 12549. Sentry Robots
 * TOPIC: bipartite matching, maxflow
 * status: Accepted
 */
#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>
#include <set>
#define N 0x80
#define K (1<<21)
#define L(i) ((i)&((~(i))+1ULL))
#define MAXE (1<<20)
#define MAXN (1<<15)
using namespace std;

int m,n,pts,obst,mm,nn,E,V,to[MAXE],next[MAXE],last[MAXN],cap[MAXE],flow[MAXE],src,sink,
	seen[MAXN],yes,visited[MAXN],indeed,d[MAXN],q[MAXN],*head,*tail;
char **g;
set<pair<int,int> > s;
vector<pair<int,int> > p,o;

void add_arcs( int x, int y, int c ) {
	int i = E++, j = E++;
	to[i] = y, next[i] = last[x], last[x] = i, cap[i] = c, flow[i] = 0;
	to[j] = x, next[j] = last[y], last[y] = j, cap[j] = 0, flow[j] = 0;
}

int bfs() {
	int x,y,i;
	for ( head=tail=q,visited[sink]=++indeed,d[*tail++=sink]=0; head<tail; )
		for ( i=last[x=*head++]; i>=0; i=next[i] )
			if ( flow[i^1]<cap[i^1] && visited[y=to[i]]!=indeed ) 
				visited[*tail++=y]=indeed,d[y]=d[x]+1;
	return visited[src] == indeed;
}

int dfs( int x, int df ) {
	int dt,i,y;
	if ( x == sink ) return df;
	if ( seen[x] == yes ) return 0;
	for ( seen[x] = yes, i = last[x]; i >= 0; i = next[i] )
		if ( flow[i] < cap[i] && visited[y=to[i]] == indeed && d[y]+1 == d[x] ) {
			if ( dt = dfs(y,min(df,cap[i]-flow[i])) ) {
				flow[i] += dt, flow[i^1] -= dt;
				return dt;
			}
		}
	return 0;
}

int maxflow() {
	int t = 0,dt;
	for(;bfs();)
		for (;++yes && (dt=dfs(src,1<<29));t+=dt);
	return t;
}

struct comp {
	bool operator () ( const pair<pair<int,int>,bool> &a, const pair<pair<int,int>,bool> &b ) {
		return a.first.second < b.first.second || a.first.second == b.first.second && a.first.first < b.first.first;
	};
};

int main() {
	int i,j,k,cs,ts,x,y,currow,curcol;
	pair<pair<int,int>,bool>r;
	vector<pair<pair<int,int>,bool> > e,re,ce;
	bool flag;
#ifndef ONLINE_JUDGE
	freopen("12549.in","r",stdin);
#endif
	for ( scanf("%d",&ts); ts--; ) {
		scanf("%d %d %d",&m,&n,&pts);
		for ( s.clear(), i = 1; i <= m; ++i )
			for ( j = 1; j <= n; s.insert(make_pair(i,j++)) );
		for ( p.clear(); pts--; scanf("%d %d",&i,&j), s.erase(make_pair(i,j)), p.push_back(make_pair(i,j)) );
		for ( scanf("%d",&obst), o.clear(); obst--; scanf("%d %d",&i,&j), s.erase(make_pair(i,j)), o.push_back(make_pair(i,j)) );
		
		for ( e.clear(), i = 0; i < (int)o.size(); e.push_back(make_pair(o[i++],true)) );
		for ( i = 0; i < (int)p.size(); e.push_back(make_pair(p[i++],false)) );

		sort(e.begin(),e.end());
		for ( re.clear(), currow = 0, i = 0; i < (int)e.size(); i = j ) {
			for ( j = i; j < (int)e.size() && e[i].first.first == e[j].first.first; ++j );
			r = e[i], r.first.first = ++currow, re.push_back(r);
			for ( k = i+1; k < j; ++k, re.push_back(r)	)
				if ( r.second == e[k].second ) 
					r = e[k], r.first.first = currow;
				else r = e[k], r.first.first = ++currow;
		}
		sort(re.begin(),re.end(),comp());
		for ( ce.clear(), curcol = 0, i = 0; i < (int)re.size(); i = j ) {
			for ( j = i; j < (int)re.size() && re[i].first.second == re[j].first.second; ++j );
			r = re[i], r.first.second = ++curcol, ce.push_back(r);
			for ( k = i+1; k < j; ++k, ce.push_back(r) )
				if ( r.second == re[k].second )
					r = re[k], r.first.second = curcol;
				else r = re[k], r.first.second = ++curcol;
		}
		sort(ce.begin(),ce.end());
		m = currow, n = curcol;

		src = 0, sink = 1+m+n, V = sink+1;
		for ( E = 0, i = 1; i <= m; last[i++] = -1 );
		for ( j = 1; j <= n; last[j+m] = -1, ++j );
		last[src] = last[sink] = -1;
		g = new char *[m+1];
		for ( i = 0; i <= m; ++i )
			g[i] = new char[n+1];
		for ( i = 0; i <= m; ++i )
			for ( j = 0; j <= n; ++j )
				g[i][j] = ' ';
		for ( k = 0; k < (int)ce.size(); ++k ) {
			i = ce[k].first.first, j = ce[k].first.second, flag = ce[k].second;
			g[i][j] = flag?'#':'*';
		}
		for ( i = 1; i <= m; ++i )
			for ( j = 1; j <= n; ++j )
				if ( g[i][j] == '*' )
					add_arcs(i,j+m,1);
		for ( i = 1; i <= m; ++i )
			add_arcs(src,i,1);
		for ( j = 1; j <= n; ++j )
			add_arcs(j+m,sink,1);
		printf("%d\n",maxflow());
	}
	return 0;
}

