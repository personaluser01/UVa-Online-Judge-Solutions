/*
 * 10290. {Sum += +i++} to reach n
 * TOPIC: maths
 * status: Accepted
 */
#include <cassert>
#include <cstdio>
#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <cmath>
#include <vector>
using namespace std;
typedef long long i64;
#define N (1<<21)

bool isprime[N];
int m;
i64 *p;
i64 n;

void sieve() {
	int i,j,k;
	for ( i = 3; i < N; i += 2 )
		isprime[i]=true;
	for ( isprime[2]=true, i = 3; i < N; i += 2 )
		for ( j = i+i; j < N && isprime[i]; j += i )
			isprime[j]=false;
	for ( m = 0, i = 2; i < N; ++i )
		if ( isprime[i] && ++m );
	p = (i64 *)malloc(m*sizeof *p);
	for ( k = 0, i = 2; i < N; ++i )
		if ( isprime[i] )
			p[k++] = i;
	assert( k == m );
}

i64 f( i64 n ) {
	int i,k;
	i64 ax = 1LL;
	for ( i = 0; i < m && p[i] <= n/p[i]; ++i, ax *= (k+1) )
		for ( k = 0; !(n%p[i]); ++k, n /= p[i] );
	if ( n > 1 ) return ax *= 2;
	return ax;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
#endif
	for ( sieve(); 1 == scanf("%lld",&n); ) {
		for ( ;!(n&1); n >>= 1 );
		printf("%lld\n",f(n));
	}
    return 0;
}

