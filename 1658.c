/*
 * 1658. Admiral
 * TOPIC: maxflow
 * status: Accepted
 */
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define MAXV (2*0x400)
#define MAXE (1<<21)
#define xchg(x,y) (((x)==(y))||((x)^=(y),(y)^=(x),(x)^=(y)))
#define bubble (xchg(pos[heap[i]],pos[heap[j]]),xchg(heap[i],heap[j]))
#define oo (1LL<<43)
typedef long long i64;

int m,n,V,E,to[MAXE],next[MAXE],cap[MAXE],last[MAXV],flow[MAXE],cap[MAXE],src,sink,heap[MAXV<<1],cnt,pos[MAXV],p[MAXV];
i64 cost[MAXE],pi[MAXV],d[MAXV];

void add_arcs( int x, int y, int c, i64 w ) {
	int i = E++, j = E++;
	to[i] = y, next[i] = last[x], last[x] = i, cap[i] = c, cost[i] =  w;
	to[j] = x, next[j] = last[y], last[y] = j, cap[j] = 0, cost[j] = -w;
	flow[i] = flow[j] = 0;
}

int pop() {
	int i,j,x = *heap;
	if ( cnt += (pos[x]=-1) )
		pos[*heap = heap[cnt]] = 0;
	for ( j = 0; (i=j,j<<1,++j)<cnt; bubble ) {
		if ( j < cnt-1 && d[heap[j]] > d[heap[j+1]] ) ++j;
		if ( d[heap[i]] <= d[heap[j]] ) break ;
	}
	return x;
}

void push( int x ) {
	int i,j;
	if ( pos[x]<0 )
		pos[heap[cnt]=x]=cnt, ++cnt;
	for ( j=pos[x]; j && d[heap[i=(j-1)>>1]]>d[heap[j]]; bubble, j = i );
}

int dijsktra() {
	int x,y,i;
	for ( cnt = 0, x = 0; x < V; d[x] = +oo, pos[x++] = -1 );
	for ( d[src] = 0, push(src); cnt; )
		for ( i=last[x=pop()]; i >= 0; i = next[i] )
			if ( flow[i] < cap[i] && d[y=to[i]] > d[x]+pi[x]-pi[y]+cost[i] )
				d[y] = d[x]+cost[p[y]=i]+pi[x]-pi[y], push(y);
	for ( x = 0; x < V; ++x )
		if ( d[x] < +oo )
			pi[x] += d[x];
	return d[sink] < +oo;
}

int main() {
	int i,j,k,x;
	i64 w;
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	for ( ;2 == scanf("%d %d",&n,&m); printf("%lld\n",w/2) ) {
		for ( V = 2*n, E = 0, src = 0, sink = n+n-1, i = 0; i < V; pi[i] = 0, last[i++] = -1 );
		for ( ;m-- && 3 == scanf("%d %d %d",&i,&j,&k); --i, --j, add_arcs(i+n,j,1,k) );
		for ( i = 1; i < n-1; ++i ) add_arcs(i,i+n,1,0);
		add_arcs(0,0+n,2,0), add_arcs(n-1,n-1+n,2,0);
		for ( i = 0; i < 2; ++i ) {
			assert( dijsktra() );
			for ( ++flow[p[sink]],--flow[p[sink]^1],x=to[p[sink]^1]; x != src; ++flow[p[x]],--flow[p[x]^1],x=to[p[x]^1] );
		}
		for ( w = 0, i = 0; i < E; w += flow[i]*cost[i], ++i );
	}
	return 0;
}

