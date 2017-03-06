/*
 * 11851. Celebrity Split
 * TOPIC: branch and bound, backtracking, heuristics, greedy
 * status: Accepted
 */
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 24
typedef long long i64;

int n;
i64 c[N],s[N],ret;

void dfs( int idx, i64 x, i64 y, i64 d ) {
	if ( idx == n && x == y && ret > d ) ret = d;
	if ( d >= ret || idx == n ) return ;
	if ( labs(x-y) > s[idx] ) return ;
	dfs(idx+1,x+c[idx],y,d), dfs(idx+1,x,y+c[idx],d), dfs(idx+1,x,y,d+c[idx]);
}

int main() {
	int i,j,k;
	i64 t;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for (;1 == scanf("%d",&n) && n;) {
		for ( i = 0; i < n; ++i )
			scanf("%lld",c+i);
		for ( j = 1; j; )
			for ( i = j = 0; i < n-1; ++i )
				if ( c[i] < c[i+1] )
					++j, t = c[i], c[i] = c[i+1], c[i+1] = t;
		for ( s[n] = 0, i = n-1; i >= 0; --i )
			s[i] = s[i+1]+c[i];
		ret = (1LL<<60), dfs(0,0,0,0), printf("%lld\n",ret);
	}
	return 0;
}

