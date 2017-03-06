/*
 * 257. Palinwords
 * TOPIC: aho-corasick
 * status: Accepted
 */
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 0x200
#define   A     26
#define   L(u)  ((u)&((~(u))+1ULL))
#define BIT(k)  (1ULL<<(k))
#define MASK(k) (BIT(k)-1ULL)
#define TST(u,k) (((u)>>(k))&1)
typedef unsigned long long u64;

typedef struct cell {
	struct cell *son[A],*p,*link;
	unsigned int u;
	char ch;
	u64 v[N>>6];
	int idx;
} cell;

void init( cell **e, char ch, cell *p ) {
	cell *x = (cell *)malloc(sizeof *x);
	x->p = p, x->u = 0, x->ch = ch, memset(x->v,0,sizeof x->v), x->link = NULL, x->idx = -1;
	*e = x;
}

char which[BIT(21)],c[N];
cell *sink;
int n,V,yes,g[N][N];

int who( const u64 u ) {
	if ( u >= BIT(60) )
		return 60+which[u>>60];
	if ( u >= BIT(40) )
		return 40+which[u>>40];
	if ( u >= BIT(20) )
		return 20+which[u>>20];
	return which[u];
}

void push( cell *root, int left, int right ) {
	cell *x;
	int i,j,k;
	/*
	k = c[right+1], c[right+1] = '\0', puts(c+left), c[right+1] = k;
	*/
	for ( x = root, i = left; i <= right && (k=c[i]-'A')>=0; ++i, x = x->son[k] ) 
		if ( !TST(x->u,k) ) x->u |= BIT(k), init(&x->son[k],k,x);
	if ( x->idx==-1 ) 
		x->idx=V++,x->v[x->idx>>6]|=BIT(x->idx&63ULL);
}

cell *q[N],**head,**tail,*e[N];
int cnt;

void suflinks( cell *root ) {
	int i,j,k;
	cell *x,*y;
	unsigned int u;
	for ( root->p = root, root->link = sink, sink->u = MASK(A), i = 0; i < A; sink->son[i++] = root );
	for ( head=tail=q,u=root->u; u; u&=~L(u) ) {
		*tail++=root->son[who(L(u))];
		assert( root->son[who(L(u))] );
	}
	for(;head<tail;){
		for(x=*head++,u=x->u;u;*tail++=x->son[who(L(u))],u&=~L(u));
		for(y=x->p->link;!(y->u&BIT(x->ch));y=y->link);
		for(x->link=y->son[x->ch],i=0;i<N/64;x->v[i]|=x->link->v[i],++i);
	}
}

void traverse( cell *root ) {
	cell *x,*y;
	int i,j,k;
	unsigned int u;
	for ( head = tail = q, *tail++ = root; head < tail; ) {
		x = *head++;
		if ( x->idx != -1 ) e[x->idx] = x;
		for ( u = x->u; u; u &= ~L(u) )
			for ( *tail++ = (y = x->son[k=who(L(u))]), j = 0; j < N/64; ++j )
				y->v[j] |= x->v[j];
	}
}

int main() {
	int i,j,k,l,t,shift;
	u64 u;
	cell *root;
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	for ( i = 0; i < 21; ++i ) which[BIT(i)] = i;
	for ( init(&sink,'$',NULL), sink->p=sink->link=sink; 1 == scanf("%s",c) && ++yes; ) {
		n = strlen(c), init(&root,'\0',NULL);
		for ( V = 0, t = 0; t < n; ++t ) {
			for ( i = t-1, j = t+1; i >= 0 && j < n && c[i] == c[j]; --i, ++j )
				if ( (j-i+1)>=3 ) push(root,i,j);
			for ( i = t, j = t+1; i >= 0 && j < n && c[i] == c[j]; --i, ++j )
				if ( (j-i+1)>=3 ) push(root,i,j);
		}
		suflinks(root);
	   	traverse(root);
		for ( t = 0; t < V; ++t )
			for ( shift = l = 0; l < N/64; ++l, shift += 64 )
				for ( u = e[t]->v[l]; u; u &= ~L(u) )
					g[t][shift+who(L(u))] = yes;
		for ( k = i = 0; i < V && !k; ++i )
			for ( j = i+1; j < V && !k; ++j )
				if ( g[i][j] != yes && g[j][i] != yes ) k = 1;
		if ( k ) puts(c);
	}
	return 0;
}

