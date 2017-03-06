/*
 * 12878. Flowery Trails
 * TOPIC: dijkstra
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define N (1<<16)
#define M (1<<21)
#define xchg(x,y) (((x)==(y))||((x)^=(y),(y)^=(x),(x)^=(y)))
#define oo (1<<29)
#define bubble (xchg(pos[heap[i]],pos[heap[j]]),xchg(heap[i],heap[j]))
typedef long long i64;

int d[2][N],last[N],cost[M],to[M],next[M],heap[2*N],cnt,pos[N],E,V,m,n;

void add_arcs( int x, int y, int len ) {
	int i = E++, j = E++;
	to[i]=y, cost[i]=len, next[i]=last[x], last[x]=i;
	to[j]=x, cost[j]=len, next[j]=last[y], last[y]=j;
}

void push( const int t, int x ) {
	int i,j;
	if ( pos[x] < 0 )
		pos[heap[cnt] = x] = cnt, ++cnt;
	for ( j = pos[x]; j && d[t][heap[i=(j-1)>>1]] > d[t][heap[j]]; bubble, j = i );
}

int pop( const int t ) {
	int i,j,x = *heap;
	if ( cnt += (pos[x]=-1) )
		pos[*heap=heap[cnt]]=0;
	for ( j = 0; (i=j,j<<=1,++j) < cnt; bubble ) {
		if ( j<cnt-1 && d[t][heap[j+1]]<d[t][heap[j]] ) ++j;
		if ( d[t][heap[i]] <= d[t][heap[j]] ) break ;
	}
	return x;
}

void dijkstra( const int t, int src, int dst ) {
	int x,y,i;
	for ( cnt = 0, x = 0; x < n; ++x ) d[t][x] = +oo, pos[x] = -1;
	for ( d[t][src]=0, push(t,src); cnt; )
		for ( i=last[x=pop(t)]; i>=0; i=next[i] )
			if ( d[t][y=to[i]]>d[t][x]+cost[i] )
				d[t][y]=d[t][x]+cost[i],push(t,y);
}

int main() {
	int i,j,k,l;
	i64 w = 0;
	while ( 2 == scanf("%d %d",&n,&m) ) {
		for ( i = 0; i < n; ++i ) last[i] = pos[i] = -1;
		for ( V = n, E = 0, l = 0; l < m; ++l ) 
			scanf("%d %d %d",&i,&j,&k), add_arcs(i,j,k);
		dijkstra(0,0,n-1), dijkstra(1,n-1,0);
		for ( w = 0, i = 0; i < E; i += 2 ) {
			if ( d[0][to[i]] < +oo && d[1][to[i^1]] < +oo && d[0][to[i]]+d[1][to[i^1]]+cost[i] == d[0][n-1] ||\
				 d[1][to[i]] < +oo && d[0][to[i^1]] < +oo && d[1][to[i]]+d[0][to[i^1]]+cost[i] == d[0][n-1] )
				w += cost[i];
		}
		printf("%lld\n",w*2);
	}
	return 0;
}

