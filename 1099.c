/*
 * 1099. Sharing Chocolate
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
#define N 16
#define DIM 0x80
#define  BIT(k)    (1UL << (k))
#define  MASK(k)   (BIT(k)-1UL)
#define  SET(a,k)  ((a)|=BIT(k))
#define  TST(a,k)  ((a)&BIT(k))
#define  CLR(a,k)  ((a)&=~BIT(k))
#define  CMPL(u) ((~(u)) & MASK(n))
#define enc(m,u) ((m)|((u)<<7))

int m,n,p,cs,c[N],A[1 << N];
unsigned char z[((1<<(7+15))>>3)+8],
			  seen[((1<<(7+15))>>3)+8];

int calc_z( int m, unsigned int u ) {
	unsigned int v,n;
	int k;

	assert( u );

	if ( TST(seen[enc(m,u)>>3],(enc(m,u)&7)) )
		return TST(z[enc(m,u)>>3],enc(m,u)&7);

	SET(seen[enc(m,u)>>3],enc(m,u)&7);
	assert( !(A[u]%m) );
	n = A[u]/m;
	SET(seen[enc(n,u)>>3],enc(n,u)&7);

	if ( !(u&(u-1)) ) {
		SET(z[enc(m,u)>>3],enc(m,u)&7);
		SET(z[enc(n,u)>>3],enc(n,u)&7);
		return 1;
	}

	for ( v = (u-1) & u; v; v = (v-1) & u ) {
		for ( k = 1; k <= m/2; ++k )
			if ( k*n == A[v] ) {
				assert( (m-k)*n == A[(~v)&u] );
				if ( calc_z(k,v) && calc_z(m-k,(~v)&u) ) {
					SET(z[enc(m,u)>>3],enc(m,u)&7);
					SET(z[enc(n,u)>>3],enc(n,u)&7);
					return 1;
				}
			}
		for ( k = 1; k <= n/2; ++k )
			if ( k*m == A[v] ) {
				assert( (n-k)*m == A[(~v)&u] );
				if ( calc_z(k,v) && calc_z(n-k,(~v)&u) ) {
					SET(z[enc(m,u)>>3],enc(m,u)&7);
					SET(z[enc(n,u)>>3],enc(n,u)&7);
					return 1;
				}
			}
	}
	return 0;
}

int main() {
	int i,j,k,u;
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	while ( 1 == scanf("%d",&p) && p > 0 ) {
		scanf("%d %d",&m,&n);
		printf("Case %d: ",++cs);
		for ( k = 0, i = 0; i < p; ++i )
			scanf("%d",&c[i]), k += c[i];
		if ( k != m*n ) {
			puts("No");
			continue ;
		}
		for ( u = 0; u < (1<<p); ++u )
			for ( A[u] = 0, i = 0; i < p; ++i )
				A[u] += c[i]*((u>>i)&1);
		memset(z,0,sizeof(z));
		memset(seen,0,sizeof(seen));
		puts(calc_z(m,MASK(p))?"Yes":"No");
	}
	return 0;
}

