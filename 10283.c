/*
 * 10283. Kissing Circles
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
#define pi (2*acos(.0))

double R,a,r,I,E,s,T,S;
int n;

int main() {
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	while ( 2 == scanf("%lf %d",&R,&n) ) {
		if ( n >= 3 ) {
			a = 2*pi/n;
			r = R/(1+1/sin(a/2));
			S = R*R*a/2;
			T = (R-r)*(R-r)*sin(a)/2;
			s = r*r*(pi/2+a/2)/2;
			E = n*(S-2*s-T);
			I = pi*R*R-E-pi*n*r*r;
		}
		else if ( n == 1 ) {
			r = R, I = E = 0;
		}
		else {
			assert( n == 2 );
			r = R/2;
			I = 0;
			E = pi*R*R-n*pi*r*r;
		}
		printf("%.10lf %.10lf %.10lf\n",r,I,E);
	}
	return 0;
}
