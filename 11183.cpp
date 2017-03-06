/*
 * 11183. Teen Girl Squads
 * TOPIC: mincost arborescence, greedy, graph contraction
 */
#include <cassert>
#include <cstdio>
#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <cmath>
#include <vector>
#include <set>
#include <queue>
#include <stack>
#define N 0x400
#define oo (1L<<29)
using namespace std;

int ts,cs,n,m;
vector<pair<int,int> > adj[N];

int edmonds( vector<pair<int,int> > adj[], int n, int m, int shift ) {
	int *cheapest_edge = new int[n],
		i,j,k,l,t,cost = 0,x,y,
		*p = new int[n];
	vector<pair<int,int> > nadj[n];

	// printf("%*d %d\n",shift,n,m);

	if ( m <= 1 ) { delete cheapest_edge; delete p; return 0; }

	bool has_cycle = false;

	for ( i = 0; i < n; cheapest_edge[i++] = +oo );

	for ( i = 0; i < n; ++i ) 
		for ( l = 0; l < (int)adj[i].size(); ++l ) 
			j = adj[i][l].first, k = adj[i][l].second, cheapest_edge[j] = min(cheapest_edge[j],k);

	stack<int> st;
	set<int> s;
	bool *seen = new bool[n];

	for ( i = 0; i < n; seen[i++] = false );

	for ( s.clear(), seen[0] = true, s.insert(0), st.push(0); !st.empty(); ) 
		for ( i = st.top(), st.pop(), s.erase(i), l = 0; l < (int)adj[i].size(); ++l ) {
			j = adj[i][l].first, k = adj[i][l].second;
			if ( cheapest_edge[j] != k ) continue ;
			if ( seen[j] ) {
				if ( s.find(j) != s.end() ) { if ( !has_cycle ) has_cycle = true, x = i, y = j; }
			}
			else seen[j]=true,p[j]=i,cost+=k,st.push(j),s.insert(j);
		}


	for ( k = 0, i = 0; i < n; ++i )
		if ( seen[i] ) ++k;

	if ( k < m ) return +oo;
	assert( k == m );

	if ( !has_cycle ) { delete seen; delete cheapest_edge; delete p; return cost; }

	vector<int> v;

	for ( v.clear(), i = x, j = y, v.push_back(j); i != j; v.push_back(i), i = p[i] );

	for ( cost = 0, l = 0; l < (int)v.size(); ++l )
		if ( v[l] != y ) cost += cheapest_edge[v[l]];

	for ( s.clear(), i = 0; i < (int)v.size(); s.insert(v[i++]) );

	for ( i = 0; i < n; nadj[i++].clear() );

	for ( t = n+1, l = 0; l < (int)v.size(); t = min(t,v[l++]) );

	for ( i = 0; i < n; ++i )
		if ( s.find(i) != s.end() ) {
			for ( l = 0; l < (int)adj[i].size(); ++l ) {
				j = adj[i][l].first, k = adj[i][l].second;
				if ( s.find(j) == s.end() )
					nadj[t].push_back(make_pair(j,k-cheapest_edge[j]));
			}
		}
		else {
			for ( l = 0; l < (int)adj[i].size(); ++l ) {
				j = adj[i][l].first, k = adj[i][l].second;
				if ( s.find(j) == s.end() )
					nadj[i].push_back(make_pair(j,k-cheapest_edge[j]));
				else nadj[i].push_back(make_pair(t,k-cheapest_edge[j]));
			}
		}

	delete seen; delete cheapest_edge; delete p;

	k = edmonds(nadj,n,n+1-v.size(),shift+4);

	if ( k == +oo ) return +oo;

	return k+cost;

}

int main() {
	int i,j,k,l,w;
#ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
#endif
	for ( scanf("%d",&ts); ts-- && 2 == scanf("%d %d",&n,&m); ) {
		printf("Case #%d: ",++cs);
		for ( i = 0; i < n; adj[i++].clear() );
		for ( l = 0; l < m; ++l ) {
			scanf("%d %d %d",&i,&j,&k);
			if ( j != 0 ) 
				adj[i].push_back(make_pair(j,k));
		}
		w = edmonds(adj,n,n,0);
		if ( w == +oo )
			puts("Possums!");
		else printf("%d\n",w);
	}
    return 0;
}

