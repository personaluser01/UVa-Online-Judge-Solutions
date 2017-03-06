/*
 * 11551. Experienced Endeavour
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
#define N 64
#define MOD 1000LL
typedef long long i64;

i64 D,A[N][N],c[N],x[N],R[N][N],r[N][N];
int n;

int main() {
	int i,j,k,ts;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( scanf("%d",&ts); ts--; ) {
		scanf("%d %lld",&n,&D);
		for ( i = 0; i < n; ++i ) scanf("%lld",c+i);
		for ( i = 0; i < n; ++i )
			for ( j = 0; j < n; ++j )
				R[i][j] = A[i][j] = 0;
		for ( i = 0; i < n; ++i ) 
			for ( scanf("%d",&k); k--; ) 
				scanf("%d",&j), A[i][j] = 1;
		for ( i = 0; i < n; ++i ) R[i][i] = 1;
		for ( ;D; D >>= 1 ) {
			if ( D & 1 ) {
				for ( i = 0; i < n; ++i )
					for ( j = 0; j < n; ++j )
						for ( r[i][j] = 0, k = 0; k < n; ++k )
							r[i][j] += R[i][k]*A[k][j], r[i][j] %= MOD;
				for ( i = 0; i < n; ++i )
					for ( j = 0; j < n; ++j )
						R[i][j] = r[i][j];
			}
			for ( i = 0; i < n; ++i )
				for ( j = 0; j < n; ++j )
					for ( r[i][j] = 0, k = 0; k < n; ++k )
						r[i][j] += A[i][k]*A[k][j], r[i][j] %= MOD;
			for ( i = 0; i < n; ++i )
				for ( j = 0; j < n; ++j )
					A[i][j] = r[i][j];
		}
		for ( i = 0; i < n; ++i ) 
			for ( x[i] = 0, j = 0; j < n; ++j )
				x[i] += R[i][j]*c[j], x[i] %= MOD;
		for ( i = 0; i < n-1; ++i )
			printf("%lld ",x[i]);
		printf("%lld\n",x[i]);
	}
	return 0;
}
