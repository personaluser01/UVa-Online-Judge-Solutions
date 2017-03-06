/*
 * 10202. Pairsumonious Numbers
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 10
typedef long long i64;

i64 n,c[N*N],sum,T,i,j,k,l,t,x[N*N],oc[N*N],m,a[N*N];

int test() {
	i64 i,j,k,t;
	for ( i = 0; i < n-1; ++i )
		if ( x[i] > x[i+1] )
			return 0;
	for ( k = 0, i = 0; i < n; ++i )
		for ( j = i+1; j < n; ++j )
			a[k++] = x[i]+x[j];
	for ( j = 1; j; )
		for ( j = i = 0; i < k-1; ++i )
			if ( a[i] > a[i+1] && ++j )
				t = a[i], a[i] = a[i+1], a[i+1] = t;
	assert( k == (n*(n-1))/2 );
	for ( i = 0; i < k; ++i )
		if ( oc[i] != a[i] )
			return 0;
	return 1;
}

int f() {
	i64 i,j,k,l,t,m = (n*(n-1))/2,
		done[N][N] = {0};

	for ( i = 0; i < m; ++i ) c[i] = oc[i];
	x[1]=c[0]-x[0], x[2]=c[1]-x[0];
	for ( j = 2; j+1 < n; x[++j] = c[0]-x[0] )
		for ( l = 0; l < j; ++l )
			for ( t = l+1; t <= j; ++t ) 
				if ( !done[l][t] ) {
					for ( k = 0; k < m && c[k] != x[l]+x[t]; ++k );
					if ( k == m-- ) return 0;
					done[l][t] = 1;
					for (;++k < m; c[k-1] = c[k] );
				}
	return 1;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	while ( 1 == scanf("%lld",&n) ) {
		for(sum=i=0;i<(n*(n-1))/2;scanf("%lld",&c[i++]),sum+=c[i-1]);
		for ( j = 1; j; )
			for ( j = i = 0; i < (n*(n-1)/2)-1; ++i )
				if ( c[i] > c[i+1] && ++j )
					k = c[i], c[i] = c[i+1], c[i+1] = k;
		for ( i = 0; i < (n*(n-1))/2; ++i ) oc[i] = c[i];
		for ( i = 2; i < (n*(n-1))/2; ++i ) {
			if ( (oc[0]+oc[1]-oc[i]) & 1 )
				continue ;
			x[0] = (oc[0]+oc[1]-oc[i])/2;
			if ( f() && test() )
				goto ok;
		}
		goto imp;
		ok: for ( i = 0; i < n-1; ++i )
			printf("%lld ",x[i]);
		printf("%lld\n",x[i]);
		continue ;
		imp: puts("Impossible");
	}
	return 0;
}
