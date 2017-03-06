/*
 * 1237. Expert Enough
 * status: Accepted
 * TOPIC: event/driven simulation, priority queue, sweep/line, intervals, covers, heap
 */
#include <cassert>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>
#include <queue>
#include <set>
#define M 0x400
using namespace std;
#define OPENING 0
#define CLOSING 1

int n,x[2][1 << 20],m,tp[1 << 20];
set<int> s;
string nm[1 << 20];

bool my_less( const pair<int,int> &a, const pair<int,int> &b ) {
	if ( x[a.second][a.first] == x[b.second][b.first] ) 
		return a.first >= n && b.first < n;
	return x[a.second][a.first] < x[b.second][b.first];
}

struct my_comparator {
	bool operator() ( const pair<int,int> &a, const pair<int,int> &b ) const {
		return my_less(b,a);
	}
};

priority_queue<pair<int,int>, vector<pair<int,int> >,my_comparator> q;

int main() {
	int i,j,k,ts,qr;
	char tmp[0x400];
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	for ( scanf("%d",&ts); ts--; ) {
		assert( 1 == scanf("%d",&n) );
		assert( s.empty() && q.empty() );
		for ( i = 0; i < n; ++i ) {
			scanf("%s %d %d",tmp,x[0]+i,x[1]+i);
			nm[i] = string(tmp);
			q.push(make_pair(i,OPENING));
		}
		for ( scanf("%d",&qr), i = n; i < n+qr; ++i ) {
			scanf("%d",x[0]+i), x[1][i] = x[0][i];
			q.push(make_pair(i,OPENING));
		}
		for ( ;!q.empty(); ) {
			pair<int,int> r = q.top(); q.pop();
			if ( r.second == OPENING ) {
				q.push(make_pair(r.first,CLOSING));
				if ( r.first < n )
					s.insert(r.first);
				continue ;
			}
			if ( r.first >= n ) {
				if ( s.size() == 1 ) 
					nm[r.first] = nm[*(s.begin())];
				else nm[r.first] = string("UNDETERMINED");
				continue ;
			}
			s.erase(r.first);
		}
		for ( i = n; i < n+qr; printf("%s\n",nm[i++].c_str()) );
		if ( ts ) putchar('\n');
	}
	return 0;
}

