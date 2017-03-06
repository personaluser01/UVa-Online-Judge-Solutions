/*
 * 10915. War on Weather
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
#define N 0x80
#define tol 1e-8
#define SQ(x) ((x)*(x))

int n,m;
long double x[N],y[N],z[N],
	 p[N],q[N],r[N],
	 ux,uy,uz,vx,vy,vz,co;

long double Len( long double x, long double y, long double z ) {
	return SQ(x)+SQ(y)+SQ(z);
}

long double f( int i, int j, long double t ) {
	long double cx = x[i]+t*(p[j]-x[i]),
		 		cy = y[i]+t*(q[j]-y[i]),
				cz = z[i]+t*(r[j]-z[i]);
	return SQ(cx)+SQ(cy)+SQ(cz);
}

int main() {
	int i,j,k,ax,t;
	long double a,b,c,na,nb,dist;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	while ( 2 == scanf("%d %d",&n,&m) && (n||m) ) {
		for ( i = 0; i < n; ++i ) 
			scanf("%Lf %Lf %Lf",x+i,y+i,z+i);
		for ( i = 0; i < m; ++i )
			scanf("%Lf %Lf %Lf",p+i,q+i,r+i);
		for ( ax = 0, j = 0; j < m; ++j, ax += t ) 
			for ( t = 0, i = 0; !t && i < n; ++i ) {
				for ( a = 0, b = 1; fabs(b-a) > tol; ) {
					na = (2*a+b)/3, nb = (a+2*b)/3;
					f(i,j,na)>f(i,j,nb)?(a=na):(b=nb);
				}
				dist = f(i,j,a);
				if ( dist < SQ(10000/acos(0.00)) ) goto nx;
				else ++t;
				nx: continue ;
			}
		printf("%d\n",ax);
	}
	return 0;
}
