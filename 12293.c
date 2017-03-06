/*
 * 12293. Box Game
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <limits.h>
#include <float.h>

typedef long long i64;
i64 n;

i64 G( i64 n ) {
	return (n&1)?G(n/2):(n/2);
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	while ( 1 == scanf("%lld",&n) && n > 0 ) { 
		puts(G(n)?"Alice":"Bob");
	}
	return 0;
}

