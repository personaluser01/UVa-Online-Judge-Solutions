/*
 * 10375. Choose and Divide
 * status: Accepted
 */
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 10008

long double logs[N];

long double f( int n, int k ) {
	assert( k <= n );
	assert( 0 <= k );
	return (logs[n] - logs[k] - logs[n-k]);
}

int main() {
	int i,j,k,l,t,p,q,r,s;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( i = 2; i < N; ++i )
		logs[i] = logs[i-1] + log(i+.0);
	while ( 4 == scanf("%d %d %d %d",&p,&q,&r,&s) ) {
		printf("%.5Lf\n",(long double)exp(f(p,q)-f(r,s)));
	}
	return 0;
}

