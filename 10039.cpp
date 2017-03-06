/*
 * 10039. Railroads
 */
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
using namespace std;
#define hrs first
#define mns second
#define oo 0xfffffffful
#define M(k) ((1UL << (k))-1UL)
#define Q (1 << 18)
#define enc(c,t) ((c)|((t)<<7))
#define T 2048
#define N 0x80

typedef pair<int,int> timestamp;
int n;

int value( timestamp &a ) {
	return (a.hrs)*60 + a.mns;
}

void print( timestamp &a ) {
	printf("%02d%02d\n",a.hrs,a.mns);
}

int diftime( timestamp &a, timestamp &b ) {
	int r;
	assert( a <= b );
	if ( a.hrs == b.hrs ) 
		return b.mns-a.mns;
	timestamp c = a;
	r = 60-c.mns, ++c.hrs;
	r += 60*(b.hrs-c.hrs) + b.mns;
	return r;
}

timestamp str2aika( char *s ) {
	timestamp a;
	a.hrs = 10*(s[0]-'0')+(s[1]-'0'), a.mns = 10*(s[2]-'0')+(s[3]-'0');
	return a;
}

int nx( timestamp *a ) {
	if ( (++a->mns) == 60 )
		a->mns = 0, ++a->hrs;
	if ( a->hrs == 24 )  {
		a->hrs = 0;
		return 0;
	}
	return 1;
}

int cs,ts;
string cname[N];
map<string,int> m;
vector<unsigned int> adj[Q];
set<pair<unsigned int,unsigned int> > s;
unsigned int d[Q];

int bfs( unsigned int src, int dst ) {
	int i,j,k,x,y,min_k = (1 << 29),nk;
	unsigned int u,v;

	for ( i = 0; i < n; ++i )
		for ( k = 0; k < T; ++k )
			d[enc(i,k)] = +oo;

	for ( s.clear(), d[src] = 0, s.insert(make_pair(0,src)); !s.empty(); ) {
		set<pair<unsigned int,unsigned int> >::iterator it = s.begin();
		u = it->second, s.erase(*it), x = (u&M(7)), k = (u>>7);
		if ( x == dst ) {
			min_k = min(min_k,k);
			continue ;
		}
		for ( i = 0; i < (int)adj[u].size(); ++i ) {
			v = adj[u][i], nk = (v>>7);
			if ( d[v] > d[u]+1)
				d[v] = d[u]+1, s.insert(make_pair(d[v],v));
		}
	}
	return min_k;
}

int main() {
	int i,j,k,trains,conns,l,
		src_city,dst,nk,x,y,
		min_so_far;
	char tmp[0x400];
	string city1,city2;
	unsigned int u,v;
	timestamp t,tm;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( scanf("%d",&ts); ts--; putchar('\n') ) {
		scanf("%d",&n), m.clear();
		for ( i = 0; i < n; ++i )
			for ( j = 0; j < T; ++j )
				adj[enc(i,j)].clear();
		for ( i = 0; i < n; ++i )
			scanf("%s",tmp), m[cname[i] = string(tmp)] = i;
		for ( scanf("%d",&trains), k = 0; k < trains; ++k ) 
			for ( u = +oo, scanf("%d",&conns), l = 0; l < conns; ++l, u = v ) {
				scanf("%s",tmp), t = str2aika(tmp);
				scanf("%s",tmp), j = m[string(tmp)];
				assert( 0 <= j && j < n );
				v = enc(j,value(t));
				if ( u < +oo ) 
					adj[u].push_back(v);
			}
		scanf("%s",tmp), t = str2aika(tmp);
		scanf("%s",tmp), src_city = m[string(tmp)], city1 = string(tmp);
		scanf("%s",tmp), dst = m[string(tmp)], city2 = string(tmp);

		int lim = 23*60+59;
		for ( i = 0; i < n; ++i )
			for ( u = enc(i,value(t)), k = value(t); (++k) < lim; u = v )
				v = enc(i,k), adj[u].push_back(v);

		for ( min_so_far = (1 << 29), k = value(t); k < T; ++k )
			if ( adj[u = enc(src_city,k)].size() > 1 ) {
				j = bfs(u,dst);
				if ( j <= min_so_far )
					min_so_far = j, nk = k;
			}
		printf("Scenario %d\n",++cs);
		if ( min_so_far == (1 << 29) ) {
			puts("No connection");
			continue ;
		}
		printf("Departure %02d%02d %s\n",nk/60,nk%60,city1.c_str());
		printf("Arrival   %02d%02d %s\n",min_so_far/60,min_so_far%60,city2.c_str());
	}
	return 0;
}

