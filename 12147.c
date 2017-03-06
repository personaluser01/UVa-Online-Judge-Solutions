/*
 * 12147. DNA Subsequences
 * TOPIC: dp, lcs, edit distance
 * status: Accepted
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#define N 0x400
#define K 0x80

int m,n,L,c[N][N];
char a[N],b[N];

int main() {
	int i,j,k,l,t,len;
	for (;1 == scanf("%d",&L) && L; printf("%d\n",c[m][n]) ) {
		scanf("%s %s",a+1,b+1), m = strlen(a+1), n = strlen(b+1);
		for ( i = 0; i <= m; ++i )
			for ( j = 0; j <= n; c[i][j++] = 0 );
		for ( i = L; i <= m; ++i )
			for ( j = L; j <= n; ++j ) {
				c[i][j] = (c[i-1][j]<c[i][j-1]?c[i][j-1]:c[i-1][j]);
				for ( len = 0, l = i, t = j; l >= 1 && t >= 1 && a[l] == b[t]; --l, --t ) 
					if ( ++len >= L )
						c[i][j] = (c[i][j]<c[l-1][t-1]+len?c[l-1][t-1]+len:c[i][j]);
			}
	}
	return 0;
}

