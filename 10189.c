/*
 * 10189. Minesweeper
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define N 0x80
#define vc(x,y) (0<=(x)&&(x)<m&&0<=(y)&&(y)<n)

int m,n,c[N][N],cs;
char g[N][N];

int main() {
	int i,j,k,l,t,ni,nj;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	while ( 2 == scanf("%d %d",&m,&n) && (m||n) ) {
		if ( ++cs > 1 ) putchar('\n');
		for ( i = 0; i < m; scanf("%s",g[i++]) );
		for ( i = 0; i < m; ++i )
			for ( j = 0; j < n; ++j )
				if ( g[i][j] == '.' ) {
					for ( c[i][j] = 0, k = -1; k <= 1; ++k )
						for ( t = -1; t <= 1; ++t ) {
							ni = i+k, nj = j+t;
							if ( vc(ni,nj) && g[ni][nj] == '*' && ++c[i][j] );
						}
				}
		printf("Field #%d:\n",cs);
		for ( i = 0; i < m; ++i, putchar('\n') )
			for ( j = 0; j < n; ++j )
				putchar(g[i][j]=='*'?g[i][j]:c[i][j]+'0');
	}
	return 0;
}
