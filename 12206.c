/*
 * 12206. Stammering Aliens
 * TOPIC: dawg, dp
 * status: in progress
 */
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BIT(k) (1<<(k))
#define N BIT(21)
#define L(k) ((k)&((~(k))+1UL))
#define is_primary(x,y) ((x)->length+1==(y)->length)
#define A 26
#define FG (fgets(s,sizeof s,stdin))
#define oo BIT(29)

int V,n,m,best_length,best_pos;

typedef struct cell {
	struct cell *son[A],*slink;
	int length,freq,pos;
	unsigned int u;
	char seen;
} cell ;

cell *src,**top,*st[N];
int which[1 << 21];

int who( unsigned int u ) {
	if ( u >= (1<<20) )
		return 20+which[u>>20];
	return which[u];
}

void add_son( cell *x, int ch, cell *y ) { x->u |= BIT(ch), x->son[ch] = y; }

cell *init( int l ) {
	int i;
	cell *x = (cell *)malloc(sizeof *x);
	assert( x );
	*++top = x, x->u=0, x->length = l, ++V, x->seen = 0, x->slink = NULL, x->freq = 0, x->pos = -oo;
	for ( i = 0; i < A; x->son[i++] = NULL ) ;
	return x;
}

cell *split( cell *x, int ch ) {
	int i;
	cell *y=x->son[ch],*t=x,*z=init(x->length+1);
	unsigned int v = y->u;
	for ( add_son(x,ch,z), z->slink=y->slink, y->slink=z; v; i=who(L(v)), add_son(z,i,y->son[i]), v &= ~L(v) );
	for ( z->freq=y->freq, z->pos=n-z->length; t != src && (t=t->slink)->son[ch]==y; t->son[ch]=z );
	for ( t = z; t; ++t->freq, t->pos = n-t->length, t = t->slink );
	return z;
}

cell *update( cell *sink, int ch ) {
	cell *newsink = init(sink->length+1),*sufstate=NULL,*x = sink,*y,*z;
	for ( add_son(sink,ch,newsink), newsink->freq=1, newsink->pos=0; x != src && !sufstate; ) {
		if ( !(y=(x=x->slink)->son[ch]) )
			add_son(x,ch,newsink);
		else if ( is_primary(x,y) ) {
			for ( sufstate = z = y; z; ++z->freq, z->pos = n-z->length, z=z->slink );
		}
		else sufstate = split(x,ch);
	}
	if ( !sufstate ) sufstate = src;
	newsink->slink = sufstate;
	return newsink;
}

void traverse( cell *x ) {
	int i;
	unsigned int v;
	if ( !x||x->seen||x->freq<m) return ;
	if ( x->freq >= m )
		if ( x->length > best_length || x->length == best_length && x->pos > best_pos )
			best_length=x->length, best_pos=x->pos;
	for ( x->seen=1, v=x->u; v; i=who(L(v)), traverse(x->son[i]), v &= ~L(v) );
}

void traverse2( cell *x ) {
	unsigned int i,v;
	if ( !x || x->seen ) return ;
	if ( x->freq >= m )
		if ( x->length > best_length || x->length == best_length && x->pos > best_pos )
			best_length=x->length, best_pos=x->pos;
	traverse2(x->slink);
}

void build_dawg( char *s ) {
	cell *sink=src=init(0);
	for ( best_length=-oo, n=0; s[n] && s[n]!='\n'; sink=update(sink,s[n++]-'a') );
	for ( ;top > st; --top )
		if ( !(*top)->seen ) traverse2(*top);
	if ( best_length == -oo ) puts("none");
	else printf("%d %d\n",best_length,best_pos);
}

char s[N];

int main() {
	int i;
#ifndef ONLINE_JUDGE
	freopen("c.txt","r",stdin);
#endif
	for(i=0;i<21;which[BIT(i)]=i,++i);
	for(;scanf("%d",&m)==1&&m>=1&&1==scanf("%s",s);V=0,top=st,build_dawg(s));
	return 0;
}

