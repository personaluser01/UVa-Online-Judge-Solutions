/*
 * 12875. Concert Tour
 * TOPIC: dag, dp
 * status: Accepted
 */
#include <algorithm>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#define SH 8
#define M (1 << 8)
#define N (1 << 8)
#define MASK(k) (BIT(k)-1UL)
#define BIT(k) (1UL<<(k))
#define enc(x,y) ((x)|((y)<<SH))
#define MAXV (BIT(8+8))
typedef long long iSH4;
using namespace std;
#define oo (1LL<<43)

int m,n,ts,g[M][M],gain[M][N],V;
vector<pair<unsigned int,int> > adj[MAXV];
iSH4 z[MAXV];

iSH4
calc_z( unsigned int u ) {
	unsigned int v;
	if ( z[u] < +oo )
		return z[u];
	z[u] = gain[u&MASK(SH)][u>>SH];
	for ( int i = 0; i < (int)adj[u].size(); ++i )
		if ( calc_z(v=adj[u][i].first) < +oo )
			z[u] = max(z[u],gain[u&MASK(SH)][u>>SH]+z[v]+adj[u][i].second);
	return z[u];
}

int main() {
	int i,j,k;
	unsigned int u,v;
	iSH4 w;
	for ( scanf("%d",&ts); ts-- && 2 == scanf("%d %d",&m,&n); ) {
		for ( i = 0; i < m; ++i )
			for ( j = 0; j < n; ++j ) 
				scanf("%d",&gain[i][j]);
		for ( i = 0; i < m; ++i )
			for ( j = 0; j < m; ++j )
				scanf("%d",&g[i][j]);
		for ( i = 0; i < m; ++i )
			for ( j = 0; j < n; ++j )
				adj[enc(i,j)].clear();
		for ( i = 0; i < m; ++i )
			for ( j = 0; j < n-1; ++j )
				for ( u = enc(i,j), k = 0; k < m; ++k )
					adj[u].push_back(make_pair(v=enc(k,j+1),-g[i][k]));
		for ( i = 0; i < m; ++i )
			for ( j = 0; j < n; ++j )
				z[enc(i,j)] = +oo;
		for ( w = 0, i = 0; i < m; ++i )
			if ( calc_z(u=enc(i,0)) < +oo )
				w = max(w,z[u]);
		printf("%lld\n",w);
	}
	return 0;
}


