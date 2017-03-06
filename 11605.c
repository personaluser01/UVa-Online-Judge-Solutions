/*
 * 11605. Lights Inside a 3D Grid
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 0x80
typedef long long i64;
#define tol 1e-9

i64 n[3],K,x[3],q[3][8],*ptr[3],m[3];
char bts[1 << 12];

i64 C( i64 x ) {
	if ( x <= 1 ) return 0;
	return (x&1) ? (x*((x-1)>>1)):((x>>1)*(x-1));
}

i64 Omega( i64 x, i64 y, i64 z ) {
	if ( x <= 0 || y <= 0 || z <= 0 ) return 0;
	return 8*C(x)*C(y)*C(z)+4*(x*C(y)*C(z)+C(x)*y*C(z)+C(x)*C(y)*z)+2*(x*y*C(z)+x*C(y)*z+C(x)*y*z)+x*y*z;
}

i64 G( int k ) {
	i64 w = 0,l;
	if ( k == 3 ) 
		return Omega(m[0],m[1],m[2]);
	for ( l = 0; l < ptr[k]-q[k]; ++l ) 
		m[k] = q[k][l], w += G(k+1);
	return w;
}

i64 W( int k, i64 *x  ) {
	unsigned int u,i;
	i64 ax,w = 0;
	for ( u = 0; u < 8; ++u ) {
		if ( bts[u] != k ) continue ;
		for ( i = 0; i <= 2; ptr[i] = q[i], ++i );
		for ( ax = 1LL, i = 0; i <= 2; ++i )
			((u>>i)&1)?(*ptr[i]++=x[i]-1,*ptr[i]++=n[i]-x[i]):(*ptr[i]++=n[i]);
		w += G(0);
	}
	return w;
}

i64 f( i64 *x ) { 
	i64 a[3],i;
	for ( i = 0; i <= 2; ++i )
		a[i] = (n[i]-x[i]+1)*x[i]-1;
	return 8*a[0]*a[1]*a[2]+4*(a[0]*a[1]+a[1]*a[2]+a[2]*a[0])+2*(a[0]+a[1]+a[2])+1;
	/*return W(0,x)-W(1,x)+W(2,x)-W(3,x);*/
}
long double p( i64 *x ) { return (f(x)+.0)/Omega(n[0],n[1],n[2]); }

long double mypow( long double x, i64 K ) {
	long double ax = 1;
	for (;K; x *= x, K >>= 1 )
		if ( K & 1 ) ax *= x;
	return ax;
}

i64 T( i64 *n ) { return n[0]*n[1]*n[2]; }

int main() {
	int i,j,k,t,ts,cs = 0;
	long double w;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( i = 1; i < (1 << 12); ++i ) bts[i] = bts[i>>1]+(i&1);
	for ( scanf("%d",&ts); ts--; printf("Case %d: %.8Lf\n",++cs,(w+T(n))/2.00) ) {
		for ( t = 0; t <= 2; scanf("%lld",&n[t++]) );
		for ( scanf("%lld",&K), w = 0, x[0] = 1; x[0] <= n[0]; ++x[0] )
			for ( x[1] = 1; x[1] <= n[1]; ++x[1] )
				for ( x[2] = 1; x[2] <= n[2]; ++x[2] )
					w += (K&1)?-mypow(1-2*p(x),K):-mypow(1-2*p(x),K);
	}
	return 0;
}

