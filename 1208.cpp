/*
 * 1208. OREON
 * TOPIC: kruskal, mst
 * status: Accepted
 */
#include <cassert>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#define N 32
#include <vector>
using namespace std;

int rank[N],p[N],n,m;

void link( int x, int y ) {
	if ( rank[x] > rank[y] ) {
		p[y] = x;
	}
	else {
		if ( rank[x] == rank[y] )
			++rank[y];
		p[x] = y;
	}
}

int find( int x ) {
	return p[x]=(p[x]==x?x:find(p[x]));
}
void merge( int x, int y ) { link(find(x),find(y)); }

void make_set( int x ) { rank[p[x]=x]=0; }

typedef struct {
	int x,y,w;
} edge;

bool operator<(const edge &a, const edge &b ) {
	if ( a.w == b.w ) {
		if ( a.x == b.x ) 
			return a.y < b.y;
		return a.x < b.x;
	}
	return a.w < b.w;
}

edge e[1<<21];
vector<pair<int,pair<char,char> > > q;

int main() {
	int i,j,k,ts,cs = 0,w;
	for ( scanf("%d",&ts); ts--; ) {
		scanf("%d",&n), m = 0;
		for ( i = 0; i < n; ++i ) 
			for ( j = 0; j < n; ++j ) {
				assert( 1 == scanf("%d",&k) );
			   	e[m].x = i, e[m].y = j, e[m++].w = k, getchar();
			}
		sort(e,e+m),q.clear();
		for ( i = 0; i < n; ++i ) make_set(i);
		for ( w = 0, i = 0; i < m; ++i )
			if ( e[i].w != 0 && find(e[i].x) != find(e[i].y) ) 
				merge(e[i].x,e[i].y), w += e[i].w, q.push_back(make_pair(e[i].w,make_pair(e[i].x+'A',e[i].y+'A')));
		sort(q.begin(),q.end());
		printf("Case %d:\n",++cs);
		for ( i = 0; i < q.size(); ++i )
			printf("%c-%c %d\n",q[i].second.first,q[i].second.second,q[i].first);
	}
	return 0;
}

