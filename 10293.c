/*
 * 10293. Word Length and Frequency
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
#define FG (ptr = fgets(buff,sizeof(buff),stdin))

char buff[0x400],*ptr;
int end() { return !0[buff]||(0[buff]=='#'&&(!1[buff]||1[buff]=='\n')); }

typedef struct cell {
	struct cell *son,*sibling;
	char ch;
	int cnt,len;
} cell;

cell *init_cell( char ch, int len ) {
	cell *x = (cell *)malloc(sizeof *x);
	x->sibling = x->son = NULL, x->ch = ch;
	x->cnt = 0, x->len = len;
	return x;
}

void trie_push( cell *root, char *s ) {
	cell *x,*y;
	int k = 1,i;
	char *q = s,tmp[0x30];
	/*
	printf("PUSH %s\n",q);
	*/
	for ( q = tmp, i = 0; s[i]; ++i )
		if ( isalnum(s[i]) )
			*q++ = s[i];
	*q = '\0', q = tmp;
	for ( x = root; *q; x = y, ++q, ++k ) {
		for ( y = x->son; y && y->ch != *q; y = y->sibling );
		if ( !y )
			y = init_cell(*q,k), y->sibling = x->son, x->son = y;
	}
	++x->cnt;
}

char *top,stack[0x30];
int freq[0x30];

void traverse( cell *x ) {
	cell *y;
	if ( x ) {
		freq[x->len] += x->cnt;
		for ( y = x->son; y; y = y->sibling )
			traverse(y);
	}
}

int main() {
	cell *root;
	int i,j,k,cnt;
	char w[0x30];
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	for ( ptr = buff; ptr; ) {
		root = init_cell('$',0);
		for ( top = stack; FG && !end(); ) {
			for ( cnt = 0; 1 == sscanf(buff+cnt,"%[a-zA-Z-'0-9]%n",w,&k); cnt += k ) {
				j = strlen(w);
				if ( !cnt ) {
					if ( top > stack ) {
						for ( i = 0; w[i]; *++top = w[i++] );
						if ( w[j-1] != '-' && top > stack ) {
							*++top = '\0', trie_push(root,stack+1), top = stack;
							goto nx;
						}
					}
				}
				if ( w[j-1] == '-' && top == stack )
					for ( i = 0; w[i]; *++top = w[i++] );
				if ( w[j-1] != '-' )
					trie_push(root,w);
				nx: 
				for (;buff[cnt+k] && buff[cnt+k] != '\n' && !isalnum(buff[cnt+k]); ++k );
				if ((!buff[cnt+k])||buff[cnt+k]=='\n') 
					break ;
			}
		}
		memset(freq,0,sizeof(freq)), traverse( root );
		for ( j = 0, i = 1; i < 0x30; ++i )
			if ( freq[i] && ++j ) 
				printf("%d %d\n",i,freq[i]);
		if ( j ) putchar('\n');
	}
	return 0;
}

