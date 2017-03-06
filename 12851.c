/*
 * 12851. Tinker's Puzzle
 * TOPIC: maths, formula
 * status: Accepted
 */
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define tol 1e-9

int ts,cs;

double f( double d, double v ) {
	double low,high,mid;
	v *= 282;
	return 2*sqrt(12*v/(7*2*acos(0.00)*d));
}

int main() {
	double d,v;
#ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
#endif
	for ( scanf("%d",&ts); ts-- && 2 == scanf("%lf %lf",&d,&v); printf("Case %d: %.3lf\n",++cs,f(d,v)+tol) );
    return 0;
}

