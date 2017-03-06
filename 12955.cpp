/*
 * 12955. Factorial
 * TOPIC: dp, trivial
 * status: Accepted
 */
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>
#define N 21
#define Q 100100
#define oo 0xfffffffful
using namespace std;

unsigned long long f[N];
unsigned int dp[Q];
int n;

int main() {
	int i,j,k;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( f[0] = 1, i = 1; i < N; ++i )
		f[i] = f[i-1]*((unsigned long long )i);
	memset(dp,0xff,sizeof dp);
	for ( dp[0]=0, k = 1; k < Q; ++k )
		for ( i = 1; i < N && f[i] <= k; ++i )
			if ( dp[k-f[i]] < +oo && dp[k] > dp[k-f[i]]+1 )
				dp[k] = dp[k-f[i]]+1;
	for(;1==scanf("%d",&n) && n>0; ) {
		printf("%u\n",dp[n]);
	}
	return 0;
}

