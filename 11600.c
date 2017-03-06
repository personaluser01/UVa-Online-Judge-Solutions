/*
 * 11600. Masud Rana
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <limits.h>
#include <float.h>
#define N 32
#define tol 1e-9

int n,m,cs;

int main() {
	int i,j,k,ts;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( scanf("%d",&ts); ts--; ) {
		scanf("%d %d",&n,&m);
		for ( k = 0; k < m; ++k ) {
			scandf("%d %d",&i,&j);
			--i, --j;
		}
		printf("Case %d: ",++cs);
	}
	return 0;
}
