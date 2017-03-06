/*
 * 13019. Wooden Signs
 * TOPIC: DP
 * status: Accepted
 */
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MOD 2147483647LL
#define N (1<<11)
#define oo (1LL<<61)
typedef long long i64;

int n,c[N];
i64 z[N][N];

int f( int x ) { if ( x ) return 1; return 0; }

i64 calc_z( int k, int l ) {
	if ( z[k][l] < +oo )
		return z[k][l];
	if ( l == c[k] ) return z[k][l] = 0;
	if ( k == n ) 
		return z[k][l] = 1;
	assert( k < n );
	return z[k][l] = (f(!(c[k]>l&&c[k+1]<l || c[k]<l&&c[k+1]>l))*calc_z(k+1,l)+f(!(l<c[k]&&c[k+1]>c[k] || c[k]<l&&c[k+1]<c[k]))*calc_z(k+1,c[k]))%MOD;
}

int main() {
	int i,j,k;
#ifndef ONLINE_JUDGE
	freopen("13019.in","r",stdin);
#endif
	for ( ;1 == scanf("%d",&n) && n; ) {
		for ( i = 0; i <= n+1; ++i )
			for ( j = 0; j <= n+1; ++j )
				z[i][j] = +oo;
		for ( i = 0; i <= n; ++i )
			scanf("%d",c+i);
		printf("%lld\n",calc_z(1,c[0]));
	}
	return 0;
}

