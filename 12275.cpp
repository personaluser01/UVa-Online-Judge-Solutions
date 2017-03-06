/*
 * 12275. Sensor Network
 * TOPIC: mst, dfs, cycles
 * status: Accepted
 */
#include <algorithm>
#include <iostream>
#include <cassert>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <vector>
#include <set>
#define N 0x200
#define M (N*N)
typedef long long i64;
using namespace std;

struct edge {
	int x,y;
	i64 w;
	edge() {};
	edge( int xx, int yy, int ww ) { x = xx, y = yy, w = ww; };
	int other( int i ) const {
		if ( x == i ) return y;
		return x;
	};
};

bool operator < ( const edge &a, const edge &b ) {
	if ( a.w == b.w ) {
		if ( a.x == b.x )
			return a.y < b.y;
		return a.x < b.x;
	}
	return a.w < b.w;
}

int n,m,seen[N],yes;
edge e[M];
set<int> adj[N];

bool visit( int src, int x, int len, int &lightest, i64 &w ) {
	if ( src == x && len > 0 )
		return true ;
	if ( seen[x] == yes ) return false ;
	seen[x] = yes;
	for ( set<int>::iterator it = adj[x].begin(); it != adj[x].end(); ++it ) {
		int y = e[*it].other(x);
		assert( x != y );
		if ( seen[y] != yes && visit(src,y,len+1,lightest,w) ) {
			if ( e[*it].w < w ) w = e[lightest = *it].w;
			return true ;
		}
	}
	return false ;
}

int main() {
	int i,j,k,l,edges,lightest;
	i64 weight,mn,mx,ans;
#ifndef ONLINE_JUDGE
	freopen("12275.in","r",stdin);
	freopen("out01.txt","w",stdout);
#endif
	for ( ;1 == scanf("%d",&n) && n > 0 && 1 == scanf("%d",&m); printf("%lld\n",ans) ) {
		for ( i = 0; i < n; adj[i++].clear() );
		for ( l = 0; l < m; ++l ) 
			scanf("%d %d %lld",&i,&j,&weight), e[l] = edge(min(i,j),max(i,j),weight);
		for ( ans=+(1LL<<61),edges=0,sort(e,e+m),l=0; l<m; ++l ) {
			i=e[l].x,j=e[l].y,weight=(1LL<<61);
			if ( ++yes && !visit(i,j,0,lightest,weight) ) {
	   			adj[i].insert(l), adj[j].insert(l);
				if ( ++edges == n-1 ) {
					mx = -(1LL<<61), mn = +(1LL<<61);
					for ( i = 0; i < n; ++i ) 
						for ( set<int>::iterator it = adj[i].begin(); it != adj[i].end(); ++it )
							mx = max(e[*it].w,mx), mn = min(e[*it].w,mn);
					ans = min(ans,mx-mn);
				}
				continue ;
			}
			if ( e[l].w > weight ) {
				assert( adj[e[lightest].x].count(lightest));
				assert( adj[e[lightest].y].count(lightest));
				adj[e[lightest].x].erase(lightest), adj[e[lightest].y].erase(lightest);
			   	adj[i].insert(l), adj[j].insert(l);
				assert( !adj[e[lightest].x].count(lightest));
				assert( !adj[e[lightest].y].count(lightest));
				if ( edges == n-1 ) {
					mx = -(1LL<<61), mn = +(1LL<<61);
					for ( i = 0; i < n; ++i ) 
						for ( set<int>::iterator it = adj[i].begin(); it != adj[i].end(); ++it )
							mx = max(e[*it].w,mx), mn = min(e[*it].w,mn);
					ans = min(ans,mx-mn);
				}
			}
		}
	}
	return 0;
}

