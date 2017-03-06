/*
 * 11855. Buzzwords
 * TOPIC: dawg, dp
 * status: Accepted
 */
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define A 26
#define N (1 << 16)
#define FG (ptr = fgets(s,sizeof s,stdin))
#define is_primary(x,y) ((x)->length+1==(y)->length)

int max( int x, int y ) { if ( x < y ) return y; return x; }

typedef struct cell {
	struct cell *son[A],*slink;
	int length,freq;
	char seen;
} cell;

char s[N],*ptr;
int n;

cell *init( int l ) {
	cell *x = (cell *)malloc(sizeof *x);
	x->slink = NULL, x->length = l, x->freq = x->seen = 0;
	memset(x->son,0,sizeof x->son);
	return x;
}

cell *src;
int G[256],cnt[0x400],SHARP;

cell *split( cell *x, int ch ) {
	int i;
	cell *y = x->son[ch], *z = init(x->length+1), *t = x;
	for ( x->son[ch]=z,z->slink=y->slink,y->slink=z, i = 0; i < A; z->son[i]=y->son[i], ++i );
	for ( z->freq=y->freq; t!=src && (t=t->slink)->son[ch]==y; t->son[ch] = z );
	for ( t = z; t; ++t->freq, t = t->slink );
	return z;
}

cell *update( cell *sink, int ch ) {
	cell *newsink = init(sink->length+1),*x=sink,*y,*sufstate=NULL,*z;
	for ( sink->son[ch]=newsink, newsink->freq=1; x != src && !sufstate; ) 
		if ( !(y=(x=x->slink)->son[ch]) ) 
			x->son[ch] = newsink;
		else if ( is_primary(x,y) ) {
			for ( sufstate = z = y; z; ++z->freq, z = z->slink );
		}
		else sufstate = split(x,ch);
	if ( !sufstate ) sufstate = src;
	newsink->slink = sufstate;
	return newsink;
}

void traverse( cell *x ) {
	int i;
	if ( !x || x->seen ) return ;
	for ( i = 1; x->freq >= 2 && i <= x->length; ++i )
		cnt[i] = max(cnt[i],x->freq);
	for ( x->seen=1, i = 0; i < A; traverse(x->son[i++]) );
}

void build_dawg() {
	cell *sink = src = init(0);
	int i,j,k;
	static int cs = 0;
	char a[0x400];
	if ( ++cs > 1 ) putchar('\n');
	for ( n=0, ptr=s; 1==sscanf(ptr,"%s%n",a,&j) && ++n; ptr+=j )
		for ( k = 0; a[k]; sink = update(sink,G[a[k++]]) );
	traverse(src);
}

int main() {
	int i,j,k;
#ifndef ONLINE_JUDGE
	freopen("c.txt","r",stdin);
#endif
	for ( i = 'A'; i <= 'Z'; G[i] = i-'A', ++i );
	for (;FG; )
		for ( memset(cnt,0,sizeof cnt), build_dawg(), k = 1; k <= 0x400 && cnt[k]>=2; printf("%d\n",cnt[k++]) );
	return 0;
}

