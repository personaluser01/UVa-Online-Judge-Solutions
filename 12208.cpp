/*
 * 12208. How Many Ones Needed?
 * TOPIC: dp
 * status: Accepted
 */
#include <cassert>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#define N 0x40
using namespace std;
typedef long long i64;

i64 a,b,c[N][N],z[N];

i64 bin2dec( i64 *d, int n ) {
	i64 res = 0,i;
	for ( i = 0; i < n; ++i )
		res |= (d[i]<<i);
	return res;
}

i64 g( i64 *d, int n ) {
	i64 res = 0,k;
	if ( n == 1 ) 
		return 0;
	assert( n >= 2 );
	if ( d[n-1] ) res += z[n-1]+bin2dec(d,n-1);
	return res+g(d,n-1);
}

i64 f( i64 a ) {
	i64 res = 0,d[N] = {0},i,j,k,n;
	if ( a < 0 ) a = 0;
	if ( a == 0 ) return res;
	for ( n = 33, i = 0; i < n; ++i )
		d[i] = ((a>>i)&1);
	return g(d,33);
}

i64 bts( i64 u ) {
	return (!u)?0:(u&1)+bts(u>>1);
}

int main() {
	int i,j,k,cs = 0;
	for ( i = 0; i < N; ++i ) c[i][0] = 1LL;
	for ( i = 1; i < N; ++i )
		for ( j = 1; j <= i; ++j )
			c[i][j] = c[i-1][j] + c[i-1][j-1];
	for ( k = 0; k < N; ++k )
		for ( i = 0; i <= k; ++i )
			z[k] += i*c[k][i];
	for(;2==scanf("%lld %lld",&a,&b)&&(a||b)&&printf("Case %d: %lld\n",++cs,f(b)+bts(b)-f(a)););
	return 0;
}

