/*
 * 13006. Cake Cut
 * TOPIC: geometry
 * status: in progress
 */
#include <cassert>
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>
#define DIM 3
#define tol 1e-12
#define N (1<<18)
#define oo (1LL<<29)
typedef long long i64;
using namespace std;

struct cell {
	i64 x[DIM];
	cell() { 0[x]=1[x]=2[x]=0; };
	cell( i64 a, i64 b ) { 0[x]=a,1[x]=b,2[x]=0; };
	cell( i64 a, i64 b, i64 c ) { 0[x]=a,1[x]=b,2[x]=c; };
	i64 operator [] ( int i ) const { return x[i]; };
	void read() {
		assert( 2 == scanf("%lld %lld",x,x+1) );
		2[x] = 0;
	};
};

bool operator < ( const cell &a, const cell &b ) {
	for ( int i = 0; i < DIM; ++i )
		if ( fabs(a[i]-b[i])>tol )
			return a[i]<b[i];
	return false ;
}

bool operator == ( const cell &a, const cell &b ) { return !(a<b||b<a); }

cell operator + ( const cell &a, const cell &b ) { return cell(a[0]+b[0],a[1]+b[1],a[2]+b[2]); }
cell operator - ( const cell &a, const cell &b ) { return cell(a[0]-b[0],a[1]-b[1],a[2]-b[2]); }

cell operator * ( const cell &a, const i64 &t ) { return cell(a[0]*t,a[1]*t,a[2]*t); }
cell operator / ( const cell &a, const i64 &t ) { return cell(a[0]/t,a[1]/t,a[2]/t); }

cell operator * ( const cell &a, const cell &b ) {
	cell r;
	for ( int j,k,i = 0; i < DIM; ++i )
		k = ((j = (i+1)%DIM)+1)%DIM, r.x[i] = a[j]*b[k]-a[k]*b[j];
	return r;
}

int n;
cell c[N];
const i64 height = 2.00;
i64 p[N],S,w,q,pref[N];

i64 f( const int k, const int i ) {
	i64 s = 0;
	int t;
	if ( k > i ) {
		s = (pref[n-2]-pref[k-1]) + (i>0?pref[(i-1+n)%n]:0);
	}
	else {
		s = pref[(i-1+n)%n]-(k==0?0:pref[k-1]);
	}
	s += (c[k][1]-c[i][1])*(c[k][0]+c[i][0]);
	return s;
}

i64 g( const int k, const int i ) {
	i64 s = f(k,i);
	return max(S-s,s);
}

int main() {
	int i,j,k,ni,nj;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( ;1==scanf("%d",&n)&&n; ) {
		for ( i = 0; i < n; c[i++].read() );
		for ( S = 0, c[n] = c[0], i = 0; i < n; ++i ) 
			S += (p[i] = (c[i+1][1]-c[i][1])*(c[i+1][0]+c[i][0]));
		for ( pref[0] = p[0], i = 1; i < n; pref[i] = pref[i-1]+p[i], ++i );
		assert( S > 0 );
		for ( w = -oo, k = 0; k < n; ++k ) {
			for ( i = (k+1)%n, j = (k-1+n)%n; j-i >= 3; ) {
				ni = (2*i+j)/3, nj = (2*j+i)/3;
				if ( g(k,ni) < g(k,nj) ) {
					j = nj;
				}
				else i = ni;
			}
			for ( q = g(k,i); ;) {
				q = min(q,g(k,i));
				if ( (++i,i%=n) == (j+1)%n ) break ;
			}
			w = max(w,q);
		}
		printf("%lld %lld\n",w,S-w);
	}
	return 0;
}


