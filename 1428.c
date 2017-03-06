/*
 * 1428. Ping-pong
 * TOPIC: fenwick trees
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 20100
#define S (1<<17)
#define L(x) ((x)&((~(x))+1))
typedef long long i64;

int n,a[N],K=S;
i64 ans,dp[N],t[S],DP[S];

void update( unsigned int idx, int dt ) {
	for ( ;idx < K; t[idx] += dt, idx += L(idx) );
}

i64 prefix( unsigned int idx ) {
	i64 s = 0;
	for ( ;idx; s += t[idx], idx &= ~L(idx) );
	return s;
}

int main() {
	int i,j,k,ts;
#ifndef ONLINE_JUDGE
	freopen("a.txt","r",stdin);
#endif
	for ( scanf("%d",&ts); ts-- && 1 == scanf("%d",&n); ) {
		for ( i = 0; i < K; t[i++] = 0 );
		for ( i = 0; i < n; scanf("%d",&a[i]), dp[i] = prefix(a[i]), DP[i] = prefix(K-1)-prefix(a[i]-1), update(a[i++],1) );
		for ( i = 0; i < K; t[i++] = 0 );
		for ( ans = 0, i = n-1; i >= 0; --i ) 
			ans += dp[i]*(prefix(K-1)-prefix(a[i]-1)), ans += prefix(a[i])*DP[i], update(a[i],1);
		printf("%lld\n",ans);
	}
	return 0;
}

