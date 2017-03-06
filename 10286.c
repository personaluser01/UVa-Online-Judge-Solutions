/*
 * 10286. Trouble With a Pentagon
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
#define pi (2*acos(0.0000))

double L,ang;

double g( double x ) {
	return -sin(ang+x)+sin(x-2*ang);
}

double f( double x ) {
	return cos(ang+x)-cos(2*ang-x);
}

int main() {
	double x[2];
	int i,j,k,t;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( ang = pi/10, x[t=0] = pi/3, x[1] = pi/2; fabs(x[0]-x[1]) >= tol; t^=1, x[t] = x[t^1]-f(x[t^1])/g(x[t^1]) );
	assert( fabs(f(x[0])) < tol );
	while ( 1 == scanf("%lf",&L) ) 
		printf("%.10lf\n",L*(cos(ang)/sin(pi-pi/2-ang-x[0])));
	return 0;
}
