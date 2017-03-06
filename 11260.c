/*
 * 11260. Odd Root Sum
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
#define MOD 100000000LL
#define tol 1e-9

typedef unsigned long long u64;
typedef long long i64;
i64 n,L,m;

i64 mpow( i64 x, i64 n ) {
	i64 ax = 1;
	while ( n ) {
		if ( n & 1 )
			ax *= x, ax %= MOD;
		x *= x, x %= MOD, n >>= 1;
	}
	return ax % MOD;
}

i64 divBy6( i64 k ) {
	i64 a = k,
		b = k-1,
		c = 2*k-1,
		res = 1;
	if ( k&1 )
		res = (a*(b/2)) % MOD;
	else
		res = ((a/2)*b) % MOD;
	res %= MOD, res *= (c % MOD), res %= MOD;
	res *= 27, res %= MOD; res *= mpow(11111111LL,2), res %= MOD;
	return res;
}

u64 Sqrt( u64 n ) {
	u64 low,high,mid;
	if ( n == 0 )
		return 0;
	for ( low = 1, high = (1ULL << 32); low+1 != high; ) {
		mid = (low+high)/2;
		if ( mid*mid <= n )
			low = mid;
		else high = mid;
	}
	return low;
}

int main() {
	i64 ax,p,w,ww,q,r;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	while ( 1 == scanf("%lld",&n) && n > 0 ) {
		if ( n < 0 ) {
			puts("0");
			continue ;
		}
		m = (n-1)/2, L = (i64)(Sqrt(2*m+1));
		p = (L/2)%MOD, ax = p*p, ax %= MOD;
		q = L/2, r = L&1;
		p = ((2*q*q) % MOD)+((2*q*r) % MOD), p %= MOD;
		/*p = (i64)ceil((L*L-1.0)/2.0);*/
		ax += ((L%MOD)*((m-p+1)%MOD))%MOD, ax %= MOD;
		ax += divBy6(L);
		while ( ax < 0 ) ax += MOD;
		printf("%lld\n",ax % MOD);
	}
	return 0;
}
