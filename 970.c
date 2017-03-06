/*
 * 970. Particles
 * TOPIC: dp, trivial
 * status: Accepted
 */
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 0x80

int n,g[3][3] = {{1,0,2},{0,1,1},{2,1,0}},z[N][N][3];
char s[N];

int main() {
	int i,j,k,t,x,y,ts;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( scanf("%d",&ts); ts--; ) {
		scanf("%s",s), n = strlen(s);
		for ( i = 0; i < n; ++i )
			for ( j = 0; j < n; ++j )
				for ( k = 0; k < 3; ++k )
					z[i][j][k] = 0;
		for ( i = 0; i < n; ++i )
			z[i][i][s[i]-'X'] = 1;
		for ( k = 2; k <= n; ++k )
			for ( i = 0; (j = i+k-1) < n; ++i ) 
				for ( t = i; t <= j-1; ++t ) {
					for ( x = 0; x < 3; ++x )
						if ( z[i][t][x] )
							for ( y = 0; y < 3; ++y )
								if ( z[t+1][j][y] )
									z[i][j][g[x][y]] = 1;
					if ( z[i][j][0] && z[i][j][1] && z[i][j][2] )
						break ;
				}
		if ( z[0][n-1][2] ) puts("Z"); else if ( z[0][n-1][1] ) puts("Y"); else puts("X");
	}
	return 0;
}

