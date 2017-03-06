/*
 * 143. Orchard Trees
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
#define oo (DBL_MAX-10000)

long double x[3],y[3],maxx,maxy,minx,miny;

int read_input() {
	int i,ok = 0;
	minx = miny = +oo, maxx = maxy = -oo;
	for ( i = 0; i < 3; ++i )
		if ( 2 == scanf("%Lf %Lf",x+i,y+i) ) {
			if ( fabs(x[i]) > tol||fabs(y[i]) > tol )
				ok = 1;
			if ( x[i] > maxx ) maxx = x[i];
			if ( x[i] < minx ) minx = x[i];
			if ( y[i] > maxy ) maxy = y[i];
			if ( y[i] < miny ) miny = y[i];
		}
		else return 0;
	return ok;
}

int signum( long double x ) {
	if ( fabs(x) < tol )
		return 0;
	return x<0?-1:1;
}

int inside( long double p, long double q ) {
	long double sa[3],ux,uy,vx,vy,S;
	int i,j,k;

	for ( i = 0; i < 3; ++i ) {
		j = (i+1) % 3;
		ux = x[i]-p, uy = y[i]-q;
		vx = x[j]-p, vy = y[j]-q;
		sa[i] = ux*vy - uy*vx;
	}
	ux = x[1]-x[0], uy = y[1]-y[0];
	vx = x[2]-x[0], vy = y[2]-y[0];
	S = ux*vy - uy*vx;
	assert( fabs(S) > tol );
	for ( i = 0; i < 3; ++i )
		if ( signum(sa[i])*signum(S) == -1 )
			return 0;
	return 1;
}

long double dist( long double a, long double b, long double t ) {
	long double xx = minx + t*(maxx-minx),
		 		yy = miny + t*(maxy-miny);
	return (xx-a)*(xx-a) + (yy-b)*(yy-b);
}

int main() {
	int i,j,k,tx,ty,ax = 0;
	long double ux,uy,vx,vy,S,a,b;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( ;read_input(); printf("%4d\n",ax) ) {
		ux = x[1]-x[0], uy = y[1]-y[0];
		vx = x[2]-x[0], vy = y[2]-y[0];
		S = ux*vy - uy*vx;
		if ( fabs(S) < tol ) {
			for ( ax = 0, tx = 1; tx < 100; ++tx )
				for ( ty = 1; ty < 100; ++ty ) {
					for(a=0,b=1;fabs(b-a)>tol;dist(tx,ty,(2*a+b)/3)>dist(tx,ty,(2*b+a)/3)?(a=(2*a+b)/3):(b=(2*b+a)/3));
					if ( dist(tx,ty,a) < tol && ++ax );
				}
		}
		else {
			for ( ax = 0, tx = 1; tx < 100; ++tx )
				for ( ty = 1; ty < 100; ax += inside(tx,ty++) );
		}
	}
	return 0;
}
