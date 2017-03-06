/*
 * 10765. Doves and Bombs
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
#define N (1 << 14)
#define M (1 << 20)
enum { WHITE, GREY, BLACK };

int min(int x,int y){return x<y?x:y;}
int max(int x,int y){return x>y?x:y;}

typedef struct {
	int x,cnt;
} cell;
cell c[N];
int n,m,last[N],next[M],to[M],E,h[N],p[N],d[N],processed,
	in[N],out[N],tick,seen[N],yes,pn[N];
char color[N];

void add_arcs( int x, int y ) {
	int i = E++, j = E++;
	to[i] = y, next[i] = last[x], last[x] = i;
	to[j] = x, next[j] = last[y], last[y] = j;
}

void dfs( int x, int depth ) {
	int y,i;

	assert( seen[x] != yes );
	in[x] = ++tick, seen[x] = yes;
	color[x]=GREY,d[x]=h[x]=depth,pn[x]=1,++processed;

	/*printf("Vertex %d with depth %d\n",x,depth);*/
	
	for ( i = last[x]; i >= 0; i = next[i] ) {
		if ( seen[y = to[i]] != yes ) {
			p[y] = x, dfs(y,depth+1);
			if ( h[y] >= d[x] ) {
				++pn[x];
			}
			h[x] = min(h[x],h[y]);
		}
		else {
			if ( p[x] == y )
				continue ;
			if ( color[y] == GREY )
				h[x] = min(h[x],d[y]);
			else {
				assert( color[y] == BLACK );
				assert( in[x] <= in[y] );
				/*h[x] = min(h[x],h[y]);*/
			}
		}
	}
	/*printf("h[%d] = %d\n",x,h[x]);*/
	out[x] = ++tick, color[x] = BLACK;
}

int cmp( const void *a, const void *b ) {
	cell *A = (cell *)a,
		 *B = (cell *)b;
	if ( A->cnt == B->cnt ) 
		return A->x-B->x;
	return A->cnt > B->cnt ? -1 : 1;
}

int main() {
	int i,j,k,l,t;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for(;2==scanf("%d %d",&n,&m)&&(n||m);putchar('\n')) {
		for(i=0;i<n;last[i++]=-1);
		for(E=0;2==scanf("%d %d",&i,&j)&&!(i==-1&&j==-1);add_arcs(i,j));
		processed = 0, tick = 0, ++yes, p[0] = -1, dfs(0,0);
		assert( processed == n );
		for ( i = 0; i < n; ++i )
			c[i].x = i, c[i].cnt = pn[i];
		--c[0].cnt;
		qsort(c,n,sizeof *c,cmp);
		for ( i = 0; i < m; ++i )
			printf("%d %d\n",c[i].x,c[i].cnt);
	}
	return 0;
}

