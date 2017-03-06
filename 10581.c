/*
 * 10581. Partitioning for Fun and Profit
 * TOPIC: dp, partitioning, recursion
 * status: Accepted
 */
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef long long i64;
typedef unsigned long long u64;
#define M 11
#define N 221
#define oo 0xffffffffffffffffull

i64 K,m,n;
u64 z[N][M][N],e[N][M][N];

u64 calc_e( int w, int k, int l ) ;

u64 calc_z( int w, int k, int l ) {
	int t;
	if ( w < 0 ) return 0ULL;
	if ( z[w][k][l] < +oo )
		return z[w][k][l];
	if ( l > w )
		return z[w][k][l] = 0ULL;
	if ( k == 1 ) {
		if ( w != l )
			return z[w][k][l] = 0ULL;
		return z[w][k][l] = 1ULL;
	}
	assert( k >= 2 && l <= w );
	assert( l != 0 );
	for ( z[w][k][l] = 0, t = l; t <= w-l; ++t )
		z[w][k][l] += calc_z(w-l,k-1,t);
	return z[w][k][l];
	/*return z[w][k][l] = calc_e(w-l,k-1,l);*/
}

u64 calc_e( int w, int k, int l ) {
	int t;
	if ( w < 0 ) return 0ULL;
	if ( e[w][k][l] < +oo )
		return e[w][k][l];
	assert( k >= 1 );
	if ( l > w ) return e[w][k][l] = 0ULL;
	if ( k == 1 ) {
		assert( w >= l );
		return e[w][k][l] = 1ULL;
	}
	assert( k >= 2 );
	/*
	for ( e[w][k][l] = 0ULL, t = 1; t <= l && t <= w; ++t )
		e[w][k][l] += calc_e(w-t,k-1,t);*/
	for ( e[w][k][l] = 0ULL, t = l; t <= w; ++t )
		e[w][k][l] += calc_z(w,k,t);
	return e[w][k][l];
}

void build( int n, int m, i64 k, int lower ) {
	int low,high,mid;
	i64 ss = 0,ww;
	if ( m == 1 ) { assert( 0 == k ); printf("%d\n",n); return ; }
	assert( m >= 2 );
	for ( high = lower; high <= n; ++high, ss += ww )
		if ( (ss+(ww=calc_e(n-high,m-1,high))) > k ) break ;
	/*
	for ( low = 1, high = n-(m-1); low+1 < high && (mid=(low+high)/2) >= 0; )
		if ( calc_e(n-mid,m-1,mid) < k )
			low = mid;
		else high = mid;
	assert( calc_e(n-low,m-1,low) < k );*/
	printf("%d\n",high), build(n-high,m-1,k-ss,high);
}

int main() {
	int i,j,k,ts,w,l;
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	memset(z,0xff,sizeof z), memset(e,0xff,sizeof e);
	for ( scanf("%d",&ts); ts-- && 3 == scanf("%lld %lld %lld",&n,&m,&K); build(n,m,K-1,1) );
	return 0;
}

