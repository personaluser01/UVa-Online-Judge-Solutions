/*
 * 10374. Election
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
#define L 0x80
#define N 0x80

int cnt[N];

typedef struct cell {
	struct cell *child, *sibling;
	char ch;
	int id;
} cell;

void trie_push( cell *root, char *s, int id ) {
	cell *x,*y;
	for ( x = root; *s; x = y, ++s ) {
		for ( y = x->child; y && y->ch != *s; y = y->sibling );
		if ( !y ) {
			y = (cell *)malloc(sizeof *y), y->child = y->sibling = NULL;
			y->ch = *s, y->id = 0, y->sibling = x->child, x->child = y;
		}
	}
	if ( !x->id ) x->id = id;
}

int get_id( cell *root, char *s ) {
	cell *x,*y;
	for ( x = root; *s; x = y, ++s ) {
		for ( y = x->child; y && y->ch != *s; y = y->sibling );
		if ( !y ) return 0;
	}
	return x->id;
}

char cname[N][L],pname[N][L];
int n,ts,m;

int main() {
	int i,j,k,max_cnt;
	cell *root;
	char nm[L];
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( scanf("%d\n",&ts); ts--; ) {
		scanf("%d\n",&n), root = (cell *)malloc(sizeof *root);
		root->child = root->sibling = NULL, root->id = 0, root->ch = '$';
		for ( i = 1; i <= n; cnt[i++] = 0 );
		for ( i = 1; i <= n; ++i ) 
			scanf("%[^\n]\n",cname[i]), trie_push(root,cname[i],i), scanf("%[^\n]\n",pname[i]);
		for ( scanf("%d\n",&m);m--; scanf("%[^\n]\n",nm), ++cnt[i = get_id(root,nm)] );
		for ( max_cnt = -(1<<29),i = 1; i <= n; ++i )
			if ( cnt[i] > max_cnt )
				max_cnt = cnt[j = i], k = 1;
			else if ( cnt[i] == max_cnt && ++k );
		puts(k > 1 ? "tie":pname[j]);
		if ( ts ) putchar('\n');
	}
	return 0;
}
