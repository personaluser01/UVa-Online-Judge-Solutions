/*
 * 11026. A Grouping Problem
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 0x400
typedef long long i64;

i64 n,M,x[N],p[N],q[N],w,tmp;

void mult( i64 *a, i64 m, i64 *b, i64 n ) {
	int i,j;
	i64 *c = (i64 *)calloc((n+m+2),sizeof *c);
	for ( i = 0; i <= m; ++i )
		for ( j = 0; j <= n; ++j )
			c[i+j] += a[i]*b[j], c[i+j] %= M;
	for ( i = 0; i <= n+m; ++i )
		a[i] = c[i];
	free(c);
}

int main() {
	int i,j,k,sign;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for (;2 == scanf("%lld %lld",&n,&M) && (n||M);) {
		for ( i = 0; i < n; scanf("%lld",&x[i++]) );
		memset(p,0,sizeof(p)), memset(q,0,sizeof(q));
		for ( p[0] = -x[0], p[1] = 1, i = 1; i < n; ++i ) 
			q[0] = -x[i], q[1] = 1, mult(p,i,q,1);
		if ( n & 1 ) sign = -1;
		else sign = 1;
		for ( w = -1, i = 0; i <= n; ++i ) {
			tmp = p[i]*sign, sign = -sign;
			while ( tmp < 0 ) tmp += M;
			if ( w == -1 || (tmp %= M) > w ) 
				w = tmp % M;
		}
		printf("%lld\n",w);
	}
	return 0;
}

