/*
 * 1449. Dominating Patterns
 * TOPIC: aho-corasick
 * status: Accepted
 */
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define A 26
#define N (1<<18)
#define M (1<<8)
#define B(k) (1ULL<<(k))
#define MASK(k) (B(k)-1ULL)
#define L(u) ((u)&((~(u))+1))
typedef unsigned long long u64;

typedef struct cell {
	struct cell *son[A],*p,*link;
	u64 u[3];
} cell ;

char wrd[M][1<<7];
int m,n,cnt[M];
cell *q[1 << 21],**head,**tail,*sink;

cell *init( cell *p ) {
	int i;
	cell *x = (cell *)malloc(sizeof *x);
	for ( x->link = NULL, x->p = p, i = 0; i < A; x->son[i++] = NULL );
	x->u[0] = x->u[1] = x->u[2] = 0;
	return x;
}

void push( cell *root, char *s, int idx ) {
	cell *x;
	for ( x = root; *s; x = x->son[*s++-'a'] )
		if ( !(x->son[*s-'a']) )
			x->son[*s-'a'] = init(x);
	x->u[idx>>6] |= B(idx&63);
}

void bfs(cell *root) {
	cell *x,*y,*z;
	int i,j;
	for ( head=tail=q,*tail++=root; head < tail; ) 
		for ( x=*head++, i = 0; i < A; ++i )
			if ( y=x->son[i] ) {
				for ( z=x->link; !z->son[i]; z=z->link );
				for ( *tail++ = y, y->link=z->son[i], j = 0; j < 3; y->u[j] |= y->link->u[j], ++j );
			}
}

char text[1 << 21],which[1<<21];

int who( u64 u ) {
	if ( u >= B(60) )
		return 60+which[u>>60];
	if ( u >= B(40) )
		return 40+which[u>>40];
	if ( u >= B(20) )
		return 20+which[u>>20];
	return which[u];
}

int main() {
	int i,j,k;
	cell *root,*x;
	u64 u,v;
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	for ( i = 0; i < 21; which[B(i)] = i, ++i );
	for ( ;1 == scanf("%d\n",&m) && m > 0; ) {
		for ( root=init(NULL), root->p=root, root->link=sink=init(NULL), i = 0; i < A; sink->son[i++] = root );
		for ( i = 0; i < m; cnt[i] = 0, scanf("%s\n",wrd[i++]), push(root,wrd[i-1],i-1) );
		for ( bfs(root), scanf("%s",text), x = root, i = 0; text[i]; ) {
			for(;!x->son[text[i]-'a'];x=x->link);
			for ( x=x->son[text[i++]-'a'], j = 0; j < 3; ++j )
				for ( u = x->u[j]; u; u &= ~L(u) )
					++cnt[k = j*64+who(L(u))];
		}
		for ( k = -1, i = 0; i < m; ++i ) if ( k < cnt[i] ) k = cnt[i];
		for ( printf("%d\n",k), i = 0; i < m; ++i )
			if ( cnt[i] == k )
				printf("%s\n",wrd[i]);
	}
	return 0;
}

