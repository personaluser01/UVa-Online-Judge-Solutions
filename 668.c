/*
 * 668. Parliament
 * status: Accepted
 * TOPIC: DP, sqrt, partitioning
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <float.h>
#define oo (DBL_MAX-1024)
#define tol 1e-9
#define N 0x400

double z[N][N],L[N],S[2*N];
int n,way[N][N],*top,st[N];

double calc_z( int n, int k ) {
	int m,r = S[2*n];
	if ( z[n][k] > -oo )
		return z[n][k];
	if ( k > n )
		return z[n][k] = calc_z(n,n);
	assert( k <= n );
	if ( n <= 4 ) {
		if ( k == n )
			return z[n][k] = L[n];
		return z[n][k] = -oo;
	}
	assert( k >= 0 );
	for ( m = k; m >= r; --m ) 
		if ( calc_z(n-m,m-1) > -oo && z[n][k] < L[m]+calc_z(n-m,m-1) )
			z[n][k] = L[m]+calc_z(n-m,m-1), way[n][k] = m;
	return z[n][k];
}

void dump( int n, int k ) {
	if ( n <= 4 ) { *++top = n; return ; }
	*++top = way[n][k], dump(n-way[n][k],way[n][k]-1);
}

int main() {
	int i,j,k,ts;
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	for ( i = 1; i < N; ++i ) L[i] = log(i);
	for ( i = 1; i < 2*N; ++i )
		S[i] = sqrt(i);
	for ( scanf("%d",&ts); ts-- && 1 == scanf("%d",&n); ) {
		for ( i = 0; i < N; ++i )
			for ( j = 0; j < N; z[i][j++] = -oo );
		z[1][1] = 0, z[2][2] = log(2), z[3][3] = log(3), z[4][4] = log(4);
		assert( n >= 5 );
		calc_z(n,n), top = st, dump(n,n);
		for ( i = 0; top > st; )
			if ( ++i > 1 )
				printf(" %d",*top--);
			else printf("%d",*top--);
		putchar('\n');
		if ( ts ) putchar('\n');
	}
	return 0;
}

