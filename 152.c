/*
 * 152. Tree's Crowd
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <limits.h>
#include <float.h>
#define N 5100
#define S(x) ((x)*(x))

int n,x[N],y[N],z[N],cnt[11];

int main() {
	int i,j,k;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( i = 0; 3 == scanf("%d %d %d",x+i,y+i,z+i) && (x[i]+y[i]+z[i]); ++i );
	for ( i = 0; i < n; ++i )
		for ( j = 0; j < n; ++j )
	return 0;
}

