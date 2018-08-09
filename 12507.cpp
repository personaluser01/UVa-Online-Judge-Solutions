/*
 * 12507. Kingdomes
 * TOPIC: MST, bitmasks
 * status: Accepted
 */
#include <bits/stdc++.h>
#define N 16
#define M 0x80
#define L(k) ((k)&((~(k))+1ULL))
#define oo (0xffffffffffffffffull)
using namespace std;
typedef unsigned long long u64;

int n,m,pop[N],weight[1<<N],who[1<<N];
u64 K,z[1<<N];

struct edge {
	int x,y;
	u64 w;
	edge() {};
};

edge e[M];
vector<int> adj[N];

int main() {
	int i,j,k,ts,ii,best;
	unsigned int u,nu,v;
	for ( i= 0; i < N; who[1<<i]= i, ++i ) ;
	for ( scanf("%d",&ts); ts--; ) {
		scanf("%d %d %llu",&n,&m,&K);
		for ( i= 0; i < n; adj[i++].clear() ) ;
		for ( i= 0; i < n; scanf("%d",&pop[i++]) ) ;
		for ( i= 0; i < m; ++i ) {
			cin >> e[i].x >> e[i].y >> e[i].w;
			--e[i].x, --e[i].y;
			adj[e[i].x].push_back(i), adj[e[i].y].push_back(i);
		}
		for ( u= 1; u < (1<<n); ++u ) 
			i= who[L(u)], weight[u]= weight[u&~(1ULL<<i)]+pop[i];
		memset(z,0xffull,sizeof z);
		for ( z[0]= 0, z[1ULL<<0]= 0, u= 1; u < (1<<n); ++u ) 
			for ( v= u, i= who[L(v)]; v; v&= ~(1ULL<<i), i= who[L(v)] ) 
				if ( z[nu= (u&~(1ULL<<i))] < +oo ) 
					for ( int l= 0; l < (int)adj[i].size(); ++l ) {
						j= adj[i][l];
						ii= e[j].x==i?e[j].y:e[j].x;
						if ( nu&(1ULL<<ii) )
							if ( z[u] > z[nu]+e[j].w && z[nu]+e[j].w <= K ) 
								z[u]= z[nu]+e[j].w;
					}
		for ( best= pop[0], u= 0; u < (1<<n); ++u )
			if ( z[u] <= K && weight[u] > best )
				best= weight[u];
		printf("%d\n",best);
	}
	return 0;
}

