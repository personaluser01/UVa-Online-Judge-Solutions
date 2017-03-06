/*
 * 10210. Rome and Juliet
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
#define S(x) ((x)*(x))
#define pi (2*acos(0.00))
#define tol 1e-9

double x[2],y[2],CMD,ENF,d,a,b,left,right;

int main() {
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	while ( 6 == scanf("%lf %lf %lf %lf %lf %lf",x,y,x+1,y+1,&CMD,&ENF) ) {
		d = sqrt( S(x[0]-x[1]) + S(y[0]-y[1]) );
		a = CMD*pi/180.0, b = ENF*pi/180.0;
		right = d/tan(a);
		left = -d/tan(b);
		printf("%.3lf\n",right-left+tol);
	}
	return 0;
}
