/*
 * 10135. Herding Frosh
 */
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 0x400
#define tol 1e-9
#define S(x) ((x)*(x))
#define pi (2*acos(.0))

typedef struct {
	long double x,y;
	long double ang,dist;
} cell;

int cmp( const void *a, const void *b ) {
	cell *A = (cell *)a,
		 *B = (cell *)b;
	if ( fabs(A->ang-B->ang) < tol ) {
		if ( fabs(A->dist-B->distr) < tol )
			return 0;
		return A->dist > B->dist ? -1 : 1;
	}
	return A->ang < B->ang ? -1 : 1;
}

int left_turn( cell *a, cell *b, cell *c ) {
	cell u,v;
	long double x,y;
	u.x = b->x-a->x, u.y = b->y-a->y;
	v.x = c->x-b->x, v.y = c->y-b->y;
	x = u.x*v.y, y = v.x*u.y;
	if ( fabs(x-y) < tol )
		return 0;
	return x > y;
}

int ts,n,m;
long double x[N],y[N],D[N][N];
cell c[N];

int main() {
	int i,j,k;
	long double sine,cosi;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( scanf("%d",&ts); ts-- && scanf("%d",&n); ) {
		for ( i = 0; i < n; ++i ) 
			scanf("%Lf %Lf",x+i,y+i);
		for ( i = 0; i < n; ++i )
			for ( j = i+1; j < n; ++j )
				D[i][j] = D[j][i] = sqrt(S(x[i]-x[j])+S(y[i]-y[j]));
		for ( m = 0, j = 0; j < n; ++j ) {
			c[m].x = x[j], c[m].y = y[j];
			c[m].dist = sqrt(S(x[j])+S(y[j]));
			sine = y[j]/c[m].dist;
			cosi = x[j]/c[m].dist;
			if ( sine >= 0 && cosi >= 0 )
				c[m++].ang = acos(cosi);
			else if ( sine >= 0 && cosi <= 0 )
				c[m++].ang = acos(cosi);
			else if ( sine <= 0 && cosi >= 0 )
				c[m++].ang = asin(sine);
			else if ( sine <= 0 && cosi <= 0 )
				c[m++].ang = pi-asin(sine);
		}
		qsort(c,m,sizeof *c,cmp);
		for ( i = 0; i < m; ++i ) {
		}
		if ( ts ) putchar('\n');
	}
	return 0;
}

