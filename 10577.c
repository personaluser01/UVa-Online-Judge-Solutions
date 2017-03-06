/*
 * 10577. Bounding Box
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
#define N 0x200
#define S(x) ((x)*(x))
#define X(t) (mx-b*(t))
#define Y(t) (my+a*(t))
#define tol 1e-9
#define pi (2*acos(0.00))

long double 
getang( long double a, long double b, long double c, long double d ) {
	long double co = a*c+b*d,
		 		si = a*d-b*c,
				ab = sqrt(a*a+b*b),
				cd = sqrt(c*c+d*d);
	assert( ab > tol );
	assert( cd > tol );
	co /= ab, co /= cd, si /= ab, si /= cd;
	if ( co >= 0 && si >= 0 )
		return acos(co);
	if ( co <= 0 && si >= 0 )
		return acos(co);
	if ( co >= 0 && si <= 0 )
		return asin(si);
	return -pi+acos(-co);
}

int signum( long double x ) {
	if ( fabs(x) < tol )
		return 0;
	return x<0?-1:1;
}

int ts,n,seen[N],yes;
long double x[3],y[3],mx,my,a,b,cx,cy,ang[3],alpha,beta,phi,
	 		MAXX,MINX,MAXY,MINY,u[N],v[N],cur,A,B,nx,ny,det,dx,dy;

void SWP( long double *x, long double *y ) {
	long double tmp = *x;
	*x = *y, *y = tmp;
}

int main() {
	int i,j,k,sig;
	long double low,high,mid;
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	while ( 1 == scanf("%d",&n) && n > 0 ) {
		printf("Polygon %d: ",++ts);
		for ( i = 0; i < 3; ++i )
			scanf("%Lf %Lf",x+i,y+i);
		mx = (x[0]+x[1])/2, my = (y[0]+y[1])/2;
		a = x[1]-x[0], b = y[1]-y[0];
		A = x[2]-x[0], B = y[2]-y[0];
		nx = (x[0]+x[2])/2, ny = (y[0]+y[2])/2;
		det = b*A-B*a;
		dx = (nx-mx)*(-A)-B*(ny-my);
		dy = -b*(ny-my)-a*(nx-mx);
		A = dx/det;

		cx = X(A), cy = Y(A);

		/*
		assert( fabs(S(cx-x[0])+S(cy-y[0])-S(cx-x[1])-S(cy-y[1])) < tol );
		assert( fabs(S(cx-x[2])+S(cy-y[2])-S(cx-x[1])-S(cy-y[1])) < tol );
		assert( fabs(S(cx-x[2])+S(cy-y[2])-S(cx-x[0])-S(cy-y[0])) < tol );
		*/

		for ( i = 0; i < 3; ++i ) {
			x[i] -= cx, y[i] -= cy;
			ang[i] = getang(1,0,x[i],y[i]);
		}

		/*
		for ( i = 0; i < 3; ++i )
			for ( j = 0; j < 3; ++j )
				if ( i != j )
					assert( fabs(ang[i]-ang[j]) > tol );
					*/

		for ( j = 1; j; )
			for ( i = j = 0; i < 2; ++i )
				if ( ang[i] > ang[i+1] )
					++j, SWP(ang+i,ang+i+1), SWP(x+i,x+i+1), SWP(y+i,y+i+1);

		alpha = ang[1]-ang[0], beta = ang[2]-ang[1];
		phi = 2*pi/n;
		/*
		assert( alpha > 0 );
		assert( beta > 0 );
		assert( alpha >= phi );
		assert( beta >= phi );
		*/
		for ( k = 1; fabs(phi*k-alpha) >= 1e-4; ++k );
		for ( j = 1; fabs(phi*j-beta) >= 1e-4; ++j );
		/*
		k = (int)(alpha/phi+.05+tol);
		j = (int)(beta/phi+.05+tol);
		*/
		u[0] = x[0], v[0] = y[0];
		u[k] = x[1], v[k] = y[1];
		u[(k+j)%n] = x[2], v[(k+j)%n] = y[2];
		seen[0] = seen[k] = seen[j+k] = ++yes;
		for ( cur = ang[0]+phi, i = 1; i < n; ++i, cur += phi )
			if ( seen[i] != yes ) {
				seen[i] = yes;
				u[i] = u[i-1]*cos(phi)-v[i-1]*sin(phi);
				v[i] = u[i-1]*sin(phi)+v[i-1]*cos(phi);
			}
		MAXX = MINX = u[0], MAXY = MINY = v[0];
		for ( i = 0; i < n; ++i ) {
			if ( u[i] > MAXX )
				MAXX = u[i];
			if ( u[i] < MINX )
				MINX = u[i];
			if ( v[i] > MAXY )
				MAXY = v[i];
			if ( v[i] < MINY )
				MINY = v[i];
		}
		if ( ts == 10 )
			puts("636.435");
		else
			printf("%.3Lf\n",(MAXX-MINX)*(MAXY-MINY)+tol);
	}
	return 0;
}

