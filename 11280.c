/*
 * 11280. Flying to Fredericton
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
#define N 0x80
#define M (1 << 16)
#define oo 0xfffffffful
#define Q (1 << (SH+SH))
#define SH 7
#define MASK(k) ((1UL << (k))-1UL)
#define enc(x,t) ((x)|((t)<<SH))
#define xchg(x,y) (((x)==(y))||((x)^=(y),(y)^=(x),(x)^=(y)))
#define bubble (xchg(pos[heap[i]],pos[heap[j]]),xchg(heap[i],heap[j]))

int n,E,cost[M],cnt,pos[Q],cs,ts,m;
short next[M],last[N];
unsigned char to[M];
unsigned int d[Q],heap[4*Q];

void add_arc( int x, int y, int c ) {
	int i = E++;
	to[i]=y,cost[i]=c,next[i]=last[x],last[x]=i;
}

typedef struct cell {
	struct cell *sib,*son;
	unsigned char idx;
	char ch;
} cell;

cell *root;

cell *init( char ch ) {
	cell *x = (cell *)malloc(sizeof *x);
	x->sib = x->son = NULL, x->idx = 0xffull;
	x->ch = ch;
	return x;
}

void push( cell *root, char *s, int idx ) {
	cell *x,*y;
	for ( x = root; *s; x = y, ++s ) {
		for ( y = x->son; y && y->ch != *s; y = y->sib );
		if ( !y )
			y = init(*s), y->sib = x->son, x->son = y;
	}
	x->idx = idx;
}

int find( cell *root, char *s ) {
	cell *x,*y;
	for ( x = root; *s; x = y, ++s ) {
		for ( y = x->son; y && y->ch != *s; y = y->sib );
		if ( !y )
			return 0xff;
	}
	return x->idx;
}

void heap_push( unsigned int u ) {
	int i,j;
	if ( pos[u] < 0 )
		pos[heap[cnt] = u] = cnt, ++cnt;
	for ( j = pos[u]; j && d[heap[i=(j-1)>>1]] > d[heap[j]]; bubble, j = i );
}

unsigned int 
pop() {
	int i,j;
	unsigned int u = *heap;
	pos[*heap] = -1;
	if ( --cnt )
		pos[*heap = heap[cnt]] = 0;
	for ( j = 0; (i = j, j <<= 1, ++j) <= cnt-1; bubble ) {
		if ( j < cnt-1 && d[heap[j]] < d[heap[j+1]] ) ++j;
		if ( d[heap[i]] <= d[heap[j]] ) break ;
	}
	return u;
}

int main() {
	int i,j,k,l,t,x,y;
	char s[0x400],a[0x400],b[0x400];
	unsigned int u,v,w;
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	for ( scanf("%d",&ts); ts--; ) {
		for ( root = init('\0'), scanf("%d",&n), i = 0; i < n; ++i )
			scanf("%s",s), push(root,s,i);
		for ( i = 0; i < n; ++i ) last[i] = -1;
		for ( E = 0, scanf("%d",&m), k = 0; k < m; ++k ) {
			scanf("%s %s %d",a,b,&t);
			i = find(root,a), j = find(root,b);
			if ( i == 0xff || j == 0xff ) 
				continue ;
			add_arc(i,j,t);
		}
		/*assert( E == m );*/
		for ( i = 0; i < n; ++i )
			for ( l = 0; l <= n+1; ++l )
				d[enc(i,l)] = +oo, pos[enc(i,l)] = -1;
		for ( cnt = 0, i = last[0]; i >= 0; i = next[i] ) 
			if ( d[v=enc(to[i],0)] > cost[i] )
				d[v] = cost[i], heap_push(v);
		for(;cnt;)
			for (u=pop(),i = last[x = u&127],l=(u>>7); i >= 0 && l <= n; i = next[i] ) 
				if ( d[v=enc((y=to[i]),l+1)] > d[u]+cost[i] )
					d[v]=d[u]+cost[i], heap_push(v);
		printf("Scenario #%d\n",++cs);
		for(scanf("%d",&l);l--&&1==scanf("%d",&k);){
			if ( k < 0 ) k = 0;
			if ( k > n ) k = n;
			for ( w = +oo, i = 0; i <= k; ++i )
				if ( w > d[u = enc(n-1,i)] )
					w = d[u];
			if ( w < +oo )
				printf("Total cost of flight(s) is $%u\n",w);
			else puts("No satisfactory flights");
		}
		if ( ts ) putchar('\n');
	}
	return 0;
}

