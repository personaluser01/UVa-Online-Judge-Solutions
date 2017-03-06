/*
 * 12879. Golf Bot
 * TOPIC: fft
 * status: Accepted
 */
#include <cassert>
#include <complex>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>
#define tol 1e-9
#define J complex<long double>(0,1)
//#define N (1<<19)
#define N (1<<19)
using namespace std;

const long double pi = 2*acos(0.00);
int is[N],yes;

struct vec {
	size_t n;
	complex<long double> *a;
	vec() { n=0;a=NULL; };
	vec( size_t n ) {
		a = new complex<long double>[this->n = n];
		for ( int i = 0; i < (int)n; a[i++] = complex<long double>(0,0) );
	};
	~vec() { if ( n && a ) delete a; };
	void fft( int sign ) {
		if ( n == 1 ) 
			return ;
		assert( !(n&(n-1)) );
		vec u(n/2),v(n/2);
		for ( int k = 0, j = 0, i = 0; i < n; u.a[j++] = a[i], v.a[k++] = a[i+1], i += 2 );
		u.fft(sign), v.fft(sign);
		complex<long double> e = exp(sign*2*pi/n*J), c = complex<long double>(1,0);
		for ( int k = 0; k < n/2; ++k ) {
			a[k]     = u.a[k] + c*v.a[k];
			a[k+n/2] = u.a[k] - c*v.a[k];
			c *= e;
		};
	};
};

int shot[N],nn,w;

int main() {
	int i,j,k,m,n;
#ifndef ONLINE_JUDGE
	freopen("12879.in","r",stdin);
#endif
	for (;1 == scanf("%d",&n);) {
		for ( w = 0, i = 0; i < n; ++i ) {
			scanf("%d",&shot[i]);
			if ( shot[i] > w ) w = shot[i];
		}
		for ( nn = 1; nn < w+w; nn <<= 1 );
		vec s(nn),t(nn);
		for ( i = 0; i < n; ++i ) 
			t.a[shot[i]] = s.a[shot[i]] = complex<long double>(1,0);
		scanf("%d",&m), ++yes;
		for ( i = 0; i < m; ++i )
			scanf("%d",&k), is[k] = yes;
	   	vec	r(nn);
		for ( s.fft(1), i = 0; i < nn; ++i )
			r.a[i] = s.a[i]*s.a[i];
		r.fft(-1);
		for ( i = 0; i < nn; ++i )
			r.a[i] /= nn;
		for ( k = 0, i = 0; i < nn; ++i ) {
			if ( is[i] == yes && abs(r.a[i]) > tol ) {
				++k;
				// printf("[%d] %.2Lf %.2Lf\n",i,r.a[i].real(),r.a[i].imag());
			}
			else if ( is[i] == yes && i < N/2 && abs(t.a[i]) > tol ) ++k;
		}
		printf("%d\n",k);
	}
	return 0;
}

