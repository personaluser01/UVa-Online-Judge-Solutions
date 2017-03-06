/*
 * TOPIC: DP, lazy dp
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 0x400
#define B 0x80
#define vc(x,y) (1<=(x)&&(x)<=m&&1<=(y)&&(y)<=n)
#define oo 0xfffffffful
enum {NORTH,SOUTH};
unsigned int min( unsigned int x, unsigned int y ) { return x<y?x:y; }

int m,n,b,space,bank[N][N],seen[N][N],yes,north[N],south[N],
	dx[] = {-1,0,1,0},
	dy[] = {0,-1,0,1};
char g[N][N];
unsigned int z[N][B];

void floodfill( int x, int y, int mark ) {
	int nx,ny,i;
	assert( seen[x][y] != yes );
	for ( bank[x][y] = mark, seen[x][y] = yes, i = 0; i < 4; ++i ) 
		if ( vc(nx=x+dx[i],ny=y+dy[i]) && g[nx][ny] == '#' && seen[nx][ny] != yes )
			floodfill(nx,ny,mark);
}

unsigned int calc_z( int col, int k ) {
	int j;

	if ( !k ) return 0;
	assert( k >= 1 );
	if ( col < k ) return +oo;
	assert( col >= k );

	if ( seen[col][k] == yes ) 
		return z[col][k];

	seen[col][k] = yes, z[col][k] = calc_z(col-1,k);
	j = col-space-1;
	if ( south[col] <= m && north[col] >= 1 && calc_z(j,k-1) < +oo ) 
		z[col][k] = min(z[col][k],calc_z(j,k-1)+(-north[col]+south[col]-1));
	return z[col][k];
}

int main() {
	int i,j,k;
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	for(;4==scanf("%d %d %d %d",&m,&n,&b,&space);) {
		for ( i = 1; i <= m; scanf("%s",1+g[i++]) );
		for ( ++yes, k = 0, i = 1; i <= m && !k; ++i )
			for ( j = 1; j <= n && !k; ++j )
				if ( g[i][j] == '#' ) 
					floodfill(i,j,NORTH), ++k;
		for ( k = 0, i = m; i >= 1 && !k; --i )
			for ( j = n; j >= 1 && !k; --j )
				if ( g[i][j] == '#' && seen[i][j] != yes )
					++k, floodfill(i,j,SOUTH);
		for ( i = 1; i <= m; ++i )
			for ( j = 1; j <= n; ++j )
				if ( g[i][j] == '#' )
					assert( seen[i][j] == yes );
		for ( j = 1; j <= n; north[j++] = i ) 
			for ( i = m; i >= 1 && !(seen[i][j] == yes && bank[i][j] == NORTH); --i );
		for ( j = 1; j <= n; south[j++] = i )
			for ( i = 1; i <= m && !(seen[i][j] == yes && bank[i][j] == SOUTH); ++i );
		for ( j = 0; j <= n; ++j )
			for ( k = 0; k <= b; ++k )
				z[j][k] = +oo, seen[j][k] = 0;
		printf("%u\n",calc_z(n,b));
	}
	return 0;
}

