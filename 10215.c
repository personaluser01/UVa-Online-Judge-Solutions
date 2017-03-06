/*
 * 10215. Largest/Smallest Box
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


double m,n,v,x0,x1,x_max;

double min( double x, double y ) {
	return x < y ? x : y;
}

double max( double x, double y ) {
	return x < y ? y : x;
}

double f( double x ) {
	return x*(m-2*x)*(n-2*x);
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	while ( 2 == scanf("%lf %lf",&m,&n) ) {
		v = (m+n)/6;
		x0 = ((m+n)-sqrt(m*m+n*n-m*n))/6, x1 = ((m+n)+sqrt(m*m+n*n-m*n))/6;
		if ( f(x0) < f(x1) )
			x_max = x1;
		else x_max = x0;
		printf("%.3lf 0.000 ",x_max+tol);
		if ( m < n ) 
			printf("%.3lf\n",m/2+tol);
		else 
			printf("%.3lf\n",n/2+tol);
	}
	return 0;
}
