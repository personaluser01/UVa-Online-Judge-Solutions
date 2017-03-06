/*
 * Packing Polygons
 * status: Accepted
 */
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iostream>
using namespace std;
#define N 0x80
#define KYLLA puts("The polygon can be packed in the circle.")
#define EI	  puts("There is no way of packing that polygon.")
#define tol 1e-7
#define DBG(x) (1)

int n,x[N],y[N];
double R;

double dist( double x0, double y0, double x1, double y1 ) {
	return ((x0-x1)*(x0-x1)+(y0-y1)*(y0-y1));
}

int center( double ox, double oy, int ii, int jj ) {
	for ( int i = 0; i < n; ++i ) {
		double tmp = dist(ox,oy,x[i],y[i]);
		if ( i == ii || i == jj )
			continue ;
		if ( fabs(tmp-R) <= tol )
			continue ;
		if ( tmp > R )
			return 0;
	}
	return 1;
}

int main() {
	int i,j;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	while ( 1 == scanf("%d",&n) && n > 0 ) {
		for ( i = 0; i < n; ++i )
			scanf("%d %d",x+i,y+i);
		scanf("%lf",&R), R = R*R;
		for ( i = 0; i < n; ++i )
			for ( j = i+1; j < n; ++j ) {
				double mx = (x[i]+x[j])/2.0,
					   my = (y[i]+y[j])/2.0,
					   a = x[i]-x[j],
					   b = y[i]-y[j],
					   c = -b,
					   d = a,
					   low,mid,high;
				if ( dist(mx,my,x[i],y[i]) > R )
					continue ;
				low = 0, high = (1 << 29);
				if ( fabs(dist(mx+c*low, my+d*low, x[i],y[i])-R) < tol ) {
					double ox = mx, oy = my;
					if ( center(ox,oy,i,j) ) {
						KYLLA;
						goto next;
					}
					else continue ;
				}
				assert( dist(mx+c*low, my+d*low, x[i],y[i]) < R );
				assert( dist(mx+c*high,my+d*high,x[i],y[i]) >= R );
				while ( fabs(high-low) >= tol ) {
					mid = (low+high)/2;
					if ( dist(mx+c*mid,my+d*mid,x[i],y[i]) < R )
						low = mid;
					else high = mid;
				}
				assert( dist(mx+c*low, my+d*low, x[i],y[i]) <= R );
				assert( dist(mx+c*high,my+d*high,x[i],y[i]) >= R );
				double ox = mx + c*high,
					   oy = my + d*high;
				DBG(printf("%lf %lf\n",ox,oy));
				DBG(printf("%lf %lf\n",dist(ox,oy,x[j],y[j]),R));
				if ( center(ox,oy,i,j) ) {
					DBG(printf("Center is (%lf,%lf)\n",ox,oy));
					KYLLA;
					goto next;
				}
				ox = x[i]+x[j]-ox, oy = y[i]+y[j]-oy;
				DBG(printf("%lf %lf\n",ox,oy));
				DBG(printf("%lf %lf\n",dist(ox,oy,x[i],y[i]),R));
				if ( center(ox,oy,i,j) ) {
					DBG(printf("Center is (%lf,%lf)\n",ox,oy));
					KYLLA;
					goto next;
				}
			}
			EI;
			next: continue;
	}
	return 0;
}

