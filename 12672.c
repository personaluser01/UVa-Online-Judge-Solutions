/*
 * 12672. Eleven
 * TOPIC: very neat DP, combinatorics, number theory, very neat decomposition, recurrence relation
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MOD (1000000000LL+7LL)
#define N 0x80
#define R 11
#define D 10
#define MAXSUM (N>>1)
typedef long long i64;

char s[N];
int m,n,cnt[D],pref[D],seen[D][MAXSUM][R],yes;
i64 factorial[N],ifac[N],C[N][N],F,ans,rem,d[N],
	z[D][MAXSUM][R];

void ext_euclid( i64 x, i64 y, i64 *a, i64 *b, i64 *d ) { !y?(*a=1,*d=x,*b=0):(ext_euclid(y,x%y,b,a,d),*b-=(*a)*(x/y)); }
i64 inv( i64 x, i64 p ) {
	i64 a,b,d;
	for ( ext_euclid(x,p,&a,&b,&d); a < 0; a += p );
	return a%p;
}

int max( int x, int y ) { return x<y?y:x; }

void enumerate( int k, int *a, int total, int mod ) {
	i64 ax,i;
	if ( k == D ) {
		if ( total == m && mod == rem ) {
			for ( ax = (m-a[0]), i = 0; i < D; ++i )
				if ( (ax *= C[cnt[i]][a[i]]) >= 2*MOD )
					ax %= MOD;
			ans += ax, ans %= MOD;
		}
		return ;
	}
	assert( k < D );
	if ( k == D-1 ) {
		if ( (a[k] = m-total) <= cnt[k] )
			enumerate(k+1,a,total+a[k],(mod+k*a[k])%R);
		return ;
	}
	for ( a[k] = max(0,m-total-(pref[D-1]-pref[k])); a[k]+total <= m && a[k] <= cnt[k]; ++a[k] )
		enumerate(k+1,a,total+a[k],(mod+k*a[k])%R);
}

i64 calc_z( int i, int s, int r ) {
	int a;

	if ( seen[i][s][r] == yes )
		return z[i][s][r];

	seen[i][s][r] = yes;

	if ( i == 0 ) {
		for ( z[i][s][r] = 0, a = s; a <= s && a <= cnt[i]; ++a )
			if ( r == 0 && (z[i][s][r] += (m-a)*C[cnt[i]][a]) >= MOD )
				z[i][s][r] %= MOD;
		return z[i][s][r];
	}
	assert( i >= 1 );
	for ( z[i][s][r] = 0, a = 0; a <= s && a <= cnt[i]; ++a ) 
		if ( (z[i][s][r] += C[cnt[i]][a]*calc_z(i-1,s-a,(r-i*a+R*R*R)%R)) >= MOD )
			z[i][s][r] %= MOD;
	return z[i][s][r];
}

int main() {
	int i,j,k,r,t,l,a[D];
	i64 res;
#ifndef ONLINE_JUDGE
	freopen("12672.in","r",stdin);
#endif
	for ( factorial[0] = ifac[0] = 1LL, i = 1; i < N; factorial[i] = (factorial[i-1]*i)%MOD, ifac[i] = (ifac[i-1]*(d[i]=inv(i,MOD)))%MOD, ++i ) ;
	for ( i = 0; i < N; C[i++][0] = 1LL ) ;
	for ( i = 1; i < N; ++i )
		for ( j = 1; j <= i; C[i][j] = (C[i-1][j-1]+C[i-1][j])%MOD, ++j ) ;
	for ( ;1 == scanf("%s",s); ) {
		n = strlen(s), memset(cnt,0,sizeof cnt);
		for ( i = 0; i < n; ++cnt[s[i++]-'0'] ) ;
		for ( pref[0] = cnt[0], i = 1; i < D; pref[i] = pref[i-1]+cnt[i], ++i ) ;
		for ( rem = 0, i = 1; i < D; rem += i*cnt[i], ++i, rem %= R );
		for ( rem *= 6, rem %= R, m = (n>>1)+(n&1), F = 1LL, i = 0; i < D; F *= ifac[cnt[i++]], F %= MOD ) ;
		F *= factorial[m-1], F %= MOD, F *= factorial[n>>1], F %= MOD;
		++yes, printf("%lld\n",res = (F*calc_z(D-1,m,rem))%MOD);
		/*++yes, res = (F*calc_z(D-1,m,rem))%MOD;*/
		/*
		ans = 0, enumerate(0,a,0,0), ans *= F, ans %= MOD;
		if ( res != ans ) printf("For this %s, %lld and %lld\n",s,ans,res);
		assert( res == ans );*/
	}
	return 0;
}

