/*
 * 11571. Simple Equations -- Extreme!
 * TOPIC: polynomials, roots
 * status: in progress, WA
 */
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define N 8
#define oo ((long double)(1ULL<<32))
#define tol 1e-10
typedef long long i64;

long double min( long double x, long double y ) { if ( x < y ) return x; return y; }

long double p[N],A,B,C,q[N],d,x0,x1,D,z[3];
int n;

long double eval( long double t ) { return t*t*t*p[3]+t*t*p[2]+t*p[1]+p[0]; }

int isint( long double t ) {
	i64 dt = (i64)(t+tol), ut = dt+1;
	return min(fabs(t-dt),fabs(ut-t)) < 1e-9;
}

int main() {
	int i,j,k,ts;
	long double low,mid,high;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( scanf("%d",&ts); ts--; ) {
		scanf("%Lf %Lf %Lf",&A,&B,&C);
		p[0] = -B, p[1] = (A*A-C)/2, p[2] = -A, p[3] = 1;
		for ( i = 2; i >= 0; q[i] = (i+1)*p[i+1], --i );
		d = q[1]*q[1]-4*q[0]*q[2], D = sqrt(d);
		x0 = (-q[1]-D)/2/q[2], x1 = (-q[1]+D)/2/q[2];
		assert( eval(-oo) < 0 );
		for ( low = -oo, high = x0; fabs(high-low) > tol; ) {
			mid = (low+high)/2;
			if ( eval(mid) < 0 ) low = mid;
			else high = mid;
		}
		z[0] = high;
		for ( low = x0, high = x1; fabs(high-low) > tol; ) {
			mid = (low+high)/2;
			if ( eval(mid) >= 0 ) low = mid;
			else high = mid;
		}
		z[1] = low;
		for ( low = x1, high = +oo; fabs(high-low) > tol; ) {
			mid = (low+high)/2;
			if ( eval(mid) > 0 ) high = mid;
			else low = mid;
		}
		z[2] = low;
		/*printf("Pre-solution %Lf %Lf %Lf\n",z[0]+tol,z[1]+tol,z[2]+tol);*/
		if ( isint(z[0]) && isint(z[1]) && isint(z[2]) && !(fabs(z[0]-z[1])<tol||fabs(z[1]-z[2])<tol||fabs(z[2]-z[0])<tol) ) {
			printf("%.Lf %.Lf %.Lf\n",z[0]+tol,z[1]+tol,z[2]+tol);
			continue ;
		}
		puts("No solution.");
	}
	return 0;
}

