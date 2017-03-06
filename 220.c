/*
 * 220. Othello
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 0x10
#define vc(x,y) (0<=(x)&&(x)<m&&0<=(y)&&(y)<n)
enum { W, B };

int m = 8,n = 8,cur,c[2];
char g[N][N],sym[2];

int bracket( int x, int y, int dx, int dy ) {
	int i,j,k = 0,nx,ny;
	for ( nx = x+dx, ny = y+dy; vc(nx,ny); nx += dx, ny += dy ) {
		if ( g[nx][ny] == sym[cur^1] ) ++k;
		if ( g[nx][ny] == sym[cur] && k ) return 1;
		if ( g[nx][ny] == '-' || g[nx][ny] == sym[cur] ) return 0;
	}
	return 0;
}

int is_legal( int x, int y ) {
	int i,j;
	if ( !vc(x,y) || g[x][y] != '-' )
		return 0;
	for ( i = -1; i <= 1; ++i )
		for ( j = -1; j <= 1; ++j )
			if ( (i||j) && bracket(x,y,i,j) )
				return 1;
	return 0;
}

void make_move( int x, int y ) {
	int i,j,k,l,nx,ny,dx,dy;

	assert( g[x][y] == '-' );
	for ( g[x][y] = sym[cur], i = -1; i <= 1; ++i )
		for ( j = -1; j <= 1; ++j )
			if(i||j){
				if ( !bracket(x,y,i,j) ) continue ;
				for ( k = l = 0, nx = x+i, ny = y+j; vc(nx,ny); nx += i, ny += j ) {
					if ( g[nx][ny] == sym[cur^1] ) {
						++k, g[nx][ny] = sym[cur];
					}
					else if ( g[nx][ny] == sym[cur] ) {
						if ( k ) { l = 1; break ; }
					}
				}
				assert( l && k );
			}
	for ( c[W] = c[B] = 0, i = 0; i < m; ++i )
		for ( j = 0; j < n; ++j )
			if ( g[i][j] == 'W' ) ++c[W];
			else if ( g[i][j] == 'B' ) ++c[B];
}

int main() {
	int i,j,k,ts;
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	sym[W] = 'W', sym[B] = 'B';
	for ( scanf("%d",&ts); ts--; ) {
		c[W] = c[B] = 0;
		for ( i = 0; i < m; ++i )
			for ( scanf("%s",g[i]), j = 0; j < n; ++j )
				if ( g[i][j] == 'W' ) ++c[W];
				else if ( g[i][j] == 'B' ) ++c[B];
		scanf("%s",g[m]);
		if ( 0[g[m]] == 'W' ) cur = W;
		else cur = B;
		while ( 1 == scanf("%s",g[m]) && 0[g[m]] != 'Q' ) {
			if ( 0[g[m]] == 'L' ) {
				for ( k = 0, i = 0; i < m; ++i )
					for ( j = 0; j < n; ++j )
						if ( is_legal(i,j) ) {
							if ( ++k > 1 ) putchar(' '); 
							printf("(%d,%d)",i+1,j+1);
						}
				if ( !k ) {
					puts("No legal move.");
				}
				else putchar('\n');
			}
			else if ( 0[g[m]] == 'M' ) {
				i = 1[g[m]]-'0', j = 2[g[m]]-'0', --i,--j;
				if ( !is_legal(i,j) ) {
					cur ^= 1;
					assert( is_legal(i,j) );
				}
				make_move(i,j), printf("Black - %2d White - %2d\n",c[B],c[W]), cur ^= 1;
			}
		}
		for ( i = 0; i < m; puts(g[i++]) );
		if ( ts ) putchar('\n');
	}
	return 0;
}

