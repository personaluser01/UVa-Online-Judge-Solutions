/*
 * 11136. Hoax or what
 * status: Accepted
 * TOPIC: red-black trees, balanced binary search trees, bst, ordered statistics
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N (1 << 21)
#define oo (1 << 29)
typedef long long i64;
enum { L, R };
enum { Red, Black };
#define flip(x) ((x)->c^=1)
#define color(x) ((x)->c)
#define which(x) ((x)->p->son[L]==(x)?L:R)
typedef long long i64;

int n,dig[256];

int getnum() {
    int n = 0,ch;
    for (;(ch=getchar()) != EOF && !dig[ch];);
    assert( ch != EOF );
    for ( n = ch-'0'; (ch = getchar()) != EOF && dig[ch]; n = 10*n+(ch-'0') );
    return n;
}

typedef struct cell {
    struct cell *son[2],*p;
    char c;
    int val,freq;
} cell ;

cell *NIL;

cell *init( int val ) {
    cell *x=(cell *)malloc(sizeof *x);
    x->c=Red,x->val=val,x->p=x->son[L]=x->son[R]=NIL,x->freq=1;
    return x;
}

typedef struct {
    cell *root;
    size_t cnt;
} tree;

tree *rb_init() {
    tree *t=(tree *)malloc(sizeof *t);
    t->root=NIL,t->cnt=0;
    return t;
}

void rotate( tree *t, cell *x, const int i ) {
    cell *y;
    assert( (y=x->son[i^1])!=NIL );
    if ( (x->son[i^1] = y->son[i]) != NIL )
		 y->son[i]->p = x;
    if ( (y->p=x->p)==NIL ) t->root=y;
    else x->p->son[which(x)] = y;
    y->son[i] = x, x->p = y;
}

void fixup( tree *t, cell *x ) {
    cell *y;
    int i;
    while ( x != t->root && color(x) == Black ) {
        assert( (y=x->p->son[(i=which(x))^1]) != NIL );
        if ( color(y) == Red ) {
            flip(y), flip(x->p), rotate(t,x->p,i);
            continue ;
        }
        if ( color(y->son[L]) && color(y->son[R]) ) {
            x = x->p, flip(y);
            continue ;
        }
        if ( color(y->son[i^1]) ) {
            flip(y), flip(y->son[i]), rotate(t,y,i^1);
            continue ;
        }
        y->c=x->p->c,x->p->c=Black,flip(y->son[i^1]),rotate(t,x->p,i),x=t->root;
    }
    x->c = Black;
}

void push( tree *t, const int entry ) {
    cell *x,*y,**hold,*g;
    int i;
    for ( x=*(hold=&t->root),y=x->p;; ) {
        if ( x == NIL ) {
            x=*hold=init(entry),x->p=y,++t->cnt;
            break ;
        }
        if ( x->val == entry ) { ++x->freq,++t->cnt; return ; }
        if ( x->val < entry ) i = R; else i = L;
        y = *hold, hold = &x->son[i], x = x->son[i];
    }
    while ( x != t->root && color(x->p) == Red ) {
        g = x->p->p, i = which(x->p), y = g->son[i^1];
        if ( color(y) == Red ) {
            flip(x->p), flip(y), flip(g), x = g;
            continue ;
        }
        if ( which(x) != i ) {
            x = x->p, rotate(t,x,i);
            continue ;
        }
        flip(x->p), flip(g), rotate(t,g,i^1);
    }
    t->root->c = Black;
}

cell *find( const tree *t, const int val ) {
    cell *x;
    for ( x = t->root; x != NIL && x->val != val; )
        if ( x->val < val ) x = x->son[R];
        else x = x->son[L];
    return x;
}

int erase( tree *t, cell *z ) {
    cell *x,*y;

    if ( z == NIL ) return 0;
    if ( --t->cnt, --z->freq ) return 1;

	assert( !z->freq );
	if ( z->son[L] == NIL || z->son[R] == NIL )
		y = z;
	else y = z->son[R];
	if ( y == z->son[R] ) {
		for (;y->son[L] != NIL; y = y->son[L] );
		z->freq = y->freq, z->val = y->val;
	}
	if ( y->son[L] != NIL )
		x = y->son[L];
	else x = y->son[R];
	if ( (x->p = y->p) != NIL )
		y->p->son[which(y)] = x;
	else t->root = x;
	if ( color(y) == Black )
		fixup(t,x);
    
    return 1;

}

cell *get_extr( const tree *t, const int i ) {
    cell *x;
    for ( x = t->root; x->son[i] != NIL; x = x->son[i] );
    return x;
}

int main() {
    int i,j,k;
    tree *t;
    i64 ans;
    cell *x,*y;
#ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
#endif
    for ( i = '0'; i <= '9'; dig[i++] = 1 );
    for (;(n = getnum()); printf("%lld\n",ans) ) {
	    NIL=(cell *)malloc(sizeof *NIL);
    	NIL->p=NIL->son[L]=NIL->son[R]=NIL,NIL->c=Black;
        for ( ans = 0, t = rb_init(), i = 0; i < n; ++i ) {
            for ( k = getnum(); k--; push(t,getnum()) );
            x = get_extr(t,R);
			assert( erase(t,x) );
		   	y = get_extr(t,L);
			assert( erase(t,y) );
            ans += (x->val-y->val);
        }
	}
    return 0;
}

