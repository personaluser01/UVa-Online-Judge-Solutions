/*
 * 126. Telephone Tangles
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
#define L 0x20
#define N (1 << 16)
#define tol 1e-9

int m,n,cents[N],dur,len[N];
char code[N][L],locname[N][L],num[L];

typedef struct cell {
	struct cell *sib,*son;
	char ch;
	int id;
} cell;

cell *root;

cell *init_cell( char ch ) {
	cell *x = (cell *)malloc(sizeof *x);
	x->sib = x->son = NULL, x->ch = ch, x->id = -1;
	return x;
}

void trie_push( cell *root, char *s, int id ) {
	cell *x,*y;
	for ( x = root; *s; x = y, ++s ) {
		for ( y = x->son; y && y->ch != *s; y = y->sib );
		if ( !y )
			y = init_cell(*s), y->sib = x->son, x->son = y;
	}
	x->id = id;
}

int srch( cell *root, char *s, int left, int right ) {
	int d = 0,k = strlen(s);
	cell *x,*y;
	for ( x = root; *s; ++d, ++s, x = y ) {
		for ( y = x->son; y && y->ch != *s; y = y->sib );
		if ( !y )
			return -1;
		if ( y->id != -1 && left <= k-d-1 && k-d-1 <= right )
			return y->id;
	}
	if ( left <= k-d && k-d <= right )
		return x->id;
	return -1;
}

void print( char *num, char *town, int shift, int dur, int cents ) {
	if ( !strcmp(town,"Unknown") )
		printf("%-16s%-25s%10s%5d%6s%7.02lf\n",num,town,"",dur,"",-1.00+tol);
	else if ( strcmp("Local",town) )
		printf("%-16s%-25s%10s%5d%6.02lf%7.02lf\n",num,town,num+shift,dur,cents/100.00+tol,cents*dur/100.00+tol);
	else 
		printf("%-16s%-5s%30s%5d%6.02lf%7.02lf\n",num,town,num+shift,dur,cents/100.00+tol,cents*dur/100.00+tol);
}

int main() {
	int i,j,k;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	root = init_cell('$');
	for ( m = 0; scanf("%s",code[m]) == 1 && strcmp(code[m],"000000"); ++m )  {
		getchar(), scanf("%[^$]$%d",locname[m],cents+m);
		trie_push(root,code[m],m);
		len[m] = strlen(code[m]);
	}
	for (;scanf("%s",num) == 1 && 0[num] != '#' && scanf("%d",&dur) == 1;) {
		if ( 0[num] != '0' ) {
			print(num,"Local",0,dur,0);
			continue ;
		}
		assert( 0[num] == '0' );
		i = srch(root,num,4,1[num] == '0'?10:7);
		if ( i == -1 ) {
			print(num,"Unknown",0,dur,0);
			continue ;
		}
		print(num,locname[i],len[i],dur,cents[i]);
	}
	return 0;
}
