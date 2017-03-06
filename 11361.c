/*
 * 11361. Div-Sum Property
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef long long i64;
typedef unsigned long long u64;
#define K 10100
#define M 12
#define Q 100
#define oo 0xffffffffffffffffull

int diglen( i64 n ) { return 1+((n<=9)?0:diglen(n/10)); }

u64 A,B,z[M][Q][Q];
i64 deg[M],mo;
char nines[M][M],one[M][M],zeroes[M][M];

u64 calc_z( int m, int r, int s ) {
	int i,rr,ss;

	for ( r %= mo; r < 0; r += mo );
	for ( s %= mo; s < 0; s += mo );

	if ( z[m][r][s] < +oo )
		return z[m][r][s];

	assert( m >= 1 );

	if ( m == 1 ) {
		if ( r != s )
			return z[m][r][s] = 0;
		for ( z[m][r][s] = 0, i = 0; i <= 9; ++i )
			if ( (i % mo) == r )
				++z[m][r][s];
		return z[m][r][s];
	}
	for ( z[m][r][s] = 0, i = 0; i <= 9; ++i ) {
		rr = (r-i+mo+mo)%mo, ss = (s-deg[m-1]*i+mo+mo)%mo;
		z[m][r][s] += calc_z(m-1,rr,ss);
	}
	return z[m][r][s];
}

u64 f( char *a, char *b, int m, int r, int s ) {
	int ch,rr,ss;
	u64 ans = 0;

	for ( r %= mo; r < 0; r += mo );
	for ( s %= mo; s < 0; s += mo );

	if ( m == 1 ) {
		if ( r != s )
			return 0;
		for ( ch = 0[a]; ch <= 0[b]; ++ch )
			if ( ((ch-'0')%mo) == r )
				++ans;
		return ans;
	}

	for ( ch = (0[a]-'0')+1; ch <= (0[b]-'0')-1; ++ch ) {
		assert( 0[a] < (ch+'0') );
		assert( (ch+'0') < 0[b] );
		rr = (r-ch+mo+mo)%mo, ss = (s-deg[m-1]*ch+mo+mo)%mo;
		ans += calc_z(m-1,rr,ss);
	}
	if ( (ch = 0[a]) == 0[b] ) {
		ch -= '0', rr = (r-ch+mo+mo)%mo, ss = (s-deg[m-1]*ch+mo+mo)%mo;
		return f(a+1,b+1,m-1,rr,ss);
	}
	if ( (ch = 0[a]) < 0[b] ) {
		ch -= '0', rr = (r-ch+mo+mo)%mo, ss = (s-deg[m-1]*ch+mo+mo)%mo;
		ans += f(a+1,nines[m-1],m-1,rr,ss);
	}
	if ( (ch = 0[b]) > 0[a] ) {
		ch -= '0', rr = (r-ch+mo+mo)%mo, ss = (s-deg[m-1]*ch+mo+mo)%mo;
		ans += f(zeroes[m-1],b+1,m-1,rr,ss);
	}
	return ans;
}

int main() {
	i64 i,j,k,e,ts,r,s,m;
	char a[0x100],b[0x100];
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( k = 1; k < M; one[k][k-1] = '1', ++k )
		for ( i = 0; i < k; nines[k][i] = '9', zeroes[k][i] = one[k][i] = '0', ++i );
	for ( scanf("%lld",&ts); ts--; ) {
		scanf("%llu %llu %lld",&A,&B,&mo);
		if ( mo >= Q ) { puts("0"); continue; }
		assert( A <= B );
		for ( k = diglen(B), i = k-1, e = A; i >= 0; a[i--] = (e%10)+'0', e /= 10 );
		for ( i = k-1, e = B; i >= 0; b[i--] = (e%10)+'0', e /= 10 );
		a[k] = b[k] = '\0';
		for ( m = 0; m <= k; ++m )
			for ( r = 0; r < mo; ++r )
				for ( s = 0; s < mo; ++s )
					z[m][r][s] = +oo;
		for ( deg[0] = 1ULL%mo, i = 1; i <= k; ++i )
			deg[i] = (deg[i-1]*10ULL)%mo;
		printf("%llu\n",f(a,b,k,0,0));
	}
	return 0;
}

