#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N (1 << 18)
#define M (1000000000LL+7)
#define L(i) ((i) & ((~(i))+1))
typedef long long i64;

int n,c[N],K;
unsigned int z[N];
i64 t[N],F[N];

void update( unsigned int i, i64 dt ) {
	for ( ;i <= (1 << K); t[i] += dt, i += L(i) );
}

i64 prefix( unsigned int i ) {
	i64 ax = 0;
	for (;i; ax += t[i], i -= L(i) );
	return ax;
}

int main() {
	int i,j,k;
	i64 ax;
	for ( F[0] = 1, ax = 1; ax < N; ++ax )
		F[ax] = F[ax-1]*ax, F[ax] %= M;
	while ( 1 == scanf("%d",&n) ) {
		memset(t,0,sizeof(t));
		for ( K = 0; (1 << K) < n; ++K );
		for ( i = 0; i < n; ++i )
			scanf("%d",c+i);
		for ( ax = 1, i = 0; i < n; ++i ) {
			update(c[i],1);
			c[i] -= prefix(c[i]-1);
			ax += (c[i]-1)*F[n-i-1], ax %= M;
		}
		printf("%lld\n",ax % M);
	}
	return 0;
}

