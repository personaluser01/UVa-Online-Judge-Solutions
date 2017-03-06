/*
 * 11620. City of Egocentrics
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <limits.h>
#include <float.h>
#define N 0x80
#define SH N
#define Q (N+SH)

typedef long long i64;

int ts,c[N][N],n,m;
i64 diag[Q][Q],row[N][N],col[N][N],a[Q][Q];

int main() {
	int i,j,k,l;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( scanf("%d",&ts); ts-- && 1 == scanf("%d",&n); ) {
		for ( m = n, i = 1; i <= n; ++i )
			for ( j = 1; j <= n; ++j )
				scanf("%d",&c[i][j]);

		memset(diag,0,sizeof(diag));
		memset(a,0,sizeof(a));
		memset(col,0,sizeof(col));
		memset(row,0,sizeof(row));
		

		for ( k = 2; k <= n+n; ++k ) {
			for ( j = n; j >= 1; --j )
				if ( (i = k-j) >= 1 && i <= n )
					break ;
			for ( l = i; l <= n; ++l )
				if ( (j = k-l) >= 1 && j <= n )
					a[k][l] = a[k][l-1]+c[l][j];
				else a[k][l] = a[k][l-1];
		}

		for ( k = (1-n); k <= n-1; ++k ) {
			for ( j = 1; j <= n; ++j ) {
				if ( (i = k+j) >= 1 && i <= n )
					break ;
			}
			for ( l = i; l <= n; ++l )
				if ( (j = l-k)>=1 && j <= n )
					diag[k+n][l] = diag[k+n][l-1] + c[l][j];
				else diag[k+n][l] = diag[k+n][l-1];
		}

		for ( i = 1; i <= n; ++i )
			for ( j = 1; j <= n; ++j )
				row[i][j] = row[i][j-1] + c[i][j];
		for ( j = 1; j <= n; ++j )
			for ( i = 1; i <= n; ++i )
				col[j][i] = col[j][i-1] + c[i][j];
		puts("H");
		for ( i = 1; i <= n; ++i )
			for ( j = 1; j <= n; ++j )
				if ( row[i][j-1] == row[i][n]-row[i][j] )
					printf("%d %d\n",i-1,j-1);
		puts("V");
		for ( i = 1; i <= n; ++i )
			for ( j = 1; j <= n; ++j )
				if ( col[j][i-1] == col[j][n]-col[j][i] )
					printf("%d %d\n",i-1,j-1);
		puts("D");
		for ( i = 1; i <= n; ++i )
			for ( j = 1; j <= n; ++j )
				if (diag[i-j+n][i-1]==diag[i-j+n][n]-diag[i-j+n][i])
					printf("%d %d\n",i-1,j-1);
		puts("A");
		for ( i = 1; i <= m; ++i )
			for ( j = 1; j <= n; ++j )
				if ( a[i+j][i-1] == a[i+j][n]-a[i+j][i] )
					printf("%d %d\n",i-1,j-1);
	}
	return 0;
}

