/*
 * 11048. Automatic Correction of Misspellings
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
typedef struct cell {
	struct cell *son,*sib;
	char ch;
	int is_term,id;
} cell;

cell *init_cell( char ch, int id ) {
	cell *x = (cell *)malloc(sizeof *x);
	x->ch = ch, x->son = x->sib = NULL, x->id = id, x->is_term = 0;
	return x;
}

void trie_push( tree *root, char *s, int id ) {
	cell *x,*y;
	for ( x = root; *s; x = y, ++s ) {
		for ( y = x->son; y && y->ch != ch; y = y->sib );
		if ( !y )
			y = init_cell(*s,id), y->sib = x->son, x->son = y;
	}
	x->is_term = 1;
}

int find( cell *x, char *s, int limit ) {
	cell *x,*y;
	for ( x = root; *s; x = y, ++s ) {
		for ( y = x->son; y && y->ch != ch; y = y->sib );
		if ( !y ) {
			if ( !limit )
				return 0;
		}
	}
	return x->is_term ? x->id : 0;
}

cell *root;
int m,n;
char s[0x400],
	 word[10002][27];

int main() {
	int i,j,k;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	root = init_cell('$',-1);
	for ( scanf("%d",&n), i = 0; i < n; scanf("%s",word[i++]) );
	for ( i = n; i; --i )
		trie_push(root,word[i-1],i);
	for ( scanf("%d",&m); m-- && scanf("%s",s) == 1;) {
		if ( find(root,s,0) ) {
			printf("%s is correct\n",s);
			continue ;
		}
		if ( !(i = find(root,s,1)) ) {
			printf("%s is unknown\n",s);
			continue ;
		}
		printf("%s is a misspelling of %s\n",s,word[i-1]);
	}
	return 0;
}
