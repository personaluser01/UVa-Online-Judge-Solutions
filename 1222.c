/*
 * 1222. Bribing FIPA
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 0x100
#define oo 0xfffffffful
#define M (1 << 20)

typedef struct cell {
	struct cell *son,*sib;
	char ch;
	int idx;
} cell ;

cell *init( char ch ) {
	cell *x = (cell *)malloc(sizeof *x);
	x->idx = -1, x->ch = ch;
	x->son = x->sib = NULL;
	return x;
}

int V;

int push( cell *root, char *s ) {
	cell *x,*y;
	for ( x = root; *s; x = y, ++s ) {
		for ( y = x->son; y && y->ch != *s; y = y->sib );
		if ( !y )
			y = init(*s), y->sib = x->son, x->son = y;
	}
	return x->idx=(x->idx==-1?V++:x->idx);
}

char buff[0x400],*ptr,a[0x400];
int m,n,cnt[N],next[M],last[N],to[M],E,out[N],in[N],g[N][N],indeed,
	*qtr,e[N],lst[N],position[N],border[N];
unsigned int z[N],d[N][N],w;
cell *root;

void add_arc( int x, int y ) {
	int i = E++;
	to[i] = y, next[i] = last[x], last[x] = i, ++out[x], ++in[y];
}

void dfs( int x ) {
	int i;
	for ( position[x] = qtr-lst, i = last[*qtr++ = x]; i >= 0; dfs(to[i]), i = next[i] );
	border[x] = qtr-lst;
}

unsigned int calc_z( int x ) {
	int i;
	if ( z[x] < +oo )
		return z[x];
	for ( z[x] = 1, i = last[x]; i >= 0; i = next[i] )
		z[x] += calc_z(to[i]);
	return z[x];
}

int main() {
	int i,j,k,t,x,y;
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	while ( gets(buff) && 2 == sscanf(buff,"%d %d",&n,&m) ) {
		root = init('\0'), ++indeed;
		for ( V = E = 0, i = 0; i < n; ++i ) in[i] = out[i] = 0, last[i] = -1;
		for ( i = 0; i < n; ++i ) {
			sscanf(ptr = gets(buff),"%s%d%n",a,&t,&k), cnt[x = push(root,a)] = t;
			for (;1 == sscanf(ptr+k,"%s%n",a,&j);k+=j)
				y=push(root,a),add_arc(x,y), g[x][y] = indeed;
		}
		memset(z,0xffull,sizeof(z));
		for ( qtr = lst, i = 0; i < V; ++i )
			if ( !in[i] )
				dfs(i);
		assert( qtr-lst == V );
		memset(d,0xfful,sizeof(d));
		for ( *qtr = -1, d[V][0] = 0, i = V-1; i >= 0; --i )
			for ( j = border[x = lst[i]], k = 0; k <= n; ++k ) {
				d[i][k]=d[i+1][k];
				if ( k >= calc_z(x) && d[j][k-z[x]] < +oo )
					if ( d[i][k] > d[j][k-z[x]]+cnt[x] )
						d[i][k] = d[j][k-z[x]]+cnt[x];
			}
		for ( w = +oo, k = m; k <= n; ++k )
			if (d[0][k]<+oo&&w>d[0][k])
				w = d[0][k];
		printf("%u\n",w);
	}
	return 0;
}

