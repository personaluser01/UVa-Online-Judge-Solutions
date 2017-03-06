/*
 * 11597. Spanning Subtrees
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
#define N 512

typedef long long i64;

int n,cs;

int main() {
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	while ( 1 == scanf("%d",&n) && n > 0 ) {
		printf("Case %d: %d\n",++cs,n/2);
	}
	return 0;
}
