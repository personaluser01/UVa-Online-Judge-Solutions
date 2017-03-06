/*
 * 1525. Falling Leaves
 * TOPIC: bst
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 0x400
enum { L, R };

char s[N][N];
int n,V;

typedef struct cell {
	struct cell *son[2];
	char ch;
} cell;
cell pool[N],*ptr = pool;

typedef struct {
	cell *root;
	size_t cnt;
} tree;

tree *init() {
	tree *t = (tree *)malloc(sizeof *t);
	ptr = pool, t->root = NULL, t->cnt = 0;
	return t;
}

void insert( tree *t, char ch ) {
	cell *x,*y,**hold;
	for ( x=t->root, hold=&t->root; x && x->ch != ch; hold = &x->son[x->ch<ch?R:L], x=x->son[x->ch<ch?R:L] );
	x = *hold = ptr++, x->ch = ch, x->son[L] = x->son[R] = NULL, ++t->cnt;
}

void traverse( cell *x ) { if ( x ) putchar(x->ch), traverse(x->son[L]), traverse(x->son[R]); }

int main() {
	int i,j,k,l;
	tree *t;
#ifndef ONLINE_JUDGE
    freopen("in.txt","r",stdin);
#endif
	for ( ;1 == scanf("%s",s[0]); ) {
		for ( n = 1; 1 == scanf("%s",s[n]) && 0[s[n]] != '*' && 0[s[n]] != '$'; ++n );
		for ( t = init(), k = n-1; k >= 0; --k ) 
			for ( i = 0; s[k][i]; insert(t,s[k][i++]) );
		traverse(t->root), putchar('\n');
	}
    return 0;
}

