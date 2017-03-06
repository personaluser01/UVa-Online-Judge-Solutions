/*
 * 201. Squares
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
#define N 9
#define vc(x,y) (0<=(x)&&(x)<n&&0<=(y)&&(y)<n)
enum { UP,RIGHT,DOWN,LEFT };
#define enc(x,y,d) ((x)|((y)<<7)|((d)<<14))
#define M(k) ((1UL<<(k))-1UL)
#define Q (N*N)

int n,cs,dx[] = {-1,0,1,0},c[N][N],deg[N*N],adj[N*N][4],m,
		 dy[] = {0,1,0,-1},g[Q][Q],yes,cnt[N],
		 xx[Q],yy[Q];

int reachable( int u, int v, int t ) {
	int x,y,nx,ny;
	x = xx[u], y = yy[u], nx = xx[v], ny = yy[v];
	if ( x == nx && y == ny )
		return 1;
	nx = x+dx[t], ny = y+dy[t];
	if ( !vc(nx,ny)||g[c[x][y]][c[nx][ny]] != yes )
		return 0;
	return reachable(c[nx][ny],v,t);
}

int main() {
	int i,j,k,ok,t,l;
	char tmp[0x400];
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for (;1 == scanf("%d",&n) && ++yes;) {
		if ( ++cs > 1 ) puts("\n**********************************\n");
		printf("Problem #%d\n\n",cs); 
		for ( k = 0, i = 0; i < n; ++i )
			for ( j = 0; j < n; c[i][j] = k, xx[k] = i, yy[k++] = j++ );
		assert( k == n*n );
		for ( i = 0; i < k; deg[i++] = 0 );
		for ( ok = 0, scanf("%d",&m), k = 0; k < m; ++k ) {
			scanf("%s %d %d",tmp,&i,&j), --i, --j;
			if ( 0[tmp] == 'H' ) 
				g[c[i][j]][c[i][j+1]] = g[c[i][j+1]][c[i][j]] = yes;
			else {
				assert( 0[tmp] == 'V' );
				t = i, i = j, j = t;
				g[c[i][j]][c[i+1][j]] = g[c[i+1][j]][c[i][j]] = yes;
			}
		}
		for ( k = 1; k <= n; ++k )
			for ( cnt[k] = 0, i = 0; i+k < n; ++i )
				for ( j = 0; j+k < n; ++j ) 
					if ( reachable(c[i][j],c[i+k][j],DOWN) )
						if ( reachable(c[i][j],c[i][j+k],RIGHT) )
							if ( reachable(c[i][j+k],c[i+k][j+k],DOWN) )
								if ( reachable(c[i+k][j],c[i+k][j+k],RIGHT) )
									++cnt[k], ++ok;
		if ( !ok ) puts("No completed squares can be found.");
		else 
			for ( k = 1; k <= n; ++k )
				if ( cnt[k] )
					printf("%d square (s) of size %d\n",cnt[k],k);
	}
	return 0;
}

