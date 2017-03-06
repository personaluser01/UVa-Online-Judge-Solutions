/*
 * 531. Compromise
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
#define N 0x400
#define M(k) ((1UL<<(k))-1UL)
#define Q 0x200
#define enc(x,y) ((x)|((y)<<7))

char buff[1 << 21],*ptr,w[Q][0x400];
int n,m[2],c[2][N],z[N][N],cs;
unsigned int track[N][N];

typedef struct cell {
	struct cell *sib,*son;
	char ch;
	int id;
} cell;

cell *init_cell( char ch ) {
	cell *x = (cell *)malloc(sizeof *x);
	x->ch = ch, x->sib = x->son = NULL, x->id = 0;
	return x;
}

cell *root;

int trie_push( cell *root, char *s ) {
	cell *x,*y;
	char p[0x400],i,k = 0;
	for ( i = 0; s[i]; ++i )
		if ( islower(s[i]) )
			p[k++] = s[i];
	p[k] = '\0';
	for ( i = 0, x = root; p[i]; x = y, ++i ) {
		for ( y = x->son; y && y->ch != p[i]; y = y->sib );
		if ( !y ) 
			y = init_cell(p[i]), y->sib = x->son, x->son = y;
	}
	if ( !x->id ) x->id = ++n;
	else strcpy(w[x->id],p);
	return x->id;
}

int is_word( char *s ) {
	int i;
	for ( i = 0; s[i]; ++i )
		if ( !islower(s[i]) )
			return 0;
	return 1;
}

int read_speech( int t ) {
	char word[0x30];
	int cnt,k;
	if ( t == 0 ) root = init_cell('$'), n = 0;
	for ( m[t] = 0; FG && *ptr != '#'; ) 
		for ( cnt = 0; 1 == sscanf(buff+cnt,"%s%n",word,&k); cnt += k )
			if ( is_word(word) )
				c[t][++m[t]] = trie_push(root,word);
	return ptr != NULL;
}

void dump( int x, int y ) {
	int nx,ny;
	if ( !x && !y ) return ;
	nx = (track[x][y]&M(7)), ny = track[x][y]>>7;
	dump(nx,ny);
	if ( nx == x-1 && ny == y-1 && c[0][x] == c[1][y] ) {
		if ( ++cs > 1 ) putchar(' ');
		printf("%s",w[c[0][x]]);
	}
}

int main() {
	int i,j,k;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	while ( read_speech(0) ) {
		assert( read_speech(1) );
		for ( i = 1; i <= m[0]; ++i )
			for ( j = 1; j <= m[1]; ++j ) {
				if ( c[0][i] == c[1][j] ) 
					z[i][j] = z[i-1][j-1]+1, track[i][j] = enc(i-1,j-1);
				else z[i][j] = z[i-1][j-1], track[i][j] = enc(i-1,j-1);
				if ( z[i-1][j] > z[i][j] )
					z[i][j] = z[i-1][j], track[i][j] = enc(i-1,j);
				if ( z[i][j-1] > z[i][j] )
					z[i][j] = z[i][j-1], track[i][j] = enc(i,j-1);
			}
		if ( !z[m[0]][m[1]] ) continue ;
		cs = 0, dump(m[0],m[1]);
		putchar('\n');
	}
	return 0;
}
