/*
 * 12387. Alphabet Soup
 * TOPIC: burnside lemma, polya counting, kmp, combinatorics
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 0x400
#define M (1<<21)
typedef long long i64;
#define MOD 100000007LL
#define CIRCLE (360000LL)

i64 n,m,TAU,ans,K;
int a[M],d[M],pi[M],s[M],shift[M],*ptr;

int cmp( const void *a, const void *b ) {
	int *x = (int *)a,
		*y = (int *)b;
	if ( *x == *y ) return 0;
	if ( *x < *y ) return -1;
	return 1;
}

i64 modpow( i64 x, i64 n ) {
	i64 ax = 1LL;
	for (;n;n>>=1,x*=x,x%=MOD)
		if ( n&1 )
			ax*=x, ax%=MOD;
	return ax%MOD;
}

i64 gcd( i64 x, i64 y ) {
	if ( !y ) return x;
	return gcd(y,x%y);
}

int main() {
	int i,j,k,l;
	for (;2==scanf("%lld %lld",&n,&m)&&(n+1||m+1); ) {
		assert( m < M );
		for ( i = 0; i < m; assert(1 == scanf("%d",&a[i++])) );
		qsort(a,(int)m,sizeof *a,cmp);
		for ( i = 0; i < m; ++i )
			assert( d[i] = (a[i]-a[(i-1+m)%m]+CIRCLE)%CIRCLE );
		for ( k = 2*m, i = 1; i <= m; ++i )
			s[i]=d[i-1];
		for ( i = 1; i <= m; ++i )
			s[i+m]=d[i-1];
		for ( j = pi[0] = -1, i = 1; i <= k; pi[i++] = ++j )
			for (;j+1 && s[j+1] != s[i]; j = pi[j] );
		for ( ptr = shift, i = m; i <= k-1; ++i )
			if ( pi[i] == m ) {
				*ptr++ = i-m;
				break ;
			}
		if ( ptr == shift ) {
			printf("%lld\n",modpow(n,m));
			continue ;
		}
		K = shift[0], ans = 0;
		assert( !(m%K) );
		for ( i = 0; i < m/K; ++i )
			ans += modpow(n,K*gcd(i,m/K)), ans %= MOD;
		ans *= K, ans %= MOD, ans *= modpow(m,MOD-2);
		printf("%lld\n",ans%MOD);
		continue ;
		/*
		for ( i = 0; i < ptr-shift; ++i ) {
			printf("shift = %d\n",shift[i]);
			if ( m%shift[i] )
				printf("These %lld %d\n",m,shift[i]);
			assert( 0 == (m%shift[i]) );
			for ( TAU = 0, j = 0; j <= shift[i]; TAU += d[j++] );
			for ( j = 0; j < m; ++j ) {
				if ( (a[j]+TAU)%CIRCLE != a[(j+shift[i])%m] )
					printf("[TAU] These %d %d\n",a[j],a[(j+shift[i])%m]);
				assert( (a[j]+TAU)%CIRCLE == a[(j+shift[i])%m] );
				puts("OK so far");
			}
		}
		*/
	}
	return 0;
}

