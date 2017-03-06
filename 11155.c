/*
 * 11155. Be Efficient
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <limits.h>
#include <float.h>
typedef long long i64;
#define N 10100
#define MOD 10100

i64 A,B,C,M,ts,n,x[N],cs,pref[N],cnt[MOD],ax;

int main() {
	int i,j,k,l,t,idx,low,high,mid;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( scanf("%lld",&ts); ts--; printf("Case %lld: %lld\n",++cs,ax) ) {
		scanf("%lld %lld %lld %lld %lld",&A,&B,&C,&M,&n);
		for ( 1[x] = A, i = 2; i <= n; x[i] = ((x[i-1]*B+C) % M)+1, ++i );
		for (i=0;i<M;++i)cnt[i]=0;
		for ( i = 1; i <= n; ++i )
			++cnt[pref[i]=(pref[i-1]+x[i])%M];
		for ( ax = cnt[0], k = 0; k < M; ++k ) 
			ax += (cnt[k]*(cnt[k]-1))/2;
	}
	return 0;
}

