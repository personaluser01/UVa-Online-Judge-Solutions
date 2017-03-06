/*
 * 11264. Coin Collector
 * TOPIC: greedy, excellent interview question, spotting the pattern
 * status: Accepted
 */
#include <cassert>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <set>
#define N 0x400
#define oo (1LL<<62)
#include <map>
#include <queue>
typedef long long i64;
using namespace std;

int n;
i64 c[N],z[N];
queue<int> q;

int main() {
	int i,j,k,ts;
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	for ( scanf("%d",&ts); ts-- && 1 == scanf("%d",&n); ) {
		for ( i = 1; i <= n; ++i )
			scanf("%lld",&c[i]), z[i] = +oo;
		for ( c[n+1] = +oo, z[1] = 1, i = 2, k = 2; i <= n; ) {
			for ( ;z[k-1]+c[i] >= c[i+1]; ++i );
			z[k] = z[k-1]+c[i++], ++k;
		}
		printf("%d\n",k-1);
	}
	return 0;
}


