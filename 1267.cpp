/*
 * 1267. Network
 * TOPIC: graphs, trees, dfs, greedy
 * status: Accepted
 */
#include <cassert>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>
#define N (2*0x400)
using namespace std;

int srv,K,n,deg[N],adj[N][N],parent[N],d[N],ans;

int dfs( int x, int depth, int &pl ) {
	int j,k,l,t,leaf = 0,place = (1<<29);
	for ( int i = 0; i < deg[x]; ++i ) {
		int y = adj[x][i];
		if ( y == parent[x] ) continue ;
		parent[y] = x, t = dfs(y,depth+1,k);
		leaf = max(leaf,t);
		place = min(place,k);
	}
	pl = place;
	if ( (leaf-depth) + (place-depth) <= K )
		leaf = 0;
	if ( leaf == depth+K ) {
		pl = depth;
		ans += (srv!=x), leaf = 0;
	}
	if ( deg[x] == 1 )
		return depth;
	return leaf;
}

int main() {
	int i,j,k,ts;
#ifndef ONLINE_JUDGE
	freopen("a.txt","r",stdin);
#endif
	for ( scanf("%d",&ts); ts-- && 3 == scanf("%d %d %d",&n,&srv,&K); ) {
		for ( --srv, i = 0; i < n; deg[i++] = 0 );
		for(k=0;k<n-1;++k) 
			scanf("%d %d",&i,&j),--i,--j,adj[i][deg[i]++]=j,adj[j][deg[j]++]=i;
		ans=0,parent[srv]=-1,dfs(srv,0,i),printf("%d\n",ans);
	}
	return 0;
}

