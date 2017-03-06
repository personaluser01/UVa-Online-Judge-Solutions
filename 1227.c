/*
 * 1227. The Longest Constant Gene
 * TOPIC: suffix automata
 * status: Accepted
 */
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define L(u) ((u)&(~(u))+1UL)
#define BIT(k) (1ULL<<(k))
#define is_primary(x,y) ((x)->length+1==(y)->length)
#define A 10
#define SHARP(k) (4+(k))
#define FG fgets(buff,sizeof buff,stdin)
#define MASK(k) (BIT(k)-1ULL)

typedef struct cell {
	struct cell *son[A],*slink;
	unsigned short u;
	unsigned char v;
	int length;
} cell;

int ts,m,n,which[1<<A],id[256],w,STATES;
char buff[0x400];

cell *init( int l ) {
	int i;
	cell *x = (cell *)malloc(sizeof *x);
	for ( ++STATES, x->slink=NULL,x->length=l,x->v=x->u=0,i=0;i < A; x->son[i++]=NULL );
	return x;
}

void add_son( cell *x, int ch, cell *y ) { x->u|=BIT(ch), x->son[ch]=y; }
cell *src;

cell *split( cell *x, int ch ) {
	cell *z = init(x->length+1),*y=x->son[ch],*t;
	unsigned int v=y->u;
	for ( add_son(x,ch,z),z->slink=y->slink,y->slink=z; v; z->v|=y->v,add_son(z,which[L(v)],y->son[which[L(v)]]), v &= ~L(v) );
	for ( t=x; t != src && (t=t->slink)->son[ch]==y; add_son(t,ch,z) );
	return z;
}

cell *update( cell *sink, int ch ) {
	/*putchar(ch+'A');*/
	cell *newsink = init(sink->length+1),*x,*y,*sufstate = NULL;
	for ( add_son(sink,ch,newsink), x = sink; x != src && !sufstate; ) 
		if ( !(y=(x=x->slink)->son[ch]) )
			add_son(x,ch,newsink);
		else sufstate=(is_primary(x,y)?y:split(x,ch));
	if ( !sufstate ) sufstate = src;
	newsink->slink = sufstate;
	return newsink;
}

void traverse( cell *x, unsigned char v ) {
	for ( ;x != src; x = x->slink ) 
		if ( (x->v|=v) == MASK(m) )
			if ( x->length > w )
				w = x->length;
}

void build_dawg( int m ) {
	int i,j;
	cell *sink = src = init(0);
	for ( STATES=0,src->v=MASK(m), w=0, i = 0; i < m; traverse(sink=update(sink,SHARP(i)),BIT(i)), ++i ) 
		for (;(j=getchar())!=EOF && j!='\n'; traverse(sink=update(sink,id[j]),BIT(i)) );
	/*puts("");*/
}

int main() {
	int i,j,k;
#ifndef ONLINE_JUDGE
	freopen("a.txt","r",stdin);
#endif
	for ( i = 0; i < A; which[BIT(i)] = i, ++i );
	id['A']=0,id['G']=1,id['T']=2,id['C']=3;
	for ( sscanf(FG,"%d",&ts); ts--; sscanf(FG,"%d",&m), build_dawg(m), printf("%d\n",w) );
	return 0;
}

