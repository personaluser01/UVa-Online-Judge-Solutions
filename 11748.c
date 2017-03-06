/*
 * 11748. Rigging Elections
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

int n,m,cand,
	g[N][N],idx[N][N],
	who[N][N],cnt[N];
unsigned char c[N][N];

int main() {
	int i,j,k,l,t;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for (;3==scanf("%d %d %d",&n,&m,&cand)&&(n||m||cand);) {
		for ( --cand, i = 0; i < m; ++i )
				for ( j = 0; j < n; ++j )
					scanf("%d",g[i]+j), idx[--g[i][j]][i] = j;
		for ( i = 0; i < n; ++i )
			for ( j = i+1; j < n; ++j ) {
				cnt[i] = cnt[j] = 0;
				for ( k = 0; k < m; ++k )
					if ( idx[i][k] < idx[j][k] )
						++cnt[i];
					else ++cnt[j];
				assert( cnt[i] != cnt[j] );
				if ( cnt[i] > cnt[j] )
					who[j][i] = who[i][j] = i;
				else who[j][i] = who[i][j] = j;
			}
		for ( i = 0; i < n; ++i )
			for ( c[i][i] = 0, j = 0; j < n; ++j )
				if ( i != j ) {
					if ( who[i][j] == i )
						c[i][j] = 1, c[j][i] = 0;
					else c[i][j] = 0, c[j][i] = 1;
				}
		for ( k = 0; k < n; ++k )
			for ( i = 0; i < n; ++i )
				for ( j = 0; j < n; ++j )
					c[i][j] |= (c[i][k]&c[k][j]);
		for ( j = 0; j < n; ++j )
			if ( j != cand &&  !c[cand][j] ) {
				puts("no");
				goto next;
			}
		puts("yes"); continue ;
next:;
	}
	return 0;
}
