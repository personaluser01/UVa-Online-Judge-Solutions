/*
 * 1240. ICPC Team Strategy
 * TOPIC: DP, bitmasks
 * status: Accepted
 */
#include <cassert>
#include <cstdio>
#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <cmath>
#include <vector>
using namespace std;
#define N 0x10
#define T (1<<9)
#define oo 0xfffffffful
#define BIT(k) (1UL<<(k))
#define MASK(k) (BIT(k)-1UL)
#include <queue>

int ts,c[3][N],n;
unsigned int z[1<<12][3],bts[1<<12];
queue<pair<unsigned int,int> > q;

int main() {
	int i,j,k,t,l,kk;
	unsigned int u,v,w;
#ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
#endif
	for ( u = 0; u < (1<<12); ++u )
		bts[u] = bts[u>>1] + (u&1);
	for ( scanf("%d",&ts); ts-- && 1 == scanf("%d",&n); ) {
		for ( t = 0; t <= 2; ++t ) for ( i = 0; i < n; scanf("%d",&c[t][i++]) );
		memset(z,0xff,sizeof z);
		for ( k = 0; k <= 2; ++k )
			for ( i = 0; i < n; ++i )
				if ( c[k][i] <= 280 )
					z[BIT(i)][k] = c[k][i], q.push(make_pair(BIT(i),k));
		for ( w = 0; !q.empty(); ) {
			pair<unsigned int,int> r = q.front();
			q.pop();
			u = r.first, k = r.second;
			w = max(w,bts[u]);
			for ( j = 0; j < n; ++j )
				if ( !(u&BIT(j)) ) {
					for ( l = 1; l <= 2; ++l ) {
						kk = (l+k)%3;
						if ( c[kk][j]+z[u][k] <= 280 )
							if ( z[v = u|BIT(j)][kk] > z[u][k]+c[kk][j] )
								z[v][kk] = z[u][k]+c[kk][j], q.push(make_pair(v,kk));
					}
				}
		}
		printf("%u\n",w);
	}
    return 0;
}

