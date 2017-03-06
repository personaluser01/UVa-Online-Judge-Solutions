/*
 * 463. Polynomial Factorization
 */
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <cfloat>
#include <climits>
#include <vector>
#define tol 1e-7
#define N 16
typedef long long i64;
using namespace std;
#define oo (DBL_MAX-1024)

i64 c[N];
double a[N];

double *diff( double *c, int n ) {
	double *d;
	assert( n >= 1 );
	assert( d = (double *)calloc(n, sizeof *d) );
	for ( int i = 0; i <= n-1; d[i] = (i+1)*c[i+1], ++i );
	return d;
}

double eval( double *c, int n, double t ) {
	double ax = 0;
	for ( int i = n+1; i; ax = ax*t+c[--i] );
	return ax;
}

void find_roots( double *c, int n, vector<double> &r ) {
	int i,j,k;
	double a,b,low,mid,high;
	assert( n >= 1 );
	assert( fabs(c[n]) > 0 );
	if ( n == 1 ) {
		r.push_back(-c[0]/c[1]);
		return ;
	}
	if ( n == 2 ) {
		double D = c[1]*c[1] - 4*c[0]*c[2];
		if ( D >= 0 ) {
			r.push_back((-c[1]-sqrt(D))/2.0/c[2]);
			r.push_back((-c[1]+sqrt(D))/2.0/c[2]);
		}
		return ;
	}
	vector<double> v;
	v.clear(), v.push_back(-oo), find_roots(diff(c,n),n-1,v), v.push_back(+oo);
	for ( i = 0; i+1 < (int)v.size(); ++i ) {
		a = v[i], b = v[i+1];
		assert( a <= b );
		if ( eval(c,n,a)*eval(c,n,b) > 0 )
			continue ;
		if ( eval(c,n,a) <= 0 ) {
			for(low=a,high=b;fabs(high-low)>tol;eval(c,n,mid=(low+high)/2)<=0?(low=mid):(high=mid));
			r.push_back(low);
		}
		else {
			for(low=a,high=b;fabs(high-low)>tol;eval(c,n,mid=(low+high)/2)<=0?(high=mid):(low=mid));
			r.push_back(high);
		}
	}
}

int main() {
	int i,j,k,n;
	vector<double> r;
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	while ( 5 == scanf("%lld %lld %lld %lld %lld",c+4,c+3,c+2,c+1,c) ) {
		for ( i = 0; i <= 4; a[i] = c[i], ++i );
		for ( n = 4; n && !c[n]; --n );
		if ( !n )
			assert( 0 );
		r.clear(), find_roots(a,n,r);
		if ( !r.size() ) {
			for ( i = 4; i; printf("%lld ",c[i--]) );
			printf("%lld\n",c[i]);
			continue ;
		}
		assert( r.size() != 1 );
	}
	return 0;
}

