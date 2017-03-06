/*
 * 11903. e-Friends
 * TOPIC: dp, bitmasks
 * status: Accepted
 */
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BIT(k)  (1ULL<<(k))
#define MASK(k) (BIT(k)-1ULL)
#define L(k) ((k)&((~(k))+1ULL))
#define N 14
#define oo (1LL<<60)
typedef long long i64;

int n,qr;
char bts[BIT(N)],which[BIT(N)];
unsigned int adj[N];
i64 D,qqr,z[BIT(N)][N][N+1],sum;

i64 calc_z( unsigned int u, int i, int k ) {
	unsigned int v,j;
	if ( k < 0 || k > bts[u]-1 ) return 0;
	if ( z[u][i][k] < +oo )
		return z[u][i][k];
	if ( !(u&BIT(i)) )
		return z[u][i][k] = 0;
	for ( z[u][i][k] = 0, v=u&~BIT(i); v && (j=which[L(v)])>=0; v&=~L(v) )
		if ( calc_z(u&~BIT(i),j,k-((adj[i]>>j)&1)) < +oo )
			z[u][i][k] += calc_z(u&~BIT(i),j,k-((adj[i]>>j)&1));
	return z[u][i][k];
}

int main() {
	int i,j,k,ts,cs = 0;
	unsigned int u,v;
#ifndef ONLINE_JUDGE
	freopen("11903.in","r",stdin);
#endif
	for ( u = 0; u < BIT(N); bts[u] = bts[u>>1]+(u&1), ++u );
	for ( i = 0; i < N; which[BIT(i)] = i, ++i );
	for ( scanf("%d",&ts); ts-- && 3 == scanf("%d %lld %d",&n,&D,&qr); ) {
		for ( i = 0; i < n; ++i ) 
			for ( adj[i]=0, scanf("%d",&k); k-- && 1==scanf("%d",&j); adj[i]|=BIT(--j) );
		for ( u = 0; u < BIT(n); ++u )
			for ( i = 0; i < n; ++i )
				for ( k = 0; k <= n; z[u][i][k++] = +oo );
		for ( i = 0; i < n; ++i ) z[BIT(i)][i][0] = 1;
		printf("Case %d:\n",++cs);
		for(;qr--&&1==scanf("%lld",&qqr); printf("%lld\n",sum) ) 
			for ( k = ((D==0)?n-1:(qqr/D<n?qqr/D:n-1)), sum = 0, i = 0; i < n; ++i )
				for ( j = 0; j <= k; ++j )
					if ( calc_z(MASK(n),i,j) < +oo )
						sum += calc_z(MASK(n),i,j);
	}
	return 0;
}

