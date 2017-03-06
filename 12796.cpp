/*
 * 12796. Teletransport
 * TOPIC: matrix power
 * status: Accepted
 */
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>
#define MOD (10000)
#define N 0x80
using namespace std;
typedef long long i64;

int src,dst,n;
i64 L,g[N][N],A[N][N],t[N][N],r[N][N];

int main() {
	int i,j,k;
#ifndef ONLINE_JUDGE
	freopen("a.txt","r",stdin);
#endif
	for (;2==scanf("%d %lld",&n,&L);) {
		scanf("%d %d",&src,&dst), --src, --dst;
		for ( i = 0; i < n; ++i )
			for ( j = 0; j < n; g[i][j++] = 0 );
		for ( i = 0; i < n; ++i ) 
			for ( k = 0; k < 4; ++k ) 
				scanf("%d",&j), --j, ++g[i][j];
		for ( i = 0; i < n; ++i )
			for ( j = 0; j < n; ++j )
				if ( i == j ) r[i][j] = 1;
				else r[i][j] = 0;
		for (;L; L>>=1 ) {
			if ( L & 1 ) {
				for ( i = 0; i < n; ++i )
					for ( j = 0; j < n; ++j )
						for ( t[i][j] = 0, k = 0; k < n; ++k )
							t[i][j] += r[i][k]*g[k][j], t[i][j] %= MOD;
				for ( i = 0; i < n; ++i )
					for ( j = 0; j < n; ++j )
						r[i][j] = t[i][j];
			}
			for ( i = 0; i < n; ++i )
				for ( j = 0; j < n; ++j )
					for ( t[i][j] = 0, k = 0; k < n; ++k )
						t[i][j] += g[i][k]*g[k][j], t[i][j] %= MOD;
			for ( i = 0; i < n; ++i )
				for ( j = 0; j < n; ++j )
					g[i][j] = t[i][j];
		}
		printf("%lld\n",r[src][dst]);
	}
	return 0;
};

