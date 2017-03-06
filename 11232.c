/*
 * 11232. Cylinder
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
#define pi (2*acos(0.0))

long double SQ( long double x ) {
	return x*x;
}

long double CB( long double x ) {
	return x*x*x;
}

long double max( long double x, long double y ) {
	return x < y ? y : x;
}

long double min( long double x, long double y ) {
	return x < y ? x : y;
}

long double w,h,x,r,a,b,c;

int main() {
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	while ( 2 == scanf("%Lf %Lf",&w,&h) && !(fabs(w)<tol&&fabs(h)<tol) ) {
		if ( w < h ) x = h, h = w, w = x;
		assert( h <= w );
		a = (pi*w-h)*SQ(h/2/pi);
		b = pi*h*SQ(min(w/(pi+1),h))/4;
		a = max(a,b);
		if ( h <= w/(pi+1) )
			c = CB(h)*pi/4, a = max(c,a);
		printf("%.3Lf\n",a);
	}
	return 0;
}
