/*
 * 11542. Square
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
#define N 0x80
#define M 0x200

unsigned char a[(M >> 3)+8];
#define SET(k) (a[(k)>>3] |= (1UL << ((k) & 7)))
#define CLR(k) (a[(k)>>3] &= ~(1UL << ((k) & 7)))
#define TST(k) (a[(k)>>3] & (1UL << ((k) & 7)))
#define xchg(x,y) (((x)==(y))||((x)^=(y),(y)^=(x),(x)^=(y)))

typedef long long i64;
int n,m;
i64 c[N],p[M],A[N][M],u;

int find_pivot( int k, int *row, int *col ) {
	int i,j;
	for ( i = k; i < m; ++i )
		for ( j = k; j < n; ++j )
			if ( A[*row = i][*col = j] ) 
				return 1;
	return 0;
}

int max( int x, int y ) { return x < y ? y : x; }

int main() {
	int i,j,k,ts,row,col;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( i = 3; i < M; SET(i), i += 2 );
	for ( SET(2), i = 3; i < M; i += 2 )
		for ( j = i+i; j < M && TST(i); CLR(j), j += i );
	for ( i = 2; i < M; ++i )
		if ( TST(i) ) p[m++] = i;
	for ( scanf("%d",&ts); ts-- && 1 == scanf("%d",&n); ) {
		for ( i = 0; i < n; ++i )
			for ( j = 0; j < m; A[j++][i] = 0 );
		for ( i = 0; i < n; ++i ) 
			for ( scanf("%lld",c+i), u = c[i], j = 0; j < m && p[j] <= u; ++j )
				for (;!(u % p[j]); u /= p[j], ++A[j][i], A[j][i] &= 1 );
		for ( k = 0; k < n && k < m && find_pivot(k,&row,&col); ++k ) {
			for ( j = 0; j < n; ++j )
				xchg(A[row][j],A[k][j]);
			for ( i = 0; i < m; ++i )
				xchg(A[i][col],A[i][k]);
			assert( A[k][k] );
			for ( i = k+1; i < m; ++i ) {
				if ( !A[i][k] ) continue ;
				for ( j = k; j < n; A[i][j] -= A[k][j], A[i][j] += 4, A[i][j++] &= 1 );
				assert( !A[i][k] );
			}
		}
		for ( k = 0; k < n && k < m && A[k][k]; ++k );
		printf("%llu\n",(1ULL<<(n-k))-1ULL);
	}
	return 0;
}
