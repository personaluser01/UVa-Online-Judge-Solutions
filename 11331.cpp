/*
 * 11331. The Joys of Farming
 * status: Accepted
 */
#include <iostream>
#include <cassert>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#define N 0x400
#include <set>
using namespace std;
enum { WHITE, BLACK };

int m,n,lines,u[20100],v[20100],seen[N+N],yes,color[N+N],
	c[N+N][2],T;
vector<int> adj[N+N];

void dfs( int x ) {
	int i,y;
	assert( seen[x] != yes );
	seen[x] = yes, ++c[T][color[x]];
	for ( i = 0; i < (int)adj[x].size(); ++i ) {
		if ( seen[y = adj[x][i]] == yes )
			continue ;
		color[y] = color[x]^1, dfs(y);
	}
}

int main() {
	int i,j,k,t,ts;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( scanf("%d",&ts); ts--; ) {
		scanf("%d %d %d",&m,&n,&lines);
		for ( i = 0; i < m+n; ++i ) adj[i].clear();
		for ( k = 0; k < lines; ++k ) {
			scanf("%d %d",u+k,v+k);
			--u[k], --v[k];
			if ( u[k] > v[k] )
				swap(u[k],v[k]);
			adj[u[k]].push_back(v[k]);
			adj[v[k]].push_back(u[k]);
		}
		for ( T = 0, ++yes, i = 0; i < m+n; ++i )
			if ( seen[i] != yes && ++T ) {
				for ( k = WHITE; k <= BLACK; ++k ) c[T][k] = 0;
				color[i] = WHITE, dfs(i);
			}
		set<int> s[2];
		set<int>::iterator it;
		for ( s[t = 0].clear(), s[t].insert(0), i = 1; i <= T; ++i )
			for ( t ^= 1, s[t].clear(), it = s[t^1].begin(); it != s[t^1].end(); ++it )
				for ( k = 0; k <= 1; ++k )
					s[t].insert((*it)+c[i][k]);
		puts(s[t].find(m)==s[t].end()?"no":"yes");
	}
	return 0;
}

