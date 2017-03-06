/*
 * 1123. Crazy Search
 * TOPIC: suffix automata, dawg, suffix links, dp on suffix automata, binary search, powers of two
 * status: Accepted
 */
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <iostream>
using namespace std;
#define N (1<<K)
#define K 27
#define FG (ptr = fgets(s,sizeof s,stdin))
#define is_primary(x,y) ((x)->length+1 == (y)->length)
#define BIT(k) (1ULL << (k))
#define TST(u,k) ((u)&(k))
#define MASK(k) (BIT(k)-1ULL)
enum { UNDEF = (1<<0), SENTINEL = (1<<1), SEEN = (1<<2) };
enum { WHITE = (1<<3), GREY = (1<<4), BLACK = (1<<5) };

int A,n,m,is[256],yes,V,v[256],KK;
char s[0x400];

int G( int ch ) {
	if ( is[ch] != yes )
		is[ch] = yes, v[ch] = V++;
	return v[ch];
}

typedef struct cell *cptr;
cell *q[1<<21],**head,**tail;

typedef struct cell {
	struct cell **son,*slink,*anc[K],*h;
	int length;
	unsigned char info;
	cell() {};
	cell( int l ) {
		this->son = new cptr[A]; 
   		this->slink = this->h = NULL, this->info = UNDEF, this->length = l;
		for ( int i = 0; i < A; this->son[i++] = NULL );
		for ( int i = 0; i < K; this->anc[i++] = NULL );
		// vec.push_back(this);
		*tail++ = this;
	};
	~cell() { delete this->son; };
} cell;

cell *src;

void g( cell *x ) {
	int i;
	if ( x == src || !(x->info,WHITE) ) return ;
	x->info &= ~WHITE, x->info |= GREY;
	for ( x->anc[0]=x->slink, g(x->slink), i=1; i<KK && x->anc[i-1]!=NULL; x->anc[i]=x->anc[i-1]->anc[i-1], ++i );
	x->info &= ~GREY,  x->info |= BLACK;
}

cell *split( cell *x, int ch ) {
	cell *z = new cell(x->length+1),*y = x->son[ch],*t;
	int i;
	for ( z->slink=y->slink,y->slink=z,x->son[ch]=z,i = 0; i < A; z->son[i]=y->son[i], ++i );
	for ( t = x; t != src && (t=t->slink)->son[ch]==y; t->son[ch] = z );
	return z;
}

cell *update( cell *sink, int ch ) {
	cell *newsink=new cell(sink->length+1),*x=sink,*suflink=NULL,*y;
	for ( sink->son[ch] = newsink; x != src && !suflink; ) 
		if ( !(y=(x=x->slink)->son[ch]) ) 
			x->son[ch] = newsink;
		else if ( is_primary(x,y) )
			suflink = y;
		else suflink = split(x,ch);
	if ( !suflink ) suflink = src;
	newsink->slink = suflink;
	return newsink;
}

void build_dawg() {
	cell *sink = src = new cell(0);
	int ch;
	for(n=0,V=0;(ch=getchar())!=EOF&&ch!='\n';sink=update(sink,G(ch)),++n);
	for ( KK = 0; (1<<KK) < n; ++KK );
}

cell *find( cell *x, int lim, int high ) {
	int low,mid;
	if ( x == src ) {
		if ( lim == 0 )
			return x;
		return NULL;
	}
	assert ( x != src );
	if ( x->length < lim ) return NULL;
	if ( x->length >= lim && (!x->slink || x->slink->length < lim) ) {
		x->info |= SENTINEL;
		return x;
	}
	if ( TST(x->info,SEEN) || TST(x->info,SENTINEL) )
		return x->h;
	x->info |= SEEN;
	assert( x->anc[low=0] && x->anc[low=0]->length >= lim );
	assert( !x->anc[high] || x->anc[high]->length < lim );
	for (;low+1<high;) {
		mid = (low+high)/2;
		if ( !x->anc[mid] || x->anc[mid]->length < lim )
			high = mid;
		else low = mid;
	}
	assert( !x->anc[high] || x->anc[high]->length < lim );
	assert( x->anc[low] && x->anc[low]->length >= lim );
	assert( !x->anc[low]->anc[low] || x->anc[low]->anc[low]->length < lim );
	x->h = find(x->anc[low],lim,low);
	if ( x->h == x ) x->info |= SENTINEL;
	return x->h;
}

void calc_h( cell *x ) {
	if ( TST(x->info,SEEN) || TST(x->info,SENTINEL) )
		return ;
	x->info |= SEEN, x->h = find(x,m,KK-1);
	if ( x->h == x ) x->info |= SENTINEL;
}

int main() {
	int i,j,k,ts,ans;
#ifndef ONLINE_JUDGE
	freopen("b.txt","r",stdin);
#endif
	for ( scanf("%d",&ts); ts--; ) {
		scanf("%d %d\n",&m,&A);
		for ( ++yes, V = 0, head=tail=q, build_dawg(), i = 0; i < tail-head; ++i ) 
			if ( TST(q[i]->info,WHITE) )
				g(q[i]);
		for ( i = 0; i < tail-head; ++i )
			calc_h(q[i]);
		for ( ans = 0, i = 0; i < tail-head; ++i )
			if ( TST(q[i]->info,SENTINEL) ) ++ans;
		printf("%d\n",ans);
		if ( ts ) putchar('\n');
		for ( i = 0; i < tail-head; ++i ) delete q[i];
	}
	return 0;
}

