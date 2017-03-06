/*
 * 1231. ACORN
 * status: Accepted
 * TOPIC: DP
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N (1<<11)
#define H N
#define oo 0xfffffffful

unsigned int max( unsigned int x, unsigned int y ) {
	if ( x < y ) return y;
	return x;
}

int n,h,dh,m[N],c[H][N];
unsigned int z[H][N],r[H];

unsigned int 
calc_z( int height, int idx ) {
	if ( z[height][idx] < +oo )
		return z[height][idx];
	if ( height == 0 ) {
		r[height] = max(r[height],z[height][idx]=c[height][idx]);
		return z[height][idx];
	}
	z[height][idx] = c[height][idx]+calc_z(height-1,idx);
	if ( height >= dh )
		z[height][idx] = max(z[height][idx],r[height-dh]+c[height][idx]);
	r[height] = max(r[height],z[height][idx]);
	return z[height][idx];
}

int main() {
	int i,j,k,ts;
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	for ( scanf("%d",&ts); ts-- && 3 == scanf("%d %d %d",&n,&h,&dh); printf("%u\n",r[h]) ) {
		for ( i = 0; i <= h; ++i )
			for ( r[i] = 0, j = 0; j < n; ++j )
				c[i][j] = 0, z[i][j] = +oo;
		for ( i = 0; i < n; ++i ) 
			for ( scanf("%d",m+i), j = 0; j < m[i]; ++j )
				scanf("%d",&k), ++c[k][i];
		for ( i = 0; i <= h; ++i )
			for ( j = 0; j < n; calc_z(i,j++) );
	}
	return 0;
}

