/*
 * 10316. Airline Hub
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
#define N 0x400
#define pi (2*acos(0.00))
#define oo (DBL_MAX-1024)

long double conv( long double x ) { return x*acos(0.00)/90; }

int n;
long double a[N],b[N],d[N][N],z[N],x[N],y[N],A,B,D[N],mi,oa[N],ob[N];

int main() {
	int i,j,k;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	while ( 1 == scanf("%d",&n) ) {
		for ( i = 0; i < n; ++i ) {
			scanf("%Lf %Lf",a+i,b+i);
			a[i] = conv(oa[i] = a[i]);
			b[i] = conv(ob[i] = b[i]);
			x[i] = cos(a[i])*cos(b[i]);
			y[i] = cos(a[i])*sin(b[i]);
			z[i] = sin(a[i]);
		}
		for ( i = 0; i < n; ++i )
			for ( j = i+1; j < n; ++j ) 
				d[i][j] = d[j][i] = acos(x[i]*x[j] + y[i]*y[j] + z[i]*z[j]);
		for ( i = 0; i < n; ++i ) 
			for ( D[i] = -oo, j = 0; j < n; ++j )
				if ( d[i][j] > D[i] ) D[i] = d[i][j];
		for ( mi = +oo, i = 0; i < n; ++i )
			if ( D[i] < mi||fabs(mi-D[i]) < tol )
				mi = D[k=i];
		printf("%.2Lf %.2Lf\n",oa[k]+tol,ob[k]+tol);
	}
	return 0;
}
