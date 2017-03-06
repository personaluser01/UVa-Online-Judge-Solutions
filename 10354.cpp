/*
 * 10354. Avoiding your boss
 * TOPIC: Dijkstra, sssp, dp, graphs
 * status: Accepted
 */
#include <cassert>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <set>
#include <vector>
#define N 0x80
#define M (1<<16)
enum { TO, FROM };
using namespace std;

int n,m,last[N],next[M],to[M],w[M],E,V,d[2][N],seen[2][N],yes[2],
	boss,office,home,market,danger[N],indeed;
set<pair<int,int> > s;

void add_arcs( int x, int y, int k ) {
	int i = E++, j = E++;
	to[i] = y, w[i] = k, next[i] = last[x], last[x] = i;
	to[j] = x, w[j] = k, next[j] = last[y], last[y] = j;
}

void dijkstra( const int t, int src ) {
	int i,x,y;
	for ( seen[t][src] = ++yes[t], d[t][src] = 0, s.insert(make_pair(0,src)); !s.empty(); ) {
		set<pair<int,int> >::iterator it = s.begin(); 
		x = it->second, s.erase(*it);
		for ( i = last[x]; i >= 0; i = next[i] ) {
			if ( danger[y=to[i]] == indeed ) continue ;
			if ( seen[t][y] != yes[t] ) {
				seen[t][y] = yes[t], d[t][y] = d[t][x]+w[i];
				s.insert(make_pair(d[t][y],y));
			}
			else if ( d[t][y] > d[t][x]+w[i] ) 
				s.insert(make_pair(d[t][y]=d[t][x]+w[i],y));
		}
	}
}

int main() {
	int i,j,k,l;
	bool vulnerable;
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	for ( ;6 == scanf("%d %d %d %d %d %d",&n,&m,&boss,&office,&home,&market) && ++indeed; ) {
		--office, --boss, --home, --market;
		vulnerable = (market==home);
		for ( i = 0; i < n; last[i++] = -1 );
		for ( E = 0, l = 0; l < m; ++l ) 
			scanf("%d %d %d",&i,&j,&k), add_arcs(--i,--j,k);
		if ( home == boss ) {
			puts("MISSION IMPOSSIBLE.");
			continue ;
		}
		for ( dijkstra(TO,boss), dijkstra(FROM,office), i = 0; i < n && seen[TO][office] == yes[TO]; ++i )
			if ( seen[TO][i] == yes[TO] && seen[FROM][i] == yes[FROM] )
				if ( d[TO][i]+d[FROM][i] == d[TO][office] ) 
					danger[i] = indeed;
		if ( seen[TO][office] == yes[TO] && home == office ) {
			puts("MISSION IMPOSSIBLE.");
			continue ;
		}
		if ( danger[home] == indeed )  {
			puts("MISSION IMPOSSIBLE.");
			continue ;
		}
		dijkstra(TO,home);
		if ( seen[TO][market] == yes[TO] )
			printf("%d\n",d[TO][market]);
		else puts("MISSION IMPOSSIBLE.");
	}
	return 0;
}

