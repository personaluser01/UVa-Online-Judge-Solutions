/*
 * 11617. An Odd Love
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <limits.h>
#include <float.h>
#define vc(x,y) (1<=(x)&&(x)<=m&&1<=(y)&&(y)<=n)
#define oo 0xfffffffful
#define N (1 << 16)

unsigned int dist( int sx, int sy, int tx, int ty ) {
	if ( sx > tx )
		return +oo;
	return abs(sx-tx)+abs(ty-sy);
}

int dx[] = {0,1,0},ts,
	dy[] = {-1,0,1},
	m,n,left[N],right[N];
char **s;
unsigned int **z,w;

int f( int row, int j, int k ) {
	int i = row;
	if ( left[row] > right[row] ) {
		return abs(j-k);
	}
	if ( j <= k ) {
		if ( left[row] <= j && k <= right[row] )
			return abs(left[i]-right[i])+abs(j-left[i])+abs(k-right[i]);
		if ( j <= left[i] && k <= right[i] )
			return abs(j-right[i])+abs(k-right[i]);
		if ( j <= left[i] && right[i] <= k )
			return abs(j-k);
		if ( k <= left[i] )
			return abs(j-right[i])+abs(right[i]-k);
		if ( right[i] <= j )
			return abs(j-left[i])+abs(left[i]-k);
		assert( left[i] <= j && right[i] <= k );
		return abs(left[i]-k)+abs(left[i]-j);
	}
	return f(row,k,j);
}

unsigned int min( unsigned int x, unsigned int y ) { return x < y ? x:y; }

int main() {
	int i,j,k,l,t;
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	for ( scanf("%d",&ts); ts--; ) {
		scanf("%d %d",&n,&m);
		s = (char **)malloc((m+2)*sizeof *s);
		for ( i = 0; i < m+2; ++i )
			s[i] = (char *)malloc((n+2)*sizeof *s[i]);
		for ( i = 1; i <= m; scanf("%s",s[i++]+1) );
		for ( i = 1; i <= m; ++i ) {
			for ( j = 1; j <= n; ++j ) {
				k = s[i][j], k -= '0';
				if ( k & 1 ) s[i][j] = '1';
				else s[i][j] = '0';
			}
		}
		z = (unsigned int **)malloc((m+2)*sizeof *z);
		for ( i = 0; i < m+2; ++i ) {
			z[i] = (unsigned int *)malloc((n+2)*sizeof *z[i]);
			for ( j = 0; j < n+2; ++j ) z[i][j] = +oo;
		}
		for ( i = 1; i <= m; ++i ) {
			for ( j = 1; j <= n && s[i][j] == '1'; ++j );
			left[i] = j;
			for ( j = n; j >= 1 && s[i][j] == '1'; --j );
			right[i] = j;
		}
		for ( i = 0, j = 0; j < n+2; ++j )
			z[i][j] = 0;
		for ( i = 1, j = 1; j <= n; ++j )
			z[i][j] = min(z[i][j],f(i,j,1));
		for ( i = 2; i <= m; ++i )
			for ( j = 1; j <= n; ++j )
				for ( k = 1; k <= n; ++k )
					z[i][j] = min(z[i][j],z[i-1][k]+1+f(i,k,j));
		for ( ;m >= 1 && left[m] > right[m]; --m );
		if ( !m ) {
			puts("0");
			continue ;
		}
		for ( w = +oo, j = 1; j <= n; ++j )
			w = min(w,z[m][j]);
		printf("%u\n",w);
		for ( i = 0; i < m+2; ++i )
			free(s[i]), free(z[i]);
		free(s), free(z);
	}
	return 0;
}

