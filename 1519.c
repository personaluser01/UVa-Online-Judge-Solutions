/*
 * 1519. Dictionary Size
 * TOPIC: trie, dp, combinatorics
 * status:
 */
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N (1<<21)
#define A 26
typedef unsigned long long u64;
#define BIT(k) (1UL<<(k))
#define MASK(k) (BIT(k)-1UL)
#define L(k) ((k)&((~(k))+1ULL))

int n,seen[256],yes;
char which[BIT(21)];

int who( u64 u ) {
	if ( u >= BIT(20) )
		return 20+which[u>>20];
	return which[u];
}

typedef struct cell {
	struct cell *son,*sib,*link;
	char ch,is_term;
	unsigned int u;
	int k;
} cell;

cell pool[N],*qtr,*que[N],**head,**tail,*sink;

cell *init( char ch ) {
	cell *x = qtr++;
	x->son = x->sib = x->link = NULL;
	x->is_term = 0, x->ch = ch, x->u = x->k = 0;
	return x;
}

typedef struct {
	cell *root,*sink;
	u64 cnt,e[A],extentions[A];
	char present[A];
} tree;

cell *_goto( tree *t, cell *x, int ch ) {
	cell *y;
	if ( x==t->sink )
		return t->root;
	if ( !((x->u>>ch)&1) )
		return NULL;
	for ( y = x->son; y && y->ch != ch+'a'; y = y->sib );
	assert( y );
	return y;
}

tree *init_tree() {
	tree *t = (tree *)malloc(sizeof *t);
	t->root = init('$'), t->cnt = 1;
	t->root->link = t->sink = init('\0'), t->sink->u=MASK(A);
   	memset(t->e,0,sizeof t->e);
   	memset(t->extentions,0,sizeof t->extentions);
	memset(t->present,0,sizeof t->present);
	return t;
}

void insert( tree *t, char *s ) {
	cell *x,*y;
	if ( !*(s+1) ) t->present[*s-'a'] = 1;
	for ( x = t->root; x && *s; x = y, ++s ) {
		for ( y = x->son; y && y->ch != *s; y = y->sib );
		if ( !y ) 
			x->u|=BIT(*s-'a'),y=init(*s),y->sib=x->son,x->son=y,++t->e[*s-'a'],++t->cnt;
	}
	x->is_term = 1;
}

void traverse( tree *t, cell *x ) {
	cell *y;
	if ( x ) 
		for ( y = x->son; y; traverse(t,y), y = y->sib )
			++t->extentions[y->ch-'a'];
}

void bfs( tree *t ) {
	cell *x,*y,*z;
	for ( head=tail=que,*tail++=t->root; head < tail; )
		for ( x = *head++, y = x->son; y; y = y->sib ) {
			for ( *tail++=y, z = x->link; z && !((z->u>>(y->ch-'a'))&1); z = z->link );
			assert( z );
			y->link = _goto(t,z,y->ch-'a');
		}
}

int dfs( cell *x ) {
	cell *y;
	if ( !x ) return 0;
	for ( x->k = x->is_term, y = x->son; y; x->k += dfs(y), y = y->sib );
	return x->k;
}

int main() {
	int i,j,k,l,m;
	tree *q,*r;
	cell *x,*y,*z;
	char s[0x400],t[0x400];
	u64 ax,cnt[A];
	unsigned int u,v;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( k = 0; k < 21; which[BIT(k)] = k, ++k );
	for (;1 == scanf("%d",&n); printf("%llu\n",ax) ) {
		for (ax=0,memset(cnt,0,sizeof cnt),qtr=pool,q=init_tree(),r=init_tree(),i=0;i<n;++i,insert(r,s),insert(q,t)) 
			for (scanf("%s",s),m=strlen(s),strcpy(t,s),l=0,j=m-1;l<j;k=t[l],t[l]=t[j],t[j]=k,++l,--j);
		for ( traverse(q,q->root), head=tail=que, *tail++=r->root; head<tail; ) {
			for(x=*head++,y=x->son;y;*tail++=y,y=y->sib);
			if ( x->ch!='$' )
				ax+=(q->cnt-q->extentions[x->ch-'a']-1);
		}
		printf("%llu\n",ax);
		for ( dfs(r->root), bfs(r), head=tail=que, *tail++=r->root; head < tail; ) 
			for ( x=*head++,ax+=x->is_term,z=x->link,u=(x->u&~(z->u)),y=x->son; y; *tail++=y,y=y->sib ) 
				if ( z!=r->root && ((u>>(y->ch-'a'))&1) )
					ax+=y->k;
		for ( i = 0; i < A; ax += r->present[i++] );
	}
	return 0;
}


