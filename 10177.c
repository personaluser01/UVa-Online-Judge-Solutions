/*
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef long long i64;

i64 sqr( i64 x ) { return x*x; }

i64 fours( i64 k ) {
	return (k+1)-15*(k+1)*(k+2)/2+25*(k+1)*(k+2)*(k+3)/3-5*(k+1)*(k+2)*(k+3)*(k+4)/2+(k+1)*(k+2)*(k+3)*(k+4)*(k+5)/5;
}

i64 threes( i64 k ) {
	return sqr((k*(k+1))/2);
}

i64 twos( i64 k ) {
	return ((k)*(k+1)*(2*k+1))/6;
}

i64 ones( i64 k ) {
	return (k*(k+1))/2;
}

int main() {
	i64 k;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	while ( 1 == scanf("%lld",&k) ) {
		printf("%lld %lld %lld %lld %lld %lld\n",twos(k),ones(k)*ones(k)-twos(k),threes(k),ones(k)*ones(k)*ones(k)-threes(k),fours(k),sqr(sqr(ones(k)))-fours(k));		
	}
	return 0;
}

