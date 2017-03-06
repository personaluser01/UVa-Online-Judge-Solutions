/*
 * 1494. National Road System
 * TOPIC: MST, lca
 * status: Accepted
 */
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cfloat>
#include <climits>
#include <iostream>
#include <vector>
#define N 0x400
#include <set>
#define S(k) ((k)*(k))
#define MAXE (N*N)
#define oo (1<<29)
#define K (13)
#include <queue>
using namespace std;

int n,last[N],_next[MAXE],to[MAXE],E,D[N],
	P[N],in_tree[N],yes,p[N],anc[N][K];
pair<double,double> vv[N];
set<pair<double,int> > s;
double cost[MAXE],d[N],A,B,max_edge[N][N],weight[N][N];
vector<pair<int,double> > adj[N];
queue<int> q;

void add_arcs( int x, int y, double c ) {
	int i = E++, j = E++;
	to[i] = y, _next[i] = last[x], last[x] = i, cost[i] = c;
	to[j] = x, _next[j] = last[y], last[y] = j, cost[j] = c;
};

int up( int x, int k ) {
	for ( int i = 0; k; k >>= 1, ++i ) {
		assert( x != -1 );
		if ( k&1 )
			x = anc[x][i];
	}
	return x;
};

int lca( int x, int y ) {
	int k;

	if ( x == y ) return x;
	if ( D[y] < D[x] )
		return lca(up(x,D[x]-D[y]),y);
	if ( D[y] > D[x] )
		return lca(y,x);
	assert( D[x] == D[y] );

	assert( anc[x][K-1] == anc[y][K-1] );
	for ( k = K-1; --k >= 0; ) {
		assert( x != -1 );
		assert( y != -1 );
		if ( anc[x][k] != anc[y][k] ) 
			x = anc[x][k], y = anc[y][k];
		assert( anc[x][k+1] == anc[y][k+1] );
	}
	return anc[x][0];
}

double f( int x, int y ) {
	if ( x == y ) return max_edge[x][y] = 0;
	if ( max_edge[x][y] < +oo )
		return max_edge[x][y];
	int z = lca(x,y);
	// printf("lca(%d,%d) = %d\n",x,y,z);
	if ( x == z ) {
		if ( p[y] == x ) return max_edge[x][y] = max_edge[y][x] = weight[x][y];
		return max_edge[x][y] = max_edge[y][x] = max(weight[y][p[y]],f(x,p[y]));
	}
	if ( y == z ) {
		if ( p[x] == y ) return max_edge[x][y] = max_edge[y][x] = weight[x][y];
		return max_edge[x][y] = max_edge[y][x] = max(weight[x][p[x]],f(y,p[x]));
	}
	assert( x != z && y != z );
	return max_edge[x][y] = max_edge[y][x] = max(f(z,x),f(z,y));
};

int main() {
	int i,j,k,ts,x,y,nx,ny,z;
	double w,ans;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( scanf("%d",&ts); ts-- && 1 == scanf("%d",&n); ) {
		for ( E = 0, i = 0; i < n; last[i++] = -1 );
		for ( i = 0; i < n; scanf("%lf %lf %d",&vv[i].first,&vv[i].second,P+i), ++i );
		for ( i = 0; i < n; ++i )
			for ( j = i+1; j < n; ++j )
				add_arcs(i,j,sqrt(S(vv[i].first-vv[j].first)+S(vv[i].second-vv[j].second)));
		for ( i = 0; i < n; ++i )
			for ( j = i+1; j < n; ++j )
				max_edge[i][j] = max_edge[j][i] = +oo;
		for ( z = 0; z < n; adj[z].clear(), d[z++] = +oo );		
		d[0] = 0, s.insert(make_pair(d[0],0)), p[0] = -1;
		for ( w = 0, ++yes; !s.empty();) {
			set< pair<double,int> > :: iterator it = s.begin();
			s.erase(*it), x = it->second;
			if ( in_tree[x] == yes ) continue ;
			if ( p[x] != -1 )
				adj[p[x]].push_back(make_pair(x,d[x]));
			for ( in_tree[x]=yes, w+=d[x], i=last[x]; i>=0; i=_next[i] )
				if ( d[y=to[i]]>cost[i] ) 
					d[y]=cost[i],p[y]=x,weight[x][y]=weight[y][x]=cost[i],s.insert(make_pair(d[y],y));
		}
		for ( i = 0; i < n; ++i )
			for ( D[i] = (1<<29), k = 0; k < K; ++k )
				anc[i][k] = -1;
		for ( D[0] = 0, q.push(0); !q.empty(); ) 
			for ( x = q.front(), q.pop(), i = 0; i < (int)adj[x].size(); ++i )
				if ( D[y=adj[x][i].first]>D[x]+1 )
					for ( D[y]=D[x]+1, q.push(y), p[y]=anc[y][0]=x, k=1; (1<<k)<=D[y]; anc[y][k] = anc[anc[y][k-1]][k-1], ++k );
		for ( ans=-(DBL_MAX-0x400), i=0; i<n; ++i )
			for ( j=i+1; j<n; ++j )
				ans = max(ans,(P[i]+P[j])/(w-f(i,j)));
		printf("%.2lf\n",ans);
	}
	return 0;
}

