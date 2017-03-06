/*
 * 10690. Expression Again
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef long long i64;
#define N 128
#define M 51
#define oo (1LL << 29)

int m,n,yes,z[N][(M+M)*N],a[N][(M+M)*N];
i64 c[N],total,mi,ma;

i64 max( i64 x, i64 y ) { return x < y ? y : x; }
i64 min( i64 x, i64 y ) { return x < y ? x : y; }

int main() {
	int i,j,k,t;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	while ( 2 == scanf("%d %d",&m,&n) && ++yes ) {
		for ( total = 0, i = 0; i < m+n; ++i )
			scanf("%lld",c+i), c[i] += 51, total += c[i];
		if ( m > n ) k = m, m = n, n = k;
		for ( i = 0; i <= m; ++i )
			for ( k = 0; k <= total; ++k )
				z[i][k] = 0;
		for ( z[0][0] = 1, i = 0; i < m+n; ++i ) {
			for ( j = 0; j < m; ++j )
				for ( k = 0; k+c[i] <= total; ++k )
					a[j+1][k+c[i]] = z[j][k];
			for ( j = 0; j < m; ++j )
				for ( k = 0; k+c[i] <= total; ++k )
					z[j+1][k+c[i]] |= a[j+1][k+c[i]];
		}
		for ( ma = -oo, mi = +oo, k = 0; k <= total; ++k )
			if ( z[m][k] ) {
				t = total-k;
				ma = max(ma,(t-51*n)*(k-51*m)), mi = min(mi,(t-51*n)*(k-51*m));
			}
		printf("%lld %lld\n",ma,mi);
	}
	return 0;
}
