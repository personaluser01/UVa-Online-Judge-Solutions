/*
 * 10743. Blocks
 * TOPIC: repeated squaring, recurrences, very mathematical
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef long long i64;
#define MOD (10000LL)
#define N 3
#define M 15

i64 x[N][N],n,
	v[0x400],b[0x400][0x400];

i64 calc( int n ) {
	i64 ans = 0,i,j,k;
	for ( i = 0; i < n; ++i )
		ans += 2*v[i];
	for ( k = 2; k <= n-2; ++k )
		for ( i = 1; i <= k; ++i )
			ans += i*v[k-i];
	return v[i] = ans;
}

i64 calc_using_1( int n ) {
	i64 ans = 0,i;
	for ( i = 0; i <= n; ++i )
		ans += b[n][i];
	return ans;
}

int main() {
	int i,j,k,ts,cs = 0,t;
	i64 a[N][N],tm[N][N],A,B;

	v[0] = 1, v[1] = 1, v[2] = 2;
	b[0][0] = 1, b[1][1] = 1;
	for ( n = 2; n <= M; ++n ) {
		for ( k = 1; k < n; ++k )
			for ( b[n][k] = 0, t = 0; t <= n-k; ++t )
				b[n][k] += (t+k-1)*b[n-k][t];
		b[n][n] = 1LL;
	}
	for ( i = 3; i <= M; ++i ) {
		v[i] = calc_using_1(i);
		/*
		printf("%lld\n",v[i]);
		*/
	}
	/*
	 * test (3)
	 */
	for ( n = 1; n <= M-1; ++n )
		for ( k = 1; k <= n-1; ++k ) {
			if ( b[n][k] != b[n+1][k+1] - v[n-k] )
				printf("These b[%lld][%d] = %lld and b[%lld][%d] = %lld, v[%lld] = %lld\n",n,k,b[n][k],n+1,k+1,b[n+1][k+1],n-k,v[n-k]);
			assert( b[n][k] == b[n+1][k+1] - v[n-k] );
		}

	for ( n = 1; n <= M-1; ++n ) {
		for ( k = 1; k <= n-1; ++k )
			assert( b[n][k] == b[n-k+1][1]+(k-1)*v[n-k] );
	}

	/*
	 * test (6)
	 */
	for ( n = 1; n <= M; ++n ) {
		for ( A = B = 0, k = 1; k <= n; ++k )
			B += b[k][1];
		for ( k = 2; k <= n-1; ++k )
			A += (k-1)*v[n-k];
		assert( A == v[n]-B );
	}

	/*
	 * test (7)
	 */
	for ( n = 1; n <= M; ++n ) {
		for ( A = b[n][1], t = 1; t <= n-1; ++t )
			A += v[t];
		assert( A == v[n] );
	}

	/*
	 * test (4)
	 */
	for ( n = 1; n <= M-1; ++n ) {
		for ( B = 0, t = 0; t <= n; ++t )
			B += t*b[n][t];
		if ( B != b[n+1][1] )
			printf("These b[%lld][1] %lld and %lld\n",n+1,b[n+1][1],B);
		assert( B == b[n+1][1] );
	}

	/*
	 * test (8)
	 */
	for ( n = 3; n <= M; ++n ) {
		for ( A = 0, t = 1; t <= n-3; ++t )
			A += t*v[n-2-t];
		if ( b[n][1] != A+v[n-1]+b[n-1][1] )
			printf("b[%lld][1] = %lld, RHS is %lld, with A = %lld, a[%lld] = %lld, b[%lld] = %lld\n",n,b[n][1],A+v[n-1]+1+b[n-1][1],A,n-1,v[n-1],n-1,b[n-1][1]);
		assert( b[n][1] == A+v[n-1]+b[n-1][1] );
	}

	/*
	 * test (9)
	 */
	for ( n = 3; n <= M; ++n ) {
		for ( A = 0, t = 1; t <= n-3; ++t )
			A += t*v[n-2-t];
		assert( v[n] == 3*v[n-1]+A );
	}

	/*
	 * test (10)
	 */
	for ( n = 5; n <= M; ++n ) {
		if ( v[n] != 5*v[n-1]-7*v[n-2]+4*v[n-3] ) 
			printf("v[%lld] = %lld, versus %lld\n",n,v[n],5*v[n-1]-7*v[n-2]+4*v[n-3]);
		assert( v[n] == 5*v[n-1]-7*v[n-2]+4*v[n-3] );
	}


	for ( scanf("%d",&ts); ts-- && 1 == scanf("%lld",&n); ) {
		if ( n == 0 ) {
			printf("Case %d: %lld\n",++cs,1LL);
			continue ;
		}
		if ( n == 1 ) {
			printf("Case %d: %lld\n",++cs,1LL);
			continue ;
		}
		if ( n == 2 ) {
			printf("Case %d: %lld\n",++cs,2LL);
			continue ;
		}
		if ( n == 3 ) {
			printf("Case %d: %lld\n",++cs,6LL);
			continue ;
		}
		if ( n == 4 ) {
			printf("Case %d: %lld\n",++cs,19LL);
			continue ;
		}
		for ( i = 0; i < N; ++i )
			for ( j = 0; j < N; ++j )
				if ( i == j )
					a[i][j] = 1LL;
				else a[i][j] = 0;
		memset(x,0,sizeof x);
		x[0][0] = 5, x[0][1] = -7, x[0][2] = 4;
		x[1][0] = 1, x[1][1] = 0, x[1][2] = 0;
		x[2][0] = 0, x[2][1] = 1, x[2][2] = 0;
		for ( n-=4; n; n >>= 1 ) {
			if ( n&1 ) {
				for ( i = 0; i < N; ++i )
					for ( j = 0; j < N; ++j )
						for ( tm[i][j] = 0, k = 0; k < N; ++k )
							tm[i][j] += ((a[i][k]*x[k][j])%MOD), tm[i][j] %= MOD;
				for ( i = 0; i < N; ++i )
					for ( j = 0; j < N; ++j )
						for ( a[i][j] = tm[i][j]; a[i][j] < MOD; a[i][j] += MOD );
			}
			for ( i = 0; i < N; ++i )
				for ( j = 0; j < N; ++j )
					for ( tm[i][j] = 0, k = 0; k < N; ++k )
						tm[i][j] += ((x[i][k]*x[k][j])%MOD), tm[i][j] %= MOD;
			for ( i = 0; i < N; ++i )
				for ( j = 0; j < N; ++j )
					for ( x[i][j] = tm[i][j]; x[i][j] < 0; x[i][j] += MOD );
		}
		printf("Case %d: %04lld\n",++cs,(a[0][0]*19+a[0][1]*6+a[0][2]*2)%MOD);
	}
	return 0;
}

