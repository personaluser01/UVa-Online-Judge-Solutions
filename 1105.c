/*
 * 1105. Coffee Central
 * TOPIC: DP
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 0x400
#define oo (1<<29)

int c[N][N],m,n,shops,qr,z[N][N];

int main() {
	int i,j,k,l,t,cs = 0,best_i,best_j,w;
	while(4==scanf("%d %d %d %d",&m,&n,&shops,&qr)){
		if ( !m && !n && !shops && !qr ) break ;
		printf("Case %d:\n",++cs);
		for ( i = 0; i <= m; ++i )
			for ( j = 0; j <= n; c[i][j++]=0 );
		for ( k = 0; k < shops; ++k )
			scanf("%d %d",&i,&j), ++c[i][j];
		for ( i = 1; i <= m; ++i )
			for ( j = 1; j <= n; ++j )
				z[i][j] = z[i-1][j]+z[i][j-1]-z[i-1][j-1]+c[i][j];
		while ( qr-- && 1 == scanf("%d",&k) ) {
			k <<= 1, ++k;
			if ( k > m ) k = m;
			if ( k > n ) k = n;
			for ( w = -oo, i = 1; i+k-1 <= m; ++i )
				for ( j = 1; j+k-1 <= n; ++j )
					if ( z[i+k-1][j+k-1]-z[i-1][j+k-1]-z[i+k-1][j-1]+z[i-1][j-1] > w ) {
						w = z[i+k-1][j+k-1]-z[i-1][j+k-1]-z[i+k-1][j-1]+z[i-1][j-1];
						best_i = i, best_j = j;
					}
					else if ( z[i+k-1][j+k-1]-z[i-1][j+k-1]-z[i+k-1][j-1]+z[i-1][j-1] == w && (best_i < i || best_i == i && best_j > j) ) 
						best_i = i, best_j = j;
			printf("%d (%d,%d)\n",w,best_i,best_j);
		}
	}
	return 0;
}

