/*
 * 10951. Polynomial GCD
 */
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;
#define N 0x100
typedef long long i64;

i64 c[2][N],n[2];

void divide_poly( i64 *c

int main() {
	int i,j,k,t,cs = 0;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	while ( 1 == scanf("%d",&MOD) && (MOD) ) {
		for ( t = 0; t <= 1; ++t ) 
			for ( scanf("%lld",n+t), i = 0; i < n[t]; c[t][n-i-1] %= MOD, ++i )
				for ( scanf("%lld",c[t]+n-i-1); c[t][n-i-1] < 0; c[t][n-i-1] += MOD );
		printf("Case %d: ",++cs);
	}
	return 0;
}

