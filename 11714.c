/*
 * 11714. Blind Sorting
 * status: Accepted
 * TOPIC: maths, logarithms
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define tol 1e-9
typedef long long i64;

i64 n;

int main() {
	while ( 1 == scanf("%lld",&n) ) {
		printf("%lld\n",(i64)(n-1+log(n-1)/log(2.00)+tol));
	}
	return 0;
}

