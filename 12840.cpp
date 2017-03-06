/*
 * 12840. The Archery Puzzle
 * TOPIC: backtracking
 * status: 
 */
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <iostream>
#define N 0x40
#define M 0x200
#define oo 0xfffffffful
using namespace std;

int ts,cs,b[N],n,m,c[M],best,a[M];
unsigned int z[N][M];

void f( int idx, int targ, int k ) {
	int i,j,l,better = 0;
	if ( k > best ) return ;
	if ( !targ ) {
		if ( best > k ) {
			for ( best = k, i = 0; i < k; ++i ) a[i] = c[i];
			return ;
		}
		for ( i = 0; i < k; ++i )
			if ( c[i] > a[i] ) { better = 1; break ; }
			else if ( c[i] < a[i] ) break ;
		if ( better )
		for ( i = 0; i < k; ++i )
			a[i] = c[i];
		return ;
	}
	if ( idx >= n ) return ;
	assert( targ >= 1 );
	for ( j = targ/b[idx]; j >= 0; --j ) {
		for ( c[k] = b[idx], l = k+1; l <= k+j-1; ++l )
			c[l] = c[k];
		f(idx+1,targ-b[idx]*j,k+j);
	}
}

int main() {
	int i,j,k;
	for ( scanf("%d",&ts); ts--; ) {
		for ( scanf("%d %d",&n,&m), i = 1; i <= n; ++i )
			scanf("%d",&b[n-i]);
		best = (1<<29), f(0,m,0);
		if ( best == (1<<29) ) {
			printf("Case %d: impossible\n",++cs);
			continue ;
		}
		printf("Case %d: [%d]",++cs,best);
		for ( i = 0; i < best; ++i )
			printf(" %d",a[i]);
		puts("");
	}
	return 0;
}

