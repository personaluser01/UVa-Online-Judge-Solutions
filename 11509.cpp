/*
 * 11509. Touring Robot
 * TOPIC: computational geometry, angle between vectors
 * status: Accepted
 */
#include <cassert>
#include <cstdio>
#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <cmath>
#include <vector>
#define NDEBUG
using namespace std;
#define N (1 << 20)
#define DIM 3
#define tol 1e-9
#define pi (2*acos(0.00))

typedef struct { double x[DIM]; } cell;
cell c[N],x_unit,y_unit,cur;

int n;

double operator ,( const cell &a, const cell &b ) {
	double s = 0;
	for ( int i = 0; i < DIM; ++i ) s += a.x[i]*b.x[i];
	return s;
}

cell operator *( const cell &a, const cell &b ) {
	int i,j,k;
	cell r;
	for ( i = 0; i < DIM; ++i ) {
		j = (i+1)%DIM, k = (j+1)%DIM;
		r.x[i] = a.x[j]*b.x[k]-a.x[k]*b.x[j];
	}
	return r;
}

double len( const cell &a ) { return sqrt((a,a)); }

double operator^( const cell &a, const cell &b ) {
	cell r = a*b;
	double co = (a,b),si = r.x[DIM-1],A = len(a), B = len(b);
	// assert( A > 0 );
	// assert( B > 0 );
	co /= A, co /= B, si /= A, si /= B;
	// printf("u = {%lf,%lf}, v = {%lf,%lf}\n",a.x[0],a.x[1],b.x[0],b.x[1]);
	// assert( fabs(co) <= 1 );
	// assert( fabs(si) <= 1 );
	if ( fabs(co-1.00) < tol ) 
		return 0;
	if ( fabs(co+1.00) < tol )
		return pi;
	if ( fabs(si-1.00) < tol )
		return pi/2;
	if ( fabs(si+1.0) < tol )
		return 3*pi/2;
	if ( co >= 0 && si >= 0 )
		return acos(co);
	if ( co >= 0 && si <= 0 )
		return 2*pi+asin(si);
	if ( co <= 0 && si >= 0 )
		return acos(co);
	return pi+asin(-si);
}

cell operator - (const cell &a, const cell &b ) {
	cell c;
	for ( int i = 0; i < DIM; c.x[i] = a.x[i]-b.x[i], ++i );
	return c;
}

int main() {
	int i,j,k;
	double h,ang,ans;
	cell cur;
#ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
#endif
	x_unit.x[0] = y_unit.x[1] = 1, cur.x[DIM-1] = 0;
	for (;1 == scanf("%d",&n) && n > 0;) {
		for ( i = 0; i < n; scanf("%lf %lf",c[i].x,c[i].x+1), c[i].x[DIM-1] = 0, ++i );
		// for ( i = 0; i < 2; ++i ) printf("c[%d] = (%lf,%lf)\n",i,c[i].x[0],c[i].x[1]);
		if ( n == 2 ) {
			puts("1");
			continue ;
		}
		if ( n == 1 ) {
			puts("0");
			continue ;
		}
		c[n] = c[0], ++n, c[n] = c[1], ++n;
		//error with c[n++] = c[0], c[n++] = c[1];
		for(/*printf("n = %d\n",n),*/ cur=(c[1]-c[0]),k=0,i=2,ans=0;i<n;h=ang,++i) {
			//printf("c[%d] = (%lf,%lf)\n",i,c[i].x[0],c[i].x[1]);
			ang=cur^(c[i]-c[i-1]), ans += ang, 0&&printf("%lf\n",ang/pi*180.00), cur = (c[i]-c[i-1]);
		}
		// for(;ans<=0;ans+=2*pi);
		printf("%.0lf\n",ans/(2*pi));
		// printf("%lf\n",((ans/pi*180)+tol));
	}
    return 0;
}

