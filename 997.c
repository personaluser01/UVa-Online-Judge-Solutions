/*
 * 997. Show the sequence
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
typedef long long i64;
#define N 64
enum { L, R };

int n;
i64 x[N];
char s[0x400],*ptr;

typedef struct cell {
	struct cell *son[2];
	char op;
	i64 val;
} cell;

cell *f() {
	cell *x;
	int k;
	if ( !*ptr ) return NULL;
	x = (cell *)malloc(sizeof *x);
	x->son[L]=x->son[R]=NULL;
	assert( *ptr++ == '[' );
	assert( *ptr == '-'||*ptr == '+'||isdigit(*ptr) );
	sscanf(ptr,"%lld%n",&x->val,&k), ptr += k;
	if ( (x->op = *ptr++) == ']' ) 
		return x;
	x->son[R] = f();
	return x;
}

i64 eval( cell *x, int i ) {
	assert( x );
	if ( x->op == ']' )
		return x->val;
	if ( i == 1 ) {
		switch ( x->op ) {
			case '+': return x->val;
			case '*': return x->val*eval(x->son[R],1);
			default: assert( 0 );
		}
	}
	assert( i > 1 );
	switch ( x->op ) {
		case '+': return eval(x,i-1)+eval(x->son[R],i-1);
		case '*': return eval(x,i-1)*eval(x->son[R],i);
		default: assert( 0 );
	}
}

int main() {
	cell *root;
	int i;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for (;2 == scanf("%s %d",s,&n);) {
		ptr = s, root = f();
		for ( i = 1; i < n; ++i )
			printf("%lld ",eval(root,i));
		printf("%lld\n",eval(root,n));
	}
	return 0;
}
