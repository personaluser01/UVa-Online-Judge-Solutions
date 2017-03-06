/*
 * 11404. Palindromic Subsequence
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <limits.h>
#include <float.h>
#define N 0x400
#define A 26
#define enc(x,y) ((x)|((y)<<10))
#define M(k) ((1UL<<(k))-1UL)

unsigned int 
max ( unsigned int x, unsigned int y ) { return x < y ? y : x; }

int n,pos[A][N],*ptr[A],len[A];
char s[N],x[N],y[N];
unsigned int c[N][N],w;

int main() {
	int i,j,k,t,l;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for (;1 == scanf("%s",x+1);) {
		for ( i = 1, j = n; i >= 1; y[i++] = x[j--] );
		for ( i = 1; i <= n; ++i )
			for ( j = 1; j <= n; ++j ) {
				c[i][j] = max(c[i-1][j],c[i][j-1]);
				if ( x[i] == y[j] )
					c[i][j] = max(c[i][j],c[i-1][j-1]+1);
			}
		for ( w = 0, i = 1; i <= n; ++i )
			for ( j = 1; j+i <= n+1; ++j )
				if ( c[i][j] > w )
					w = c[i][j];
	}
	return 0;
}

