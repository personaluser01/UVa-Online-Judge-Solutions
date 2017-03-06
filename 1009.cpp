/*
 * 1009. Balloons in a Box
 * TOPIC: geometry, greedy, binary search
 * status: Accepted
 */
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <cfloat>
#include <vector>
#define oo (1<<29)
#define tol 1e-9
#define DIM 3
#define N 8
#define pi (2*acos(.00))
using namespace std;

int n;
struct cell { 
	double x[DIM]; 
	cell () {};
	cell operator -= ( const cell &other ) {
		for ( int j = 0; j < DIM; ++j )
			this->x[j] -= other.x[j];
	}
};

bool operator < ( const cell &a, const cell &b ) {
	for ( int i = 0; i < DIM; ++i )
		if ( a.x[i] != b.x[i] )
			return a.x[i] < b.x[i];
	return false ;
}

int nearest( double x ) {
	int dx = (int)(x+tol),
		ux = dx+1;
	return x-dx < ux-x?dx:ux;
}

cell c[2],a[N];
vector<int> idx;
double r[N],d[N][N];

bool inside_balls( int k ) {
	for ( int i = 0; i < k; ++i )
		if ( r[i] < +oo && d[idx[i]][idx[k]] <= r[i]*r[i] )
			return true ;
	return false ;
}

cell operator - ( const cell &a, const cell &b ) {
	cell r;
	for ( int i = 0; i < DIM; ++i )
		r.x[i] = a.x[i]-b.x[i];
	return r;
}

double operator , ( const cell &a, const cell &b ) {
	double s = 0;
	for ( int i = 0; i < DIM; ++i )
		s += a.x[i]*b.x[i];
	return s;
}

double V( const cell &c, const cell &d ) {
	double v = 1;
	for ( int i = 0; i < DIM; v *= fabs(c.x[i]-d.x[i]), ++i );
	return v;
}

bool intersects_boundaries( double R, int i ) {
	for ( int l = 0; l < i; ++l )
		if ( r[l] < +oo )
			if ( d[idx[i]][idx[l]] < (R+r[l])*(R+r[l]) )
				return true ;
	for ( int l = 0; l < DIM; ++l ) 
		if ( fabs(c[1].x[l]-a[idx[i]].x[l]) < R || fabs(c[0].x[l]-a[idx[i]].x[l]) < R )
			return true ;
	return false ;
}

int main() {
	int i,j,k,l,t,cs = 0;
	double low,high,mid,w,volume;
#ifndef ONLINE_JUDGE
	freopen("c.txt","r",stdin);
#endif
	for (;1==scanf("%d",&n) && n > 0;) {
		for ( t = 0; t <= 1; ++t )
			for ( j = 0; j < DIM; scanf("%lf",&c[t].x[j++]) );
		for ( w = -oo, idx.clear(), i = 0; i < n; ++i )
			for ( idx.push_back(i), j = 0; j < DIM; scanf("%lf",&a[i].x[j++]) );
		for ( i = 0; i < n; ++i )
			for ( j = i+1; j < n; ++j ) 
				d[i][j] = d[j][i] = (a[i]-a[j],a[i]-a[j]);
		do {
			for ( volume = 0, i = 0; i < n; ++i )
				if ( !inside_balls(i) ) {
					for(low=0,high=+oo;fabs(high-low)>tol;intersects_boundaries(mid=(low+high)/2,i)?(high=mid):(low=mid));
					r[i] = low, volume += r[i]*r[i]*r[i];
				}
				else r[i] = +oo;
			w = max(w,volume);
		} while ( next_permutation(idx.begin(),idx.end()) );
		printf("Box %d: %d\n\n",++cs,nearest(V(c[1],c[0])-4*w*pi/3));
	}
	return 0;
}

