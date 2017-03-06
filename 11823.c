/*
 * 11823. Two Longest Paths
 * TOPIC: mincost maxflow, vertex capacities
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define xchg(x,y) (((x)==(y))||((x)^=(y),(y)^=(x),(x)^=(y)))
#define bubble (xchg(pos[heap[i]],pos[heap[j]]),xchg(heap[i],heap[j]))
#define MAXN 0x400
#define N MAXN
#define MAXE (1<<14)
#define oo (1<<29)
#define IN(x) (2*(x)+1)
#define OUT(x) (2*(x)+2)
#define admissible(i) (pi[to[(i)^1]]-pi[to[i]]+cost[i] == 0)

int last[MAXN],to[MAXE],cost[MAXE],next[MAXE],m,n,cap[MAXE],flow[MAXE],pi[MAXN],d[MAXN],src,sink,V,E,
	heap[2*MAXN],pos[MAXN],cnt,parent[MAXN],q[MAXN],*head,*tail,seen[MAXN],yes,in[MAXN],out[N];

void add_arcs( int x, int y, int c, int w ) {
	int i = E++, j = E++;
	to[i] = y, cost[i] =  w, cap[i] = c, flow[i] = 0, next[i] = last[x], last[x] = i;
	to[j] = x, cost[j] = -w, cap[j] = 0, flow[j] = 0, next[j] = last[y], last[y] = j;
	assert( (i^1) == j );
	assert( (j^1) == i );
}

void push( int x ) {
	int i,j;
	if ( (j=pos[x]) < 0 )
		(j=pos[heap[cnt]=x]=cnt),++cnt;
	for (;j && d[heap[i=(j-1)>>1]] > d[heap[j]]; bubble, j = i );
}

int pop() {
	int i,j,x = *heap;
	if ( ((pos[x]=-1),--cnt) )
		pos[*heap=heap[cnt]] = 0;
	for ( j = 0; (i = j, j <<= 1, ++j) < cnt; bubble ) {
		if ( j < cnt-1 && d[heap[j]] > d[heap[j+1]] ) ++j;
		if ( d[heap[i]] <= d[heap[j]] ) break ;
	}
	return x;
}

int dijkstra() {
	int x,y,i;
	for ( x = 0; x < V; pos[x] = -1, d[x++] = +oo );
	for ( parent[src] = -1, cnt = 0, d[src] = 0, push(src); cnt;)
		for ( i = last[x = pop()]; i >= 0; i = next[i] ) 
			if ( flow[i]<cap[i] && d[y=to[i]]>d[x]+(pi[x]-pi[y]+cost[i]) ) 
				d[y]=d[x]+(pi[x]-pi[y]+cost[i]), push(y), parent[y]=i;
	for ( x = 0; x < V; ++x )
		if ( d[x] < +oo )
			pi[x] += d[x];
	return d[sink]<+oo;
}

void G( int i ) {
	int x = to[i^1], y = to[i];
	if ( y-x != 1 )
		return ;
	if ( (y&1) )
		return ;
	if ( (y-1)/2 != x/2 )
		return ;
	if ( x/2 >= n )
		return ;
}

void mincost_maxflow() {
	int x,y,i,j,ans = 0,tot = 0,k,weight = 0;
	for ( x = 0; x < V; pi[x++] = 0 );
	for ( ;tot < 2; ) {
		if ( dijkstra() ) {
			for ( ++tot, i = parent[sink]; i != -1; i = parent[to[i^1]] ) 
				++flow[i], --flow[i^1];
		}
	}
	assert( tot == 2 );
	for ( weight = 0, i = 0; i < E; ++i ) {
		if ( flow[i] > 0 && to[i] != src && to[i] != sink && to[i^1] != src && to[i^1] != sink && !(to[i]&1) && (to[i]-to[i^1]==1) && (to[i^1]/2 == (to[i]-1)/2) )
			++ans;
		if ( flow[i] > 0 )
			weight += cost[i];
	}
	/*printf("%d %d\n",pi[src],pi[sink]);*/
	printf("%d\n",ans);
	/*printf("weight = %d\n",weight);*/
}

int main() {
	int i,j,k,cs,x[6101],y[6101],dist[2][MAXN],length[6101],old_m;
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	for ( scanf("%d",&cs); cs-- && 2 == scanf("%d %d",&n,&m) && ++yes; ) {
		for ( V = 2+2*n, i = 0; i < V; out[i] = in[i] = 0, last[i++] = -1 );
		E = 0, src = 0, sink = 2*n+1;
		assert( sink+1 == V );
		for ( k = 0; k < m; ++k ) {
			assert( 2 == scanf("%d %d",&i,&j) );
		   	--i, --j;
			x[k] = i, y[k] = j, length[k] = 1;
			assert( 0 <= i && i <= n-1 && 0 <= j && j <= n-1 );
			++in[j], ++out[i];
		}
		if ( n == 1 ) {
			puts("1");
			continue ;
		}
		V = 2*n+2, E = 0, src = 0, sink = 2*n+1;
		for ( E = 0, i = 0; i < V; last[i++] = -1 );
		for ( i = 0; i < m; ++i ) 
			add_arcs(OUT(x[i]),IN(y[i]),1,-1);
		for ( i = 0; i < n; ++i ) {
			add_arcs(IN(i),OUT(i),1,-1);
			/*add_arcs(src,IN(i),1,10*(n+3-forward[i]));
		   	add_arcs(OUT(i),sink,1,10*(n+3-backward[i]));*/
			add_arcs(src,IN(i),1,1);
		   	add_arcs(OUT(i),sink,1,1);
		}
		/*
		for ( i = 0; i < E; ++i )
			if ( cost[i] >= 0 ) {
				printf("cost(%d --> %d) = %d\n",to[i^1],to[i],cost[i]);
			}
			*/
		mincost_maxflow();
	}
	return 0;
}


