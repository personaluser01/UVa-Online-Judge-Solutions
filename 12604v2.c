/*
 * 12604. Casear Cipher
 * TOPIC: aho-corasick
 * status: Accepted
 */
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N (1<<21)
#define A 62
#define BIT(k) (1ULL<<(k))
#define L(k) ((k)&(~(k)+1ULL))
#define TST(u,i) (((u)>>(i))&1ULL)
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
	struct cell *son[A],*slink,*p;
	u64 u;
	unsigned char idx;
} cell ;

void add_son( cell *x, int ch, cell *y ) {
	x->son[ch]=y,x->u|=BIT(ch),y->p=x;
}

cell *q[50000*62+0x400],**head,**tail,*sink,pool[50000*62+0x400],*nx=pool;

cell *init( cell *p ) {
	cell *x = nx++;
	x->u = 0, x->p = p, x->idx = -1, x->slink = NULL;
	return x;
}

char alph[0x400],s[N],word[1<<16],w[1<<16];
int st[0x400],*top,G[256],n,m,W,cn[0x400];

void push( cell *root, char *s, int idx ) {
	cell *x;
	for ( x = root; *s; x=x->son[G[*s++]] ) 
		if ( !TST(x->u,G[*s]) )
			add_son(x,G[*s],init(x));
	x->idx = idx;
}

void compute_links( cell *root ) {
	cell *x,*z,*y;
	u64 v,i;
	for ( head=tail=q, *tail++=root; head < tail; )
		for ( v=(x=*head++)->u; v && (i=who(L(v)))>=0; y->slink=z->son[i], v &= ~L(v) ) 
			for ( *tail++=y=x->son[i],  z=x->slink; z && !TST(z->u,i); z = z->slink );
}

void count_occurrences( cell *root, char *s ) {
	cell *x;
	for ( x = root; *s; ++s ) {
		for ( ;x && !TST(x->u,G[*s]); x = x->slink );
		assert ( x );
		x = x->son[G[*s]];
		if ( x->idx != -1 )
			++cn[x->idx];
	}
}

int main() {
	int i,j,k,ts;
	cell *root;
#ifndef ONLINE_JUDGE
	freopen("c.txt","r",stdin);
#endif
	for ( i = 0; i < 21; which[BIT(i)] = i, ++i );
	for ( scanf("%d\n",&ts); ts--; ) {
		fgets(alph,sizeof alph,stdin);
		fgets(word,sizeof word,stdin);
		fgets(s,sizeof s,stdin), nx = pool;
		for ( n = 0; s[n] && s[n] != '\n'; ++n );
		for ( s[n] = '\0', i = 0; alph[i] && alph[i] != '\n'; G[alph[i]] = i, ++i );
		for ( W = 0; word[W] && word[W] != '\n'; ++W );
		word[W] = '\0', m=i,root=init(NULL),sink=init(NULL),root->slink=sink;
		for ( i = 0; i < A; add_son(sink,i++,root) );
		for ( root->p=NULL, w[W]='\0', top=st, i = 0; i <= m-1; push(root,w,i++) ) 
			for ( cn[i] = 0, j = 0; j < W; w[j] = alph[(G[word[j]]+i)%m], ++j );
		for ( compute_links(root), top = st, count_occurrences(root,s), i = 0; i <= m-1; ++i )
			if ( cn[i] == 1 ) *++top = i;
		if ( top == st ) puts("no solution");
		else if ( top-st == 1 ) printf("unique: %d\n",*top--);
		else {
			for ( printf("ambiguous:"), i = 1; i <= top-st; printf(" %d",st[i++]) );
			putchar('\n');
		}
	}
	return 0;
}

