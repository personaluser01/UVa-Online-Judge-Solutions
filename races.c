#include <stdio.h>
#include <assert.h>
#define N 128

int n,K,g[N][N],yes;

int main() {
	int i,j,k;
	freopen("input.txt","r",stdin);
	  freopen("output.txt","w",stdout);
	while ( 2 == scanf("%d %d",&n,&K) && ++yes ) {
		while ( 2 == scanf("%d %d",&i,&j) && (i||j) )
			g[--i][--j] = yes;
		for ( k = 0; k < n; ++k )
			for ( i = 0; i < n; ++i )
				for ( j = 0; j < n; ++j )
					if ( g[i][k] == yes && g[k][j] == yes )
						g[i][j] = yes;
		for ( k = 0, i = 0; i < n; ++i )
			if ( i != K-1 && g[K-1][i] && ++k );
		puts(k == n-1 ? "Yes" : "No");
	}
	return 0;
}


