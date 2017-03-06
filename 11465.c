/*
 * 11465. Count the Polygons
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
#define N 32
#define L(i) ((i) & ((~(i))+1))


typedef long long i64;
i64 n,K,c[N],ax,pref[N],C[N][N],sentinel;
i64 max( i64 x, i64 y ) { return x < y ? y : x; }

void rec( int k, int i, i64 sum ) {
	int j;
	if ( k == K-1 ) {
		if ( c[sentinel] < sum ) ++ax;
		return ;
	}
	if ( sentinel-i < K-1-k )
		return ;
	if ( i <= sentinel-K+k+1 && pref[sentinel-1]-pref[sentinel-K+k]+sum <= c[sentinel] )
		return ;
	if ( i+K-k-2 < sentinel && sum+pref[i+K-k-2]-pref[i-1] > c[sentinel] ) {
		ax += C[sentinel-i][K-k-1];
		return ;
	}
	for ( j = i; j <= sentinel-K+k+1; ++j )
		rec(k+1,j+1,sum+c[j]);
}

int main() {
	i64 i,j,k,ts,cs = 0,low,high;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( i = 0; i < N; ++i ) C[i][0] = 1;
	for ( i = 1; i < N; ++i )
		for ( j = 1; j <= i; ++j )
			C[i][j] = C[i-1][j-1]+C[i-1][j];
	for ( scanf("%lld",&ts); ts--; ) {
		scanf("%lld %lld",&n,&K), ax = 0;
		for ( i = 1; i <= n; ++i ) scanf("%lld",c+i);
		for ( j = 1; j; )
			for ( j = 0, i = 1; i <= n-1; ++i )
				if ( c[i] > c[i+1] ) 
					++j, k = c[i], c[i] = c[i+1], c[i+1] = k;
		for ( i = 1; i <= n; ++i )
			pref[i] = pref[i-1]+c[i];
		for ( ax = 0, k = n; k >= K; --k ) 
			sentinel = k, rec(0,1,0);
		printf("Case %lld: %lld\n",++cs,ax);
	}
	return 0;
}

