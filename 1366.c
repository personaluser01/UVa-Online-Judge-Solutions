/*
 * 1366. Martian Mining
 * TOPIC: dp, trivial
 * status: Accepted
 */
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 0x200
typedef long long i64;
i64 max( i64 x, i64 y ) { return x<y?y:x; }

i64 c[2][N][N],row[N][N],col[N][N],z[N][N];

int main() {
	int i,j,k,t,m,n;
#ifndef ONLINE_JUDGE
	freopen("c.txt","r",stdin);
#endif
	for (;2 == scanf("%d %d",&m,&n) && (m||n); printf("%lld\n",z[m][n]) ) {
		for ( t = 0; t <= 1; ++t ) {
			for ( i = 1; i <= m; ++i )
				for ( j = 1; j <= n; ++j )
					scanf("%lld",&c[t][i][j]);
			for ( i = 1; i <= m && t == 0; ++i )
				for ( j = 1; j <= n; ++j )
					row[i][j] = row[i][j-1]+c[t][i][j];
			for ( j = 1; j <= m && t == 1; ++j )
				for ( i = 1; i <= m; ++i )
					col[j][i] = col[j][i-1]+c[t][i][j];
		}
		for ( i = 0; i <= m; ++i )
			for ( j = 0; j <= n; z[i][j++] = 0 );
		for ( i = 1; i <= m; ++i )
			for ( j = 1; j <= n; ++j )
				z[i][j] = max(z[i-1][j]+row[i][j],z[i][j-1]+col[j][i]);
	}
	return 0;
}

