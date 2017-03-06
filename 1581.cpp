/*
 * 1581. Pollution Solution
 * TOPIC: geometry, world finals, angles, trigonomtery
 * status: Accepted
 */
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <cmath>
#define DIM 3
#define N 0x80
#define tol 1e-13
using namespace std;

long double S( long double t ) { return t*t; };
const long double pi = 2*acos(0.00);

bool equal( long double x, long double y ) { return fabs(x-y) < tol; };

struct cell {
	long double x[DIM];
	cell() { memset(x,0,sizeof x); };
	cell( long double a, long double b, long double c ) {
		0[x] = a, 1[x] = b, 2[x] = c;
	};
	long double operator [] ( int i ) const { return x[i]; };
	long double getlen() const {
		long double s = 0;
		for ( int i = 0; i < DIM; s += x[i]*x[i], ++i );
		return sqrt(s);
	};
};

cell ZERO;

bool operator < ( const cell &a, const cell &b ) {
	for ( int i = 0; i < DIM; ++i )
		if ( !equal(a[i],b[i]) )
			return a[i] < b[i];
	return false ;
};

bool operator == ( const cell &a, const cell &b ) { return !(a<b||b<a); };

cell operator + ( const cell &a, const cell &b ) {
	cell r;
	for ( int i = 0; i < DIM; r.x[i] = a[i]+b[i], ++i );
	return r;
};
cell operator - ( const cell &a, const cell &b ) {
	cell r;
	for ( int i = 0; i < DIM; r.x[i] = a[i]-b[i], ++i );
	return r;
};
long double operator , ( const cell &a, const cell &b ) {
	long double s = 0;
	for ( int i = 0; i < DIM; s += a[i]*b[i], ++i );
	return s;
};
cell operator * ( const cell &a, long double t ) {
	cell r;
	for ( int i = 0; i < DIM; r.x[i] = a[i]*t, ++i );
	return r;
};
cell operator * ( long double t, const cell &a ) {
	cell r;
	for ( int i = 0; i < DIM; r.x[i] = a[i]*t, ++i );
	return r;
};
cell operator * ( const cell &a, const cell &b ) {
	cell r;
	for ( int j,k,i = 0; i < DIM; ++i )
		k=((j=(i+1)%DIM)+1)%DIM, r.x[i] = a[j]*b[k]-a[k]*b[j];
	return r;
};
cell operator / ( const cell &a, long double t ) {
	cell r;
	for ( int i = 0; i < DIM; r.x[i] = a[i]/t, ++i );
	return r;
};
void operator /= ( cell &a, long double t ) {
	for ( int i = 0; i < DIM; a.x[i++] /= t );
}
void operator *= ( cell &a, long double t ) {
	for ( int i = 0; i < DIM; a.x[i++] *= t );
}
cell operator ~ ( const cell &a ) { return a/a.getlen(); };
long double operator ^ ( const cell &a, const cell &b ) {
	assert( !(a == ZERO) );
	assert( !(b == ZERO) );
	cell na = ~a, nb = ~b;
	long double co = (na,nb), si = (na*nb)[DIM-1];
	co = min((long double)1.00,max((long double)-1.00,co));
	si = min((long double)1.00,max((long double)-1.00,si));
	if ( fabs(co-1.00) < tol )
		return 0.00;
	if ( fabs(co+1.00) < tol )
		return pi;
	if ( co >= 0 && si >= 0 )
		return acos(co);
	if ( co >= 0 && si <= 0 )
		return asin(si);
	if ( co <= 0 && si >= 0 )
		return acos(co);
	return -pi+acos(-co);
};

long double R;
int n;
cell unit(1,0,0),c[N];

long double f( cell *p ) {
	cell m = p[1]-p[0], u[2], q[] = {R*(~p[0]),R*(~p[1])};
	long double a = (m,m), b = 2*(p[0],m), c = (p[0],p[0])-S(R), d = S(b)-4*a*c, D, tau[2], r = S(R);

	if ( d <= 0 ) {
		0 && puts("Case 1");
		return r*(q[0]^q[1])/2;
	}

	D = sqrt(d), tau[0] = (-b-D)/(2*a), tau[1] = (-b+D)/(2*a);

	if ( tau[0] >= 1 || tau[1] <= 0 ) {
		0 && puts("Case 2");
		return r*(q[0]^q[1])/2;
	}

	if ( tau[0] <= 0 && tau[1] >= 1 ) {
		0 && puts("Case 3");
		return (p[0]*p[1])[DIM-1]/2;
	}

	for ( int i = 0; i < 2; u[i] = p[0]+tau[i]*m, ++i );

	if ( 0 <= tau[0] && tau[1] <= 1 )  {
		0 && puts("Case 4");
		return (r*(q[0]^u[0])+(u[0]*u[1])[DIM-1]+r*(u[1]^q[1]))/2;
	}

	if ( 0 <= tau[0] && tau[0] <= 1 ) {
		0 && puts("Case 5");
		return (r*(q[0]^u[0])+(u[0]*p[1])[DIM-1])/2;
	}

	if ( 0 <= tau[1] && tau[1] <= 1 ) {
		0 && puts("Case 6");
		return ((p[0]*u[1])[DIM-1]+r*(u[1]^q[1]))/2;
	}
	assert( 0 );
};

int main() {
	int i,j,k;
	long double s,ds;
#ifndef ONLINE_JUDGE
	freopen("1581.in","r",stdin);
#endif
	for (;2==scanf("%d %Lf",&n,&R)&&n>0;printf("%.9Lf\n",s+1e-14)) {
		for ( i = 0; i < n; ++i )
			for ( j = 0; j < DIM-1; scanf("%Lf",c[i].x+j), ++j );
		for ( c[n] = c[0], s = 0, i = 0; i < n; s += (ds=f(c+i)), ++i );
	}
	return 0;
};

