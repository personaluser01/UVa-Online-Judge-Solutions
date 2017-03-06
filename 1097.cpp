/*
 * 1097. Rain
 * TOPIC: dijkstra
 * status:
 */
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <map>
#include <iostream>
#define SH 6
#define BIT(k) (1ULL<<(k))
#define MASK(k) (BIT(k)-1ULL)
#define N (1<<12)
#define L(k) ((k)&(~(k)+1ULL))
#define MAXV BIT(21)
#define MAXE BIT(21)
using namespace std;
typedef long long i64;
typedef unsigned long long u64;

int m,n,id[256],vx[N],deg[MAXV],adj[MAXV][3],last[MAXV],next[MAXE],to[MAXE],V,E,mp[1<<12];
map<u64,int> region_name;
char which[BIT(21)];
pair<i64,i64> vv[N];
i64 h[N],height[MAXE];
u64 a[N][N>>6],r[MAXV];

int who( u64 u ) {
	if ( u >= BIT(60) )
		return 60+which[u>>60];
	if ( u >= BIT(40) )
		return 40+which[u>>40];
	if ( u >= BIT(20) )
		return 20+which[u>>20];
	return which[u];
};

u64 make_triple( u64 x, u64 y, u64 z ) {
	return min(x,min(y,z))|((x+y+z-min(x,min(y,z))-max(x,max(y,z)))<<12)|(max(x,max(y,z))<<24);
};

void add_arcs( int x, int y, i64 cost ) {
	int i = E++, j = E++;
	to[i] = x, next[i] = last[x], last[x] = i, height[i] = cost;
	to[j] = y, next[j] = last[y], last[y] = j, height[j] = cost;
};

bool are_adjacent( const u64 u, const u64 v, u64 &e ) {
	u64 x[3],y[3];
	for ( int i = 0; i < 3; ++i )
		x[i] = ((u>>(i*12))&MASK(12));
	for ( int i = 0; i < 3; ++i )
		y[i] = ((v>>(i*12))&MASK(12));
	for ( int i = 0; i < 3; ++i )
		for ( int j = i+1; j < 3; ++j )
			for ( int k = 0; k < 3; ++k )
				for ( int t = k+1; t < 3; ++t )
					if ( x[i]==y[k] && x[j]==y[t] ) {
						e = x[i]|(x[j]<<12);
						return true ;
					}
	return false ;
};

int main() {
	int i,j,k,l,t;
	char tmp[0x10],tmp2[0x10];
	u64 u,v,ee;
#ifndef ONLINE_JUDGE
	freopen("1097.in","r",stdin);
#endif
	for ( i = 0; i < 21; which[BIT(i)] = i, ++i );
	for ( i='A'; i<='Z'; id[i]=i-'A', ++i );
	for ( i='a'; i<='z'; id[i]=i-'a'+26, ++i );
	for(;2==scanf("%d %d",&n,&m)&&(m||n);) {
		for ( i = 0; i < n; ++i ) {
			scanf("%s %lld %lld %lld",tmp,&vv[i].first,&vv[i].second,&h[i]);
			mp[vx[i]=id[0[tmp]]|(id[1[tmp]]<<SH)] = i;
			memset(a[vx[i]],0,sizeof a[vx[i]]);
		};
		for ( region_name.clear(), l = 0; l < m; ++l ) {
			scanf("%s %s",tmp,tmp2);
			i = id[0[tmp]]|(id[1[tmp]]<<SH);
			j = id[0[tmp2]]|(id[1[tmp2]]<<SH);
			a[i][j>>6]|=BIT(j&63);
			a[j][i>>6]|=BIT(i&63);
		};
		for ( V = 0, region_name.clear(), i = 0; i < n; ++i )
			for ( l = 0; l <= (n>>6); ++l )
				for ( u = a[i][j]; u && (j=who(L(u))+l*64) >= 0; u &= ~L(u) )
					for ( t = 0; t <= (n>>6); ++t )
						for ( v = a[j][t]; v && (k=who(L(v))+t*64) >= 0; v &= ~L(v) )
							if ( a[k][i>>6]&BIT(i&63) ) 
								region_name[make_triple(i,j,k)] = 1;
		for ( map<u64,int>::iterator it=region_name.begin(); it!=region_name.end(); r[it->second=V++]=it->first, ++it );
		for ( E = 0, i = 0; i < V; last[i++] = -1 );
		for ( i = 0; i < V; ++i )
			for ( j = i+1; j < V; ++j )
				if ( are_adjacent(r[i],r[j],ee) ) {
					k = mp[ee&MASK(12)], t = mp[ee>>12];
					add_arcs(i,j,min(h[k],h[t]));
				}
	};
	return 0;
};

