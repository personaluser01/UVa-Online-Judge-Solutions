/*
 * TOPIC: aho-corasick
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define A 10
#define N       (1 << 21)
#define M       (100001)
#define BIT(k)  (1ULL<<(k))
#define MASK(k) (BIT(k)-1ULL)
#define TST(k)  (a[(k)>>3] & BIT((k)&7ULL))
#define CLR(k)  (a[(k)>>3] &= ~BIT((k)&7ULL))
#define SET(k)  (a[(k)>>3] |= BIT((k)&7ULL))

int n,cnt;
char s[N],buff[0x20];
unsigned char a[((M+0x400)>>3)+1];

typedef struct cell {
	struct cell *son[A],*p,*link;
	char ch;
	int num,depth;
} cell;

cell *q[N],**head,**tail,*sink;

cell *init( char ch, int d ) {
	cell *x = (cell *)malloc(sizeof *x);
	x->p = x->link = NULL, x->num = -1, x->ch = ch, x->depth = d;
	for ( ch = 0; ch < A; x->son[ch++] = NULL );
	return x;
}

void push( cell *root, char *s, int k ) {
	cell *x,*y;
	char *p = s;
	for ( x = root; *s; x = y, ++s ) 
		if ( !(y=x->son[*s-'0']) ) 
			++cnt, x->son[*s-'0']=y=init(*s,x->depth+1), y->p = x;
	x->num = k;
}

void traverse( cell *root, char *s ) {
	int k = 0;
	cell *x,*y;
	for ( x = root; *s; ) {
		if ( x->num > k ) k = x->num;
		if ( !(y=x->son[*s-'0']) )
			x = x->link;
		else x = y, ++s;
	}
	printf("%d\n",k);
}

int main() {
	int i,j,k,is[A] = {0},yes = 0;
	cell *root,*x,*y;
	for ( SET(2), i = 3; i < M; SET(i), i += 2 );
	for ( i = 3; i < M; i += 2 )
		for ( j = i+i; TST(i) && j < M; CLR(j), j += i );
	for ( root = init('$',0), sink = init('&',-1), i = 0; i < A; ++i ) sink->son[i] = root;
	root->p = root->link = sink->p = sink->link = sink;
	for ( i = 0; i < M; ++i )
		if ( TST(i) ) 
			sprintf(buff,"%d",i), push(root,buff,i);
	for ( head = tail = q, *tail++ = root; head < tail; ) {
		for ( x = *head++, i = 0; i < A; ++i )
			if ( x->son[i] ) *tail++ = x->son[i];
		if ( x->link ) continue ;
		for ( k = x->ch-'0', y = x->p->link; y && !y->son[k]; y = y->link );
		assert( y );
		x->link = y->son[k];
		if ( x->num == -1 || x->num < x->link->num )
			x->num = x->link->num;
	}
	for ( ;1 == scanf("%s",s) && strcmp(s,"0"); traverse(root,s) );
    return 0;
}


