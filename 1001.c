/*
 * 1001. Say Cheese
 * TOPIC: floyd-warshall
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define N 0x80

double g[N][N];
int x[N],y[N],z[N],r[N];
int n,cs = 0;

int main() {
	int i,j,k;
	double rr,sq,a,b,c,rsq;
	for ( ;1 == scanf("%d",&n) && n != -1; ) {
		for ( i = 0; i < n+2; ++i ) {
			scanf("%d %d %d",x+i,y+i,z+i);
			if ( i < n ) scanf("%d",r+i);
			else r[i] = 0;
		}
		for ( i = 0; i < n+2; ++i ) g[i][i] = 0;
		for ( i = 0; i < n+2; ++i )
			for ( j = i+1; j < n+2; ++j ) {
				a = x[i]-x[j], b = y[i]-y[j], c = z[i]-z[j];
				sq = sqrt(a*a+b*b+c*c), rr = r[i]+r[j];
				if ( sq <= r[i]+r[j] )
					g[i][j] = g[j][i] = 0;
				else g[i][j] = g[j][i] = sq-r[i]-r[j];
			}
		for ( k = 0; k < n+2; ++k )
			for ( i = 0; i < n+2; ++i )
				for ( j = 0; j < n+2; ++j )
					if ( g[i][k] + g[k][j] < g[i][j] )
						g[i][j] = g[i][k]+g[k][j];
		printf("Cheese %d: Travel time = %.0lf sec\n",++cs,g[n][n+1]*10);
	}
	return 0;
}


