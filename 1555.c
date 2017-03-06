/*
 * 1555. Garland
 * TOPIC: binary search
 * status: Accepted
 */
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#define oo (DBL_MAX-0x400)
#define tol 1e-9
#define N 0x400

int n;
double A,x[N];

double f( double NA, double *res ) {
	int i;
	for ( x[0]=A,x[1]=NA,i=2; i < n; ++i )
		if ( (x[i] = 2+2*x[i-1]-x[i-2]) < 0 )
			return 0;
	if ( res ) *res = x[n-1];
	return 1;
}

int main() {
	int i,j,k;
	double low,high,mid,res;
#ifndef ONLINE_JUDGE
	freopen("c.txt","r",stdin);
#endif
	for (;1==scanf("%d",&n) && n>0 && 1==scanf("%lf",&A); ) {
		for ( low = 0, high = +oo; fabs(high-low) > tol; )
			if ( f(mid=(low+high)/2,NULL) )
				high = mid;
			else low = mid;
		f(high,&res);
		printf("%.2lf\n",res);
	}
	return 0;
}

