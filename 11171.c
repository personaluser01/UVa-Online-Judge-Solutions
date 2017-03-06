/*
 * 11171. SMS
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 10100
#define LEN 250100
#define oo 0xffffffffffffffffull

typedef unsigned long long u64;

int n,V;
char buff[LEN],s[LEN],mp[256];
const char *A = "abcdefghijklmnopqrstuvwxyz";

unsigned int min( unsigned int x, unsigned int y ) { return x < y ? x:y; }

typedef struct cell {
	struct cell *son,*sib;
	char ch;
	int idx,cnt,n,cluster;
} cell ;

cell *init( char ch ) {
	cell *x = (cell *)malloc(sizeof *x);
	x->sib = x->son = NULL;
	x->ch = ch, x->idx = -1, x->cnt = 0, x->n = -1;
	return x;
}

int push( cell *root, char *s, char *conv, int IDX ) {
	cell *x,*y;
	for ( x = root; *s; x = y, ++s ) {
		for ( y = x->son; y && y->ch != conv[*s]; y = y->sib );
		if ( !y )
			y = init(conv[*s]), y->sib = x->son, x->son = y;
	}
	x->idx = IDX;
	return x->cnt++;
}

int query( cell *x, char *s, int *u ) {
	cell *y;
	if ( !*s ) { *u = x->idx; return x->cnt; }
	for ( y = x->son; y && y->ch != mp[*s]; y = y->sib );
	assert( y );
	return query(y,++s,u);
}

void cleanup( cell *x ) { if ( x ) cleanup(x->sib), cleanup(x->son), free(x); }

cell *root,*T;
u64 z[LEN];
char word[LEN],keyseq[N][0x10],identity[256];
int next[LEN],seq[LEN],p[LEN];

#define TRANSIT(i) ((i)<=n?1:0)

u64 f( int k ) {
	cell *x,*y;
	int i,len,up,down,presses,tmp;
	if ( z[k] < +oo )
		return z[k];
	assert( k <= n+1 );
	if ( k == n+1 )
		return z[k] = 0;
	for ( len = 1, i = k, x = root; i <= n; ++i, x = y, ++len ) {
		for ( y = x->son; y && y->ch != word[i]; y = y->sib );
		if ( y && y->idx >= 0 && f(i+1) < +oo ) {
			if ( y->n == -1 )
				tmp = word[i+1], word[i+1] = '\0', y->n = query(T,word+k,&y->cluster), word[i+1] = tmp;
			up = y->idx, down = (y->n-y->idx)%y->n;
			presses = min(up,down);
			if ( len+presses+z[i+1]+TRANSIT(i+1) < z[k] ) {
				z[k] = len+presses+z[i+1]+TRANSIT(i+1);
				p[k] = (up>down?0:1)|(presses<<1), next[k] = i+1, seq[k] = y->cluster;
			}
		}
		if ( !y ) return z[k];
	}
	return z[k];
}

void dump( int k ) { 
	if ( k <= n ) {
		printf("%s",keyseq[seq[k]]);
		if ( (p[k]>>1) ) {
			if ( p[k] & 1 )
				printf("U(%d)",p[k]>>1);
			else
				printf("D(%d)",p[k]>>1);
		}
		if ( next[k] <= n )
			putchar('R');
		dump(next[k]); 
	}
}

int main() {
	int i,j,k,t,ts;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif

	for ( k = '2', i = 0, j = 0; j < 3; ++j, ++i )
		mp[A[i]] = k;
	for ( ++k, j = 0; j < 3; ++j, ++i )
		mp[A[i]] = k;
	for ( ++k, j = 0; j < 3; ++j, ++i )
		mp[A[i]] = k;
	for ( ++k, j = 0; j < 3; ++j, ++i )
		mp[A[i]] = k;
	for ( ++k, j = 0; j < 3; ++j, ++i )
		mp[A[i]] = k;
	for ( ++k, j = 0; j < 4; ++j, ++i )
		mp[A[i]] = k;
	for ( ++k, j = 0; j < 3; ++j, ++i )
		mp[A[i]] = k;
	for ( ++k, j = 0; j < 4; ++j, ++i )
		mp[A[i]] = k;
	assert( k == '9' );
	assert( i == 26 );
	for ( i = 'a'; i <= 'z'; ++i ) identity[i] = i;

	while ( gets(buff) && 1 == sscanf(buff,"%d",&n) && n > 0 ) {
		for ( V = 0, T = init('\0'), root = init('\0'), i = 0; i < n; ++i ) {
			for ( gets(s), t = push(T,s,mp,i), push(root,s,identity,t), j = 0; s[j]; ++j )
				keyseq[i][j] = mp[s[j]];
			keyseq[i][j] = '\0';
		}
		for ( sscanf(gets(buff),"%d",&ts); ts--;) {
			for ( n = strlen(gets(word+1)), i = 0; i <= n+1; ++i ) z[i] = +oo;
			assert( f(1) < +oo );
			dump(1), putchar('\n');
		}
		/*cleanup(root), cleanup(T);*/
	}
	return 0;
}

