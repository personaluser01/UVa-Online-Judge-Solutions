/*
 * 10180. Rope Crisis in Ropeland
 * status: Accepted
 */
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define S(x) ((x)*(x))
#define tol 1e-9
#define pi (2*acos(0.00))

long double x[2],y[2],R,h0,h1;
int ts;

long double f( long double t ) {
	long double cx = x[0]+t*(x[1]-x[0]),
		 		cy = y[0]+t*(y[1]-y[0]);
	return S(cx)+S(cy);
}

int main() {
	long double a,b,c,d,t,na,nb,r;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( scanf("%d",&ts); ts--;) {
		scanf("%Lf %Lf %Lf %Lf %Lf",x,y,x+1,y+1,&R);
		for ( a = 0, b = 1; fabs(b-a) > tol; ) {
			na = (2*a+b)/3, nb = (a+2*b)/3;
			if ( f(na) < f(nb) )
				b = nb;
			else a = na;
		}
		if ( f(a) >= S(R) )
			printf("%.3Lf\n",(long double)sqrt(S(x[0]-x[1])+S(y[0]-y[1]))+1e-10);
		else {
			r = sqrt((h0 = S(x[0])+S(y[0]))-S(R))+sqrt((h1 = S(x[1])+S(y[1]))-S(R));
			a = acos(R/sqrt(h0)), b = acos(R/sqrt(h1));
			c = asin(fabs(x[0]*y[1]-x[1]*y[0])/sqrt(h0)/sqrt(h1));
			d = (x[0]*x[1] + y[0]*y[1])/sqrt(h0)/sqrt(h1);
			if ( d < 0 ) c = pi-c;
			printf("%.3Lf\n",r+R*(c-a-b)+1e-10);
		}
	}
	return 0;
}
