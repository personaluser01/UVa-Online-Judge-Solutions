/*
 * 12961. Lottery
 * TOPIC: systems of linear equations, gauss elimination modulo 2, matrix rank
 * status: Accepted
 */
#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>
#define N (1<<15)
#define M (1<<6)
using namespace std;

int a[M][N],m,n;

bool find_pivot( int k, int &r, int &c ) {
	for ( int i = k; i < m; ++i )
		for ( int j = k; j < n; ++j )
			if ( a[i][j]&=1 ) {
				r = i, c = j;
				return true ;
			}
	return false ;
}

void swap_rows(int i1,int i2) {
	for ( int j = 0; j < n; ++j )
		swap(a[i1][j],a[i2][j]);
}
void swap_cols( int j1, int j2 ) {
	for ( int i = 0; i < m; ++i )
		swap(a[i][j1],a[i][j2]);
}

int main() {
	int i,j,k,l,row,col,rank;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for (;2 == scanf("%d %d",&n,&m) && (m||n);) {
		for ( j = 0; j < n; ++j )
			for ( i = 0; i < m; ++i )
				scanf("%d",&a[i][j]), a[i][j]&=1;
		/*if ( m > n ) { puts("S"); continue ; }
		assert( m <= n );*/

			for ( rank = m, k = 0; k < m; ++k ) {
				if ( !find_pivot(k,row,col) ) {
					rank = k;
					break ;
				}
				swap_cols(k,col), swap_rows(k,row);
				for ( i = k+1; i < m; ++i )
					if ( a[i][k] ) {
						for ( l = k; l < n; ++l )
							a[i][l] ^= a[k][l];
						assert( !a[i][k] );
					}
			}
		if (rank < m)	puts("S");
		else {
			if (n > rank)	puts("N");	// for zeroes
			else			puts("S");
		}

			//puts(rank==m?"N":"S");

	}
	return 0;
}

