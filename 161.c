/*
 * 161. Traffic Lights
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
#define N 0x80

int n,c[N],tt;

int color( int i, int t ) {
	int k = t % ((c[i]+5)*2);
	return (k >= c[i] ? 0 : 1);
}

int rinp() {
	int i;
	for ( i = 0; 1 == scanf("%d",c+i) && c[i]; ++i );
	for ( n = i, tt = (1<<29), i = 0; i < n; ++i )
		if ( tt > (c[i] -= 5) )
			tt = c[i];
	return n;
}

int main() {
	int i,j,k,t;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	while ( rinp() ) {
		for ( t = tt; t <= 5*60*60; ++t ) {
			for ( i = 0; i < n; ++i )
				if ( !color(i,t) )
					goto next;
			k = t / 60;
			printf("%02d:%02d:%02d\n",k/60,k%60,t%60);
			goto ok;
			next: continue ;
		}
		nx: puts("Signals fail to synchronise in 5 hours");
		ok: continue ;
	}
	return 0;
}
