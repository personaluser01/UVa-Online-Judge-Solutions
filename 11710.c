/*
 * 11710. Expensive Subway
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <limits.h>
#include <float.h>
#define N 0x200
#define M (1 << 21)
#define xchg(x,y) (((x)==(y))||((x)^=(y),(y)^=(x),(x)^=(y)))
#define bubble (xchg(pos[heap[i]],pos[heap[j]]),xchg(heap[i],heap[j]))
#define oo (1<<29)

typedef long long i64;

typedef struct cell{struct cell*son,*sib;char ch;int idx;}cell;
int n,V,to[M],next[M],last[N],cost[M],E,p[N],d[N],heap[2*N],pos[N],cnt,yes,seen[N],mm,m;
i64 weight;

void heap_push( int x ) {
	int i,j;
	if ( pos[x] < 0 )
		pos[heap[cnt] = x] = cnt, ++cnt;
	for ( j = pos[x]; j && d[heap[i=(j-1)>>1]] > d[heap[j]]; bubble, j = i );
}

int pop() {
	int i,j,r = *heap;
	pos[r]=-1;
	if ( --cnt )
		pos[heap[0] = heap[cnt]] = 0;
	for ( j = 0; (i=j,j<<=1,++j) < cnt; bubble ) {
		if ( j < cnt-1 && d[heap[j+1]] < d[heap[j]] ) ++j;
		if ( d[heap[i]] <= d[heap[j]] ) break ;
	}
	return r;
}

cell *init( char ch ) {
	cell *x = (cell *)malloc(sizeof *x);
	x->son = x->sib = NULL;
	x->ch = ch, x->idx = -1;
	return x;
}

void upd( int x ) {
	if ( seen[x] == yes ) return ;
	seen[x] = yes, weight += d[x], ++mm;
}

int push(cell*root,char*s){
	cell *x,*y;
	for ( x = root; *s; x = y, ++s ) {
		for ( y = x->son; y && *s != y->ch; y = y->sib );
		if ( !y )
			y = init(*s), y->sib = x->son, x->son = y;
	}
	if ( x->idx == -1 )
		x->idx = V++;
	return x->idx;
}


cell *root;

void add_arcs( int x, int y, int c ) {
	int i = E++, j = E++;
	to[i] = y, next[i] = last[x], last[x] = i, cost[i] = c;
	to[j] = x, next[j] = last[y], last[y] = j, cost[j] = c;
}

void cleanup( cell *x ) {
	if ( !x ) return ;
	cleanup(x->son), cleanup(x->sib), free(x);
}

int main() {
	int i,j,k,l,x,y;
	char s[0x400],t[0x400];
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	while ( 2 == scanf("%d %d\n",&n,&m) ) {
		if ( !n && !m ) break ;
		root = init('\0');
		for ( V = E = 0, i = 1; i <= n; ++i )
			scanf("%s",s),j=push(root,s),pos[j]=last[j]=-1;
		for ( k = 0; k < m; ++k ) {
			scanf("%s %s %d",s,t,&l);
			i = push(root,s), j = push(root,t);
			add_arcs(i,j,l);
		}
		scanf("%s",s), y = push(root,s);
		for ( cnt = 0, x = 0; x < V; ++x ) p[x] = -1, d[x] = +oo;
		for ( weight = 0, ++yes, d[y] = 0, heap_push(y), mm = 0; mm < n && cnt; )
			for ( upd(x = pop()), i = last[x]; i >= 0; i = next[i] )
				if ( d[y = to[i]] > cost[i] )
					p[y]=x,d[y]=cost[i],heap_push(y);
		if ( mm < n ) puts("Impossible");
		else printf("%lld\n",weight);
		cleanup(root);
	}
	return 0;
}
