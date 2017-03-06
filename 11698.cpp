/*
 * 11698. Code Permutations
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
#define MOD ((1LL<<31)-1LL)
typedef long long i64;
#define N 101
#include <iostream>
using namespace std;
#include <vector>

typedef struct { i64 x,p; } divisor;

unsigned char a[1 << 10];
#define SET(k) (a[(k)>>3] |= (1UL<<((k)&7)))
#define TST(k) (a[(k)>>3] & (1UL<<((k)&7)))
#define CLR(k) (a[(k)>>3] &= ~(1UL<<((k)&7)))
i64 p[N],delta[N*N],beta[N*N],C[N][N],F[N],Delta[N*N],Q,pr[N],D,
	z[N][N*N],alpha[N*N],kappa[N*N],*qtr,q[N*N],**lcm;
double LO[N];
int PR;
divisor d[N*N],*ptr;
vector<i64> e[N*N];

void gener( int k, i64 ax ) {
	i64 x,i;
	if ( k == Q ) {
		*qtr++ = ax;
		return ;
	}
	for ( x = 1LL, i = 0; i <= kappa[k]; ++i, gener(k+1,ax*x), x *= pr[k] );
}

void gen_divisors( int k, i64 ax, i64 p ) {
	i64 x,i;
	if ( k == Q ) { ptr->x = ax, ptr->p = p, ++ptr; return ; }
	for ( x = 1ll, i = 0; i <= Delta[k]; gen_divisors(k+1,x*ax,x == 1?p:pr[k]), (x *= pr[k]), ++i );
}

i64 gcd( i64 x, i64 y ) { return !y ? x : gcd(y,x%y); }
i64 LCM( i64 x, i64 y ) { return x*y/gcd(x,y); }

int cmp( const void *a, const void *b ) {
	i64 *x = (i64 *)a,
		*y = (i64 *)b;
	if ( *x < *y )
		return -1;
	if ( *x > *y )
		return 1;
	return 0;
}

int find_which( i64 x ) {
	int i,j,k;

	if ( d[i = 0].x == x )
		return 0;
	if ( d[j = D-1].x == x )
		return D-1;
	if ( x < d[i].x||x>d[D-1].x )
		return -1;
	assert( d[i].x <= x );
	assert( d[j].x > x );
	while ( i+1 != j ) {
		k = (i+j)/2;
		if ( d[k].x <= x )
			i = k;
		else j = k;
	}
	if ( d[i].x == x )
		return i;
	return -1;
}

i64 pwr( i64 x, i64 n ) {
	i64 ax = 1ll;
	while ( n ) {
		if ( n & 1 )
			ax *= x;
		x *= x, n >>= 1;
	}
	return ax;
}

int main() {
	i64 i,j,k,l,t,m,n,mm,ts,tt,x,nq;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( i = 0; i < N; ++i ) LO[i] = log(i);
	for ( SET(2), i = 3; i < N; i += 2 ) SET(i);
	for ( i = 3; i < N; i += 2 )
		for ( j = i+i; TST(i) && j < N*N; j += i ) CLR(j);
	for ( PR = 0, i = 2; i < N; ++i )
		if ( TST(i) ) p[PR++] = i;
	for ( F[0] = 1, i = 1; i < N; ++i )
		F[i] = i*F[i-1], F[i] %= MOD;
	for ( j = 0; j < N; ++j ) C[j][0] = 1LL;
	for ( i = 1; i < N; ++i )
		for ( j = 1; j <= i; ++j )
			C[i][j] = C[i-1][j-1]+C[i-1][j], C[i][j] %= MOD;
	for ( scanf("%lld",&ts); ts-- && 2 == scanf("%lld %lld",&n,&m); ) {
		for ( mm = m, Q = 0, i = 0; i < PR && p[i] <= n; ++i ) {
			beta[i] = (int)(LO[n]/LO[p[i]]);
			for ( delta[i] = 0; 0 == (mm % p[i]) && delta[i] <= beta[i]; ++delta[i], mm /= p[i] );
			if ( delta[i] > beta[i] ) { puts("0"); goto next; }
			if ( Delta[Q] = delta[i] ) pr[Q++] = p[i];
		}
		if ( mm > 1 ) {
			puts("0");
			goto next;
		}
		ptr = d, gen_divisors(0,1LL,1), D = ptr-d;
		qsort( d, D, sizeof *d, cmp );
		lcm = (i64 **)malloc((D+1)*sizeof *lcm);
		for ( i = 0; i < D; ++i )
			lcm[i] = (i64 *)malloc((D+1)*sizeof *lcm[i]);
		for ( i = 0; i < D; ++i )
			for ( j = 0; j < D; ++j )
				lcm[i][j] = LCM(d[i].x,d[j].x);
		for ( i = 0; i < D; ++i ) 
			for ( e[i].clear(), j = 0; j <= i; ++j )
				if ( !(d[i].x%d[j].x) )
					e[i].push_back(j);
		assert( d[D-1].x == m );
		for ( i = 0; i <= n; ++i )
			for ( j = 0; j < D; ++j )
				z[i][j] = 0;
		for ( z[0][0] = z[1][0] = 1, k = 2; k <= n; ++k )
			for ( i = 0; i < D; ++i ) 
				if ( d[i].p <= k ) {
					for ( j = 0; j < (int)e[i].size() && d[e[i][j]].x <= k; ++j )
						if ( 1||d[e[i][j]].x <= k ) {
							for ( tt = 0; tt < (int)e[i].size(); ++tt ) {
								if ( !z[k-d[e[i][j]].x][e[i][tt]] )
									continue ;
								if ( lcm[e[i][j]][e[i][tt]] != d[i].x )
									continue ;
								z[k][i] += (((((C[k-1][d[e[i][j]].x-1]*F[d[e[i][j]].x-1])%MOD)*z[k-d[e[i][j]].x][e[i][tt]]))%MOD);
								z[k][i] %= MOD;
							}
							/*
							for ( l = 0; l <= i; ++l )
								if ( z[k-d[j].x][l] && !(d[i].x % d[l].x) && LCM(d[l].x,d[j].x) == d[i].x ) {
									z[k][i] += (((C[k-1][d[j].x-1]*F[d[j].x-1]) % MOD)*z[k-d[j].x][l]);
									z[k][i] %= MOD;
								}
							*/
						}
				}
		printf("%lld\n",z[n][D-1]);
		next: continue ;
	}
	return 0;
}
