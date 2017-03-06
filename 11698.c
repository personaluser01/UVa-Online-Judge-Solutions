/*
 * 11698. Code Permutations
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <limits.h>
#include <float.h>
#define N 101
#define MOD ((1LL << 31)-1LL)
typedef long long i64;
i64 n,m,ax;

void ext_euclid( i64 *a, i64 *b, i64 x, i64 y, i64 *d ) {
	if ( !y ) { *a = 1, *d = x, *b = 0; return ; }
	ext_euclid(b,a,y,x%y,d), *b -= (*a)*(x/y);
}

i64 modinv( i64 p, i64 q ) {
	i64 a,b,d;
	ext_euclid(&a,&b,p,q,&d);
	assert( a*p + b*q == d );
	assert( d == 1 );
	while ( a < 0 ) a += q;
	return a%q;
}

unsigned char a[1 << 10];
#define SET(k) (a[(k)>>3] |= (1UL<<((k)&7)))
#define TST(k) (a[(k)>>3] & (1UL<<((k)&7)))
#define CLR(k) (a[(k)>>3] &= ~(1UL<<((k)&7)))
i64 primes[N],PR,p[N],c[N],d[1 << 15],*ptr,quot[N][N],Factorial[N],Inv[N],Pow[N][N],****z,F[N];
int beta[N],delta[N],Q,Delta[N],K,Degree[N][N],D,V,len[N],pref[N];
unsigned int v[N*N];
char A[N][N];
long double LO[N];

void gen_divs( int k, i64 ax ) {
	int i;
	i64 x = 1ll;
	if ( k == Q ) {
		*ptr++ = ax;
		return ;
	}
	for ( i = 0; i <= Delta[k]; ++i ) {
		gen_divs(k+1,ax*x);
		x *= p[k];
	}
}

int find_which( i64 x ) {
	int i,j,k;
	i = 0, j = D-1;
	assert( d[j] >= x );
	if ( d[j] == x )
		return j;
	if ( d[i] == x )
		return i;
	assert( d[i] < x );
	assert( d[j] > x );
	while ( i+1 != j ) {
		k = (i+j)/2;
		if ( d[k] <= x )
			i = k;
		else j = k;
	}
	if ( d[i] == x ) return i;
	return -1;
}

i64 gcd( i64 x, i64 y ) { return !y ? x : gcd(y,x%y); }

int cmp( const void *a, const void *b ) {
	i64 *x = (i64 *)a,
		*y = (i64 *)b;
	if ( *x == *y )
		return 0;
	return *x < *y ? -1 : 1;
}

int main() {
	int i,j,k,ts,t,l,jj,flag,ni,nj;
	i64 mm,LCM;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( SET(2), i = 3; i < N; i += 2 ) SET(i);
	for ( i = 3; i < N; i += 2 )
		for ( j = i+i; TST(i) && j < N; CLR(j), j += i );
	for ( PR = 0, i = 2; i < N && PR < N; ++i )
		if ( TST(i) ) primes[PR++] = i;

	for ( i = 1; i < N; ++i )
		for ( j = 0; j < PR; ++j )
			for ( mm = i; !(mm % primes[j]); mm /= primes[j], ++Degree[i][j] );

	for ( i = 1; i < N; ++i )
		LO[i] = log(i);

	for ( i = 1; i < N; ++i )
		Inv[i] = modinv(i,MOD);
	for ( Factorial[0] = 1, i = 1; i < N; ++i )
		for ( Factorial[i] = 1, j = 1; j <= i; ++j )
			Factorial[i] *= Inv[j], Factorial[i] %= MOD;
	for ( i = 1; i < N; ++i )
		for ( Pow[i][0] = 1, j = 1; j < N; ++j )
			Pow[i][j] = Inv[i]*Pow[i][j-1], Pow[i][j] %= MOD;
	
	for ( i = 1, F[0] = 1; i < N; ++i )
		F[i] = i*F[i-1], F[i] %= MOD;

	for ( scanf("%d",&ts); ts--; ) {
		scanf("%lld %lld",&n,&m);
		for ( Q = 0, i = 0; i < PR; ++i ) {
			beta[i] = (int)(LO[n]/LO[primes[i]]);
			for ( mm = m, delta[i] = 0; 0 == (mm % primes[i]) && delta[i] <= beta[i]; mm /= primes[i], ++delta[i] );
			if ( delta[i] > beta[i] )
				goto nil;
			if ( Delta[Q]=delta[i] ) p[Q++] = primes[i];
		}
		for ( K = 0, i = 1; i <= n; ++i ) {
			for ( j = 0; j < PR; ++j )
				if ( Degree[i][j] > delta[j] )
					goto nx;
			c[++K] = i;
			assert( !(m % i) );
			nx: continue ;
		}
		for ( i = 1; i <= n; ++i )
			for ( j = 1; j <= K; ++j )
				A[i][j] = !(i % c[j]);
		ptr = d, gen_divs(0,1LL), D = ptr-d;
		qsort( d, D, sizeof *d, cmp );
		/*
		for ( i = 0; i < D; ++i )
			printf("%lld\n",d[i]);
		return 0;
		*/

		for ( V = 0, j = 1; j <= K; ++j )
			for ( len[j] = 0, i = 1; i <= n; ++i )
				if ( A[i][j] )
					v[V++] = (i|(j<<7)), ++len[j], quot[i][j] = i/c[j];
		for ( j = 1; j <= K; ++j )
			pref[j] = pref[j-1]+len[j];
		
		z = (i64 ****)malloc(2*sizeof *z);
		for ( k = 0; k <= 1; ++k ) {
			z[k] = (i64 ***)malloc((n+2)*sizeof *z[k]);
			for ( i = 0; i < n+1; ++i ) {
				z[k][i] = (i64 **)malloc((V+1)*sizeof *z[k][i]);
				for ( j = 0; j < V; ++j )
					z[k][i][j] = (i64 *)calloc((D+1),sizeof *z[k][i][j]);
			}
		}
		for ( k = 0; k < V; ++k ) {
			i = v[k]&127, j = v[k]>>7;
			l = find_which(c[j]);
			assert( 0 <= l && l < D );
			z[0][i][k][l] = (Factorial[quot[i][j]]*Pow[c[j]][quot[i][j]]) % MOD;
		}
		for ( ax = 0, t = 0, flag = 1; flag; ) {
			t ^= 1;
			for ( flag = 0, i = 1; i <= n; ++i )
				for ( k = 0; k < V; ++k )
					for ( j = 0; j < D; ++j ) 
						if ( z[t^1][i][k][j] ) {
							if ( i == n ) {
								if ( d[j] == m )
									ax += z[t^1][i][k][j], ax %= MOD;
								z[t^1][i][k][j] = 0;
								continue ;
							}
							for ( l = k+1; l < V; ++l )
								if ( (v[l]>>7) > (v[k]>>7) ) {
									ni = (v[l]&127), nj = (v[l]>>7);
									if ( i+ni > n )
										continue ;
									LCM = d[j]*c[nj]/gcd(d[j],c[nj]);
									if ( LCM > m||(m % LCM) ) continue ;
									jj = find_which(LCM);
									assert( 0 <= jj && jj < D );
									z[t][i+ni][l][jj] += z[t^1][i][k][j]*((Factorial[quot[ni][nj]]*Pow[c[nj]][quot[ni][nj]])%MOD);
									z[t][i+ni][l][jj] %= MOD;
									flag |= (z[t][i+ni][l][jj]!=0);
								}
							z[t^1][i][k][j] = 0;
						}
		}
		while ( ax < 0 ) ax += MOD;
		printf("%lld\n",(F[n]*ax)%MOD);
		continue ;
		nil: puts("0");
	}
	return 0;
}
