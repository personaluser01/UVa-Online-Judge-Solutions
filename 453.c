/*
 * KEYWORDS: Coordinate Transformation
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define tol 1e-4
#define eps 1e-4

double sqr( double x ) { return x*x; }

double x[2],y[2],r[2],sx,sy,p,q,s,a,b,tx,ty,w,
	   cose,sine;

int main() {
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	while ( 3 == scanf("%lf %lf %lf",x,y,r) ) {
		scanf("%lf %lf %lf",x+1,y+1,r+1);
		w = sqrt(sqr(x[0]-x[1])+sqr(y[0]-y[1]));
		if ( w >= r[0]+r[1]+tol ) {
			nx: puts("NO INTERSECTION");
			continue ;
		}
		if ( fabs(x[0]-x[1]) < tol && fabs(y[0]-y[1]) < tol && fabs(r[0]-r[1]) < tol ) {
			if ( fabs(r[0]) < tol ) {
				printf("(%.3lf,%.3lf)\n",x[0]+tol,y[0]+tol);
				continue ;
			}
			nosol: puts("THE CIRCLES ARE THE SAME");
			continue ;
		}
		p = x[1]-x[0], q = y[1]-y[0], w = sqrt(sqr(p)+sqr(q));
		if ( fabs(x[0]-x[1]) < tol && fabs(y[0]-y[1]) < tol )
			goto nx;
		a = x[0], b = y[0];
		x[1] -= a, y[1] -= b, x[0] = y[0] = 0;
		assert( w > tol );
		cose = p/w, sine = q/w;
		p = x[1], q = y[1];
		x[1] = cose*p+sine*q;
		y[1] = -sine*p+cose*q;
		assert( fabs(y[1]) < tol );
		assert( fabs(x[1]) > tol );
		sx = (sqr(r[0])-sqr(r[1])+sqr(x[1]))/2.0/x[1];
		if ( sqr(r[0])+tol < sqr(sx) )  
			goto nx;
		sy =  sqrt(sqr(r[0])-sqr(sx)+1e-9);
		ty = -sqrt(sqr(r[0])-sqr(sx)+1e-9);
		
		p = sx, q = sy, s = ty;
		sx = p*cose - q*sine + a;
		sy = p*sine + q*cose + b;
		tx = p*cose - s*sine + a;
		ty = p*sine + s*cose + b;

		if ( fabs(ty-sy) < tol && fabs(tx-sx) < tol ) {
			printf("(%.3lf,%.3lf)\n",sx+eps,sy+eps);
		}
		else {
			if ( sx < tx || (fabs(sx-tx) < tol && sy < ty) ) {
				/*printf("(%.3lf,%.3lf)(%.3lf,%.3lf)\n",sx+tol,sy+tol,tx+tol,ty+tol);*/
				printf("(%.3lf,%.3lf)(%.3lf,%.3lf)\n",sx+eps,sy+eps,tx+eps,ty+eps);
			}
			else {
				/*printf("(%.3lf,%.3lf)(%.3lf,%.3lf)\n",tx+tol,ty+tol,sx+tol,sy+tol);*/
				printf("(%.3lf,%.3lf)(%.3lf,%.3lf)\n",tx+eps,ty+eps,sx+eps,sy+eps);
			}
		}
	}
	return 0;
}

