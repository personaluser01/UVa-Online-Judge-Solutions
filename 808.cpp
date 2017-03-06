/*
 * 808. Bee Breeding
 * TOPIC: bfs, hexagonal grids, nice trick
 * status: Accepted
 */
#include <algorithm>
#include <cmath>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <map>
#include <vector>
// #define pi (2*acos(0.00))
#define pi (1.00)
#include <queue>
#include <set>
#define N (10100)
#define oo 0xfffffffful
using namespace std;
typedef long long i64;

vector<int> adj[N];
queue<pair<i64,i64> > q;
queue<int> s;
int n,seen[N],yes;
unsigned int d[N];

map<pair<i64,i64>,int> m;

pair<i64,i64> operator+( const pair<i64,i64> &a, const pair<i64,i64> &b ) {
	pair<i64,i64> res = make_pair(a.first+b.first,a.second+b.second);
	return res;
}

unsigned int 
dijkstra( const int src, const int dst ) {
	int x,y,i;
	for(;!s.empty();s.pop());
	for ( d[dst] = +oo, seen[src]=++yes, d[src]=0, s.push(src); d[dst] == +oo && !s.empty(); ) 
		for ( x = s.front(), s.pop(), i = 0; i < (int)adj[x].size(); ++i ) 
			if ( seen[y=adj[x][i]] != yes )
				seen[y] = yes, d[y] = d[x]+1, s.push(y);
			else { assert( d[y] <= d[x]+1 ); }
	return d[dst];
}

pair<i64,i64> w[6];
map<int,pair<i64,i64> > T;

int main() {
	int i,j,k,prev;
	pair<i64,i64> e;
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	w[0] = make_pair(0,-1);
	w[1] = make_pair(-1,-1);
	w[2] = make_pair(-1,0);
	w[3] = make_pair(0,1);
	w[4] = make_pair(1,1);
	w[5] = make_pair(1,0);
	for ( n=0, prev=-1, m.clear(), m[e=make_pair(0,0)]=n++, q.push(e); !q.empty() && n < N; prev=k ) {
		pair<i64,i64> r=q.front(),t,p,v;
		assert( m.find(r) != m.end() );
		// assert( m[r] == prev+1 );
		q.pop(), k = prev+1;
		if ( k == 0 ) {
			for ( i = 0; i < 6; ++i )
				m[t=r+w[i]] = n++, q.push(t);
			continue ;
		}
		for ( i = 0; !(m.find(r+w[i]) != m.end() && m.find(r+w[(i+5)%6]) == m.end()); ++i, i %= 6 );
		for ( ;m.find(r+w[i]) != m.end(); ++i, i %= 6 );
		for ( ;m.find(t=r+w[i])==m.end() && n < N; ++i, i %= 6 )
			m[t] = n++, q.push(t);
	}
	for ( map<pair<i64,i64>,int >::iterator it = m.begin(); it != m.end(); T[it->second] = it->first, ++it );
	for ( map<int,pair<i64,i64> >::iterator it = T.begin(); it != T.end(); ++it ) {
		k = it->first;
		assert( adj[k].size() == 0 );
		pair<i64,i64> r = it->second;
		// printf("%lld %lld\n",r.first,r.second);
		for ( i = 0; i < 6; ++i ) {
			pair<i64,i64> t = r+w[i];
			if ( m.find(t) == m.end() ) continue ;
			j = m[t];
			adj[k].push_back(j);
			// adj[j].push_back(k);
		}
		/*
		if ( adj[k].size() != 6 )
			printf("This %d %lu\n",k+1,adj[k].size());
		*/
	}
	/*
	for ( i = 0; i < adj[k-1].size(); ++i )
		printf("%d %d\n",k,adj[k-1][i]+1);
		*/
	// for (;2 == scanf("%d %d",&i,&j) && (i||j); printf("The distance between cells %d and %d is %u.\n",i,j,dijkstra(min(i-1,j-1),max(i-1,j-1))) );
	for (;2 == scanf("%d %d",&i,&j) && (i||j); printf("The distance between cells %d and %d is %u.\n",i,j,dijkstra(i-1,j-1)) );
	return 0;
}


