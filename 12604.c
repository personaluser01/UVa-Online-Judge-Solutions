/*
 * 12604. Ceasar Cipher
 * TOPIC: dawg
 * status: in progress
 */
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define is_primary(x,y) ((x)->length+1==(y)->length)
#define N (1<<21)
#define A 62
#define BIT(k) (1ULL<<(k))
#define L(k) ((k)&(~(k)+1ULL))
typedef unsigned long long u64;

int which[BIT(21)];
int who( u64 u ) {
	if ( u >= BIT(60) )
		return 60+which[u>>60];
	if ( u >= BIT(40) )
		return 40+which[u>>40];
	if ( u >= BIT(20) )
		return 20+which[u>>20];
	return which[u];
}

typedef struct cell {
	struct cell *son[A],*slink;
	int length,freq;
	u64 u;
} cell ;

cell *init( int l ) {
	cell *x = (cell *)malloc(sizeof *x);
	x->slink = NULL, x->length = l, x->u = x->freq = 0;
	memset(x->son,0,sizeof x->son);
	return x;
}

void add_son( cell *x, int ch, cell *y ) { x->u|=BIT(ch),x->son[ch]=y; }

cell *src;

cell *split( cell *x, int ch ) {
	cell *y = x->son[ch], *z = init(x->length+1), *t = x;
	u64 v,i;
	for ( add_son(x,ch,z),z->slink=y->slink,y->slink=z,v=y->u; v && (i=who(L(v)))>=0; add_son(z,i,y->son[i]), v &= ~L(v) );
	for (;t!=src && (t=t->slink)->son[ch]==y; add_son(t,ch,z) );
	for ( z->freq=y->freq, t=z; t; ++t->freq, t=t->slink );
	return z;
}

cell *update( cell *sink, int ch ) {
	cell *newsink = init(sink->length+1), *sufstate = NULL, *x = sink, *y, *z;
	for ( newsink->freq=1,add_son(sink,ch,newsink); x != src && !sufstate; )
		if ( !(y=(x=x->slink)->son[ch]) )
			add_son(x,ch,newsink);
		else if ( is_primary(x,y) )
			for ( sufstate = z = y; z; ++z->freq, z=z->slink );
		else sufstate = split(x,ch);
	if ( !sufstate ) sufstate = src;
	newsink->slink = sufstate;
	return newsink;
}

int st[0x400],*top,G[256],n,m,W;

cell *build_dawg( char *s, int n ) {
	cell *sink = src = init(0);
	int i;
	for ( i = 0; i < n; sink = update(sink,G[s[i++]]) );
	return sink;
}

char alph[0x400],s[N],word[1<<16],w[1<<16];

int unique_occurrence( char *w ) {
	cell *x = src,*y;
	int i;
	for ( i = 0; i < W; ++i ) {
		for ( y = x; y && !(y->son[G[w[i]]]); y=y->slink );
		if ( !y ) return 0;
		x = y->son[G[w[i]]];
		if ( x->length < (i+1) ) return 0;
	}
	return i == W && x && x->freq==1;
}

int main() {
	int i,j,k,ts;
	cell *sink;
#ifndef ONLINE_JUDGE
	freopen("c.txt","r",stdin);
#endif
	for ( i = 0; i < 21; which[BIT(i)] = i, ++i );
	for ( scanf("%d\n",&ts); ts--; ) {
		scanf("%s %s %s\n",alph,word,s);
		for ( n = strlen(s), i = 0; alph[i]; G[alph[i]] = i, ++i );
		m=i,sink=build_dawg(s,n),W=strlen(word);
		for ( top=st, i = 0; i <= m-1; ++i ) {
			for ( j = 0; j < W; w[j] = alph[(G[word[j]]+i)%m], ++j );
			if ( unique_occurrence(w) == 1 ) *++top = i;
		}
		if ( top == st ) puts("no solution");
		else if ( top-st == 1 ) printf("unique: %d\n",*top--);
		else {
			for ( printf("ambiguous:"), i = 1; i <= top-st; printf(" %d",st[i++]) );
			putchar('\n');
		}
	}
	return 0;
}

