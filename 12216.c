/*
 * 12216. How Many Bases?
 * TOPIC: combinatorics, pie, inclusion-exclusion, prime decomposition theorem, neat
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MOD 100000007LL
typedef long long i64;
#define N (100010)

i64 n,m,t,T,p[N],beta[N],Gamma[N],delta[N];
int len,betalen,K;
char isprime[N];

int main() {
	int i,j,k,cs = 0;
	i64 nn,ax,bx;
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	for ( i = 3; i < N; i += 2 ) isprime[i] = 1;
	for ( isprime[2] = 1, i = 3; i < N; i += 2 )
		for ( j = i+i; j < N && isprime[i]; j += i )
			isprime[j] = 0;
	for ( len = 0, i = 0; i < N; ++i )
		if ( isprime[i] ) ++len;
	for ( k = 0, i = 0; i < N; ++i )
		if ( isprime[i] )
			p[k++] = i;
	for ( ;3 == scanf("%lld %lld %lld",&n,&m,&t) && (n||m||t); ) {
		printf("Case %d: ",++cs), T = t;
		for ( nn = n, betalen = 0, i = 0; i < len && p[i]*p[i] <= nn; ++i )
			if ( 0 == (nn%p[i]) )
				for ( ++betalen, beta[betalen-1] = 0; 0 == (nn%p[i]); ++beta[betalen-1], nn /= p[i] );
		if ( nn > 1 ) 
			++betalen, beta[betalen-1] = 1;
		for ( K = betalen, i = 0; i < K; Gamma[i] = beta[i]*m/T, ++i );
		for ( i = 0; i < K; ++i ) 
			delta[i] = beta[i]*m/(T+1)+1;
		for ( ax = bx = 1LL, i = 0; i < K; ++i ) {
			ax *= (Gamma[i]+1), ax %= MOD; 
			bx *= (delta[i]), bx %= MOD;
		}
		for ( ax -= bx; ax < 0; ax += MOD );
		printf("%lld\n",ax%MOD);
	}
	return 0;
}

