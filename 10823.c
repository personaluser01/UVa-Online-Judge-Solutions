/*
 * 10823. Of Circles and Square
 * TOPIC: ad hoc
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef long long i64;
#define N 0x80
#define S(k) ((k)*(k))

int m,n,sq,cr;
i64 px,py,r,R,G,B,x[2][N],y[2][N],L[2][N],red[2][N],green[2][N],blue[2][N];

i64 f( i64 x, i64 k ) {
	double n = ((double)x)/k;
	return (i64)(n+0.5);
}

int main() {
	int i,j,k,cs = 0,ts,border;
	char tmp[0x400];
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	for ( scanf("%d",&ts); ts--; ) {
		printf("Case %d:\n",++cs);
		scanf("%d %d",&m,&n), cr = sq = 0;
		for ( k = 0; k < m; ++k ) {
			assert( 7 == scanf("%s %lld %lld %lld %lld %lld %lld",tmp,&px,&py,&r,&R,&G,&B) );
			if ( 0 == strcmp("CIRCLE",tmp) ) {
				x[0][cr] = px, y[0][cr] = py, L[0][cr] = r;
				red[0][cr] = R, green[0][cr] = G, blue[0][cr++] = B;
			}
			else {
				/*assert( 0 == strcmp("SQUARE",tmp) );*/
				x[1][sq] = px, y[1][sq] = py, L[1][sq] = r;
				red[1][sq] = R, green[1][sq] = G, blue[1][sq++] = B;
			}
		}
		for ( ;n-- && 2 == scanf("%lld %lld",&px,&py); ) {
			for ( border=k=R=G=B=0, i = 0; i < sq; ++i ) {
				if ( x[1][i] <= px && px <= x[1][i]+L[1][i] )
					if ( y[1][i] <= py && py <= y[1][i]+L[1][i] )
				 		R += red[1][i], G += green[1][i], B += blue[1][i], ++k;
				if ( x[1][i] <= px && px <= x[1][i]+L[1][i] )
					if ( y[1][i] <= py && py <= y[1][i]+L[1][i] )
						if ( x[1][i] == px || x[1][i]+L[1][i] == px || y[1][i] == py || y[1][i]+L[1][i] == py )
							border = 1;
			}
			for ( i = 0; i < cr; ++i ) {
				if ( S(x[0][i]-px)+S(y[0][i]-py) <= S(L[0][i]) )
					R += red[0][i], G += green[0][i], B += blue[0][i], ++k;
				if ( S(x[0][i]-px)+S(y[0][i]-py) == S(L[0][i]) )
					border = 1;
			}
			if ( border ) {
				puts("(0, 0, 0)");
				continue ;
			}
			if ( !k ) {
				puts("(255, 255, 255)");
				continue ;
			}
			printf("(%lld, %lld, %lld)\n",f(R,k),f(G,k),f(B,k));
		}
		if ( ts ) putchar('\n');
	}
	return 0;
}

