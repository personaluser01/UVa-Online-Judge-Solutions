/*
 * 11190. Series of Powers
 * TOPIC: mantissa, exponent, simulation, repeated squaring, very hard
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <float.h>
#define oo (DBL_MAX-0x400)
#define tol 1e-13
#define N (0x400)
typedef long long i64;

i64 l,h,k,n,beta[N],maxb;
double m,D,e,T,tmp,
	 alpha[N];

int main() {
	int i,j,cs = 0;
	i64 t;
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	while ( 3 == scanf("%lld %lld %lld",&l,&h,&k) && (l+1||h+1||k+1) ) {
		printf("Case %04d: ",++cs);
		if ( l == h && h == 0 ) {
			puts("0.000000e0000000001");
			continue ;
		}
		for ( maxb = -(1LL<<62), i = 0, t = l; t <= h; ++t, ++i ) {
			tmp = k*log10(t);
			beta[i] = (i64)(tmp+1);
			for ( alpha[i] = pow(10,tmp-beta[i]); alpha[i] >= 1; alpha[i] /= 10, ++beta[i] );
			if ( maxb < beta[i] ) maxb = beta[i];
		}
		for ( m = 0, t = l, i = 0; t <= h; ++i, ++t ) {
			beta[i] -= maxb;
			alpha[i] *= pow(10.00,beta[i]), m += alpha[i];
		}
		for ( k = (i64)(log10(m)+1), maxb += k, m /= pow(10.00,k); m >= 1; m /= 10, ++maxb );
		printf("%.6lfe%010lld\n",m,(i64)(maxb+tol));
	}
	return 0;
}

