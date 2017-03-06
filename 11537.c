/*
 * 11537. Secret Problemsetters' Union
 * TOPIC: data structures, red-black trees, order statistics
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef  long long i64;
#define  flip(x)  ((x)->c^=1)
#define  color(x) ((x)->c)
#define  which(x) ((x)->p->son[L]==(x)?L:R)
#define  set_color(x,k) ((x)->c=(k))
enum { L, R };
enum { Red, Black };
#define N 0x40
#define oo (1<<29)
#define MOD 100007
#define DBG(x) (1)

typedef struct cell {
	struct cell *son[2],*p;
	int val,freq,card;
	char c;
} cell;

typedef struct {
	cell *root,*NIL;
	size_t cnt;
} tree;

cell *NIL;

tree *init_tree() {
	tree *t = (tree *)malloc(sizeof *t);
	t->NIL=(cell *)malloc(sizeof *(t->NIL));
	t->NIL->p=t->NIL->son[L]=t->NIL->son[R]=t->NIL,set_color(t->NIL,Black),t->NIL->card=t->NIL->freq=0;
	t->root=t->NIL,t->cnt=0;
	return t;
}

void rotate( tree *t, cell *x, const int i ) {
	cell *y;
	assert( (y=x->son[i^1])!=t->NIL );
	if ( (x->son[i^1]=y->son[i])!=t->NIL )
		x->son[i^1]->p=x;
	(y->p=x->p)==t->NIL?(t->root=y):(x->p->son[which(x)]=y);
	y->son[i]=x,x->p=y;
	for(y=x;y!=t->NIL;y->card=y->son[L]->card+y->son[R]->card+y->freq,y=y->p);
}

void push( tree *t, const int val, const int cn, const int trid ) {
	cell *x,*y,*g,**hold,*z;
	int i;

	DBG(puts("entering push()"));
	for ( y=t->NIL,hold=&t->root,x=t->root;; ) {
		if ( x==t->NIL ) {
			*hold=x=(cell *)malloc(sizeof *x),set_color(x,Red);
			x->son[L]=x->son[R]=t->NIL;
			x->val=val,x->freq=cn,x->p=y,t->cnt+=cn;
			for(z=x;z!=t->NIL;z->card=z->son[L]->card+z->son[R]->card+z->freq,z=z->p);
			break ;
		}
		if ( x->val == val ) {
			t->cnt+=cn,x->freq+=cn;
			for(y=x;y!=t->NIL;y->card=y->son[L]->card+y->son[R]->card+y->freq,y=y->p);
			return ;
		}
		if ( x->val < val ) i = R; else i = L;
		y = *hold, hold = &x->son[i], x = x->son[i];
	}
	DBG(puts("inside push(): before fixup"));
	while ( x != t->root && color(x->p) == Red ) {
		assert( x != NIL && color(x) == Red );
		g = x->p->p, i = which(x->p), y = g->son[i^1];
		if ( color(y) == Red ) {
			flip(x->p), flip(y), flip(g), x = g;
			continue ;
		}
		if ( which(x)==(i^1) )
			x=x->p,rotate(t,x,i);
		flip(g),flip(x->p),rotate(t,g,i^1);
	}
	set_color(t->root,Black);
	/* printf("Added %d into tree %d\n",MOD-1-val,trid);*/
	DBG(puts("out of push()"));
}

cell *find( tree *t, const int val ) {
	cell *x;
	for ( x = t->root; x != t->NIL; ) {
		if ( x->val==val ) return x;
		if ( x->val<val ) x=x->son[R]; else x=x->son[L];
	}
	return NULL;
}

