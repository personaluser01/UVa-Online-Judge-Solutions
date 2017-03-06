/*
 * 10710. Chinese Shuffle
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef long long i64;
#define KYLLA(n) (printf("%lld is a Jimmy-number\n",n))
#define EI(n) (printf("%lld is not a Jimmy-number\n",n))


i64 n,m,ax,x;

int main() {
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	while ( 1 == scanf("%lld",&n) && n >= 0 ) {
		for ( x = 2, ax = 1, m = n-1; m; x *= x, m >>= 1, x %= (n) )
			if ( m & 1 ) ax *= x, ax %= (n);
		if ( ax == 1 )
			KYLLA(n);
		else EI(n);
	}
	return 0;
}

