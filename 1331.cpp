/*
 * 1331. Minimax Triangulation
 * TOPIC: geometry, triangulation, dp
 * status: Accepted
 */
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cassert>
#include <cstdlib>
#include <cstring>
#include <cfloat>
#include <cmath>
#define oo (DBL_MAX-0x400)
using namespace std;
#define DIM 3
#define N 0x40
#define tol 1e-9

struct cell {
	int x[DIM];
	cell() { memset(x,0,sizeof x); };
	cell( int a, int b ) {
		0[x] = a, 1[x] = b, 2[x] = 0;
	}
	int operator [] ( int i ) const {
		return x[i];
	}
};

cell c[N];
int n;

cell operator - ( const cell &a, const cell &b ) {
	cell r;
	for ( int i = 0; i < DIM; ++i ) r.x[i] = a[i]-b[i];
	return r;
}
cell operator + ( const cell &a, const cell &b ) {
	cell r;
	for ( int i = 0; i < DIM; ++i ) r.x[i] = a[i]+b[i];
	return r;
}
double operator , ( const cell &a, const cell &b ) {
	double s = 0;
	for ( int i = 0; i < DIM; s += a[i]*b[i], ++i );
	return s;
}

cell operator ^ ( const cell &a, const cell &b ) {
	cell r;
	for ( int j,k,i = 0; i < DIM; ++i ) {
		j = (i+1)%DIM, k = (j+1)%DIM;
		r.x[i] = a[j]*b[k]-a[k]*b[j];
	}
	return r;
}

bool lies_between( const cell &a, const cell &b, const cell &p ) {
	double co = (a-p,b-p), si = ((a-p)^(b-p))[DIM-2];
	return fabs(si) < 0 && co <= 0;
}

bool intersect( const cell &a, const cell &b, const cell &c, const cell &d ) {
	cell m = b-a, n = d-c, f = c-a;
	double det = m[0]*(-n[1])-m[1]*(-n[0]), dtau = m[0]*f[1]-m[1]*f[0], dt = f[0]*(-n[1])-f[1]*(-n[0]);
	if ( fabs(det) < tol ) {
		return lies_between(a,b,c) || lies_between(a,b,d) || lies_between(c,d,a) || lies_between(c,d,b);
	}
	else {
		double t = dt/det, tau = dtau/det;
		return 0 <= t && t <= 1 && 0 <= tau && tau <= 1;
	}
}

bool adjacent( int i, int j, int n ) {
	return (i+1)%n == j || (j+1)%n == i || (i+n-1)%n == j || (j+n-1)%n == i;
}

bool crosses_edges( const int i, const int j, const cell *c, const int n ) {
	int k,t,post_j = (j+1)%n, pre_i = (i+n-1)%n, post_i = (i+1)%n, pre_j = (j+n-1)%n;
	for ( k = post_j, t = (k+1)%n; t != i; ++k, k %= n, ++t, t %= n )
		if ( intersect(c[i],c[j],c[k],c[t]) ) {
			//printf("Intersection between (%d,%d)--(%d,%d) and (%d,%d)--(%d,%d)\n",c[i][0],c[i][1],c[j][0],c[j][1],c[k][0],c[k][1],c[t][0],c[t][1]);
			//printf("<%d,%d> -- <%d,%d>\n",i,j,k,t);
			return true ;
		}
	for ( k = post_i, t = (k+1)%n; t != j; ++k, k %= n, ++t, t %= n )
		if ( intersect(c[i],c[j],c[k],c[t]) ) {
			//printf("Intersection between (%d,%d)--(%d,%d) and (%d,%d)--(%d,%d)\n",c[i][0],c[i][1],c[j][0],c[j][1],c[k][0],c[k][1],c[t][0],c[t][1]);
			//printf("<%d,%d> -- <%d,%d>\n",i,j,k,t);
			return true ;
		}
	return false ;
}

double area( const cell *c, const int n ) {
	double s = 0;
	int i,j;
	for ( i = 0; i < n; ++i ) {
		j = (i+1)%n;
		s += (c[i][0]-c[j][0])*(c[i][1]+c[j][1]);
	}
	return fabs(s)/2.00;
}

double triangle_area( const cell &a, const cell &b, const cell &c ) {
	cell g[3] = {a,b,c};
	return area(g,3);
}

double calc_area( const int i, const int j, const cell *c, const int n ) {
	cell nc[n];
	int m=0,k=i,stop=(j+1)%n;
	for ( ;k != stop; nc[m++] = c[k++], k %= n );
	return area(nc,m);
}

double z[N][N],a[N][N],ta[N][N][N],A;
bool valid_triangle[N][N][N],valid_chord[N][N];

int main() {
	int i,j,k,t,ts;
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	for ( scanf("%d",&ts); ts-- && 1 == scanf("%d",&n); ) {
		for ( i = 0; i < n; ++i )
			scanf("%d %d",&j,&k), c[i] = cell(j,k);
		A = area(c,n);
		for ( i = 0; i < n; ++i )
			for ( j = 0; j < n; ++j )
				for ( k = 0; k < n; valid_triangle[i][j][k++] = false );
		for ( i = 0; i < n; ++i )
			for ( j = i+2; j < n; ++j )
				for ( t = i+1; t <= j-1; ++t )
					ta[i][t][j] = triangle_area(c[i],c[t],c[j]);
		for ( i = 0; i < n; ++i )
			for ( j = 0; j < n; ++j )
				z[i][j] = +oo;
		for ( i = 0; i < n-1; z[i][i+1] = 0, ++i );
		for ( i = 0; i < n; z[i][i] = 0, ++i );
		for ( i = 0; i < n; ++i ) 
			for ( j = i+2; j < n; ++j )
				valid_chord[i][j] = valid_chord[j][i] = !crosses_edges(i,j,c,n);
		for ( i = 0; i < n; ++i ) {
			j = (i+1)%n;
			valid_chord[i][j] = valid_chord[j][i] = true ;
		}
		for ( i = 0; i < n; ++i )
			for ( j = 0; j < n; ++j )
				if ( i != j ) 
					a[i][j] = calc_area(i,j,c,n);
		for ( i = 0; i < n; ++i )
			for ( j = i+2; j < n; ++j )
				for ( t = i+1; t <= j-1; ++t )
					valid_triangle[i][t][j] = valid_chord[i][t] && valid_chord[t][j] && valid_chord[j][i] && fabs(a[i][t]+a[t][j]+a[j][i]+ta[i][t][j]-A)<tol; 
		for ( k = 3; k <= n; ++k )
			for ( i = 0; (j=i+k-1) < n; ++i )
				for ( t = i+1; t <= j-1; ++t )
					if ( valid_triangle[i][t][j] )
						if ( z[i][t] < +oo && z[t][j] < +oo )
							z[i][j] = min(z[i][j],max(ta[i][t][j],max(z[i][t],z[t][j])));
		printf("%.1lf\n",z[0][n-1]);
	}
	return 0;
}

