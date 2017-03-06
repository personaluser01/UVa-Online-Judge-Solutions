/*
 * 12043. Divisors
 * TOPIC: sieve, number theory
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N (1<<17)
typedef long long i64;

i64 a,b,m,d[N],sigma[N];
char isprime[N];

i64 D( i64 x, i64 n ) {
	i64 ax = 1LL;
	for ( ;n; n >>= 1, x *= x )
		if ( n&1 )
			ax *= x;
	return ax;
}

int main() {
	i64 i,j,k,cs,l,t,G,S;
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	for ( isprime[2] = 1, i = 3; i < N; i += 2 ) isprime[i] = 1;
	for ( i = 0; i < N; ++i ) d[i] = 1, sigma[i] = 1;
	for ( i = 2; i < N; ++i )
		if ( isprime[i] ) 
			for ( sigma[i] = i+1, d[i] = 2, j = i+i; j < N; d[j] *= (k+1), sigma[j] *= (D(i,k+1)-1)/(i-1), j += i ) 
				for ( isprime[j] = 0, k = 0, l = j; !(l%i); l /= i, ++k );
	for ( scanf("%lld",&cs); cs-- && 3 == scanf("%lld %lld %lld",&a,&b,&m); ) {
		for ( G = S = 0, i = a; i <= b; ++i )
			if ( !(i%m) ) G += d[i], S += sigma[i];
		printf("%lld %lld\n",G,S);
	}
	return 0;
}

