/*
 * 11833. Route Change
 * TOPIC: weighted graphs, sssp, dijkstra
 * status: Accepted
 */
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define N 0x200
#define oo (1<<29)
#define xchg(x,y) (((x)==(y))||((x)^=(y),(y)^=(x),(x)^=(y)))
#define bubble (xchg(heap[i],heap[j]),xchg(pos[heap[i]],pos[heap[j]]))
#define Q (1<<21)

int n,m,srv,kk,g[N][N],heap[Q],pos[N],cnt,d[N];

void push( int x ) {
	int i,j;
	if ( pos[x] < 0 ) pos[heap[cnt] = x]=cnt, ++cnt;
	for ( j = pos[x]; j && d[heap[i=(j-1)>>1]] > d[heap[j]]; bubble, j = i );
}

int pop() {
	int x = *heap,i,j;
	if ( pos[x]=-1,--cnt )
		pos[heap[0]=heap[cnt]]=0;
	for ( j = 0; (i=j,j<<=1,++j)<cnt; bubble ) {
		if ( j < cnt-1 && d[heap[j]] > d[heap[j+1]] ) ++j;
		if ( d[heap[i]] <= d[heap[j]] ) break ;
	}
	return x;
}

int dijk( int src ) {
	int x,y,i,j,k;
	for ( cnt = 0, x = 0; x < n; d[x]=+oo, pos[x++]=-1 );
	for ( d[src] = 0, push(src); cnt; ) {
		if ( (x=pop())==srv-1 ) continue ;
		if ( x < srv ) {
			assert( g[x][x+1] < +oo );
			if ( d[y=x+1] > d[x]+g[x][y] )
				d[y] = d[x]+g[x][y], push(y);
		}
		else {
			for ( y = 0;  y < n; ++y )
				if ( g[x][y] < +oo && d[y] > d[x]+g[x][y] )
					d[y] = d[x]+g[x][y], push(y);
		}
	}
	return d[srv-1];
}

int main() {
	int i,j,k,l;
	for(;4==scanf("%d %d %d %d",&n,&m,&srv,&kk);) {
		if ( !n && !m && !srv && !kk ) break ;
		for ( i = 0; i < n; ++i )
			for ( j = 0; j < n; ++j )
				g[j][i] = g[i][j] = +oo;
		for ( l = 0; l < m; ++l ) 
			scanf("%d %d %d",&i,&j,&k), g[j][i] = g[i][j] = k;
		printf("%d\n",dijk(kk));
	}
	return 0;
}

