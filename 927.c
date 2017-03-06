/*
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef long long i64;
#define N 32

i64 c[N],n,d,K;

i64 eval( i64 x ) {
	i64 ax = 0, i;
	for ( i = n; i >= 0; --i )
		ax = x*ax, ax += c[i];
	return ax;
}

long double f( i64 n ) {
	if ( n & 1 )
		return (n*((n+1)/2));
	return ((n/2)*(n+1));
}

int main() {
	int i,j,k,cs;
	i64 high,low,mid;
	long double L;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( scanf("%d",&cs); cs--; ) {
		for ( scanf("%lld",&n), i = 0; i <= n; ++i )
			scanf("%lld",c+i);
		scanf("%lld %lld",&d,&K);
		if ( K == 1 ) {
			printf("%lld\n",eval(1));
			continue ;
		}
		L = K/(d+.0);
		for ( low = 1, high = (1LL << 29); low+1 != high; ) {
			if ( f(mid = (low+high)/2) < L )
				low = mid;
			else high = mid;
		}
		printf("%lld\n",eval(high));
	}
	return 0;
}

