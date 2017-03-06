/*
 * 13038. Directed Forest
 * TOPIC: dp
 * status: Accepted
 */
#include <bits/stdc++.h>
#define N (1<<17)
using namespace std;

int m,n,indeg[N];
vector<int> adj[N];

int dfs( int x ) {
	int ans = 1;
	for ( auto y: adj[x] )
		ans = max(ans,1+dfs(y));
	return ans;
}

int main() {
	int i,j,k,ts,ans,cs = 0;
	for ( scanf("%d",&ts); ts--; ) {
		for ( scanf("%d %d",&n,&m), i = 0; i < n; adj[i].clear(), indeg[i++] = 0 );
		for ( k = 0; k < m; ++k ) {
			scanf("%d %d",&i,&j), --i, --j;
			adj[i].push_back(j), ++indeg[j];
		}
		for ( ans = -1, i = 0; i < n; ++i )
			if ( !indeg[i] )
				ans = max(dfs(i),ans);
		printf("Case %d: %d\n",++cs,ans);
	}
	return 0;
}

