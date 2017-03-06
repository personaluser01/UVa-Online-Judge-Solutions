/*
 * 1073. Glenbow Museum
 * TOPIC: dp
 * status: Accepted
 */
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 0x400
#define oo (1LL<<62)
typedef long long i64;

int n,m,p;
i64 z[2][N][N][2];

i64 calc_z( int k, int m, int p, int t ) {
	if ( p < 0 || m < 0 ) return 0;
	if ( z[k][m][p][t] < +oo )
		return z[k][m][p][t];
	if ( m == 2 && p == 0 ) {
		if ( k == 0 || t == 0 )
			return z[k][m][p][t] = 0;
		return z[k][m][p][t] = 1;
	}
	if ( m == 0 && p == 2 ) {
		return z[k][m][p][t] = 0;
	}
	if ( m == 1 && p == 1 ) {
		if ( k != t )
			return z[k][m][p][t] = 1;
		return z[k][m][p][t] = 0;
	}
	if ( m+p == 1 ) {
		if ( k != t )
			return z[k][m][p][t] = 0;
		if ( p == 1 && k == 0 )
			return z[k][m][p][t] = 1;
		if ( m == 1 && k == 1 )
			return z[k][m][p][t] = 1;
		return z[k][m][p][t] = 0;
	}
	assert( m+p >= 3 );
	if ( k == 0 && t == 0 ) {
		if ( p < 2 ) return z[k][m][p][t] = 0;
		return z[k][m][p][t] = calc_z(1,m,p-2,1);
	}
	if ( k == 0 && t == 1 ) {
		if ( p < 1 || m < 1 ) return z[k][m][p][t] = 0;
		return z[k][m][p][t] = calc_z(1,m-1,p-1,0)+calc_z(1,m-1,p-1,1);
	}
	if ( k == 1 && t == 0 ) {
		if ( p < 1 && m < 1 ) return z[k][m][p][t] = 0;
		return z[k][m][p][t] = calc_z(0,m-1,p-1,1)+calc_z(1,m-1,p-1,1);
	}
	if ( m < 2 ) return z[k][m][p][t] = 0;
	return z[k][m][p][t] = calc_z(0,m-2,p,0)+calc_z(0,m-2,p,1)+calc_z(1,m-2,p,0)+calc_z(1,m-2,p,1);
}

int main() {
	int i,j,k,cs = 0,t;
#ifndef ONLINE_JUDGE
	freopen("1073.in","r",stdin);
#endif
	for ( i = 0; i < N; ++i )
		for ( j = 0; j < N; ++j )
			for ( k = 0; k < 2; ++k )
				for ( t = 0; t < 2; ++t )
					z[k][i][j][t] = +oo;
	for (;1==scanf("%d",&n) && n>0;) {
		printf("Case %d: ",++cs);
		if ( n&1 ) { puts("0"); continue ; }
		assert( n >= 2 );
		m = n/2+2, p = n/2-2;
		printf("%lld\n",(calc_z(0,m,p,1)+calc_z(1,m,p,0)+calc_z(1,m,p,1)));
	}
	return 0;
}

