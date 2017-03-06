/*
 * Direct Visibility DIRVS
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 0x100
#define is_valid(x,y) (0<=(x)&&(x)<m&&0<=(y)&&(y)<n)

int m,n,height[N][N];

int can_climb( int x, int y, int nx, int ny ) {
	assert( is_valid(nx,ny) );
	if ( !is_valid(nx,ny) )
		return 0;
	if ( height[x][y] == height[nx][ny] )
		return 1;
	if ( height[x][y] < height[nx][ny] )
		return height[x][y]+1 <= height[nx][ny];
	return height[x][y]-height[nx][ny] <= 3;
}

int directly_visible( int r0, int c0, int r1, int c1 ) {
	double x0,y0,z0,
		   x1,y1,z1;
	x0 = r0 + .5, y0 = c0 + .5, z0 = height[r0][c0] + .5;
	x1 = r1 + .5, y1 = c1 + .5, z1 = height[r1][c1] + .5;
}

int main() {
	int i,j,k,ts;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( scanf("%d",&ts); ts-- && scanf("%d %d",&m,&n); ) {
		for ( i = 0; i < m; ++i )
			for ( j = 0; j < n; ++j )
				scanf("%d",&height[i][j]);
		scanf("%d %d %d %d",sx,sy,sx+1,sy+1);
	}
	return 0;
}

