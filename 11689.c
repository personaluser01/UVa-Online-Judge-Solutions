/*
 * 11689. Soda Surpler
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

int main() {
	int i,j,k,ts,ax,a;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( scanf("%d",&ts); ts--; ) {
		scanf("%d %d %d",&i,&j,&k);
		for ( ax = 0, a = i+j; a >= k; ) 
			ax += a/k, a = (a%k)+(a/k);
		printf("%d\n",ax);
	}
	return 0;
}
