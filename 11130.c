/*
 * 11130. Billiard Bounces
 * status: Accepted
 * TOPIC: trigonometry, maths
 */
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define tol 1e-9
#define pi (2*acos(0.00))

double a,b,v,alpha,s,t,r,L,e;

double max( double x, double y ) { return x < y ?x:y; }

int main() {
	int i,j,k;
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	for (;5 == scanf("%lf %lf %lf %lf %lf",&a,&b,&v,&alpha,&s);) {
		if ( fabs(a)<tol && fabs(b)<tol && fabs(v)<tol && fabs(alpha)<tol && fabs(s)<tol )
			break ;
		alpha = alpha*pi/180.00;
		t = tan(alpha), r = b/a;

		if ( fabs(t-r) < tol ) {
			L = sqrt(a*a+b*b);
			if ( v*s < L ) {
				puts("0 0");
				continue ;
			}
			k = 1, e = v*s/2-L/2, k += (int)floor(e/L);
			printf("%d %d\n",k,k);
			continue ;
		}

		if ( t > r ) {
			k = (int)(floor((v*s*cos(alpha)-a)/(2*a))-max(0,ceil((3-t/r)/2/(t/r-1)))+1+tol);
			printf("%d ",k);
		}
		else {
			k = (int)floor((v*s*cos(alpha)-a)/(2*a))+1;
			printf("%d ",k);
		}
		t = 1/tan(alpha), r = a/b;
		if ( t > r ) {
			k = (int)(floor((v*s*sin(alpha)-b)/(2*b))-max(0,ceil((3-t/r)/2/(t/r-1)))+1+tol);
			if ( k < 0 ) k = 0;
			printf("%d\n",k);
		}
		else {
			k = (int)floor((v*s*sin(alpha)-b)/(2*b))+1;
			if ( k < 0 ) k = 0;
			printf("%d\n",k);
		}
	}
	return 0;
}


