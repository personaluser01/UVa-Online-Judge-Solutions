/*
 * 12712. Pattern Locker
 * TOPIC: binomial coefficients
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
#define MOD 10000000000007LL
#define N 0x80
#define Q (1 << 14)
using namespace std;
typedef unsigned long long u64;
typedef long long i64;

int ts,cs,n,a,b;
u64 f[Q],g[Q];
i64 pref[Q];

void ext_euclid( i64 x, i64 y, i64 *a, i64 *b, i64 *d ) {
	if ( !y ) { *a = 1LL, *b = 0, *d = x; return; }
	ext_euclid(y,x%y,b,a,d), *b -= (x/y)*(*a);
}

i64 inv( i64 x, i64 p ) {
	i64 a,b,d;
	ext_euclid(x,p,&a,&b,&d);
	for(;d < 0; d += p);
	d %= p;
	assert( d == 1 );
	for ( a %= p; a < 0; a += p );
	return a%p;
}

i64 norm( i64 x ) {
	for( x %= MOD; x < 0; x += MOD );
	return x;
}

int main() {
	i64 i,j,k,ax,s;
#ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
#endif
	for(f[0]=1,i=1;i<Q;++i)
		f[i]=norm(f[i-1]*i);
	for ( scanf("%d",&ts); ts-- && 3 == scanf("%d %d %d",&n,&a,&b) && printf("Case %d: ",++cs); ) {
		for ( s = 1LL, k = n*n-a+1; k <= n*n; ++k ) s = norm(s*k);
		for ( ax = s, k = n*n-a; k >= n*n-b+1; --k ) {
			s = norm(s*k), ax += s, ax = norm(ax);
		}
		printf("%lld\n",ax);
	}
    return 0;
}

