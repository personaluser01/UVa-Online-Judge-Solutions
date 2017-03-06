/*
 * 11646. Athletics Track
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <limits.h>
#include <float.h>
#define pi (2*acos(0.0))
#define tol 1e-9

long double phi,R,L,W,t;

int main() {
	int i,j,k,cs = 0;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	while ( 2 == scanf("%d : %d",&i,&j) ) {
		printf("Case %d: ",++cs);
		t = (i+0.0)/j;
		phi = 2*acos(t/sqrt(t*t+1));
		L = 400*t/(2*t+phi*sqrt(t*t+1));
		W = L/t;
		assert( fabs(L*j - W*i) < tol );
		printf("%.9Lf %.9Lf\n",L,W);
	}
	return 0;
}
