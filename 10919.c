/*
 * 10919. Prerequisites?
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
#define N 0x80

int m,n,q[N],r[N],cat[N];
char cname[N][8],g[N][N][8];

typedef struct cell {
	struct cell *son,*sib;
	int cnt;
	char ch;
} cell;

cell *init_cell( char ch ) {
	cell *x = (cell *)malloc(sizeof *x);
	x->son = x->sib = NULL;
	x->ch = ch, x->cnt = 0;
	return x;
}

void trie_push( cell *root, char *s ) {
	cell *x,*y;
	for ( x = root; *s; x = y, ++s ) {
		for ( y = x->son; y && y->ch != *s; y = y->sib );
		if ( !y )
			y = init_cell(*s), y->sib = x->son, x->son = y;
	}
	x->cnt = 1;
}

int find( cell *root, char *s ) {
	cell *x,*y;
	for ( x = root; *s; x = y, ++s ) {
		for ( y = x->son; y && y->ch != *s; y = y->sib );
		if ( !y ) return 0;
	}
	return x->cnt;
}

cell *root[N];

int main() {
	int i,j,k;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	while ( 2 == scanf("%d %d",&n,&m) ) {
		for ( i = 0; i < n; scanf("%s",cname[i++]) );
		for ( i = 0; i < m; ++i ) {
			root[i] = init_cell('$'), scanf("%d %d",q+i,r+i), cat[i] = 0;
			for ( j = 0; j < q[i]; scanf("%s",g[i][j++]), trie_push(root[i],g[i][j-1]) );
		}
		for ( i = 0; i < n; ++i )
			for ( j = 0; j < m; ++j )
				cat[j] += find(root[j],cname[i]);
		for ( i = 0; i < m; ++i )
			if ( cat[i] < r[i] )
				goto nx;
		puts("yes");
		continue ;
		nx: puts("no");
	}
	return 0;
}

