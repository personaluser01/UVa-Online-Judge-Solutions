#include <cassert>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
#define N 32
#include <algorithm>
using namespace std;
typedef pair<pair<int,int>,int> state;

bool seen[N][N][N];

void make_seen( state s ) {
	seen[s.first.first][s.first.second][s.second] = true;
}

void normalise( state &s ) {
	vector<int> v(3);
	v[0] = s.first.first, v[1] = s.first.second, v[2] = s.second;
	sort(v.begin(),v.end());
	s.first.first = v[0], s.first.second = v[1], s.second = v[2];
}

queue<state> q;

int main() {
	state u,v;
	int x,y,z;
	for ( u = make_pair(make_pair(7,9),11), make_seen(u), q.push(u); q.size(); ) {
		u = q.front(), q.pop();
		x = u.first.first, y = u.first.second, z = u.second;
		printf("(%d,%d,%d)\n",x,y,z);
		if ( x > 0 && y > 0 ) {
			v = make_pair(make_pair(x-1,y-1),z+2);
			normalise(v);
			if ( !seen[v.first.first][v.first.second][v.second] )
				make_seen(v), q.push(v);
		}
		if ( x > 0 && z > 0 ) {
			v = make_pair(make_pair(x-1,y+2),z-1);
			normalise(v);
			if ( !seen[v.first.first][v.first.second][v.second] )
				make_seen(v), q.push(v);
		}
		if ( z > 0 && y > 0 ) {
			v = make_pair(make_pair(x+2,y-1),z-1);
			normalise(v);
			if ( !seen[v.first.first][v.first.second][v.second] )
				make_seen(v), q.push(v);
		}
	}
	puts(seen[0][0][27] ? "YES" : "NO");
	return 0;
}
