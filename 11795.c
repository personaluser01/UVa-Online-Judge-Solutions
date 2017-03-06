/*
 * 11795. Mega Man's Mission
 * TOPIC: bitmasks, DP
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 17
#define Q (1<<21)
#define oo 0xffffffffffffffffull
#define B(k) (1UL<<(k))
#define M(k) (B(k)-1UL)

int n,gr[1<<N][N],yes;
char g[N+2][N+N];
typedef unsigned long long u64;
u64 z[Q],cover[N];

u64 calc_z( unsigned int u ) {
	int j;
	if ( z[u] < +oo )
		return z[u];
	if ( !u ) return z[u] = 1;
	for ( z[u] = 0, j = 0; j < n; ++j )
		if ( (u&B(j)) && gr[u&~B(j)][j]==yes )
			z[u]+=calc_z(u&~B(j));
	return z[u];
}

int main() {
	int i,j,k,ts,cs = 0;
	unsigned int u,v;
#ifndef ONLINE_JUDGE
    freopen("in.txt","r",stdin);
#endif
	for ( scanf("%d",&ts); ts-- && printf("Case %d: ",++cs) && ++yes; ) {
		memset(z,0xffull,sizeof z);
		for ( scanf("%d",&n), i = 0; i <= n; scanf("%s",g[i++]+1) );
		for ( i = 0; i <= n; cover[i++] = 0 );
		for ( i=1; i<=n; ++i )
			for ( j=1; j<=n; ++j )
				if ( i!=j&&g[i][j]=='1' )
					cover[j-1]|=B(i-1);
		for ( u = 0; u < B(n); ++u )
			for ( j = 0; j < n; ++j )
				if ( !(u&B(j)) && (g[0][j+1]=='1'||(cover[j]&u)) )
					gr[u][j] = yes;
		printf("%llu\n",calc_z(M(n)));
	}
    return 0;
}

