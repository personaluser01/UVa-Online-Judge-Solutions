/*
 * 10037. Bridge
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <limits.h>
#include <float.h>
#define N 0x400

int ts,c[N],cnt[101],n,
	x[N*N],y[N*N],m,T,len[N*N];

int main() {
	int i,j,k,l,t;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( scanf("%d",&ts); ts--; ) {
		memset(cnt,0,sizeof(cnt));
		for ( scanf("%d",&n), i = 0; i < n; ++i )
			scanf("%d",c+i), ++cnt[c[i]];
		for ( k = 0, i = 0; i <= 100; ++i )
			for(;cnt[i]--; c[k++] = i );
		assert( n == k );
		if ( n == 1 ) 
			printf("%d\n%d\n",0[c],0[c]);
		else if ( n == 2 ) {
			printf("%d\n",1[c]);
			printf("%d %d\n",0[c],1[c]);
		}
		else if ( n == 3 ) {
		}
		if ( ts ) putchar('\n');
	}
	return 0;
}
