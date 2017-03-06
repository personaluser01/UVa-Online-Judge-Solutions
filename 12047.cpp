/*
 * status: Accepted
 * TOPIC: dijkstra, binary search, state
 */
#include <cassert>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <iostream>
#include <queue>
#include <set>
#define N (1 << 14)
using namespace std;
#define W (1000001)

vector<pair<int,int> > adj[N];
int n,m,limit,seen[N],yes,d[N];
set<pair<int,int> > s;
queue<int> q;

bool reachable( int src, int dst, int L ) {
	int i,j,k,x,y,l,t,nt,u,v;
	s.clear(), s.insert(make_pair(d[src<<1]=0,src<<1)), seen[src<<1] = ++yes;
	for (;!s.empty();) {
		set<pair<int,int> >::iterator it = s.begin();
		u = it->second, t = (u&1), x = (u>>1), s.erase(*it);
		for ( int i = 0; i < (int)adj[x].size(); ++i ) {
			if ( d[u]+adj[x][i].second > limit ) continue ;
			nt = t, y = adj[x][i].first;
			if ( adj[x][i].second >= L ) nt = 1;
			v = nt|(y<<1);
			if ( seen[v] != yes || d[v] > d[u]+adj[x][i].second )
				seen[v] = yes, s.insert(make_pair(d[v] = d[u]+adj[x][i].second,v));
		}
	}
	return seen[1|(dst<<1)]==yes;
}

int main() {
	int i,j,k,ts,src,t,l,low,high,mid;
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	for ( scanf("%d",&ts); ts--; ) {
		scanf("%d %d %d %d %d",&n,&m,&src,&t,&limit);
		--src, --t;
		for ( i = 0; i < n; ++i ) adj[i].clear();
		for ( l = 0;  l < m; ++l ) {
			scanf("%d %d %d",&i,&j,&k), --i, --j;
			if ( k > limit ) continue ;
			adj[i].push_back(make_pair(j,k));
		}
		if ( !reachable(src,t,0) ) {
			puts("-1");
			continue ;
		}
		for ( low = 0, high = W; low+1 < high; ) {
			mid = (low+high)/2;
			if ( reachable(src,t,mid) )
				low = mid;
			else high = mid;
		}
		printf("%d\n",low);
	}
	return 0;
}

