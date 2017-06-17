/*
 * 12206. Stammering Aliens
 * TOPIC: DAWG, bfs on suffix automata, dp on suffix automata
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N (1<<16)
#define L(k) ((k)&((~(k))+1ULL))
#define SET(u,k) ((u)|=BIT(k))
#define BIT(k)   (1ULL<<(k))
#define MASK(k)  (BIT(k)-1ULL)
#define TST(u,k) (((u)>>(k))&1ULL)
#define A 26
#define is_primary(x,y) ((x)->len+1==(y)->len)
#define max(x,y) ((x)<(y)?(y):(x))

typedef struct cell {
	struct cell *son[A],*slink;
	unsigned int map;
	int len,pos,freq,outdeg;
} cell;

cell pool[2*N],*ptr = pool,*q[2*N],**head,**tail;
char which[1<<21];

int who( unsigned int u ) {
	if ( u >= BIT(20) )
		return 20+which[u>>20];
	return which[u];
}

cell *init( int len, int pos ) {
	cell *x = ptr++;
	x->freq = x->map = x->outdeg = 0, x->slink = NULL, x->len = len, x->pos = pos;
	return x;
}

void add_son( cell *x, int ch, cell *y ) {
	SET(x->map,ch), x->son[ch] = y;
}

int min_freq,n;
char str[N];
cell *root,*sink;

void make_suffix_link( cell *x, cell *y ) {
	x->slink = y, ++y->outdeg;
}

cell *split( cell *x, int ch, int pos ) {
	unsigned int u;
	cell *y=x->son[ch],*z=init(x->len+1,pos);
	for ( z->slink=y->slink,make_suffix_link(y,z),u=z->map=y->map;u;z->son[who(L(u))]=y->son[who(L(u))],u&=~L(u) ) ;
	for ( x->son[ch]=z,x=x->slink; x && TST(x->map,ch) && x->son[ch]==y; x->son[ch]=z, x=x->slink ) ;
	return z;
}

cell *update( int ch, int pos ) {
	cell *new_sink=init(sink->len+1,pos),*x,*y;
	new_sink->freq = 1;
	for ( add_son(sink,ch,new_sink), x=sink->slink; x && !TST(x->map,ch); add_son(x,ch,new_sink), x=x->slink ) ;
	if ( !x ) {
		make_suffix_link(new_sink,root);
		return new_sink;
	}
	if ( is_primary(x,x->son[ch]) ) 
		make_suffix_link(new_sink,x->son[ch]);
	else 
		make_suffix_link(new_sink,split(x,ch,pos));
	return new_sink;
}

int main() {
	int i,j,k,maxlen,pos;
	cell *x,*y;
	for ( i = 0; i < 21; which[BIT(i)] = i, ++i ) ;
	for ( ;1 == scanf("%d",&min_freq) && min_freq && 1 == scanf("%s",str); ) {
		ptr = pool, root = sink = init(0,-1);
		for ( n = 0; str[n]; sink = update(str[n]-'a',n), ++n ) ;
		for ( head=tail=q, i = 0; i < ptr-pool; ++i )
			if ( !(pool[i].outdeg) )
				*tail++ = pool+i;
		for ( k = 0; head < tail; ) {
			x = *head++, ++k, y = x->slink;
			if ( y ) y->freq += x->freq, y->pos = max(y->pos,x->pos);
			if ( y && !--y->outdeg && y != root )
				*tail++ = y;
		}
		assert( k == ptr-pool-1 );
		for ( maxlen = -1, i = 0; i < ptr-pool; ++i ) 
			if ( pool[i].len && pool[i].freq >= min_freq ) {
				if ( pool[i].len > maxlen )
					pos = pool[i].pos, maxlen = pool[i].len;
				else if ( pool[i].len == maxlen && pool[i].pos > pos )
					pos = pool[i].pos;
			}
		if ( maxlen == -1 ) 
			puts("none");
		else printf("%d %d\n",maxlen,pos-maxlen+1);
	}
	return 0;
}

