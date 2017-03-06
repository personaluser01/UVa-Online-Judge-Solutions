/*
 * 11864. Probability Calculation
 * TOPIC: probability, binomial distribution, recurrence, dp, very neat, binomial coefficients
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define tol 1e-15
#define N (50010)
typedef long long i64;

long double p,lfac[N],logp,logq,F[N],pref[N];
int M;

long double LC( int n, int k ) {
	return lfac[n]-lfac[n-k]-lfac[k];
}

int main() {
	int i,j,k,cs = 0,n,qr;
#ifndef ONLINE_JUDGE
	freopen("11864.in","r",stdin);
#endif
	for ( lfac[1] = 0, i = 2; i < N; lfac[i] = lfac[i-1] + log(i), ++i );
	for ( ;2 == scanf("%Lf %d",&p,&qr) && qr;) {
		logp = log(p), logq = log(1-p);
		for ( F[1] = p, n = 1; n < N; ++n ) {
			if ( n&1 ) {
				k = (n+2)/2;
				F[n+1] = F[n]+exp(LC(n,k-1)+k*logp+(n-k+1)*logq);
			}
			else {
				k = (n+1)/2;
				F[n+1] = F[n]-exp(LC(n,k)+k*logp+(n-k+1)*logq);
			}
		}
		for ( i = 1; i < N; ++i )
			pref[i] = pref[i-1]+F[i];
		for ( printf("Case %d:\n",++cs); qr-- && 1 == scanf("%d",&M); printf("%.8Lf\n",pref[M]) );
	}
	return 0;
}

