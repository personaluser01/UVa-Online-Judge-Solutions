/*
 * 11766. Racing Car Computer
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 0x400
#define oo (1>>15)

int min( int x, int y ) { return x < y ? x : y; }
int max( int x, int y ) { return x > y ? x : y; }

int n,ts,m,ans,cs,cnt[N][N],z[N];

int main() {
	int i,j,k,l,t,s;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	while ( 1 == scanf("%d",&n) && n ) {
		for ( i = 0; i <= n+1; ++i )
			for ( j = 0; j <= n+1; cnt[i][j++] = 0 );
		for ( m = 1; m <= n; ++m ) 
			scanf("%d %d",&i,&j), ++cnt[i = min(i,n)][j = min(j,n)];
		for ( m = 0; m <= n; z[m++] = 0 );
		for ( t = n; t >= 1; --t ) 
			for ( k = 1; k <= t; ++k )
				z[t-k] = max(z[t-k],min(k,cnt[t-k][n-t])+z[t]);
		printf("Case %d: %d\n",++cs,n-z[0]);
	}
	return 0;
}

