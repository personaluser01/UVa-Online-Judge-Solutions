/*
 * 11234. Expressions
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
#define N 10100
enum { L, R };

typedef struct cell {
	struct cell *son[2];
	char ch;
} cell;

cell pool[N],*st[N],**top,*ptr,*x,*y,*z,*q[N],**head,**tail;
char out[N],*qtr,s[N];
int n;

cell *init( char ch ) {
	cell *x = ptr++;
	x->ch = ch, x->son[L] = x->son[R] = NULL;
	return x;
}

int main() {
	int i,j,k,ts;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for(scanf("%d",&ts);ts--&&scanf("%s",s);){
		for ( top = st, ptr = pool, i = 0; s[i]; ++i ) {
			if ( islower(s[i]) ) 
				*++top = init(s[i]);
			else {
				y = *top--, x = *top--;
				z = init(s[i]);
				z->son[L] = x, z->son[R] = y;
				*++top = z;
			}
		}
		for ( n = i, qtr = out+n-1, head = tail = q, *tail++ = *top--; head < tail;)
			for ( x = *head++, *qtr-- = x->ch, i = L; i <= R; ++i )
				if ( x->son[i] )
					*tail++ = x->son[i];
		out[n] = '\0', puts(out);
	}
	return 0;
}

