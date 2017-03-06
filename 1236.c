/*
 * 1236. Disjoint Paths
 * TOPIC: mincost maxflow
 * status:
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 0x80
#define MAXE (1<<20)
#define xchg(x,y) (((x)==(y))||((x)^=(y),(y)^=(x),(x)^=(y)))
#define bubble (xchg(heap[i],heap[j]),xchg(pos[heap[i]],pos[heap[j]]))
#define VIN(x) ((x))
#define VOUT(x) ((x)+n)
#define oo (1<<29)
typedef long long int i64;

int from[MAXE],to[MAXE],next[MAXE],cost[MAXE],last[N],cap[MAXE],flow[MAXE],p[N],
	cnt,heap[N<<1],pos[N],
	d[N],pi[N],n,K,V,src,sink,E;

void push( int x ) {
	int i,j;
	if ( pos[x]<0 ) pos[heap[cnt]=x]=cnt,++cnt;
	for ( j=pos[x]; j && d[heap[i=(j-1)>>1]]>d[heap[j]]; bubble, j=i );
}

int pop() {
	int i,j,x = *heap;
	if ( (pos[x]=-1,--cnt) )
		pos[heap[0]=heap[cnt]]=0;
	for ( j = 0; (i=j,j<<=1,++j)<cnt; bubble ) {
		if ( j<cnt-1 && d[heap[j]]>d[heap[j+1]] ) ++j;
		if ( d[heap[i]]<=d[heap[j]] ) break ;
	}
	return x;
}

void add_arcs( int x, int y, int c, int w ) {
	int i = E++, j = E++;
	to[i] = y, cost[i] =  w, next[i] = last[x], last[x] = i, flow[i] = 0, from[i] = x, cap[i] = c;
	to[j] = x, cost[j] = -w, next[j] = last[y], last[y] = j, flow[j] = 0, from[j] = y, cap[j] = 0;
}

int dijkstra() {
	int i,j,k,x,y;
	for ( cnt = 0, x = 0; x < V ; ++x )
		pos[x] = -1, d[x] = +oo;
	for ( d[src] = 0, push(src); cnt; ) 
		for ( i=last[x=pop()]; i >= 0 && (y=to[i])>=0; i=next[i] ) 
			if ( flow[i] < cap[i] && d[y] > pi[x]+d[x]+cost[i]-pi[y] ) 
				p[y]=i,d[y]=cost[i]+d[x]+pi[x]-pi[y],push(y);
	for(x=0;x<V;++x)
		if ( d[x]<+oo )
			pi[x] += d[x];
	return d[sink] < +oo;
}

i64 mcmf() {
	int x,y,i,j,k = 0;
	i64 w = 0;
	for (;dijkstra() && k < K;) {
		for ( x = sink; x != src; i = p[x], ++flow[i], --flow[i^1], x = from[i] );
		if ( (++k) == K ) break ;
	}
	for ( i = 0; i < E; ++i )
		w += cost[i]*flow[i];
	return -w/2;
}

int main() {
	int i,j,k,l,ts;
	for ( scanf("%d",&ts); ts--; printf("%lld\n",mcmf()) ) {
		scanf("%d %d",&n,&K), src = 0, V = 2*n+2, sink = V-1, E = 0;
		for ( i = 0; i < V; ++i ) last[i] = -1, pi[i] = 0;
		for ( k = 0; k < n-1; ++k ) 
			scanf("%d %d %d",&i,&j,&l), add_arcs(VOUT(i),VIN(j),1,-l), add_arcs(VOUT(j),VIN(i),1,-l);
		for ( i = 1; i <= n; ++i ) 
			add_arcs(src,VIN(i),1,0), add_arcs(VOUT(i),sink,1,0), add_arcs(VIN(i),VOUT(i),1,0);
	}
	return 0;
}


