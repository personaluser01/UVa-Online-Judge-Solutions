/*
 * 10697. Firemen Barracks
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
#define eps 1e-12
#define oo (DBL_MAX-1024)
#define pi (2*acos(0.00))
#define SQ(x) ((x)*(x))

int ts;
long double x[3],y[3];
char s[0x400],r[0x400];

void f( long double x, char *s ) {
	long double xx;
	int a,b,d;
	if ( fabs(x) < 0.05 ) {
ok:
		sprintf(s,"0.0");
		return ;
	}
	xx = (x)*100;
	/*
	printf("%Lf %Lf\n",x,xx);
	*/
	if ( ((int)(fabs(xx)+eps)) == 0 ) 
		goto ok;

	d = ((int)(fabs(xx)+eps)) % 10;
	a = ((int)(fabs(xx)+eps)) / 100;
	/*
	if ( (int)(x)+12798400 == 0 ) {
		sprintf(s,"-%d.0",a);
		return ;
	}
	if ( a-12799200 == 0 ) {
		sprintf(s,"%d.0",a);
		return ;
	}
	*/
	b = (((int)(fabs(xx)+eps)) - 100*a - d) / 10;
	/*printf("a = %d, b = %d, d = %d\n",a,b,d);*/
	if ( d >= 5 ) ++b;
	if ( b == 10 ) b = 0, ++a;
	if ( x < 0 ) {
		sprintf(s,"-%d.%d",a,b);
	}
	else {
		sprintf(s,"%d.%d",a,b);
	}
}

long double angle( long double a, long double b, long double c, long double d ) {
	long double L = sqrt((a*a+b*b)*(c*c+d*d)),
				co = (a*c + b*d)/L,
		 		si = (a*d - b*c)/L;
	if ( co >= 0 && si >= 0 )
		return asin(si);
	if ( co >= 0 && si <= 0 )
		return asin(si);
	if ( co <= 0 && si >= 0 )
		return acos(co);
	return -pi+acos(-co);
}

long double dist( long double x0, long double y0, long double x1, long double y1 ) {
	return (SQ(x0-x1)+SQ(y0-y1));
}

long double Diff( long double a, long double b, long double c, long double d, long double e, long double f ) {
	return SQ(c)-SQ(e)+SQ(d)-SQ(f)+2*a*(e-c)+2*b*(f-d);
}

int main() {
	int i,j,k;
	long double area,ux,uy,vx,vy,x0,y0,t,m,n,
		 low,high,diff,d,ang,c0,c1,det,mm,nn;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( scanf("%d",&ts); ts--; ) {
		for ( i = 0; i < 3; ++i )
			scanf("%Lf %Lf",x+i,y+i);
		ux = x[1]-x[0], uy = y[1]-y[0];
		vx = x[2]-x[0], vy = y[2]-y[0];
		area = ux*vy - uy*vx;
		if ( fabs(area) < tol ) {
			for ( k = 0, i = 0; i < 3; ++i )
				for ( j = i+1; j < 3; ++j )
					if ( fabs(x[i]-x[j])>tol||fabs(y[i]-y[j])>tol )
						++k;
			if ( k == 3 ) {
				puts("There is no possible location.");
				goto next;
			}
			puts("There is an infinity of possible locations.");
			goto next;
		}
		for ( i = 0; i < 3; ++i ) {
			x0 = (x[i]+x[(i+1)%3])/2, y0 = (y[i]+y[(i+1)%3])/2;
			if ( fabs(dist(x0,y0,x[i],y[i])-dist(x0,y0,x[(i+2)%3],y[(i+2)%3])) < tol ) {
				printf("The equidistant location is (%.1Lf, %.1Lf).\n",x0+eps,y0+eps);
				goto next;
			}
		}
		x0 = (x[0]+x[1])/2, y0 = (y[0]+y[1])/2;
		m = -(y[1]-y[0]), n = (x[1]-x[0]);
		ang = angle(x[1]-x[0],y[1]-y[0],m,n);
		if ( angle(x[1]-x[0],y[1]-y[0],m,n)*angle(x[1]-x[0],y[1]-y[0],x[2]-x[0],y[2]-y[0]) < 0 )
			m = -m, n = -n;
		/*
		high = +oo, low = 0;
		diff = (dist(x0,y0,x[1],y[1])-dist(x0,y0,x[2],y[2]))<0?-1:1;
		for(; fabs(high-low) > tol;) {
			t = (low+high)/2;
			if ( diff < 0 ) {
				(d = (Diff(x0+t*m,y0+t*n,x[1],y[1],x[2],y[2]))) < 0 ? (low = t) : (high = t);
			}
			else {
				(d = (Diff(x0+t*m,y0+t*n,x[1],y[1],x[2],y[2]))) > 0 ? (low = t) : (high = t);
			}
			printf("%Lf %Lf %Lf %Lf\n",low,high,t,d);
		}
		t = high;
		*/
		mm = -(y[2]-y[0]), nn = (x[2]-x[0]);
		c0 = (x[2]-x[1])/2;
		c1 = (y[2]-y[1])/2;
		det = mm*n-nn*m;
		assert( fabs(det) > tol );
		t = mm/det*c1-nn/det*c0;
		printf("The equidistant location is (%s, %s).\n",(f(x0+m*t,s),s),(f(y0+n*t,r),r));
		next: continue ;
	}
	return 0;
}
