/*
 * 11136. Hoax or What
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
enum { L, R };
enum { Red, Black };
#define color(x) ((x)->c)
#define flip(x) ((x)->c ^= 1)
#define which(x) ((x)->p->son[L]==x?L:R)
typedef long long i64;

int dig[256];
int getnum() {
	int n = 0,ch;
	for(;(ch = getchar()) != EOF && !dig[ch];);
	for ( n = ch-'0'; (ch = getchar()) != EOF && dig[ch]; n = 10*n+(ch-'0') );
	return n;
}

typedef struct cell {
	struct cell *son[2],*p;
	int val,freq;
	char c;
} cell;

cell *NIL;

cell *init( const int val ) {
	cell *x = (cell *)malloc(sizeof *x);
	x->c = Red, x->freq = 1, x->val = val, x->son[L] = x->son[R] = x->p = NIL;
	return x;
}

typedef struct {
	cell *root;
	size_t cnt;
} tree;

tree *rb_init() {
	tree *t = (tree *)malloc(sizeof *t);
	t->root = NIL, t->cnt = 0;
	return t;
}

void display( cell * x );

void rotate( tree *t, cell *x, int i ) {
	cell *y = x->son[i^1];
	assert( y != NIL );
	if ( (x->son[i^1] = y->son[i]) != NIL )
		y->son[i]->p = x;
	if ( (y->p = x->p) == NIL ) t->root = y;
	else x->p->son[which(x)] = y;
	y->son[i] = x, x->p = y;
}

void fixup( tree *t, cell *x ) {
	cell *y;
	int i;
	while ( x != t->root && color(x) == Black ) {
		assert( (y=x->p->son[(i=which(x))^1]) != NIL );
		if ( color(y) == Red ) {
			flip(x->p), flip(y), rotate(t,x->p,i);
			continue ;
		}
		if ( color(y->son[L]) == Black && color(y->son[R]) == Black ) {
			flip(y), x = x->p;
			continue ;
		}
		if ( color(y->son[i^1]) == Black ) {
			flip(y), flip(y->son[i]), rotate(t,y,i^1);
			continue ;
		}
		flip(y->son[i^1]), y->c = x->p->c, x->p->c = Black, rotate(t,x,i);
		break ;
	}
	x->c = Black;
}

void push( tree *t, int val ) {
	cell *x,*y,**hold,*g;
	int i;
	for ( x=*(hold=&t->root), y=x->p;; ) {
		if ( x == NIL ) {
			x = *hold = init(val), ++t->cnt, x->p = y;
			break ;
		}
		if ( x->val == val ) { ++x->freq, ++t->cnt; return ; }
		if ( x->val < val ) i = R; else i = L;
		hold = &x->son[i], y=x, x = x->son[i];
	}
	while ( x != t->root && color(x->p) == Red ) {
		assert( color(t->root) == Black );
		g = x->p->p, i = which(x->p), y = g->son[i^1];
		if ( color(y) == Red ) {
			flip(x->p), flip(y), flip(g), x = g;
			continue ;
		}
		if ( which(x) == i )
			flip(x->p), flip(g), rotate(t,g,i^1);
		else x = x->p, rotate(t,x,i);
	}
	t->root->c = Black;
}

cell *find( tree *t, int val ) {
	cell *x;
	for ( x = t->root; x != NIL && x->val != val; )
		if ( x->val < val ) x = x->son[R];
		else x = x->son[L];
	return x;
}

int erase( tree *t, int val ) {
	cell *z = find(t,val),*x,*y;
	if ( z == NIL ) return 0;
	if ( (--t->cnt,--z->freq) ) 
		return 1;
	if ( z->son[R] != NIL ) {
		for ( y = x = z->son[R]; y->son[L] != NIL; y = y->son[L] );
		z->val = y->val, z->freq = y->freq;
		z = y, x = z->son[R];
	}
	else x = z->son[L];
	if ( z == t->root )
		x->p = NIL, t->root = x;
	else if ( (z->p->son[which(z)] = x) != NIL )
		x->p = z->p;
	if ( color(z) == Black )
		fixup(t,x);
	return 1;
}

int get_extr( const tree *t, const int i ) {
	cell *x = t->root;
	assert( x != NIL );
	for ( ;x->son[i] != NIL; x = x->son[i] );
	assert( x != NIL );
	return x->val;
}

void display( cell * x ) {
	if ( x == NIL ) return ;
	display(x->son[L] );
	if ( x->c == Red )
		printf("\033[1;31m %d (%d) \033[0m",x->val,x->freq);
	else printf("%d (%d) ",x->val,x->freq);
	display(x->son[R]);
}

int main() {
	int i,j,k,n;
	i64 ans;
	tree *t;
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	NIL=init(0),NIL->p=NIL->son[L]=NIL->son[R]=NIL,NIL->c=Black;
	for ( i = '0'; i <= '9'; dig[i++] = 1 );
	for (;(n = getnum()); printf("%lld\n",ans) ) {
		for ( t = rb_init(), ans = 0, i = 0; i < n; ++i ) {
			for ( k = getnum(); k--; push(t,getnum()) );
			j = get_extr(t,L), k = get_extr(t,R), ans += (k-j);
			assert( erase(t,j) ); 
			assert( erase(t,k) );
		}
	}
	return 0;
}

