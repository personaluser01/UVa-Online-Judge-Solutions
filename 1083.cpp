/*
 * 1083. Fare and Balanced
 * TOPIC: DP,DAG, binary search, world finals
 * status: Accepted
 * NOTES: notice that if the cost can be made uniformly X, then it is also possible to make it uniformly (X+1)
 * so, we binary search for the lowest X such that the assignment is possible. 
 */
#include <cassert>
#include <iostream>
#include <set>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <map>
#define N 50100
#define oo (1LL<<32)
enum { S, T };
typedef long long i64;
using namespace std;

int n,m,src,sink,seen[N],yes;
map<pair<int,i64>,bool> q;
i64 toll[N];
vector<pair<pair<int,int>,int> > roads[2];
vector<int> adj[2][N];
pair<i64,i64> z[2][N];
bool can_reach[2][N];

bool two( pair<i64,i64> &p ) {
	assert( p.first <= p.second );
	return p.first < p.second;
}

void replace( pair<i64,i64> &p, i64 mi, i64 ma ) {
	if ( p.first == -1 ) {
		p = make_pair(mi,ma);
		return ;
	}
	if ( p.first > mi )
		p.first = mi;
	if ( p.second < ma )
		p.second = ma;
}

void calc_set( const int t, int x ) {
	if ( seen[x] == yes )
		return ;
	seen[x] = yes;
	if ( t == S && x == sink || t == T && x == src ) {
		z[t][x] = make_pair(0,0);
		can_reach[t][x] = true ;
		return ;
	}
	can_reach[t][x] = false, z[t][x] = make_pair(-1,-1);
	for ( int w,y,j,i = 0; i < (int)adj[t][x].size(); ++i ) {
		j = adj[t][x][i], y = roads[t][j].first.second, w = roads[t][j].second;
		calc_set(t,y);
		if ( !can_reach[t][y] ) continue ;
		else can_reach[t][x] = true ;
		i64 mi = z[t][y].first+w, ma = z[t][y].second+w;
		replace(z[t][x],mi,ma);
	}
}

bool f( int x, bool change_made, i64 total_cost ) {
	bool ok = false ;
	if ( x == sink && !total_cost ) return q[make_pair(x,total_cost)] = true ;
	if ( x == sink ) return false ;
	if ( total_cost < 0 || !can_reach[S][x] ) return false ;
	if ( change_made ) 
		return !two(z[S][x]) && z[S][x].first == total_cost;
	if ( q.find(make_pair(x,total_cost)) != q.end() )
		return q[make_pair(x,total_cost)];
	if ( z[S][x].second > total_cost )
		return q[make_pair(x,total_cost)] = false ;
	for ( int w,y,j,i = 0; i < (int)adj[S][x].size(); ++i ) {
		j = adj[S][x][i], y = roads[S][j].first.second, w = roads[S][j].second;
		if ( !can_reach[S][y] ) continue ;
		else ok = true ;
		if ( w > total_cost ) return false ;
		if ( f(y,false,total_cost-w) ) 
			continue ;
		if ( two(z[T][x]) || two(z[S][y]) ) 
			return q[make_pair(x,total_cost)] = false ;
		toll[j] = (total_cost-z[S][y].first-w);
		if ( toll[j] < 0 )
			return q[make_pair(x,total_cost)] = false;
		if ( !f(y,true,total_cost-w-toll[j]) ) 
			return q[make_pair(x,total_cost)] = false ;
	}
	assert( can_reach[S][x] );
	assert( ok );
	return q[make_pair(x,total_cost)] = true ;
}

bool possible_to_assign( i64 cost ) {
	return f(src,false,cost);
}

void make_assignment( i64 cost ) {
	memset(toll,0,sizeof toll);
	f(src,false,cost);
}

int main() {
	int i,j,k,l,cs = 0;
	i64 bad,good,mid;
#ifndef ONLINE_JUDGE
	freopen("1083.in","r",stdin);
#endif
	for ( ;2 == scanf("%d %d",&n,&m) && (n||m) && ++yes; ) {
		printf("Case %d:",++cs), q.clear();
		for ( i = 0; i < n; adj[S][i].clear(),adj[T][i++].clear() );
		roads[S].clear(),roads[T].clear(),src=0,sink=n-1;
		for ( l = 0; l < m; ++l ) {
			scanf("%d %d %d",&i,&j,&k), --i, --j;
			roads[S].push_back(make_pair(make_pair(i,j),k));
			roads[T].push_back(make_pair(make_pair(j,i),k));
			adj[S][i].push_back(l), adj[T][j].push_back(l);
		}
		calc_set(S,src), ++yes, calc_set(T,sink);
		if ( !can_reach[S][src] || !possible_to_assign(good=z[S][src].second) ) {
			puts(" No solution");
			continue ;
		}
		/*
		for ( bad = z[S][src].first-1; bad+1 < good; ) {
			mid = (good+bad)/2;
			if ( possible_to_assign(mid) )
				good = mid;
			else bad = mid;
		}
		*/
		q.clear();
		make_assignment(good);
		for ( k = 0, i = 0; i < m; ++i )
			if ( toll[i] >= 1 ) ++k;
		printf(" %d %lld\n",k,good);
		for ( l = 0, i = 0; i < m; ++i ) 
			if ( toll[i] >= 1 )
				printf("%d %lld\n",i+1,toll[i]);
	}
	return 0;
}

