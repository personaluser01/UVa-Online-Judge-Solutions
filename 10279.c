/*
 * 10279. Minesweeper
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
#define N 0x10
#define vc(x,y) (0<=(x)&&(x)<n&&0<=(y)&&(y)<n)

int n;
char g[N][N],a[N][N],r[N][N];

int main() {
	int i,j,k,nx,ny,x,y,l,t,ts,ok;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( scanf("%d",&ts); ts-- && (ok = 1);) {
		for ( scanf("%d",&n), i = 0; i < n; scanf("%s",g[i++]));
		for ( i = 0; i < n; scanf("%s",a[i++]) );
		for ( i = 0; i < n; ++i )
			for ( j = 0; j < n; ++j ) {
				if ( a[x=i][y=j]=='.' ) { r[x][y] = '.'; continue ; }
				assert( a[x][y] == 'x' );
				if ( g[x][y] == '*' ) { r[x][y] = '*';  ok = 0; continue ; }
				for ( t = 0, k = -1; k <= 1; ++k )
					for ( l = -1; l <= 1; ++l )
						if ( (k||l) && vc(nx=x+k,ny=y+l) && g[nx][ny] == '*' && ++t );
				r[x][y] = t+'0';
			}
		for ( i = 0; i < n && !ok; ++i )
			for ( j = 0; j < n; ++j )
				if ( g[i][j] == '*' )
					r[i][j] = '*';
		for ( i = 0; i < n; ++i, putchar('\n') )
			for ( j = 0; j < n; putchar(r[i][j++]) );
		if ( ts ) putchar('\n');
	}
	return 0;
}
