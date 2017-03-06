/*
 * 11637. Garbage Remembering Exam
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define tol 1e-9
#define N 100001
typedef long long i64;

long double pref[N];

long double f( i64 n, i64 k, i64 l ) {
	if ( l+k > n-1-2*k )
		return 0;
	if ( n-1-l-k < 0 )
		return 0;
	return 2*exp(pref[n-1-2*k]-pref[n-1-l-3*k]+pref[n-l-1-k]-pref[n-1]);
}

long double g( i64 n, i64 k, i64 l ) {
	if ( n-1-2*k < 2*k )
		return 0;
	return exp(pref[n-1-2*k]-pref[n-1-4*k]+pref[n-1-2*k]-pref[n-1]);
}

int main() {
	i64 k,l,n,cs = 0;
	long double w;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( k = 2; k < N; ++k )
		pref[k] = pref[k-1] + (long double)log((long double )k);
	for ( ;2 == scanf("%lld %lld",&n,&k) && (n||k); printf("Case %lld: %.4Lf\n",++cs,n==1&&k==1?0.00+tol:w) ) {
		for ( w = n, l = 0; l <= k-1; w -= f(n,k,l++) );
		for ( l = k; l <= n-1-k; w -= g(n,k,l++) );
	}
	return 0;
}

