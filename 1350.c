/*
 * 1350. Pinary Number
 * TOPIC: combinatorics, counting
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define L (1<<19)
#define LIMIT (1LL<<61)
typedef long long i64;

int K,M;
char *ptr,s[L];
i64 n,z[L],agg[L],q[L][2];

void construct( i64 n, int length, int cur ) {
	if ( !length ) { *ptr = '\0'; return ; }
	assert( n <= q[length][0]+q[length][1] );
	if ( cur == 1 ) {
		*ptr++ = '0';
		construct(n,length-1,0);
		return ;
	}
	if ( q[length][0] >= n ) {
		*ptr++ = '0';
		construct(n,length-1,0);
		return ;
	}
	*ptr++ = '1', construct(n-q[length][0],length-1,1);
}

int main() {
	int i,j,k,ts,low,high,mid,length;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( q[1][0] = q[1][1] = 1LL, n = 2; ; ++n ) {
		q[n][0] = q[n-1][0]+q[n-1][1];
	   	q[n][1] = q[n-1][0];
		if ( q[n][0]+q[n][1] >= LIMIT ) { M = n; break; }
	}
	for ( z[1] = 1, agg[1] = 1, n = 2; n <= M; ++n ) 
		if ( (agg[n]=(agg[n-1]+(z[n]=q[n-1][0]))) >= LIMIT ) {
			K = n;
			break;
		}
	for ( scanf("%d",&ts); ts-- && 1 == scanf("%lld",&n); ) {
		if ( n == 1 ) { puts("1"); continue ; }
		assert( agg[low = 0] < n );
		assert( agg[high = K] >= n );
		for(low=1,high=K-1;low+1<high;agg[mid=(low+high)/2]<n?(low=mid):(high=mid));
		assert( agg[low] < n );
		assert( agg[high] >= n );
		length = high;
		n -= agg[low];
		assert( q[length-1][0] >= n );
		ptr = s, *ptr++ = '1', construct(n,length-1,1);
		puts(s);
	}
	return 0;
}

