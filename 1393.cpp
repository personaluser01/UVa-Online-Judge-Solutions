/*
 * 1393. Network
 * TOPIC: dp, combinatorics, counting
 * status: Accepted
 */
#include <algorithm>
#include <cstdio>
#include <iostream>
#define N 0x200
typedef long long i64;
using namespace  std;

i64 g[N][N],m,n;

int main() {
	i64 i,j,k,ans;
	for ( i = 1; i < N; ++i )
		for ( j = 1; j < N; ++j )
			g[i][j] = __gcd(i,j);
	while ( 2 == scanf("%lld %lld",&m,&n) && (m||n) ) {
		for ( ans = 0, i = 1; i < m; ++i )
			for ( j = 1; j < n; ++j ) {
				if ( g[i][j] != 1 ) continue ;
				k = (m-i)*(n-j);
				k -= max(0LL,m-2*i)*max(0LL,n-2*j);
				ans += k;
			}
		printf("%lld\n",ans*2);
	}
	return 0;
}

