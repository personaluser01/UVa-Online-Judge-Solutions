/*
 * 13021. Game of Cards
 * TOPIC: sprague-grundy, nim, nimbers, xor
 * status: Accepted
 */
#include <assert.h>
#include <algorithm>
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <set>
#define MAXK 11
#define M 0x80
#define N 0x400
#define oo (1<<29)
using namespace std;

int m,n[M],c[M][N],z[M][N],K;

int calc_z( const int pile, int left ) {
	int i;
	if ( z[pile][left] < +oo )
		return z[pile][left];
	set<int> s;
	assert( left <= n[pile] );
	s.clear();
	for ( i = 0; i <= K && i <= left; ++i ) {
		int face = c[pile][left-i];
		if ( face <= left-i ) 
			s.insert(calc_z(pile,left-i-face));
	}
	for ( i = 0; s.count(i); ++i );
	assert( !s.count(i) );
	return z[pile][left] = i;
}

int main() {
	int i,j,ans;
#ifndef ONLINE_JUDGE
	freopen("13021.in","r",stdin);
#endif
	for(;2==scanf("%d %d",&m,&K)&&(m||K);) {
		for(i=0;i<m;++i) 
			for ( c[i][0] = +oo, scanf("%d",n+i), j=1; j <= n[i]; scanf("%d",&c[i][j++]) );
		for ( i = 0; i < m; ++i )
			for ( j = 0; j <= n[i]; z[i][j++] = +oo );
		for ( ans = calc_z(0,n[0]), i = 1; i < m; ans ^= calc_z(i,n[i]), ++i );
		puts(ans?"Alice can win.":"Bob will win.");
	}
	return 0;
}

