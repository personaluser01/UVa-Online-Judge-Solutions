/*
 * 11227. The Silver Bullet
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
#define tol 1e-9
#define N 0x80

int n,m;
typedef struct {long double x,y;}cell;
cell c[N],a[N];

int cmp( const void *a, const void *b ) {
	cell *A = (cell *)a,
		 *B = (cell *)b;
	if ( fabs(A->x-B->x) < tol ) {
		if ( fabs(A->y-B->y) < tol )
			return 0;
		return A->y < B->y ? -1 : 1;
	}
	return A->x < B->x ? -1 : 1;
}

int main() {
	int i,j,k,ts,cs = 0,ans,ax;
	long double si,ux,uy,vx,vy;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( scanf("%d",&ts); ts-- && ++cs; ) {
		scanf("%d",&n);
		for ( i = 0; i < n; ++i ) 
			scanf("%Lf %Lf",&c[i].x,&c[i].y);
		qsort(c,n,sizeof *c,cmp);
		for ( m = 0, i = 0; i < n; a[m++] = c[i], i = j ) 
			for ( j = i+1; j < n && 0 == cmp(c+i,c+j); ++j );
		for ( i = 0; i < m; ++i ) c[i] = a[i];
		if ( m == 1 ) {
			printf("Data set #%d contains a single gnu.\n",cs);
			continue ;
		}
		for ( ans = 0, i = 0; i < m; ++i )
			for ( j = i+1; j < m; ++j ) {
				for ( ax = 2, k = 0; k < m; ++k )
					if ( k != i && k != j ) {
						ux = c[i].x-c[k].x, uy = c[i].y-c[k].y;
						vx = c[j].x-c[k].x, vy = c[j].y-c[k].y;
						if ( fabs(ux*vy-uy*vx) < tol && ++ax );
					}
				if ( ax > ans ) ans = ax;
			}
		printf("Data set #%d contains %d gnus, out of which a maximum of %d are aligned.\n",cs,m,ans);
	}
	return 0;
}
