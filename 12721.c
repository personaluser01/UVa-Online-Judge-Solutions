/*
 * 12721. Cheap B-Sequence
 * TOPIC: dp
 * status: Accepted
 */
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 0x80
#define A 26
#define K 16
#define oo (1LL<<61)
#define MAXB N
typedef long long i64;
i64 max( i64 x, i64 y ) { if ( x < y ) return y; return x; };
i64 min( i64 x, i64 y ) { if ( x > y ) return y; return x; };

int n,B,len[A],p[A][K],c[A][K];
char s[N];
i64 z[N][MAXB],cost[N][N];

i64 calc_z( int k, int m ) {
	int ch,i,flag;
	if ( z[k][m] < +oo )
		return z[k][m];
	if ( k < m ) return z[k][m] = +oo;
	if ( k == 0 ) {
		assert( m == 0 );
		return z[k][m] = 0;
	}
	if ( m == 0 ) return z[k][m] = 0;
	assert( m >= 1 && k >= 1 );
	z[k][m]=calc_z(k-1,m), ch = s[k]-'a';
	if ( calc_z(k-1,m-1) < +oo )
		z[k][m] = min(z[k][m],calc_z(k-1,m-1)+cost[m][ch]);
	return z[k][m];
}

int main() {
	int i,j,k,ts,cs = 0;
	i64 w;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( scanf("%d",&ts); ts--; ) {
		printf("Case #%d: ",++cs),scanf("%s",s+1),n=strlen(s+1),scanf("%d",&B);
		memset(cost,0,sizeof cost);
		for ( i = 0; i < A; ++i ) 
			for ( scanf("%d",len+i), j = 0; j < len[i]; ++j ) 
				for ( scanf("%d %d",p[i]+j,c[i]+j), k = p[i][j]; k <= n; cost[k][i] += (k/p[i][j])*c[i][j], k += p[i][j] );
		for ( i = 0; i <= n; ++i )
			for ( j = 0; j <= B; ++j )
				z[i][j] = +oo;
		for ( w = +oo, k = B; k <= n; ++k )
			w = min(w,calc_z(k,B));
		printf("%lld\n",w);
	}
	return 0;
}

