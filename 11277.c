/*
 * 11277. Cyclic Polygons
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
#define N 64
#define tol 1e-9
#define pi (2*acos(0.00))

long double S( long double x ) { return x*x; }

int n;
long double c[N],Pi;

long double 
getang( long double a, long double b, long double c, long double d ) {
	long double co = a*c+b*d,
		 		si = a*d-b*c,
				L  = sqrt((a*a+b*b)*(c*c+d*d));
	co /= L, si /= L;
	if ( co >= 0 && si >= 0 )
		return asin(si);
	if ( co >= 0 && si <= 0 )
		return asin(si);
	if ( co <= 0 && si >= 0 )
		return acos(co);
	return -Pi+acos(-co);
}

int main() {
	int i,j,k,ts;
	long double low,high,mid,tmp,
				 R,x,y,phi,mx,my,ang,A,ax,len,co,si;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	Pi = pi;
	for ( scanf("%d",&ts); ts--; ) {
		scanf("%d",&n);
		for ( i = 0; i < n; ++i ) 
			scanf("%Lf",c+i);
		for ( j = 1; j; )
			for ( i = j = 0; i < n-1; ++i )
				if ( c[i] > c[i+1] )
					tmp = c[i], c[i] = c[i+1], c[i+1] = tmp, ++j;
		for ( i = 0, tmp = 0; i < n-1; ++i )
			tmp += c[i];
		if ( tmp <= c[n-1] ) {
			puts("0.000");
			continue ;
		}
		for ( ax = 0, low = c[n-1]/2, high = (1L << 21); high-low > tol; ) {
			mid = R = (low+high)/2;
			for ( ax = 0, x = R, y = 0, i = 0; i < n-1; ++i ) {
				phi = acos(1-S(c[i]/R)/2);
				mx = x, my = y;
				co = cos(phi), si = sin(phi);
				x = co*mx - si*my;
				y = si*mx + co*my;
				ax += phi;
			}
			if ( fabs(ax-Pi) < tol ) {
				if ( fabs(2*R-c[n-1]) < tol ) {
					low = mid;
					break ;
				}
				assert( 2*R >= c[n-1] );
				high = mid;
			}
			else if ( ax < Pi ) {
				len = 2*R*sin(ax/2);
				if ( fabs(len-c[n-1]) < tol ) {
					low = mid;
					break ;
				}
				if ( len > c[n-1] )
					high = mid;
				else low = mid;
			}
			else {
				len = 2*R*sin(Pi-ax/2);
				if ( fabs(len-c[n-1]) < tol ) {
					low = mid;
					break ;
				}
				if ( len > c[n-1] )
					high = mid;
				else low = mid;
			}
		}
		for ( A = 0, x = R = low, y = 0, i = 0; i < n-1; ++i ) {
			phi = acos(1-S(c[i]/R)/2);
			mx = x, my = y;
			co = cos(phi), si = sin(phi);
			x = co*mx - si*my;
			y = si*mx + co*my;
			A += sin(phi);
		}
		ang = getang(x,y,1,0);
		A += sin(ang), A *= R, A *= R, A /= 2;
		printf("%.3Lf\n",A);
	}
	return 0;
}

