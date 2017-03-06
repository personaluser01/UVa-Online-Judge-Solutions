/*
 * 11202. The Least Possible Effort
 * TOPIC: formula, recursion
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N (1 << 15)
typedef long long i64;

int m,n;

i64 F( int m ) { return (m>>1)+(m&1); }

int main() {
	int i,j,k;
	i64 ax;
#ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
#endif
	for ( scanf("%d",&k); k-- && 2 == scanf("%d %d",&m,&n); ) {
		if ( m > n ) i = m, m = n, n = i;
		assert( m <= n );
		if ( m < n ) {
			for ( ax = 0; m >= 1 && n >= 1; m -= 2, n -= 2 )
				ax += F(m)+F(n)-1;
		}
		else {
			for ( ax = 0; m >= 1; m -= 2 )
				ax += F(m);
		}
		printf("%lld\n",ax);
	}
    return 0;
}

