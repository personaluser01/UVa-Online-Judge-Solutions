/*
 * 12395. Regular Convex Polygon
 * TOPIC: geometry
 * status: Accepted
 */
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>
#include <cmath>
#include <set>
#define DIM 3
#define N 0x400
#define tol 1e-6
using namespace std;
#define FG (ptr = fgets(buff,sizeof buff,stdin))

char buff[0x400],*ptr;
const long double pi = 2*acos(0.00);

struct cell {
	long double x[DIM];
	cell() { 0[x]=1[x]=2[x]=0; };
	cell( long double X, long double Y, long double Z ) { 0[x] = X, 1[x] = Y, 2[x] = Z; };
	long double operator [] ( int i ) const { return this->x[i]; };
	bool read() { return 2 == sscanf(buff,"%Lf %Lf",x,x+1); };
	long double getlen() const {
		long double s = 0;
		for ( int i = 0; i < DIM; s += x[i]*x[i], ++i );
		return sqrt(s);
	};
};

bool operator < ( const cell &a, const cell &b ) {
	for ( int i = 0; i < DIM; ++i )
		if ( fabs(a[i]-b[i]) >= tol )
			return a[i]<b[i];
	return false;
};

bool operator == ( const cell &a, const cell &b ) { return !(a<b||b<a); }

cell operator + ( const cell &a, const cell &b ) { return cell(a[0]+b[0],a[1]+b[1],a[2]+b[2]); }
cell operator - ( const cell &a, const cell &b ) { return cell(a[0]-b[0],a[1]-b[1],a[2]-b[2]); }
cell operator * ( const cell &a, const cell &b ) {
	cell r;
	for ( int j,k,i = 0; i < DIM; ++i )
		k = ((j=(i+1)%DIM)+1)%DIM, r.x[i] = a[j]*b[k]-a[k]*b[j];
	return r;
};
long double operator , ( const cell &a, const cell &b ) {
	long double s = 0;
	for ( int i = 0; i < DIM; s += a[i]*b[i], ++i );
	return s;
};
cell operator ^ ( const cell &a, const long double &t ) {
	long double co = cos(t), si = sin(t);
	return cell(a[0]*co-a[1]*si,a[0]*si+a[1]*co,0);
};
cell operator * ( const cell &a, const long double &t ) {
	return cell(a[0]*t,a[1]*t,a[2]*t);
};
cell operator / ( const cell &a, const long double &t ) {
	return cell(a[0]/t,a[1]/t,a[2]/t);
};

cell center,c[3],p[N],cur;
set<cell> s;
long double R,phi,CO,SI;

cell rot( cell &c ) { return cell(CO*c[0]-SI*c[1],SI*c[0]+CO*c[1],0); };

long double operator | ( const cell &a, const cell &b ) {
	long double A = a.getlen(), B = b.getlen(),
		 co = (a,b)/A/B, si = (a*b).x[DIM-1]/A/B;
	if ( fabs(co-1) < tol ) 
		return 0.00;
	if ( fabs(co+1) < tol )
		return pi;
	if ( co >= 0 && si >= 0 )
		return acos(co);
	if ( co >= 0 && si <= 0 )
		return 2*pi+asin(si);
	if ( co <= 0 && si >= 0 )
		return acos(co);
	return pi+acos(-co);
};

int main() {
	int i,j,k,nn,ui,uj;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( ;FG && *ptr != 'E'; printf("%d\n",nn) ) {
		assert( c[0].read() );
		for ( i = 1; i < 3; ++i ) 
			assert( FG && c[i].read() );
		cell c01 = (c[0]+c[1])/2, c12 = (c[1]+c[2])/2,
			 m = (c[1]-c[0]), n = (c[2]-c[1]);
		long double det = m[0]*n[1]-m[1]*n[0], 
			 dx = (c01,m)*n[1]-(c12,n)*m[1],
			 dy = m[0]*(c12,n)-n[0]*(c01,m);
		center.x[0] = dx/det, center.x[1] = dy/det;
		assert ( fabs((center-c01,m)) < tol );
		assert ( fabs((center-c12,n)) < tol );
		R = (center-c[0]).getlen();
		long double A = (c[0]-center)|(c[1]-center),
			 		B = (c[0]-center)|(c[2]-center);
		for ( nn = 3; nn < N; ++nn ) {
			phi = 2*pi/nn;
			i = (int)(A/phi), j = (int)(B/phi);
			ui = i+1, uj = j+1;
			if ( fabs(ui-A/phi) < fabs(i-A/phi) ) i = ui;
			if ( fabs(uj-B/phi) < fabs(j-B/phi) ) j = uj;
			//printf("%Lf, %Lf\n",A*180/pi,B*180/pi);
			//printf("%Lf, %Lf\n",A/phi,B/phi);
			//printf("i = %d, j = %d\n",i,j);
			//break ;
			if ( fabs(i*phi-A) < tol && fabs(j*phi-B) < tol )
				break ;
		}
	}
	return 0;
};

