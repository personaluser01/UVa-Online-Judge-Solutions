/*
 * 11753. Creating Palindrome
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
#define N 100100
#define K 21

int min( int x, int y ) { return x < y ? x:y; }

int n,m,c[N];

int f( int left, int right, int limit ) {
	int i,j,k = 0,w;
	for ( i = left, j = right; i<j && c[i] == c[j]; ++i, --j );
	if ( i >= j ) return k;
	if ( (++k) > limit ) return m+7;
	w = min(f(i+1,j,limit-k),f(i,j-1,limit-k))+k;
	return w;
}

int main() {
	int i,j,k,l,t,cs = 0,ts,w;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( scanf("%d",&ts); ts-- && scanf("%d %d",&n,&m) == 2; ) {
		printf("Case %d: ",++cs);
		for ( i = 1; i <= n; scanf("%d",&c[i++]) );
		if ( (w = f(1,n,m)) > m )
			puts("Too difficult");
		else if ( w == 0 )
			puts("Too easy");
		else printf("%d\n",w);
	}
	return 0;
}

