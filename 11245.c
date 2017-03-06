/*
 * 11245. Anti-Arithmetic Sequence
 * TOPIC: maths, modulo, prime, number base conversion, usamo 1995
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef long long i64;
typedef unsigned long long u64;
#define N 0x400

int ts;
u64 P,n,m,d[N];

int main() {
	int i,j,k;
#ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
#endif
	for ( scanf("%d",&ts); ts-- && 2 == scanf("%llu %llu",&n,&P); printf("%llu\n",++m) ) {
		for ( k = 0, m = n-1; m; d[k++] = (m%(P-1)), m /= (P-1) );
		for (;--k >= 0; m *= P, m += d[k] );
	}
    return 0;
}

