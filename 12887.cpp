/*
 * 12887. The Soldier's Dilemma
 * TOPIC: combinatorics
 * status: Accepted
 */
#include <bits/stdc++.h>
#define N 5001
#define MOD 1000000007LL
typedef long long i64;

i64 n,z[N];

int main() {
	int i,j,k,ts;
#ifndef ONLINE_JUDGE
	freopen("12887.in","r",stdin);
#endif
	for ( z[0] = 1LL, n = 1; n < N; ++n )
		for ( k = 0; k <= n-1; ++k )
			if ( (z[n] += z[k]*z[n-1-k]) >= MOD )
				z[n] %= MOD;
	for ( scanf("%d",&ts); ts-- && 1 == scanf("%lld",&n); printf("%lld\n",z[n]) );
	return 0;
};

