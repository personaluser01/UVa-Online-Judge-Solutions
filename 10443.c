/*
 * 10443. Rock, Scissors, Paper
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
#define N 0x100
#define vc(x,y) (0<=(x)&&(x)<m&&0<=(y)&&(y)<n)

int m,n,ts,days,di[] = {-1,0,1,0},
dj[] = {0,-1,0,1},ni,nj,upd[N][N],yes;
char g[2][N][N],c[256][256];

int main() {
	int i,j,k,t;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	c['R']['S'] = c['S']['P'] = c['P']['R'] = 1;
	for ( scanf("%d",&ts); ts-- && scanf("%d %d %d",&m,&n,&days); ) {
		for ( t = i = 0; i < m; scanf("%s",g[t][i++]) );
		for ( k = 0; k <= 1; ++k )
			for ( i = 0; i < m; strcpy(g[k^1][i],g[k][i]), ++i );
		while ( days-- && ++yes )  {
			for ( t ^= 1, i = 0; i < m; ++i )
				for ( j = 0; j < n; ++j )
					for ( k = 0; k < 4; ++k )
						if (vc(ni=i+di[k],nj=j+dj[k])&&g[t^1][ni][nj]!=g[t^1][i][j])
							c[g[t^1][i][j]][g[t^1][ni][nj]]?(upd[ni][nj]=yes,g[t][ni][nj]=g[t^1][i][j]):(upd[i][j]=yes,g[t][i][j]=g[t^1][ni][nj]);
			for ( i = 0; i < m; ++i )
				for ( j = 0; j < n; ++j )
					if ( upd[i][j] != yes )
						g[t][i][j] = g[t^1][i][j];
		}
		for ( i = 0; i < m; puts(g[t][i++]) );
		if ( ts ) putchar('\n');
	}
	return 0;
}
