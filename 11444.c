/*
 * 11444. Sum
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
#define N 100009
#define MOD 1000000009ULL
#define K 21
typedef unsigned long long u64;

u64 R( u64 x ) {
	return x < MOD ? x : (x%MOD);
}

u64 p[K][N],c[N],C[K][K],deg[K][N],dig[256],m,n;

u64 Rint() {
	u64 n = 0;
	int ch;
	for(;(ch = getchar()) != EOF && !dig[ch]; );
	for ( n = ch-'0'; (ch = getchar()) != EOF && dig[ch]; )
		n = (n<<1)+(n<<3)+(u64)((ch-'0'));
	return n;
}

int main() {
	u64 i,j,k,l,t,ts,e,q,cs;
	u64 w1,w2;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( i = '0'; i <= '9'; ++i ) dig[i] = 1;
	for ( i = 0; i < K; ++i )
		C[i][0] = 1;
	for ( i = 1; i < K; ++i )
		for ( j = 1; j <= i; ++j )
			C[i][j] = R(C[i-1][j]+C[i-1][j-1]);
	for ( i = 1; i < N; ++i )
		for ( k = 1, deg[0][i] = 1; k < K; ++k )
			deg[k][i] = R(deg[k-1][i]*i);
	for ( ts = Rint(), cs = 0; cs < ts; ++cs ) {
		for ( n = Rint(), i = 1; i <= n; c[i++] = Rint() );
		for ( e = 0; e < K; ++e )
			for ( i = 1; i <= n; ++i )
				p[e][i] = R( p[e][i-1]+R(c[i]*deg[e][i]) );
		for ( l = 0, q = Rint(); l < q; ++l ) {
			k = Rint(); m = Rint(); n = Rint();
			assert( m >= 1 );
			assert( n >= 1 );
			/*printf("%d %d %d\n",k,m,n);*/
			if ( m == 1 ) {
				printf("%llu\n",p[k][n]);
				continue ;
			}
			for ( w1 = 0, j = 0; j <= k; ++j ) {
				if ( j & 1 )
					w1 += (MOD-R( R(C[k][j]*deg[j][m-1]) * p[k-j][n]) );
				else
					w1 +=      R( R(C[k][j]*deg[j][m-1]) * p[k-j][n]);
				w1 = R(w1);
			}
			for ( w2 = 0, j = 0; j <= k && m > 1; ++j ) {
				if ( j & 1 )
					w2 += (MOD-R( R(C[k][j]*deg[j][m-1]) * p[k-j][m-1]) );
				else
					w2 +=      R( R(C[k][j]*deg[j][m-1]) * p[k-j][m-1]);
				w2 = R(w2);
			}
			if ( w1 > w2 )
				printf("%llu\n",R(w1-w2));
			else
				printf("%llu\n",R(w1+(MOD-w2)));
		}
	}
	return 0;
}
