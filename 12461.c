/*
 * 12461. Airplane
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 0x400
typedef long long i64;

i64 gcd( i64 x, i64 y ) {
	return !y ? x : gcd(y,x%y);
}

i64 n;

int main() {
	while ( 1 == scanf("%lld",&n) && n ) {
		if ( n == 1 )
			puts("1/1");
		else puts("1/2");
	}
	return 0;
}
