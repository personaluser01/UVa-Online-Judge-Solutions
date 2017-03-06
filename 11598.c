/*
 * 11598. Optimal Segments
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <limits.h>
#include <float.h>
#define  N   31
#define  K   16
#define  W   (1UL << 10)
#define tol 1e-9

int cs,ts,n,kk,c[N],pref[N],ones[N],twos[N];
unsigned int z[N][K][W],oo,weight[N][K][W];
char tick[N][K][W];

int sum( int i, int j ) { return pref[j]-pref[i-1]; }
int contains_x( int i, int j ) { return ones[j]-ones[i-1] >= 1; }
int contains_normal( int i, int j ) { return twos[j]-twos[i-1] >= 1; }

unsigned short min( unsigned short x, unsigned short y ) { return x < y ? x : y; }

void dump( int m, int k, int w ) {
	int i,j = tick[m][k][w];
	if ( k >= 2 ) {
		for ( i = m; i >= j; --i )
			if ( c[i] == 0 ) 
				printf("%cX",i == m?'(':' ');
			else 
				printf("%c%d",i == m?'(':' ',c[i]);
		putchar(')');
		dump(j-1,k-1,weight[m][k][w]);
	}
	else {
		for ( i = m; i >= 1; --i )
			if ( c[i] == 0 ) 
				printf("%cX",i == m?'(':' ');
			else 
				printf("%c%d",i == m?'(':' ',c[i]);
		putchar(')');
	}
}

int main() {
	int i,j,k,xx,a,b,t,last_piece,m,T,w,rat,ww;
	char tmp[0x100];
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( scanf("%d",&ts); ts--; ) {
		printf("Case %d: ",++cs);
		scanf("%d %d",&n,&kk);
		for ( xx = 0, i = n; i >= 1; --i ) {
			scanf("%s",tmp);
			if ( 0[tmp] == 'X' )
				c[i] = 0, ++xx;
			else c[i] = atoi(tmp);
		}
		for ( T = 0, i = 1; i <= n; ++i ) {
			pref[i] = pref[i-1]+c[i];
			ones[i] = ones[i-1];
			twos[i] = twos[i-1];
			if ( c[i] == 0 ) ++ones[i];
			else ++twos[i];
			T += c[i];
		}
		if ( xx < kk ) {
			puts("not possible!");
			continue ;
		}
		memset(z,0xfful,sizeof(z)), oo = z[0][0][0];
		for ( m = 2; m <= n; ++m )
			for ( j = 2; j <= m; ++j ) {
				if ( !contains_x(1,j-1)||!contains_x(j,m) )
					continue ;
				a = sum(1,j-1), b = sum(j,m);
				if ( a > b )
					t = a, a = b, b = t;
				if ( z[m][2][b] == +oo||z[m][2][b]<a||z[m][2][b]==a&&m-j>m-tick[m][2][b] )
					z[m][2][b] = a, tick[m][2][b] = j;
			}
		for ( m = 3; m <= n; ++m )
			for ( k = 3; k <= kk && k <= m; ++k )
				for ( w = 0; w <= T; ++w )
					for ( j = m; j >= 2 && (last_piece = sum(j,m)) <= w; --j ) {
						if ( !contains_x(j,m) )
							continue ;
						if ( last_piece < w ) {
							if ( z[j-1][k-1][w] == +oo )
								continue ;
							if ( last_piece < z[j-1][k-1][w] ) {
								if ( z[m][k][w]==+oo||z[m][k][w]<last_piece||z[m][k][w]==last_piece&&m-j>m-tick[m][k][w] )
									z[m][k][w] = last_piece, tick[m][k][w] = j, weight[m][k][w] = w;
							}
							else {
								if ( z[m][k][w]==+oo||z[m][k][w]<z[j-1][k-1][w]||z[m][k][w]==z[j-1][k-1][w]&&m-j>m-tick[m][k][w])
									z[m][k][w] = z[j-1][k-1][w], tick[m][k][w] = j, weight[m][k][w] = w;
							}
						}
						else {
							assert( last_piece == w );
							for ( ww = 0; ww <= w; ++ww ) {
								if ( z[j-1][k-1][ww] == +oo )
									continue ;
								if(z[m][k][w]==+oo||z[m][k][w]<z[j-1][k-1][ww]||z[m][k][w]==z[j-1][k-1][ww]&&m-j>m-tick[m][k][w])
									z[m][k][w] = z[j-1][k-1][ww], tick[m][k][w] = j, weight[m][k][w] = ww;
							}
						}
					}

		for ( rat = +oo, w = 0; w <= T; ++w )
			if ( z[n][kk][w] < +oo ) {
				assert( w >= z[n][kk][w] );
				if ( rat > w-z[n][kk][w] ) 
					rat = w-z[n][kk][w], ww = w;
			}
		if ( rat == +oo ) {
			puts("not possible!");
			continue ;
		}
		if ( (double)rat >= 15.0*(1+log(5.0)/log(2.0))+tol )
			puts("overflow");
		else {
			printf("%llu ",(1ULL<<rat));
			dump(n,kk,ww);
			putchar('\n');
		}
	}
	return 0;
}

