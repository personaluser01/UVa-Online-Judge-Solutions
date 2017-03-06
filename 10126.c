/*
 * 10126. Zipf Law
 * status: Accepted
 */
#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define L 0x400
#define N 10100

char word[L],*ptr;
int n,m;

typedef struct cell {
	struct cell *child,*sibling;
	char ch;
	int cnt;
} cell;

int getword() {
	int ch,i;
	while ( (ch = getchar()) != EOF && !isalpha(ch) );
	assert( ch != EOF );
	for ( i = 0; ch != EOF && isalpha(ch); word[i++] = ch, ch = getchar() );
	word[i] = '\0';
	if ( !strcmp(word,"EndOfText") )
		return 0;
	for ( i = 0; word[i]; ++i )
		word[i] = tolower(word[i]);
	return 1;
}

cell *init_cell( char ch ) {
	cell *x = (cell *)malloc(sizeof *x);
	x->ch = ch, x->child = x->sibling = NULL, x->cnt = 0;
	return x;
}

void trie_push( cell *root, char *s ) {
	cell *x,*y;
	for ( x = root; *s; x = y, ++s ) {
		for ( y = x->child; y && y->ch != *s; y = y->sibling );
		if ( !y ) 
			y = init_cell(*s), y->sibling = x->child, x->child = y;
	}
	++x->cnt;
}

cell *root;
char w[N][L];

void traverse( cell *x ) {
	cell *y;
	if ( !x ) return ;
	if ( x->cnt == n ) 
		*ptr = '\0', strcpy(w[m++],word);
	for ( y = x->child; y; *ptr++ = y->ch, traverse(y), --ptr, y = y->sibling );
}

int main() {
	int cs = 0,i;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	while ( scanf("%d\n",&n) == 1 ) {
		if ( ++cs > 1 ) putchar('\n');
		for ( root = init_cell('$'); getword(word); trie_push(root,word) );
		ptr = word, m = 0, traverse(root);
		qsort(w,m,L,strcmp);
		for ( i = 0; i < m; ++i )
			printf("%s\n",w[i]);
		if ( !m ) puts("There is no such word.");
	}
	return 0;
}

