/*
 * 11168. Airport
 * TOPIC: convex hull, graham scan, center of gravity, barycenter
 * status: Accepted
 */
#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cfloat>
#include <iostream>
#include <set>
#define DIM 3
#define N (1<<17)
#define tol 1e-9
#define oo (DBL_MAX-0x400)
using namespace std;

int n;
const double pi = (2*acos(0.00));

struct cell {
	double x[DIM];
	cell() { memset(x,0,sizeof x); }
	cell( double a, double b ) {
		0[x] = a, 1[x] = b, 2[x] = 0;
	}
	double operator [] ( int i ) const {
		return x[i];
	}
	double ang, dist;
};

cell operator + ( const cell &a, const cell &b ) {
	cell r;
	for ( int i = 0; i < DIM; r.x[i] = a[i]+b[i], ++i );
	return r;
}
cell operator - ( const cell &a, const cell &b ) {
	cell r;
	for ( int i = 0; i < DIM; r.x[i] = a[i]-b[i], ++i );
	return r;
}
cell operator / ( const cell &a, const double &t ) {
	cell r;
	for ( int i = 0; i < DIM; r.x[i] = a[i]/t, ++i );
	return r;
}
void operator /= ( cell &a, const double &t ) {
	for ( int i = 0; i < DIM; a.x[i++] /= t );
}
void operator += ( cell &a, const cell &b ) {
	for ( int i = 0; i < DIM; a.x[i] += b[i], ++i );
}
void operator -= ( cell &a, const cell &b ) {
	for ( int i = 0; i < DIM; a.x[i] -= b[i], ++i );
}

double operator , ( const cell &a, const cell &b ) {
	double s = 0;
	for ( int i = 0; i < DIM; s += a[i]*b[i], ++i );
	return s;
}
cell operator ^ ( const cell &a, const cell &b ) {
	cell r;
	for ( int j,k,i = 0; i < DIM; ++i )
		j = (i+1)%DIM, k = (j+1)%DIM, r.x[i] = a[j]*b[k]-a[k]*b[j];
	return r;
}
double operator | ( const cell &a, const cell &b ) {
	double A = sqrt((a,a)), B = sqrt((b,b)), 
		   co = (a,b)/A/B, si = (a^b)[DIM-1]/A/B;
	if ( fabs(co-1.00) < tol )
		return 0.00;
	if ( fabs(co+1.00) < tol )
		return -pi;
	if ( co >= 0 && si >= 0 )
		return acos(co);
	if ( co >= 0 && si <= 0 )
		return asin(si);
	if ( co <= 0 && si >= 0 )
		return acos(co);
	return -pi+acos(-co);
}
bool operator < ( const cell &a, const cell &b ) {
	for ( int i = 0; i < DIM; ++i )
		if ( fabs(a[i]-b[i]) >= tol )
			return a[i]<b[i];
	return false ;
}
double dist( const cell &p, const cell &a, const cell &b ) {
	cell m = b-a, u = a-p;
	double A = (m,m), B = 2*(m,u), C = (u,u), t = -B/2/A;
	return (A*t*t + B*t + C);
}

cell c[N], unit(1,0), ZERO, a[N], ch[N], original[N];
int m,st[N],*top,nn;

struct comp {
	bool operator() ( const cell &a, const cell &b ) const {
		if ( fabs(a.ang-b.ang) < tol ) 
			return a.dist>b.dist;
		return a.ang<b.ang;
	}
};

bool is_left_turn( const cell &a, const cell &b, const cell &c ) {
	cell u = b-a, v = c-b;
	double scalar = (u,v), outer = (u^v)[DIM-1];
	if ( fabs(outer) < tol ) {
		assert(scalar > 0);
		return false ;
	}
	return outer > 0;
}

int main() {
	int i,j,k,cs = 0,ts;
	cell pole,sum;
	double w;
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	for ( scanf("%d",&ts); ts-- && 1 == scanf("%d",&n) && printf("Case #%d: ",++cs); ) {
		for ( nn = 0, i = 0; i < n; scanf("%lf %lf",&c[i].x[0],&c[i].x[1]), original[nn++] = c[i], ++i );
		if ( n <= 2 ) {
			puts("0.000");
			continue ;
		}
		assert( n >= 3 );
		for ( sort(c,c+n), pole = c[0], i = 1; i < n; c[i] = c[i]-pole, ++i );
		for ( i = 0; i < nn; original[i++] -= pole );
		for ( c[0] = ZERO, i = 1; i < n; c[i].dist = (c[i],c[i]), c[i].ang = (unit|c[i]), ++i );
		for ( sort(c+1,c+n,comp()), m = 0, a[m++] = c[0], i = 1; i < n; a[m++] = c[i], i = j ) 
			for ( j = i+1; j < n && fabs(c[j].ang-c[i].ang) < tol; ++j );
		for ( top = st, *++top = 0, *++top = 1, *++top = 2, i = 3; i < m; *++top = i++ )
			for ( ;top-st>=2 && !is_left_turn(a[*(top-1)],a[*top],a[i]); --top );
		for ( m = 0, i = 1; i <= top-st; ch[m++] = a[st[i++]] );
		for ( sum = ZERO, i = 0; i < nn; sum += original[i++] );
		for ( sum /= nn, w = +oo, i = 0; i < m; ++i ) 
			j = (i+1)%m, w = min(w,dist(sum,ch[i],ch[j]));
		printf("%.3lf\n",sqrt(w));
	}
	return 0;
}