void fixup( tree *t, cell *x ) {
	cell *y,*w;
	int i;
	while ( x != t->root && color(x) == Black ) {
		i = which(x), y = x->p->son[i^1];
		if ( color(y) == Red ) {
			flip(x->p), flip(y), rotate(t,x->p,i);
			continue ;
		}
		if ( color(y->son[i]) == Black && color(y->son[i^1]) == Black ) {
			flip(y), x = x->p;
			continue ;
		}
		if ( color(y->son[i]) == Red   && color(y->son[i^1]) == Black ) {
			flip(y), flip(y->son[i]), rotate(t,y,i^1);
			continue ;
		}
		assert ( color(y->son[i^1]) == Red );
		flip(y->son[i^1]), set_color(y,color(x->p)), set_color(x->p,Black), rotate(t,x->p,i);
		x = t->root;
	}
	set_color(x,Black);
}

void erase( tree *t, const int val ) {
	cell *x,*y,*z;
	int i;

	if ( !(z = find(t,val)) ) { DBG(printf("val %d was not found\n",val)); return ; }
	if ( (--z->freq) >= 1 ) {
		for(--t->cnt;z!=t->NIL;z->card=z->son[L]->card+z->son[R]->card+z->freq,z=z->p);
		return ;
	}
	if ( (y=z->son[L]==t->NIL||z->son[R]==t->NIL?z:z->son[R]) != z ) {
		for(;y->son[L]!=t->NIL;y=y->son[L]);
		z->val=y->val,z->freq=y->freq;
	}
	x=(y->son[L]!=t->NIL?y->son[L]:y->son[R]);
	(x->p=y->p)==t->NIL?(t->root=x):(y->p->son[which(y)]=x);
	for(z=x;z!=t->NIL;z->card=z->son[L]->card+z->son[R]->card+z->freq,z=z->p);
	if ( color(y)==Black )
		fixup(t,x);
}

int order_statistic( const tree *t, cell *x, int k ) {
	cell *y,*z;
	assert( x!=t->NIL );
	assert( x->card>=k );
	assert( k>=0 && k<t->cnt );
	if ( x->son[L]->card>k )
		return order_statistic(t,x->son[L],k);
	if ( k >= x->son[L]->card && k < x->son[L]->card+x->freq )
		return x->val;
	return order_statistic(t,x->son[R],k-x->son[L]->card-x->freq);
}

int ts,m;
tree *T[N],*M;

void traverse( const tree *t, cell *x, tree *d ) {
	if ( !t||!x ) return ;
	if ( x == t->NIL ) return ;
	traverse(t,x->son[L],d),traverse(t,x->son[R],d);
	push(d,x->val,x->freq,m);
}

int main() {
	int i,j,k,l,t,id,high,low,merged;
	i64 xx,a0,a;
	char tmp[0x400];
#ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
#endif
	for ( scanf("%d",&ts); ts--; ) {
		M = init_tree(), scanf("%d",&m), merged = 0;
		for ( i = 0; i <= m; T[i++] = init_tree() );
		for (;1==scanf("%s",tmp) && 0[tmp]!='Q';) {
			switch ( 0[tmp] ) {
				case 'I': assert( 4 == scanf("%d %d %lld %lld",&id,&k,&a0,&xx) ); 
						  DBG(puts("[-] insert"));
						  if ( merged ) id = m; else --id;
						  for ( i = 1, a = ((a0+1*xx)%MOD); i <= k; a = (a+(++i)*xx)%MOD )
								 push(T[id],MOD-a-1,1,id+1);
						  DBG(puts("[+] insert"));
						  break ;
				case 'U': assert( 2 == scanf("%d %d",&id,&k) );
						  DBG(puts("[-] use & remove"));
						  high = -(low = +oo);
						  if ( merged ) id = m; else --id;
						  for ( i = 0; i < k; ++i ) {
								j = order_statistic(T[id],T[id]->root,0),erase(T[id],j);
								if ( j > high ) high = j;
								if ( j < low ) low = j;
						  }
						  if ( low < +oo ) printf("%d %d\n",MOD-low-1,MOD-high-1);
						  else puts("0 0");
						  DBG(puts("[+] use & remove"));
						  break ;
				case 'M': /* assert( !merged ); */
						  for(merged=1,i=0;i<m;traverse(T[i],T[i]->root,T[m]),++i);
						  break ;
				default: assert( 0 );
			}
		}
		if ( ts ) putchar('\n');
	}
    return 0;
}

