/*
 * 12271. Compring Answers
 * TOPIC: probabilistic algorithms, Freivalds' Algorithm, swerc2010
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define N 0x400
typedef long long i64;

int n;
i64 A[N][N],B[N][N],C[N][N],r[N],u[N],v[N],w[N];

int main() {
	int i,j,k,t,ok;
	for (;1 == scanf("%d",&n) && n>0;) {
		for ( i = 0; i < n; ++i )
			for ( j = 0; j < n; ++j )
				scanf("%lld",&A[i][j]), B[i][j] = A[i][j];
		for ( i = 0; i < n; ++i )
			for ( j = 0; j < n; ++j )
				scanf("%lld",&C[i][j]);
		for ( ok = 1, t = 0; t < 20 && ok; ++t ) {
			for ( i = 0; i < n; ++i )
				r[i] = abs(rand()&7);
			for ( i = 0; i < n; ++i )
				for ( v[i] = 0, j = 0; j < n; ++j )
					v[i] += B[i][j]*r[j];
			for ( i = 0; i < n; ++i )
				for ( u[i] = 0, j = 0; j < n; ++j )
					u[i] += A[i][j]*v[j];
			for ( i = 0; i < n; ++i )
				for ( w[i] = 0, j = 0; j < n; ++j )
					w[i] += C[i][j]*r[j];
			for ( i = 0; i < n && (ok &= (w[i]==u[i])); ++i );
		}
		puts(ok?"YES":"NO");
	}
	return 0;
}

