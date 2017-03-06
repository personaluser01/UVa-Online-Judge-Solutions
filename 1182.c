/*
 * 1182. Sequence Alignment
 * TOPIC: dp
 * status: Accepted
 */
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 0x40
enum { MATCH = 2, GAP = -1, GAP_EXTENSION = 0 };
#define oo (1<<29)
#define enc(x,y,t) ((x)|((y)<<6)|((t)<<12))

int n[2],ts,z[N][N][4],d[N][N];
unsigned int way[N][N][4];
char a[2][N];

int max( int x, int y ) { if ( x<y ) return y; return x; }

int main() {
	int i,j,k,t,w;
#ifndef ONLINE_JUDGE
	freopen("c.txt","r",stdin);
#endif
	for ( scanf("%d\n",&ts); ts--; printf("%d\n",w) ) {
		for ( w = 0, i = 0; i <= 1; scanf("%[^\n]\n",a[i]+1), n[i] = strlen(a[i]+1), ++i );
		for ( t = 0; t <= 1; ++t )
			for ( i = 1, j = n[t]; i < j; ++i, --j )
				k = a[t][i], a[t][i] = a[t][j], a[t][j] = k;
		for ( i = 0; i <= n[0]; ++i )
			for ( j = 0; j <= n[1]; d[i][j++] = -oo )
				for ( k = 0; k <= 3; z[i][j][k++] = -oo );
		for ( d[0][0] = 0, i = 1; i <= n[0]; ++i ) d[i][0] = z[i][0][2] = GAP;
		for ( j = 1; j <= n[1]; ++j ) d[0][j] = z[0][j][1] = GAP;
		for ( i = 1; i <= n[0]; ++i )
			for ( j = 1; j <= n[1]; ++j ) {
				if ( a[0][i] == a[1][j] && d[i-1][j-1] > -oo ) 
					z[i][j][0] = d[i-1][j-1]+MATCH, way[i][j][0] = enc(i-1,j-1,3);
				if ( d[i-1][j-1] > -oo && z[i][j][0] < d[i-1][j-1] )
					z[i][j][0] = d[i-1][j-1];
				if ( z[i][j-1][1] > -oo && z[i][j-1][1]+GAP_EXTENSION > z[i][j][1] )
					z[i][j][1] = z[i][j-1][1]+GAP_EXTENSION, way[i][j][1] = enc(i,j-1,1);
				if ( d[i][j-1] > -oo && d[i][j-1]+GAP > z[i][j][1] )
					z[i][j][1] = d[i][j-1]+GAP, way[i][j][1] = enc(i,j-1,3);
				if ( z[i-1][j][2] > -oo && z[i-1][j][2]+GAP_EXTENSION > z[i][j][2] )
					z[i][j][2] = z[i-1][j][2]+GAP_EXTENSION, way[i][j][2] = enc(i-1,j,2);
				if ( d[i-1][j] > -oo && d[i-1][j]+GAP > z[i][j][2] )
					z[i][j][2] = d[i-1][j]+GAP, way[i][j][2] = enc(i-1,j,3);
				d[i][j] = max(z[i][j][0],max(z[i][j][1],z[i][j][2]));
				if ( z[i][j][0] == d[i][j] ) way[i][j][3] = enc(i,j,0);
				else if ( z[i][j][1] == d[i][j] ) way[i][j][3] = enc(i,j,1);
				else if ( z[i][j][2] == d[i][j] ) way[i][j][3] = enc(i,j,2);
				if ( i == n[0] || j == n[1] )
					w = max(w,d[i][j]);
			}
	}
	return 0;
}

