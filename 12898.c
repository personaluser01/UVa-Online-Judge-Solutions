/*
 * 12898. And Or
 * TOPIC: binary system, excellent interview question, constructive algorithms
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define T(a,k) (((a)>>(k))&1ULL)
typedef unsigned long long u64;

int ts,cs;
u64 a,b,OR,AND;

int main() {
	int i,j,k;
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	for ( scanf("%d",&ts); ts--; ) {
		scanf("%llu %llu",&a,&b);
		printf("Case %d: ",++cs);
		for ( k = 0, i = 63; i >= 0 && T(a,i) == T(b,i); --i, ++k );
		if ( i < 0 ) {
			assert( a == b );
			printf("%llu %llu\n",a,b);
			continue ;
		}
		assert( a < b );
		assert( T(a,i) == 0 && T(b,i) ==  1 );
		for ( OR = AND = 0, j = 63; j >= i+1; --j )
			OR |= (T(b,j)<<j), AND |= (T(b,j)<<j);
		for ( ;j >= 0; --j )
			OR |= (1ULL<<j);
		printf("%llu %llu\n",OR,AND);
	}
	return 0;
}

