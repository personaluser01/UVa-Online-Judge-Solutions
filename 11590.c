/*
 * 11590. Prefix Lookup
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
#define V(ch) (ch-'0')
typedef unsigned long long u64;
#define FG (ptr = fgets(s,sizeof(s),stdin))

int m,n;

typedef struct cell { struct cell *son[2]; u64 sum; unsigned char is_term,processed; } cell;

cell *cinit() {
	int i;
	cell *x = (cell *)malloc(sizeof *x);
	for ( i = 0; i <= 1; x->son[i++] = NULL );
	x->is_term = 0, x->processed = x->sum = 0;
	return x;
}

typedef struct { cell *root; } tree;

cell *root;
char s[0x400];

u64 Pow2( int e ) {
	if ( e == 64 ) return 0;
	return (1ULL<<e);
}

u64 calc_sum( cell *x, int depth ) {
	int i;
	u64 ret = 0,left,right;
	if ( !x ) return 0;
	if ( x->processed )
		return x->sum;
	left = calc_sum(x->son[0],depth+1);
	right = calc_sum(x->son[1],depth+1);
	x->sum = left+right;
	if ( x->is_term )
		x->sum += Pow2(m-depth)-left-right;
	x->processed = 1;
	return x->sum;
}

void cleanup( cell *x ) {
	if ( x ) {
		cleanup(x->son[0]), cleanup(x->son[1]);
		free( x );
	}
}

int main() {
	int i,j,k,l,t,len;
	char *ptr;
	cell *x;
	char buf[0x400];
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for (;2 == scanf("%d %do\n",&n,&m) && (n||m); putchar('\n') ) {
		root = cinit(), root->is_term = 1;
		for ( i = 0; i < n; ++i ) {
			scanf("%s\n",s);
			len = strlen(s);
			for ( x = root, t = 1, l = 0; l < len && s[l] != '*'; x = x->son[V(s[l])], ++l, ++t ) 
				if ( !x->son[V(s[l])] )
					x->son[V(s[l])] = cinit();
			x->is_term = 1;
		}
		for ( scanf("%d\n",&k); k--; ) {
			scanf("%s\n",s), len = strlen(s);
			for ( x = root, l = 0, t = 0; l < len && s[l] != '*'; x = x->son[V(s[l])], ++l, ++t );
			printf("%llu\n",Pow2(m-t)-calc_sum(x->son[0],t+1)-calc_sum(x->son[1],t+1));
		}
		cleanup(root);
	}
	return 0;
}

