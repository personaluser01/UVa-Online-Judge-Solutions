/*
 * 514. Rails
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
#define N 0x400

int n,a[N],st[N],*top,at_station[N],yes,*head,*tail,q[N];

int rinp() {
	int i,j;
	for ( i = 0; i < n && 1 == scanf("%d",&a[i]) && a[i]; ++i );
	for ( j = 0; j < n; --a[j++] );
	return i == n;
}

int main() {
	int i,j,k;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for(;1 == scanf("%d",&n) && n > 0; putchar('\n') ) {
		for(;rinp() && ++yes;) {
			for ( head = tail = q, i = 0; i < n; *tail++ = i++ );
			for ( top = st, i = 0; i < n; ++i, --top ) {
				for(;at_station[a[i]] != yes && head < tail; at_station[*++top = *head++] = yes );
				if ( *top != a[i] ) goto bad;
			}
			puts("Yes");
			continue ;
			bad: puts("No");
		}
	}
	return 0;
}
