/*
 * 1262. Passwords
 * TOPIC: backtracking
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 8
#define M 8
#define BIT(k) (1UL<<(k))
#define MASK(k) (BIT(k)-1UL)
#define L(k) ((k)&((~(k))+1UL))
typedef long long i64;

int K,m = 6, n = 5;
i64 cn[N],prod[N];
unsigned int u[2][N],w[N];
char g[2][M][N],which[1 << 21],ans[N],*ptr;
const char *A = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

int who( unsigned int u ) {
	if ( u < (1<<20) )
		return which[u];
	return 20+which[u>>20];
}

int bts( unsigned int u ) { return !u?0:1+bts(u&~L(u)); }

int Select( unsigned int w, int i ) {
	assert( bts(w) > i );
	for ( ;i--; w &= ~L(w) );
	return who(L(w));
}


int construct( int col, i64 k ) {
	i64 ax = 0,i;
	if ( k <= 0 ) return 0;
	if ( col == n-1 ) {
		if ( k > cn[col] )
			return 0;
		*ptr++ = A[Select(w[col],k-1)];
		return 1;
	}
	for ( ax = 0, i = 0; i < cn[col]; ax += prod[col+1], ++i )
		if ( ax+prod[col+1] >= k ) 
			break ;
	if ( i == cn[col] )
		return 0;
	*ptr++ = A[Select(w[col],i)];
	return construct(col+1,k-ax);
}

int main() {
	int ts,i,j,k,t,l;
	for ( i = 0; i < 21; ++i )
		which[BIT(i)] = i;
	for ( scanf("%d",&ts); ts--; ) {
		memset(u,0,sizeof u);
		for ( scanf("%d",&K), t = 0; t <= 1; ++t ) {
			for ( i = 0; i < m; ++i ) scanf("%s",g[t][i]);
			for ( j = 0; j < n; ++j )
				for ( i = 0; i < m; ++i )
					u[t][j] |= BIT(g[t][i][j]-'A');
		}
		for ( j = 0; j < n; ++j )
			cn[j] = bts(w[j]=(u[0][j]&u[1][j]));
		for ( prod[n] = 1LL, j = n-1; j >= 0; --j )
			prod[j] = prod[j+1]*cn[j];
		if ( prod[0] < K ) {
			puts("NO");
			continue ;
		}
		assert( (ptr=ans,construct(0,K)) );
		*ptr = '\0', puts(ans);
	}
	return 0;
}


