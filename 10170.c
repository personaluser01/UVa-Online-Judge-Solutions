/*
 * 10170. Hotel with Infinite Rooms
 * status: Accepted
 */
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef unsigned long long u64;

u64 S,D,low,high,mid;

u64 f( u64 k ) { return (2*S+k)*(k+1); }


int main() {
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for(;2 == scanf("%llu %llu",&S,&D); ) {
		if ( f(0) >= 2*D ) {
			printf("%llu\n",S);
			continue ;
		}
		low = 0, high = (u64)(sqrt(2*D+(2*S-1.0)*(2*S-1.0)/4)-(2*S-1.0)/2+8);
		assert( f(high) >= 2*D );
		while ( low+1 < high ) {
			mid = (low+high)/2;
			if ( f(mid) < 2*D )
				low = mid;
			else high = mid;
		}
		printf("%llu\n",S+high );
	}
	return 0;
}

