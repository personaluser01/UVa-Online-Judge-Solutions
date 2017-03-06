/*
 * 10987. AntiFloyd
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 0x80
#define OK (puts("Need better measurements."))
typedef struct { int x,y,d; } edge;

int ts,cs,n,g[N][N],p[N][N],a[N][N],m;
edge e[N*N],E[N*N];

int cmp( const void *a, const void *b ) {
	edge *aa = (edge *)a,
		 *bb = (edge *)b;
	return aa->d-bb->d;
}

int cmp_by_vx( const void *a, const void *b ) {
	edge *aa = (edge *)a,
		 *bb = (edge *)b;
	if ( aa->x == bb->x ) 
		return aa->y - bb->y;
	return aa->x < bb->x ? -1 : 1;
}


int main() {
	int i,j,k,l,t,x,y,z;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( scanf("%d",&ts); ts-- && printf("Case #%d:\n",++cs); putchar('\n') ) {
		scanf("%d",&n);
		for ( i = 0; i < n; ++i )
			for ( j = 0; j < n; ++j )
				g[i][j] = -1;
		for ( i = 0; i < n; ++i ) g[i][j] = 0;
		for ( m = 0, k = 0; k < n-1; ++k ) 
			for ( l = 0; l < k+1; ++l ) 
				scanf("%d",&g[l][k+1]);
		for ( i = 0; i < n; ++i )
			for ( j = 0; j < n; ++j )
				if ( g[i][j] == -1 && g[j][i] != -1 )
					g[i][j] = g[j][i];
		for ( i = 0; i < n; ++i )
			for ( j = i+1; j < n; ++j )
				e[m].x = i, e[m].y = j, e[m++].d = g[i][j];
		qsort(e,m,sizeof *e,cmp);
		for ( t = 0, k = 0; k < m; ++k ) {
			x = e[k].x, y = e[k].y;
			for ( z = 0; z < n; ++z ) {
				if (x==z||y==z||g[x][z]+g[z][y]>e[k].d)
					continue ;
				if ( g[x][z]+g[z][y] < e[k].d )
					goto FAIL;
				p[x][y] = p[z][y];
				goto ok;
			}
			E[t++] = e[k];
			ok: continue ;
		}
		qsort(E,t,sizeof *E,cmp_by_vx);
		printf("%d\n",t);
		for ( i = 0; i < t; ++i )
			printf("%d %d %d\n",E[i].x+1,E[i].y+1,E[i].d);
		continue ;
		FAIL: OK;
	}
	return 0;
}
