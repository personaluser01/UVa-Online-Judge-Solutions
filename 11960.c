/*
 * 11960. Divisor Game
 * status: Accepted
 * TOPIC: sieve, number of divisors, number theory, dp
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 1000001
#define M N
typedef long long i64;

int n,m,ts,d[N],z[N],ans[N];
i64 *p;
unsigned char a[M];

int main() {
	i64 i,j,k,l;
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	for ( a[2] = 1, i = 3; i < M; i += 2 ) a[i] = 1;
	for ( m = 1, i = 3; i < M; i += 2 )
		if ( a[i] && ++m )
			for ( j = i+i; j < M; j += i )
				a[j] = 0;
	p = (i64 *)malloc(m*sizeof *p);
	for ( i = 0, k = 0; i < M; ++i )
		if ( a[i] ) p[k++] = i;
	assert( m == k );
	for ( i = 0; i < N; d[i++] = 1LL );
	for ( i = 2; i < M; ++i )
		if ( a[i] )
			for ( d[i] = 2, j = i+i; j < M; d[j] *= (l+1), j += i )
				for ( k = j, l = 0; !(k%i); k /= i, ++l );
	for ( z[1] = 1, ans[1] = 1, i = 2; i < N; ++i )
		if ( d[i] >= z[i-1] )
			z[i] = d[i], ans[i] = i;
		else z[i] = z[i-1], ans[i] = ans[i-1];

	for ( scanf("%d",&ts); ts-- && 1 == scanf("%d",&n); ) {
		printf("%d\n",ans[n]);
	}

	return 0;

}

