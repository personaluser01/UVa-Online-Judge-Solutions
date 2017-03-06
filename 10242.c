/*
 * 10205. Stack Them Up
 * statsu: Accepted
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

double x[10],y[10],rx,ry,dx,dy;
int id[10];

int cmp( int i, int j ) {
	if ( fabs(x[id[i]]-x[id[j]]) < tol ) {
		if ( fabs(y[id[i]]-y[id[j]]) < tol )
			return 0;
		return y[id[i]] < y[id[j]] ? -1 : 1;
	}
	return x[id[i]] < x[id[j]] ? -1 : 1;
}

int main() {
	int i,j,k;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	while ( 8 == scanf("%lf %lf %lf %lf %lf %lf %lf %lf",x,y,x+1,y+1,x+2,y+2,x+3,y+3) ) {
		for ( i = 0; i < 4; ++i ) id[i] = i;
		for ( j = 1; j;)
			for ( j = i = 0; i+1 < 4; ++i )
				if ( cmp(i,i+1) > 0 && ++j )
					k = id[i], id[i] = id[i+1], id[i+1] = k;
		if ( cmp(0,1) == 0 ) {
			dx = x[id[2]]-x[id[0]], dy = y[id[2]]-y[id[0]];
			rx = x[id[3]]+dx, ry = y[id[3]]+dy;
		}
		else if ( cmp(1,2) == 0 ) {
			dx = x[id[0]]-x[id[1]], dy = y[id[0]]-y[id[1]];
			rx = x[id[3]]+dx, ry = y[id[3]]+dy;
		}
		else {
			assert( cmp(2,3) == 0 );
			dx = x[id[0]]-x[id[2]], dy = y[id[0]]-y[id[2]];
			rx = x[id[1]]+dx, ry = y[id[1]]+dy;
		}
		printf("%.3lf %.3lf\n",rx,ry);
	}
	return 0;
}
