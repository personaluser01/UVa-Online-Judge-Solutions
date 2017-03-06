/*
 * 12828. Arc and Point
 * TOPIC: geometry, rotation, trigonometry
 * status: Accepted
 */
#include <bits/stdc++.h>
#include <vector>
#define pi (2*acos(0.00))
#define NDEBUG
#define oo (1<<29)
#define tol 1e-9
using namespace std;

struct cell {
	double x,y;
	cell() {};
	cell( double x, double y ) { this->x = x, this->y = y; };
};

cell operator + ( const cell &a, const cell &b ) {
	cell r(a.x+b.x,a.y+b.y);
	return r;
};

cell operator - ( const cell &a, const cell &b ) {
	cell r(a.x-b.x,a.y-b.y);
	return r;
};

cell operator * ( const cell &a, const double &t ) {
	cell r(a.x*t,a.y*t);
	return r;
};

double operator , ( const cell &a, const cell &b ) {
	return a.x*b.x + a.y*b.y;
};

double cross( const cell &a, const cell &b ) {
	return a.x*b.y - a.y*b.x;
};

double operator ^ ( const cell &a, const cell &b ) {
	double A = sqrt((a,a)),
		   B = sqrt((b,b)),
		   co = (a,b)/A/B,
		   si = cross(a,b)/A/B;
	if ( fabs(co-1.00) < tol )
		return 0.00;
	if ( fabs(co+1.00) < tol )
		return pi;
	if ( fabs(si-1.00) < tol )
		return pi/2;
	if ( fabs(si+1.00) < tol )
		return 3*pi/2;
	if ( co >= 0 && si >= 0 )
		return acos(co);
	if ( co >= 0 && si <= 0 )
		return 2*pi+asin(si);
	if ( co <= 0 && si >= 0 )
		return acos(co);
	return pi+acos(-co);
};

double operator | ( const cell &a, const cell &b ) {
	double A = sqrt((a,a)),
		   B = sqrt((b,b)),
		   co = (a,b)/A/B,
		   si = cross(a,b)/A/B;
	if ( co >= 0 && si >= 0 )
		return acos(co);
	if ( co >= 0 && si <= 0 )
		return asin(si);
	if ( co <= 0 && si >= 0 )
		return acos(co);
	return -pi+acos(-co);
};

cell v[4],unit(1,0);

cell rotate( cell &e, double tau ) {
	cell r(e.x*cos(tau)-e.y*sin(tau),e.x*sin(tau)+e.y*cos(tau));
	return r;
};

int main() {
	int i,j,k,l,t,cs = 0;
	double det,dx,dy,r,dist,ans,low,high,tau,w;
	for (;2 == scanf("%lf %lf",&v[0].x,&v[0].y); ) {
		for ( i = 1; i < 4; scanf("%lf %lf",&v[i].x,&v[i].y), ++i );
		cell a = (v[0]+v[1])*.5, b = (v[1]+v[2])*0.5,
			 m = v[1]-v[0], n = v[2]-v[1],
			 c = a-b,u;
		det = (m.y*n.x-n.y*m.x);
		dx = (c.x*n.x+c.y*n.y)/det;
		dy = (m.y*c.y+m.x*c.x)/det;
		u.x = -m.y, u.y = m.x;
		u = a+u*dx;
		assert( 1 || fabs((u-a,m)) < tol );
		assert( 1 || fabs((u-b,n)) < tol );

		for ( i = 0; i < 4; v[i] = v[i]-u, ++i );
		r = sqrt((v[0],v[0]));
		assert( 1 || fabs(r*r-(v[1],v[1])) < tol );
		assert( 1 || fabs(r*r-(v[2],v[2])) < tol );
nx:
		double aa = v[0]^v[1],
			   bb = v[0]^v[2];
		if ( aa > bb ) {
			swap(v[0],v[2]);
			goto nx;
		}
		for ( tau = unit^v[0], i = 0; i < 4; v[i] = rotate(v[i],-tau), ++i );
		low=unit^v[0], high=unit^v[2];
		assert( 1 || fabs(low) < tol );

		vector<double> suspects;
		suspects.clear(), suspects.push_back(low), suspects.push_back(high);
		if ( fabs(u.x-v[3].x) < tol && fabs(u.y-v[3].y) < tol ) {
			w = r;
			goto next;
		}
		if ( low<=(tau=unit^v[3]) && tau<=high ) suspects.push_back(tau);
		for ( w = +oo, i = 0; i < (int)suspects.size(); ++i ) {
			cell q(cos(suspects[i]),sin(suspects[i]));
			q = q*r, w = min(w,sqrt((q-v[3],q-v[3])));
		}
next:
		printf("Case %d: %.3lf\n",++cs,w+tol);
	}
	return 0;
}

