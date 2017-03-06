/*
 * 11410. LAEncoding
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
#define A 26
typedef unsigned long long u64;

char mess[0x100],keys[0x100],works[A],d[0x100],*ptr;
u64 n,B,yes;

void pr( u64 n ) { (n<B)?putchar(d[n]+'A'):(pr(n/B),putchar(d[n%B]+'A')); }

int main() {
	int i,j,k,ts;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( scanf("%d",&ts); ts-- && ++yes; pr(n), putchar('\n') ) {
		scanf("%s %s",mess,keys);
		for ( i = 0; i < A; works[i++] = yes );
		for ( i = 0; keys[i]; works[keys[i++]-'A'] = 0 );
		for ( ptr = d, i = 0; i < A; ++i )
			if ( works[i] == yes ) *ptr++ = i;
		for ( B = ptr-d, n = 0, i = 0; mess[i]; n = n*A+(mess[i++]-'A') );
		/*printf("%llu\n",n);*/
	}
	return 0;
}
