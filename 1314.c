/*
 * 1314. Hidden Password
 * TOPIC: minimal cyclic shift, duval, lyndon decomposition, dawg
 * status: Accepted
 */
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N (1<<21)
#define BIT(k) (1UL<<(k))
#define L(k) ((k)&(~(k)+1UL))
#define A 26
#define is_primary(x,y) ((x)->length+1==(y)->length)
int max( int x, int y ) { if ( x < y ) return y; return x; }

int which[BIT(21)],G[256],ans,n;
char s[N];

int who( unsigned int u ) {
	if ( u >= BIT(20) )
		return 20+which[u>>20];
	return which[u];
}

typedef struct cell {
	struct cell *son[A],*slink;
	int length,maxlen,pos;
	unsigned int u;
	char seen;
} cell ;

cell *init( int l ) {
	cell *x = (cell *)malloc(sizeof *x);
	x->slink=NULL,x->u=0,x->length=l,x->pos=x->seen=0;
	memset(x->son,0,sizeof x->son);
	return x;
}

void add_son( cell *x, int ch, cell *y ) { x->u|=BIT(ch),x->son[ch]=y; }

cell *src;

cell *split( cell *x, int ch ) {
	cell *y = x->son[ch], *z = init(x->length+1), *t=x;
	unsigned int v=y->u,i;
	for ( add_son(x,ch,z),z->slink=y->slink,z->pos=y->pos+(y->length-x->length),y->slink=z; v; i=who(L(v)), add_son(z,i,y->son[i]), v&=~L(v) );
	for ( ;t != src && (t=t->slink)->son[ch]==y; add_son(t,ch,z) );
	return z;
}

cell *update( cell *sink, int ch ) {
	cell *newsink=init(sink->length+1),*x=sink,*sufstate=NULL,*y;
	for ( add_son(sink,ch,newsink),newsink->pos=0; x != src && !sufstate; )
		if ( !(y=(x=x->slink)->son[ch]) )
			add_son(x,ch,newsink);
		else if ( is_primary(x,y) )
			sufstate = y;
		else sufstate = split(x,ch);
	if ( !sufstate ) sufstate = src;
	newsink->slink = sufstate;
	return newsink;
}

void build_dawg( char *s, int n ) {
	int i;
	cell *sink = src = init(0);
	for ( i = 0; i < n; sink = update(sink,G[s[i++]]) );
}

void calc_dp( cell *x ) {
	unsigned int v,i;
	for ( x->maxlen=0, v=x->u; v && (i=who(L(v)))>=0; v &= ~L(v) ) 
		calc_dp(x->son[i]), x->maxlen=max(x->maxlen,x->son[i]->maxlen+1);
}

int traverse( cell *x, int k, int SH ) {
	unsigned int v,i;
	if ( !x || x->seen ) return 0;
	if ( (x->seen=1) && x->length>=n/2 ) {
		ans = x->pos+(x->length-k);
		return 1;
	}
	for ( v = x->u; v && (i=who(L(v))) >= 0; v &= ~L(v) ) {
		/*printf("%*c\n",SH,i+'a');*/
		if ( traverse(x->son[i],k+1,SH+4) ) return 1;
		/*printf("%*c\n",SH,i+'a');*/
	}
	return 0;
}

int main() {
	int i,j,k,cs,m;
#ifndef ONLINE_JUDGE
	freopen("c.txt","r",stdin);
#endif
	for ( i = 0; i < 21; which[BIT(i)] = i, ++i );
	for ( i = 'a'; i <= 'z'; G[i]=i-'a', ++i );
	for ( scanf("%d\n",&cs); cs--; ) {
		scanf("%d %s\n",&m,s);
		for ( i=0, n=m; i<n; s[m++]=s[i++] );
		assert( (n<<=1) == m );
		build_dawg(s,n);
		assert ( traverse(src,0,0) );
	   	printf("%d\n",ans);
	}
	return 0;
}

