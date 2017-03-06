/*
 * 12428. Enemy at the Gates
 * TOPIC: binary search, graphs
 * status: Accepted
 */
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef long long i64;

i64 n,m,ts,low,high,mid;

i64 f( i64 k ) { return k*k-k*(2*n-3)+n*n-n; }

int main() {
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	for ( scanf("%lld",&ts); ts-- && 2 == scanf("%lld %lld",&n,&m); ) {
		if ( f(n-1) >= 2*m ) { printf("%lld\n",n-1); continue ; }
		for(low=0,high=n-1;low+1<high;f(mid=(low+high)/2)<2*m?(high=mid):(low=mid));
		printf("%lld\n",low);
	}
	return 0;
}

