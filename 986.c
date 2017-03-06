/*
 * 986. How Many?
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 21
typedef long long i64;
enum { UP, DOWN };

i64 z[2*N][N][N][2],n,r,K;

int main() {
	int i,j,k,x,y;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	while ( 3 == scanf("%lld %lld %lld",&n,&r,&K) ) {
		memset(z,0,sizeof(z));
		for ( z[1][1][0][UP] = 1, x = 2; x <= 2*n; ++x )
			for ( y = 0; y <= x; ++y )
				if ( y+1 == K ) {
					for ( j = 0; j <= r; ++j ) {
						z[x][y][j+1][DOWN] += z[x-1][y+1][j][UP];
						z[x][y][j][DOWN] += z[x-1][y+1][j][DOWN];
						if ( y )
							z[x][y][j][UP] += z[x-1][y-1][j][UP] + z[x-1][y-1][j][DOWN];
					}
				}
				else if ( y != K ) {
					for ( j = 0; j <= r; ++j ) {
						z[x][y][j][DOWN] += z[x-1][y+1][j][UP]+z[x-1][y+1][j][DOWN];
						if ( y )
							z[x][y][j][UP] += z[x-1][y-1][j][UP]+z[x-1][y-1][j][DOWN];
					}
				}
				else {
					for ( j = 0; j <= r; ++j ) {

					}
				}
		printf("%lld\n",z[2*n][0][r][DOWN]);
	}
	return 0;
}
