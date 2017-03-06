/*
 * 12240. Cocircular Points
 * TOPIC: geometry
 * status: Accepted
 */
#include <cassert>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>
#define N 0x80
#define DIM 3
#include <cmath>
#define tol 1e-6
using namespace std;

struct cell {
	double x[DIM];
	cell( double a, double b, double c ) {
		0[x]=a,1[x]=b,2[x]=c;
	}
	cell( double a, double b ) {
		0[x]=a,1[x]=b,2[x]=0;
	}
	cell() { 0[x]=1[x]=2[x]=0; }
	double operator [] ( int i ) const { return x[i]; };
	void read() {
		assert(2==scanf("%lf %lf",x,x+1));
		2[x]=0;
	}
};

bool operator < ( const cell &a, const cell &b ) {
	for ( int i = 0; i < DIM; ++i )
		if ( fabs(a[i]-b[i]) >= tol )
			return a[i]<b[i];
	return false;
}

bool operator == ( const cell &a, const cell &b ) {
	return !(a<b||b<a);
}

cell operator + ( const cell &a, const cell &b ) { return cell(a[0]+b[0],a[1]+b[1],a[2]+b[2]); }
cell operator - ( const cell &a, const cell &b ) { return cell(a[0]-b[0],a[1]-b[1],a[2]-b[2]); }

double operator , ( const cell &a, const cell &b ) {
	double s = 0;
	for ( int i = 0; i < DIM; s += a[i]*b[i], ++i );
	return s;
}

cell operator * ( const cell &a, const double &t ) { return cell(a[0]*t,a[1]*t,a[2]*t); }
cell operator / ( const cell &a, const double &t ) { return cell(a[0]/t,a[1]/t,a[2]/t); }
cell operator * ( const cell &a, const cell &b ) {
	cell r;
	for ( int j,k,i = 0; i < DIM; ++i )
		k=((j=((i+1)%DIM))+1)%DIM, r.x[i]=a[j]*b[k]-a[k]*b[j];
	return r;
}

int n;
cell c[N],a,b;

void find_intersection( cell &m, cell &n,cell &u, cell &v, cell &o ) {
	cell w = v-u,O;
	double det = -m[0]*n[1]+m[1]*n[0],
		 		dt =  -w[0]*n[1]+w[1]*n[0],
				dtau = m[0]*w[1]-m[1]*w[0];
	assert( fabs(det) > tol );
	o = u+(m*(dt/det));
	O = v+(n*(dtau/det));
	// assert( o == O );
}

int main() {
	int i,j,k,w,ans,l;
	double RSQUARE;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for (;1==scanf("%d",&n)&&n>0; printf("%d\n",ans) ) {
		for ( i = 0; i < n; c[i++].read() );
		for ( ans = min(2,n), i = 0; i < n; ++i )
			for ( j = i+1; j < n; ++j )
				for ( a=(c[i]+c[j])/2, k = j+1; k < n; ++k ) {
					b=(c[i]+c[k])/2;
					if ( fabs(((c[k]-c[i])*(c[j]-c[i]))[DIM-1]) < tol ) continue ;
					cell A(-(c[j][1]-c[i][1]),c[j][0]-c[i][0]),B(-(c[k][1]-c[i][1]),c[k][0]-c[i][0]), o;
					find_intersection(A,B,a,b,o), RSQUARE = (c[i]-o,c[i]-o);
					for ( w = 0, l = 0; l < n; ++l )
						if ( fabs((c[l]-o,c[l]-o)-RSQUARE) < tol && ++w );
					ans = max(ans,w);
				}
	}
	return 0;
}

