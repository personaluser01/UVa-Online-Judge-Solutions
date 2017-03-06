/*
 * 13014. Keep it energized
 * TOPIC: sweepline
 * status: Accepted
 */
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>
#include <queue>
#include <map>
#define N (1<<21)
#define oo (1LL<<43)
#include <set>
typedef long long i64;
using namespace std;
#define energy first
#define ccost second

struct cell {
	i64 cost,e;
	int level;
	cell() {};
	cell( i64 cost, i64 e, int level ) : cost(cost), e(e), level(level) {};
};

bool operator < ( const cell &a, const cell &b ) {
	if ( a.cost == b.cost ) {
		if ( a.level == b.level ) 
			return a.e > b.e;
		return a.level < b.level;
	}
	return a.cost < b.cost;
};

bool operator == ( const cell &a, const cell &b ) {
	return a.cost == b.cost && a.level == b.level && a.e == b.e;
};

struct comparator {
	bool operator () ( const cell &a, const cell &b ) {
		return b < a;
	};
};

i64 E[N],pref[N];
vector<pair<i64,i64> > shop[N];
int n,m;
priority_queue<cell,vector<cell>,comparator> pq;
set<cell> s;

int main() {
	i64 i,j,k,t;
#ifndef ONLINE_JUDGE
	freopen("13014.in","r",stdin);
#endif
	for (;2 == scanf("%d %d",&n,&m); ) {
		for ( i = 1; i <= n; ++i ) 
			scanf("%lld",E+i), shop[i].clear(), pref[i] = pref[i-1]+E[i];
		for ( i = 0; i < m; ++i ) {
			scanf("%lld %lld %lld",&j,&k,&t);
			shop[j].push_back(make_pair(k,t));
		}
		for ( s.clear(), i = 1; i <= n; ++i ) {
			while ( !s.empty() ) {
				cell u = *s.begin();
				if ( u.e < pref[i-1]-pref[u.level-1] )
					s.erase(s.begin());
				else break ;
			}
			if ( s.empty() && i != 1 ) {
			}
			else {
				i64 mm = i==1?0:s.begin()->cost;
				for ( j = 0; j < (int)shop[i].size(); ++j ) {
					pair<i64,i64> p = shop[i][j];
					if ( p.energy >= E[i] )
						s.insert(cell(mm+p.ccost,p.energy,i));
				}
			}
		}
		while ( !s.empty() ) {
			cell u = *s.begin();
			if ( u.e < pref[n]-pref[u.level-1] )
				s.erase(s.begin());
			else break ;
		}
		if ( s.empty() )
			puts("-1");
		else printf("%lld\n",s.begin()->cost);
	}
	return 0;
}

