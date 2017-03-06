/*
 * 10883. Supermean
 * status: Accepted
 */
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 50008

int n;
long double c[N],logs[N],w;

long double f( int n, int k ) {
	return exp(logs[n] - logs[k] - logs[n-k] - n*log(2.00));
}

int main() {
	int i,j,k,t,l,ts,cs = 0;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( i = 2; i < N; ++i )
		logs[i] = logs[i-1] + log(i+.0);
	for ( scanf("%d",&ts); ts-- && printf("Case #%d: ",++cs); ) {
		for ( w = 0, scanf("%d",&n), i = 0; i < n; ++i )
			scanf("%Lf",c+i), w += f(n-1,i)*c[i];
		printf("%.3Lf\n",w);
	}
	return 0;
}

