/*
 * 11311. Exclusively Edible
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
#define N 0x40
#define H (puts("Gretel"))
#define G (puts("Hansel"))

int n,m,xx,yy;

int main() {
	int i,j,k,ts,l,t;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( scanf("%d",&ts); ts--; ) {
		scanf("%d %d %d %d",&m,&n,&xx,&yy);
		i = xx, l = m-1-xx, j = yy, k = n-1-yy;
		t = (i^j^k^l);
		if ( !t ) G; else H;
	}
	return 0;
}

