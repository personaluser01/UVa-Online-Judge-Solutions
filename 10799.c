/*
 * 10799. OOPS!
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
#define N 20000001
typedef long long i64;

int n,ts;
i64 L,H,m;

i64 f( i64 M, i64 k ) {
	i64 q = M/k,
		ax;
	if ( q & 1 )
		ax = ((q-1)>>1)*q*k;
	else 
		ax = (q>>1)*(q-1)*k;
	ax += ((M%k)+1)*q;
	return ax;
}

i64 g( i64 M, i64 k ) {
	i64 q = (M+1)/(2*k);
	return k*q*(q-1) + q*(((M+1)%(2*k)));
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for (;3 == scanf("%lld %lld %lld",&L,&H,&m) && (L||H||m); ) {
		printf("Case %d: ",++ts);
		assert ( m > 1 );
		if ( m & 1 ) {
			printf("%lld\n",f(H-L,m-1));
		}
		else {
			printf("%lld\n",g(H-L,m-1));
		}
	}
	return 0;
}
