/*
 * 11437. Triangle Fun
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <limits.h>
#include <float.h>
typedef long long i64;
#define A(x) ((x)<0?-(x):(x))
#define tol 1e-9

i64 f( long double x ) {
	i64 dx = (i64)(x+tol),
		ux = dx+1;
	return A(x-dx)<A(ux-x)?dx:ux;
}

int ts;
long double x[3],y[3],S;

int main() {
	int i;
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	for ( scanf("%d",&ts); ts--; ) {
		for ( i = 0; i < 3; ++i )
			scanf("%Lf %Lf",x+i,y+i);
		for ( S = 0, i = 0; i < 3; ++i )
			S += (x[i]-x[(i+1)%3])*(y[i]+y[(i+1)%3]);
		S = A(S)/2;
		printf("%lld\n",f(S/7.00));
	}
	return 0;
}

