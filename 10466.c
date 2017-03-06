/*
 * 10466. How Far?
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
#define N 0x40
#define pi (acos(-1.00))

int n;
long double r[N],t[N],T,w[N],a[N],x[N],y[N],d[N];;

int main() {
	int i,j,k;
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	while ( 2 == scanf("%d %Lf",&n,&T) ) {
		for ( i = 1; i <= n; ++i ) {
			scanf("%Lf %Lf",r+i,t+i);
			w[i] = 2*pi*r[i]/t[i];
		}
		for ( i = 1; i <= n; ++i ) {
			x[i] = x[i-1]+r[i]*cos(2*pi*T/t[i]);
			y[i] = y[i-1]+r[i]*sin(2*pi*T/t[i]);
			d[i] = sqrt(x[i]*x[i] + y[i]*y[i]);
		}
		for ( i = 1; i <= n-1; ++i )
			printf("%.4Lf ",d[i]);
		printf("%.4Lf\n",d[i]);
	}
	return 0;
}
