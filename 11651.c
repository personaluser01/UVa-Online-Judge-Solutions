/*
 * 11651. Kyrpton Number System
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
typedef unsigned long long u64;
#define MASK ((1ULL<<32)-1ULL)
#define MOD MASK
#define N 0x100
#define is_base(i) (0<=(i) && (i)<B)

i64 n,B;
u64 A[N][N],tmp[N][N],E[N][N];
int V,last[N],tail[N];

int main() {
	int i,j,k,t,ts,cs = 0,x,y,l;
	u64 w;
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	for(scanf("%d",&ts);ts--&&2==scanf("%lld %lld",&B,&n)&&printf("Case %d: ",++cs);) {
		memset(A,0,sizeof(A));
		for ( i = 0; i < B-1; ++i )
			A[i][i+1] = A[i+1][i] = 1, last[i] = i, tail[i] = 0;
		last[B-1] = B-1, tail[B-1] = 0;
		for ( V = B, k = 2; k < B; ++k ) 
			for ( t = k*k-1, i = 0; (j = i+k) < B; ++i ) {
				for ( x = last[i], l = 0; l < t-tail[i]; ++l, x = y )
					last[i] = y = V++, A[x][y] = 1;
				tail[i] = t;
				A[last[i]][j] = 1;
				for ( x = last[j], l = 0; l < t-tail[j]; ++l, x = y )
					last[j] = y = V++, A[x][y] = 1;
				tail[j] = t;
				A[last[j]][i] = 1;
			}
		assert( V < N );
		for ( i = 0; i < V; ++i )
			for ( E[i][i] = 1, j = i+1; j < V; ++j )
				E[i][j] = E[j][i] = 0;
		for(;n;n >>= 1) {
			if (n&1) {
				for ( i = 0; i < V; ++i )
					for ( j = 0; j < V; ++j ) {
						tmp[i][j] = 0;
						for ( k = 0; k < V; ++k )
							tmp[i][j] += ((E[i][k]*A[k][j]) & MOD), tmp[i][j] &= MOD;
					}
				for ( i = 0; i < V; ++i )
					for ( j = 0; j < V; ++j )
						E[i][j] = tmp[i][j];
			}
			for ( i = 0; i < V; ++i )
				for ( j = 0; j < V; ++j ) {
					tmp[i][j] = 0;
					for ( k = 0; k < V; ++k )
						tmp[i][j] += ((A[i][k]*A[k][j]) & MOD), tmp[i][j] &= MOD;
				}
			for ( i = 0; i < V; ++i )
				for ( j = 0; j < V; ++j )
					A[i][j] = tmp[i][j];
		}
		for ( w = 0, i = 1; i < B; ++i )
			for ( w += E[i][i], w &= MOD, j = 0; j < B; ++j )
				if ( i != j ) 
					w += E[i][j], w &= MOD;
		printf("%llu\n",w);
	}
	return 0;
}

