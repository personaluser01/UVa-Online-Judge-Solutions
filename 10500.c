/*
 * 10500. Robot Maps
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define vc(x,y) (0<=(x)&&(x)<m&&0<=(y)&&(y)<n)
enum { NOR, EAS, SOU, WES };
#define N 16
#define enc(x,y) ((x)|((y)<<4))
#define M(k) ((1UL<<(k))-1UL)

int dx[] = {-1,0,1,0},
	dy[] = {0,1,0,-1},
	m,n,X0,Y0,visited[N*N],yes,ax;
unsigned int stack[N*N],*top;
char g[N][N][3],p[N][N];

void dfs( int x, int y ) {
	int i,nx,ny,k = 0,
		sx,sy;
	if ( visited[enc(x,y)] == yes )
		return ;
	sx = sy = -1;
	visited[enc(x,y)] = yes, p[x][y] = '0', ++ax;
	for ( i = 0; i < 4; ++i ) {
		nx=x+dx[i], ny = y+dy[i];
		if ( !vc(nx,ny) ) continue ;
		if ( g[nx][ny][0] == 'X' ) {
			p[nx][ny] = 'X';
			continue ;
		}
		p[nx][ny] = '0';
		if ( sx < 0 && sy < 0 && visited[enc(nx,ny)] != yes ) 
			sx = nx, sy = ny;
	}
	if ( sx != -1 && sy != -1 )
		dfs(sx,sy);
}

int main() {
	int i,j,k,x,y,nx,ny;
	unsigned int u,v;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	while ( scanf("%d %d",&m,&n) && (m||n) && putchar('\n') && ++yes ) {
		scanf("%d %d",&X0,&Y0),--X0,--Y0;
		for ( i = 0; i < m; ++i ) 
			for ( j = 0; j < n; ++j )
				scanf("%s",g[i][j]), p[i][j] = '?';
		ax = 0, dfs(X0,Y0);
		for ( i = 0; i < m; ++i ) {
			for ( j = 0; j < 4*n+1; ++j )
				putchar(!(j%4)?'|':'-');
			for ( putchar('\n'), j = 0; j < 4*n+1; ++j )
				if ( !(j%4) )
					putchar('|');
				else if ( (j%4) == 2 )
					putchar(p[i][j/4]);
				else putchar(' ');
			putchar('\n');
		}
		for ( j = 0; j < 4*n+1; ++j )
			putchar(!(j%4)?'|':'-');
		printf("\n\nNUMBER OF MOVEMENTS: %d\n",ax-1);
	}
	return 0;
}
