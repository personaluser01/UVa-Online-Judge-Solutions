/*
 * 12457. Tennis contest
 * KEYWORDS: Probability, Binomial Distribution, DP
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 0x100
#define tol 1e-9
typedef long long i64;

int ts,n;
double p,z[N][N],deg[N],w,ideg[N];
i64 c[N][N];

double min( double x, double y ) {
	return x < y ? x : y;
}

double max( double x, double y ) {
	return x > y ? x : y;
}


int main() {
	int i,j,k;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( i = 0; i < N; ++i )
		c[i][0] = 1;
	for ( i = 1; i < N; ++i )
		for ( j = 1; j <= i; ++j )
			c[i][j] = c[i-1][j-1] + c[i-1][j];
	for ( scanf("%d",&ts); ts-- && 2 == scanf("%d %lf",&n,&p); ) {
		memset(z,0,sizeof(z));
		for ( deg[0]  = 1, k = 1; k <= 2*n-1; deg[k]  = deg[k-1]*p, ++k );
		for ( ideg[0] = 1, k = 1; k <= 2*n-1; ideg[k] = ideg[k-1]*(1-p), ++k );
		for ( z[0][0] = 1, j = 1; j <= n; z[0][j++] = 0 );
		for ( k = 1; k <= n-1; z[k][0] = z[k-1][0]*(1-p), ++k );
		for ( k = 1; k <= 2*n-1; ++k )
			for ( j = 1; j <= n-1; ++j )
				if ( k-j < n && k-j >= 0 )
					z[k][j] = c[k][j]*deg[j]*ideg[k-j];
		for ( w = 0, k = 0; k <= 2*n-1; ++k )
			if ( k-n+1 < n )
				w += p*z[k][n-1];
		printf("%.2lf\n",max(min(w+tol,1.00),0.00)+tol);
	}
	return 0;
}

