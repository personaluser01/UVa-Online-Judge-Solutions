/*
 * 11524. In-Circle
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
#define oo (DBL_MAX-100000)

long double r;

int main() {
	int i,j,k,ts;
	long double low,high,mid,x,y,z,a,b,c,p,A,m[3],n[3],K;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( scanf("%d",&ts); ts--; ) {
		scanf("%Lf",&r);
		for ( i = 0; i < 3; ++i ) 
			scanf("%Lf %Lf",m+i,n+i);
		a = (m[1]+n[1]);
		b = n[1]*(m[2]+n[2])/m[2];
		c = n[2]*n[1]*(m[0]+n[0])/m[0]/m[2];
		p = (a+b+c)/2;
		K = sqrt((p-a)*(p-b)*(p-c)/p);
		x = r/K;
		printf("%Lf\n",r*p*x+tol);
	}
	return 0;
}
