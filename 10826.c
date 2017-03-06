/*
 * 10826. Hot or Cold?
 * TOPIC: dp
 * status: Accepted
 */
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define oo 0xfffffffful
#define N 301
unsigned int min( unsigned int x, unsigned int y ) { if ( x<y ) return x; return y; }
unsigned int max( unsigned int x, unsigned int y ) { if ( x>y ) return x; return y; }

unsigned int Z[N][N][N],z[] = {
1,
3,
4,
5,
5,
5,
6,
6,
6,
7,
7,
7,
7,
7,
7,
7,
7,
7,
8,
8,
8,
8,
8,
8,
8,
8,
8,
8,
8,
8,
9,
9,
9,
9,
9,
9,
9,
9,
9,
9,
9,
9,
9,
9,
9,
9,
9,
9,
9,
9,
9,
9,
9,
9,
10,
10,
10,
10,
10,
10,
10,
10,
10,
10,
10,
10,
10,
10,
10,
10,
10,
10,
10,
10,
10,
10,
10,
10,
10,
10,
10,
10,
10,
10,
10,
10,
10,
10,
10,
10,
10,
10,
10,
10,
10,
11,
11,
11,
11,
11,
11,
11,
11,
11,
11,
11,
11,
11,
11,
11,
11,
11,
11,
11,
11,
11,
11,
11,
11,
11,
11,
11,
11,
11,
11,
11,
11,
11,
11,
11,
11,
11,
11,
11,
11,
11,
11,
11,
11,
11,
11,
11,
11,
11,
11,
11,
11,
11,
11,
11,
11,
11,
11,
11,
11,
11,
11,
11,
11,
11,
11,
11,
11,
11,
11,
11,
12,
12,
12,
12,
12,
12,
12,
12,
12,
12,
12,
12,
12,
12,
12,
12,
12,
12,
12,
12,
12,
12,
12,
12,
12,
12,
12,
12,
12,
12,
12,
12,
12,
12,
12,
12,
12,
12,
12,
12,
12,
12,
12,
12,
12,
12,
12,
12,
12,
12,
12,
12,
12,
12,
12,
12,
12,
12,
12,
12,
12,
12,
12,
12,
12,
12,
12,
12,
12,
12,
12,
12,
12,
12,
12,
12,
12,
12,
12,
12,
12,
12,
12,
12,
12,
12,
12,
12,
12,
12,
12,
12,
12,
12,
12,
12,
12,
12,
12,
12,
12,
12,
12,
12,
12,
12,
12,
12,
12,
12,
12,
12,
12,
12,
12,
12,
12,
12,
12,
12,
12,
12,
12,
12,
12,
12,
12,
12,
12,
13,
13,
13,
13,
13
};

unsigned int calc_z( int i, int j, int k ) {
	int t,l,r;
	if ( i > j )
		return Z[i][j][k] = 0;
	if ( Z[i][j][k] < +oo )
		return Z[i][j][k];
	if ( j-i == 1 ) {
		if ( k == i || k == j )
			return Z[i][j][k] = 2;
		return Z[i][j][k] = 3;
	}
	if ( i == j ) {
		return Z[i][j][k] = 1;
	}
	for ( t = i; t <= j; ++t ) {
		if ( k == t ) continue ;
		l = (k+t)/2;
		r = (k+t)/2+((k+t)&1);
		Z[i][j][k] = min(Z[i][j][k],1+max(calc_z(r,j,t),calc_z(i,l,t)));
	}
	/*
	for ( t = k+1; t <= j; ++t ) {
		l = (int)ceil((k+t+0.00)/2);
		r = (int)floor((k+t+0.00)/2);
		z[i][j][k] = min(z[i][j][k],1+max(calc_z(r,j,t),calc_z(i,l,t)));
	}
	*/
	return Z[i][j][k];
}

unsigned int ans( int n ) {
	int t;
	unsigned int w = +oo;
	for ( t = 0; t < n; w = min(w,1+calc_z(0,n-1,t++)) );
	return w;
}

int main() {
	int n;
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	for(memset(Z,0xff,sizeof Z);1==scanf("%d",&n)&&n>0; printf("%u guess(es) required.\n",z[n-1]) );
	/*for(memset(z,0xff,sizeof z), n = 1; n < N; ++n )
		printf("z[%d] = %u;\n",n,ans(n));*/
	return 0;
}

