/*
 * 11560. Fixing the Bugs
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <limits.h>
#include <float.h>
#define tol 1e-9
#define N 0x10

int n;
long double p[N],lambda;
i64 s[N];

int main() {
	int i,j,k;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for (;3 == scanf("%d %d %Lf",&n,&T,&lambda);) {
		for ( i = 0; i < n; ++i )
			scanf("%Lf %lld",p+i,s+i);
	}
	return 0;
}
