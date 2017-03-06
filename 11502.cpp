/*
 * 11502. Rocket Stages
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <limits.h>
#include <float.h>
#define N 0x400
typedef long long i64;
#define oo (DBL_MAX-0x400)
#define G (9.8)
#define W 100001
#include <iostream>
#include <queue>
#include <vector>
#include <set>
using namespace std;

int n;
i64 S[N],L[N],T[N],C[N];
long double z[N][W],v,cand;

int main() {
	i64 i,j,k,w,ts;
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	for ( scanf("%lld",&ts); ts--; ) {
		assert( 1 == scanf("%d",&n) );
		for ( i = 1; i <= n; ++i ) 
			assert( 4 == scanf("%lld %lld %lld %lld",S+i,L+i,T+i,C+i) );
		for ( i = 1; i <= n+1; ++i )
			for ( j = 0; j < W; ++j )
				z[i][j] = +oo;
		for ( z[0][0] = 0, k = 0; k <= n-1; ++j )
			for ( w = 0; w < W; ++w )
				if ( z[k][w] < +oo ) {
					if ( w+L[k+1]+S[k+1] >= W )
						continue ;
					cand = z[k][w] + T[k+1]*(log(w+L[k+1]+S[k+1])-log(w+S[k+1]))/C[k+1];
					if ( z[k+1][w+L[k+1]+S[k+1]] == +oo || z[k+1][w+L[k+1]+S[k+1]] > cand )
						z[k+1][w+L[k+1]+S[k+1]] = cand;
				}
		for ( v = -1, w = 0; w < W; ++w )
			if ( z[n][w] < +oo && z[n][w] > v )
				v = z[n][w];
		printf("%Lf\n",v);
	}
	return 0;
}

