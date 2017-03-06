/*
 * 12467. Secret Word
 * TOPIC: suffix automata
 * status: Accepted
 */
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define A 26
#define N (1<<21)
#define is_primary(x,y) ((x)->length+1 == (y)->length)
#define FG fgets(s,sizeof s,stdin)

int max( int x, int y ) { if ( x < y ) return y; return x; }

char s[N];
int n;

typedef struct cell {
	struct cell *son[A],*slink;
	int length;
} cell;

cell *init( int l ) {
	int i;
	cell *x = (cell *)malloc(sizeof *x);
	for ( x->length = l, x->slink = NULL, i = 0; i < A; x->son[i++] = NULL );
	return x;
}

cell *src;

cell *split( cell *x, int ch ) {
	int i;
	cell *t;
	cell *y = x->son[ch], *z = init(x->length+1);
	for ( x->son[ch]=z, z->slink = y->slink, y->slink = z, i = 0; i < A; z->son[i] = y->son[i], ++i );
	for ( t = x; t != src && (t=t->slink)->son[ch] == y; t->son[ch] = z );
	return z;
}

cell *update( cell *sink, int ch ) {
	cell *newsink = init(sink->length+1),*x,*sufstate=NULL,*y;
	for ( sink->son[ch] = newsink, x=sink; x != src && !sufstate; ) {
		x = x->slink;
		if ( !(y=x->son[ch]) ) 
			x->son[ch] = newsink;
		else {
			if ( is_primary(x,y) )
				sufstate = y;
			else sufstate = split(x,ch);
		}
	}
	if ( !sufstate ) sufstate = src;
	newsink->slink = sufstate;
	return newsink;
}

cell *build_dawg() {
	int i;
	cell *sink = src = init(0);
	for ( i = 0; i < n; sink = update(sink,s[i++]-'a') );
	return src;
}

int main() {
	int i,j,k,ts;
	cell *x,*y;
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	for ( sscanf(FG,"%d",&ts); ts--; ) {
		for ( FG, n = 0; s[n] && s[n] != '\n'; ++n );
		for ( i = 0, j = n-1; i < j; ++i, --j )
			k = s[i], s[i] = s[j], s[j] = k;
		build_dawg();
		for ( i = 0, j = n-1; i < j; ++i, --j )
			k = s[i], s[i] = s[j], s[j] = k;
		for ( k=0, x=src, i=0; i<n && (y=x->son[s[i]-'a']); ) {
			if ( is_primary(x,y) )
				k=max(k,x->length);
		   	x=x->son[s[i++]-'a'];
		}
		for ( j = i-1; j >= 0; putchar(s[j--]) );
		puts("");
	}
	return 0;
}

