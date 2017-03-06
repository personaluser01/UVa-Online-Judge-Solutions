/*
 * 11273. Warping of N-Dimensional Space
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
typedef long long i64;
#define MOD 4000039LL
#define N 4000000

i64 phi[N],n,pref[N];

void ext_euclid( i64 *a, i64 *b, i64 x, i64 y, i64 *d ) 
{ (!y)?(*a=1,*b=0,*d=x):(ext_euclid(b,a,y,x%y,d),*b-=(*a)*(x/y)); }

i64 modinv( i64 p, i64 q ) {
	i64 x,y,d;
	ext_euclid(&x,&y,p,q,&d);
	while ( x < 0 ) x += q;
	return x % q;
}

int main() {
	i64 i,j,k,ax;
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	for ( k = 0; k < N; ++k ) phi[k] = k;
	for ( k = 2; k < N; ++k )
		if ( phi[k] == k )
			for ( j = k+k, --phi[k], i = modinv(k,MOD); j < N; j += k )
				phi[j] *= (k-1), phi[j] %= MOD, phi[j] *= i, phi[j] %= MOD;
	for ( pref[1]=1, k = 2; k < N; ++k )
		pref[k] = pref[k-1]*phi[k], pref[k] %= MOD;
	while ( 1 == scanf("%lld",&n) ) {
		printf("%lld\n",pref[n]);
	}
	return 0;
}

