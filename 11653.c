/*
 * 11653. Stick Makes Gold
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <limits.h>
#include <float.h>
#define N 100010

typedef struct { int t,a,b; } stick;
stick s[N];
typedef unsigned long long u64;
int ts,cs,n,L,mx,mi;

int cmp( const void *X, const void *Y ) {
	stick *x = (stick *)X,
		  *y = (stick *)Y;
	if ( x->a < y->a )
		return -1;
	if ( x->a > y->a )
		return 1;
	if ( x->b < y->b )
		return -1;
	if ( x->b > y->b )
		return 1;
	return 0;
}

int main() {
	int i,j,k,qr,pos,idx;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( scanf("%d",&ts); ts--; ) {
		printf("Case %d:\n",++cs);
		scanf("%d %d",&L,&n);
		for ( i = 0; i < n; ++i ) 
			scanf("%d %d %d",&s[i].t,&s[i].a,&s[i].b);
		qsort(s,n,sizeof *s,cmp), mi = s[0].a, mx = s[n-1].b;
		s[n].a = mx+1, s[n].b = mx+2, ++n;
		for ( scanf("%d",&qr); qr-- && scanf("%d",&pos) == 1; ) {
			if ( pos >= s[n-1].a ) {
				puts("0");
				continue ;
			}
			if ( s[0].b > pos ) 
				idx = 0;
			else {
			}
		}
	}
	return 0;
}
