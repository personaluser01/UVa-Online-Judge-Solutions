/*
 * 10232. Bit-Wise Sequence
 * TOPIC: gray codes, binary search, recursion, generation, greedy, binary
 * status:
 */
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef long long i64;
typedef unsigned long long u64;
#define N 32

i64 n,*ptr,dig[0x400];
u64 c[N][N],block[N],pref[N],ans;

void gen( i64 k, int m, int len ) {
	assert( m <= len );
	if ( len == 1 ) {
		assert( k <= 1 );
		assert( m <= 1 );
		if ( m == 0 ) {
			assert( k == 0 );
			*ptr++ = 0L;
			return ;
		}
		if ( m == 1 ) {
			assert( k == 0 );
			*ptr++ = 1L;
			return ;
		}
		assert( 0 );
	}
	assert( len >= 2 );
	if ( m == 0 ) {
		assert( k == 0 );
		for(;len--;*ptr++ = 0L );
		return ;
	}
	assert( m >= 1 );
	if ( c[len-1][m] > k ) {
		*ptr++ = 0LL;
		gen(k,m,len-1);
	}
	else {
		*ptr++ = 1LL;
		gen(k-c[len-1][m],m-1,len-1);
	}
}

int main() {
	int i,j,k,low,high,mid;
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	for ( i = 0; i < N; ++i )
		c[i][0] = 1;
	for ( i = 1; i < N; ++i )
		for ( j = 1; j <= i; ++j )
			c[i][j] = c[i-1][j]+c[i-1][j-1];
	for ( i = 0; i < N; ++i ) block[i] = c[N-1][i];
	for ( pref[0] = block[0], i = 1; i < N; ++i )
		pref[i] = pref[i-1]+block[i];
	for ( ;1 == scanf("%lld",&n); ) {
		if ( (++n) <= 2 ) { printf("%lld\n",n-1); continue ; }
		assert( pref[low=0] < n );
		assert( pref[high=N-1] >= n );
		for(;low+1<high;) {
			mid = (low+high)/2;
			if ( pref[mid] < n ) low = mid;
			else high = mid;
		} 
		for ( ans = 0, ptr = dig, gen(n-pref[low]-1,(int)high,N-1), i = 0; i < ptr-dig; ans = (ans<<1)+(dig[i++]) );
		printf("%llu\n",ans);
	}
	return 0;
}

