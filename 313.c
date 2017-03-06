/*
 * 313. Intervals
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
#define N 512
#define tol 1e-9
#define DIM 2
#define pi (2*acos(0.00))

int n;
long double b[DIM],c[N][DIM],r[N],u[DIM],v[DIM],L,ang,A[N],B[N],p[N],q[N];

long double dist( long double *c, long double t ) {
	long double A,B,C,co = cos(t),si = sin(t);
	A = si, B = -co, C = -si*b[0]+co*b[1];
	return fabs(A*c[0]+B*c[1]+C);
}

long double max( long double x, long double y ) { return x < y ? y : x; }

long double get_ang( long double a, long double b, long double c, long double d ) {
	long double sine,cose,ang,L = sqrt((a*a+b*b)*(c*c+d*d));
	assert( fabs(L) > tol );
	sine = (a*d-c*b)/L;
	cose = (a*c+b*d)/L;
	if ( cose >= 0 && sine >= 0 ) 
		ang = acos(cose);
	else if ( cose <= 0 && sine >= 0 ) 
		ang = acos(cose);
	else if ( cose >= 0 && sine <= 0 ) 
		ang = asin(sine);
	else 
		ang = -pi+acos(-cose);
	return ang;
}

void xchg( long double *a, long double *b ) {
	long double t = *a;
	*a = *b, *b = t;
}

int main() {
	long double cose,sine,good,bad,mid,xx,yy,hyp,left,right;
	int i,j,k;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for (;1 == scanf("%d",&n) && n; putchar('\n') ) {
		for ( i = 0; i < DIM; scanf("%Lf",b+i), ++i );
		for ( i = 0; i < n; scanf("%Lf",&r[i++]) ) 
			for ( j = 0; j < DIM; scanf("%Lf",c[i]+j), ++j );
		for ( i = 0; i < n; ++i ) {
			memset(v,0,sizeof(v));
			for ( L = 0, v[0] = 1, j = 0; j < DIM; ++j )
				u[j] = c[i][j]-b[j], L += u[j]*u[j];
			ang = get_ang(v[0],v[1],u[0],u[1]);
			assert( ang < 0 );
			for ( good = ang, bad = 0; fabs(good-bad) > tol; dist(c[i],mid=(good+bad)/2)<=r[i]?(good=mid):(bad=mid) );
			assert( -pi <= good );
			assert( good < 0 );
			hyp = fabs(b[1]/sin(good));
			B[i] = xx = b[0] + hyp*cos(good), yy = b[1] + hyp*sin(good);
			assert( fabs(yy) < tol );
			ang = get_ang(c[i][0]-b[0],c[i][1]-b[1],xx-b[0],yy-b[1]);
			assert( ang >= 0 );
			good -= 2*ang;
			hyp = fabs(b[1]/sin(good));
			A[i] = xx = b[0] + hyp*cos(good), yy = b[1] + hyp*sin(good);
			assert( fabs(yy) < tol );
			assert( A[i] <= B[i] );
		}
		for ( j = 1; j; )
			for ( i = j = 0; i < n-1; ++i )
				if ( A[i] > A[i+1] && ++j )
					xchg(A+i,A+i+1), xchg(B+i,B+i+1);
		left = A[0], right = B[0];
		for ( k = 0, i = 1; i < n; ++i ) 
			A[i] <= right ? (right = max(right,B[i])) : (p[k] = left, q[k] = right, ++k, left = A[i], right = B[i]);
		if ( left < right ) p[k] = left, q[k] = right, ++k;
		for ( i = 0; i < k; ++i )
			printf("%.2Lf %.2Lf\n",p[i],q[i]);
	}
	return 0;
}
