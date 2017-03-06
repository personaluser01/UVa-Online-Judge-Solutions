/*
 * 10218. Let's Dance!
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <limits.h>
#include <float.h>
#define tol 1e-9
#define N 2048
#define L 0x80

long double pref[N],w,a[N][L];
int m,n,K;

long double f( int n, int k ) { return k > n ? 0 : pref[n]-pref[k]-pref[n-k]; }

int main() {
	int i,j,k;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( i = 1; i < N; ++i )
		pref[i] = pref[i-1] + log(i);
	for ( i = 1; i < N; ++i )
		for ( a[i][0] = 0, k = 1; k < L; ++k ) 
			a[i][k] = k*log(i);
	while ( 3 == scanf("%d %d %d",&m,&n,&K) && (n||m) ) {
		if ( !m ) {
			puts("1.0000000");
			continue ;
		}
		if ( !n ) {
			if ( K%2 == 0 ) {
				puts("1.0000000");
			}
			else puts("0.0000000");
			continue ;
		}
		for ( w = 0, k = 0; 2*k <= K; ++k )
			w += exp(f(K,2*k)+a[m][2*k]+a[n][K-2*k]-a[m+n][K]);
		printf("%.7Lf\n",w+tol);
	}
	return 0;
}
