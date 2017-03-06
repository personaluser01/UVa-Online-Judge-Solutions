/*
 * 11259. Coin Changing Again
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <limits.h>
#include <float.h>
#define N 0x80
#define V (1 << 17)
typedef long long i64;

i64 c[4],d[N][4],v[N],C[V][4],z[5][V];
unsigned char bts[0x400];
int m;

int main() {
	int i,j,k,ts,l,t,cur;
	unsigned int u;
	i64 w,ans;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( i = 0; i < 0x400; ++i )
		bts[i] = bts[i>>1]+(i&1);
	for ( i = 0; i < N; C[i++][0] = 1 );
	for ( i = 1; i < N; ++i )
		for ( j = 1; j <= 3; ++j )
			C[i][j] = C[i-1][j]+C[i-1][j-1];
	for ( scanf("%d",&ts); ts--; ) {
		scanf("%lld %lld %lld %lld %d",c,c+1,c+2,c+3,&m);
		for ( z[0][0] = 1LL, i = 1; i <= 4; ++i )
			for ( w = 0; w < V; ++w ) {
				z[i][w] = z[i-1][w];
				if ( w >= c[i-1] ) z[i][w] += z[i][w-c[i-1]];
			}
		for ( cur = 0; cur < m; printf("%lld\n",ans), ++cur ) {
			for ( j = 0; j < 4; scanf("%lld",&d[cur][j++]) );
			for ( scanf("%lld",v+cur), ans = 0, u = 0; u < 16; ++u ) {
				for ( w = v[cur], j = 0; j < 4; ++j )
					w -= ((u>>j)&1)*d[cur][j]*c[j], w -= ((u>>j)&1)*c[j];
				if ( w < 0 ) continue ;
				if (bts[u]&1) {
					/*printf("Subtracting C[%lld][%d] = %lld\n",w+3,3,C[w+3][3]);*/
					ans -= z[4][w];
				}
				else {
					/*printf("Adding C[%lld][%d] = %lld\n",w+3,3,C[w+3][3]);*/
					ans += z[4][w];
				}
			}
		}
	}
	return 0;
}

