/*
 * 11502. Rocket Stages
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
#define N 0x400
typedef long long i64;
#define oo (DBL_MAX-0x400)
#define G (9.8)
#define W 10001
#define tol 1e-9
#define A(x) ((x)<0?-(x):(x))

int n;
i64 S[N],L[N],T[N],C[N];
long double z[N][W],v,cand;

i64 nearest( long double x ) {
	i64 dx = (i64)(x),
		ux = dx+1;
	return (x-dx)<(ux-x)?dx:ux;
}

int main() {
	i64 i,j,k,w,ts,t;
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	for ( scanf("%lld",&ts); ts-- && 1 == scanf("%d",&n); ) {

		for ( i = 1; i <= n; ++i ) 
			assert( 4 == scanf("%lld %lld %lld %lld",S+i,L+i,T+i,C+i) );

		for ( i = 0; i <= n+1; ++i )
			for ( j = 0; j < W; ++j )
				z[i][j] = +oo;
		for ( z[0][0] = 0, k = 0; k <= n-1; ++k ) {
			for ( w = 0; w < W; ++w ) {
				if ( z[k][w] < +oo ) {
					if ( A(z[k+1][w]-oo) < tol || z[k+1][w] < z[k][w] )
						z[k+1][w] = z[k][w];
					if ( w+L[k+1]+S[k+1] >= W )
						continue ;
					if ( 10*T[k+1] < 98*(w+L[k+1]+S[k+1]) )
						continue ;
					cand = z[k][w] + (T[k+1]*(log(w+L[k+1]+S[k+1])-log(w+S[k+1])))/C[k+1] - (L[k+1]*G)/C[k+1];
					if ( A(z[k+1][w+L[k+1]+S[k+1]]-oo) < tol || z[k+1][w+L[k+1]+S[k+1]] < cand ) 
						z[k+1][w+L[k+1]+S[k+1]] = cand;
				}
			}
		}
			for ( v = -1, w = 0; w < W; ++w )
				if ( z[n][w] < +oo && z[n][w] > v )
					v = z[n][w];
		printf("%lld\n",nearest(v));
	}
	return 0;
}

