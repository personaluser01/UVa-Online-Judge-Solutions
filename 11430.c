/*
 * 11430. ETS Problem Setting
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
#define MOD 100000000ULL
typedef unsigned long long u64;

int n;
u64 C[N][N],ax;

u64 R( u64 x ) { return x < MOD ? x : (x%MOD); }

int main() {
	i64 x,y,c,m,i,j,k;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( i = 0; i < N; C[i++][0] = 1 );
	for ( i = 1; i < N; ++i )
		for ( j = 1; j <= i; ++j )
			C[i][j] = R(C[i-1][j]+C[i-1][j-1]);
	for (;1 == scanf("%d",&n) && n; printf("%llu\n",R(ax)) ) 
		for ( ax = 0, c = 0; c <= n; ++c )
			for ( y = 0; c+y <= n; ++y ) 
				if ( (c+y) && 0 == ((m = (n-c-y)*c)%(c+y)) && (x = m/(c+y))+c+y <= n && (x+c) ) 
					ax += R(R(C[n][c]*C[n-c][y])*C[n-c-y][x]);
	return 0;
}
