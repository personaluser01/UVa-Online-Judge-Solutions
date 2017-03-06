/*
 * 12338. Anti-Rhyme Pairs
 * TOPIC: lca, trie, clear-cut
 * status: Accepted
 */
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N (1<<17)
#define K (20)
#define BIT(k) (1ULL<<(k))
#define L(k) ((k)&((~(k))+1ULL))
#define get_id(x) ((x)-pool)
#define A 26
#define Q (1<<21)

typedef struct cell {
	struct cell *son[A];
	unsigned int u;
	int depth;
} cell;

cell pool[Q],*ptr,*q[Q],**head,**tail;
char which[1<<20],s[N];
int n,anc[N][K],v[N],V,d[Q];

int who( unsigned int u ) {
	if ( u < (1<<20) )
		return which[u];
	return 20+which[u>>20];
}

cell *init() {
	cell *x = ptr++;
	x->u = 0;
	return x;
}

int push( cell *root, char *s ) {
	cell *x;
	for ( x = root; *s; x = x->son[*s++-'a'] ) 
		if ( !((x->u>>(*s-'a'))&1) )
			x->son[*s-'a']=init(),x->u|=BIT(*s-'a');
	return get_id(x);
}

int up( int x, int k ) {
	int i = 0;
	for (;k;k>>=1,++i)
		if (k&1) x = anc[x][i];
	return x;
}

int lca( int x, int y ) {
	int k;
	if ( d[y] > d[x] )
		return lca(y,x);
	if ( d[x] > d[y] )
		return lca(up(x,d[x]-d[y]),y);
	assert( d[x] == d[y] );
	if ( x == y ) return x;
	assert( anc[x][K-1] == anc[y][K-1] );
	for ( k = K-1; k--; ) {
		if ( anc[x][k] != anc[y][k] )
			x = anc[x][k], y = anc[y][k];
		assert( anc[x][k+1] == anc[y][k+1] );
	}
	return anc[x][0];
}

int main() {
	int i,j,k,ts,cs = 0,qr;
	cell *x,*y,*root;
	unsigned int u;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( i = 0; i < 20; which[BIT(i)] = i, ++i );
	for ( scanf("%d",&ts); ts-- && 1 == scanf("%d",&n); ) {
		printf("Case %d:\n",++cs), ptr = pool, root = init();
		for ( i = 0; i < n; ++i )
			scanf("%s",s), v[i] = push(root,s);
		for ( head = tail = q, V = ptr-pool, i = 0; i < V; ++i )
			for ( k = 0; k < K; ++k )
				anc[i][k] = -1;
		for ( *tail++=root; head<tail; )
			for ( x=*head++, u=x->u; u&&(i=who(L(u)))>=0; u&=~L(u) )
				for(*tail++=(y=x->son[i]),d[get_id(y)]=d[get_id(x)]+1,anc[get_id(y)][0]=get_id(x),k=1;\
					(1<<k)<=d[get_id(y)];anc[get_id(y)][k]=anc[anc[get_id(y)][k-1]][k-1],++k);
		for ( scanf("%d",&qr); qr-- && 2 == scanf("%d %d",&i,&j); printf("%d\n",d[lca(v[i-1],v[j-1])]) );
	}
	return 0;
}

