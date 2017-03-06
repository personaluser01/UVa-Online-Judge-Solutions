/*
 * 11613. Acme Corporation
 * TOPIC: mincost maxflow, bipartite graphs, dijkstra, potentials
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXN 0x400
#define MAXE (1 << 20)
#define xchg(x,y) (((x)==(y)) || ((x)^=(y),(y)^=(x),(x)^=(y)))
#define bubble (xchg(pos[heap[i]],pos[heap[j]]),xchg(heap[i],heap[j]))
#define N MAXN
typedef long long i64;
#define oo (1LL << 43)

i64 min( i64 x, i64 y ) { if ( x < y ) return x; return y; }
i64 max( i64 x, i64 y ) { if ( x < y ) return y; return x; }

int ts,cs,n,m,V,E,to[MAXE],last[MAXN],next[MAXE],cap[MAXE],I,src,sink,
	price[N],ee[N],manufacturing_cost[N],nn[N],ss[N],parent[N],cnt,heap[2*MAXN],pos[MAXN];
i64 flow[MAXE],cost[MAXE],pi[MAXN],d[MAXN];

void add_arcs( int x, int y, int c, i64 w ) {
	int i = E++, j = E++;
	to[i] = y, next[i] = last[x], last[x] = i, cost[i] =  w, cap[i] = c, flow[i] = 0;
	to[j] = x, next[j] = last[y], last[y] = j, cost[j] = -w, cap[j] = 0, flow[j] = 0;
}

void push( int x ) {
	int i,j;
	if ( pos[x] < 0 ) 
		pos[heap[cnt]=x]=cnt,++cnt;
	for ( j = pos[x]; j && d[heap[i=(j-1)>>1]] > d[heap[j]]; bubble, j = i );
}

int pop() {
	int i,j,x = *heap;
	if ( ((pos[x]=-1),--cnt) )
		pos[heap[0]=heap[cnt]] = 0;
	for ( j = 0; (i = j, j <<= 1, ++j) < cnt; bubble ) {
		if ( j < cnt-1 && d[heap[j]] > d[heap[j+1]] ) ++j;
		if ( d[heap[i]] <= d[heap[j]] ) break ;
	}
	return x;
}

int dijkstra() {
	int x,y,i,j;
	for ( cnt = 0, x = src; x <= sink; pos[x] = -1, d[x++] = +oo );
	for ( parent[src] = -1, d[src] = 0, push(src); cnt; )
		for ( i = last[x=pop()]; i >= 0; i = next[i] )
			if ( flow[i]<cap[i] && (y=to[i]) >= 0 &&  d[y] > d[x]+(pi[x]-pi[y]+cost[i]) )
				d[y] = d[x]+(pi[x]-pi[y]+cost[i]), parent[y] = i, push(y);
	for ( x = src; x <= sink; ++x )
		if ( d[x] < +oo )
			pi[x] += d[x];
	return d[sink] < +oo;

}

int valid_edge( int i ) {
	int x = to[i^1],
		y = to[i];
	return 1 <= x && x <= n && n+1 <= y && y <= n+n && x <= (y-n) && (y-n) <= x+ee[x];
}

void mincost_maxflow() {
	int i;
	i64 ans = 0,df;
	for (;dijkstra();) {
		for ( df = +oo, i = parent[sink]; i != -1; i = parent[to[i^1]] )
			df = min(df,cap[i]-flow[i]);
		for ( i = parent[sink]; i != -1; i = parent[to[i^1]] ) {
			flow[i] += df, flow[i^1] -= df;
			assert( flow[i] <= cap[i] );
			assert( flow[i^1] <= cap[i^1] );
		}
	}
	for ( i = 0; i < E; ++i )
		if ( flow[i] > 0 && valid_edge(i) ) {
			ans += flow[i]*cost[i];
			if ( to[i] != src && to[i] != sink && to[i^1] != src && to[i^1] != sink ) {
				/*printf("%d items produced in month %d are sold in month %d\n",flow[i],to[i^1],to[i]-n);
				printf("Production costs %d, storage costs %d\n",manufacturing_cost[to[i^1]]*flow[i],(to[i]-to[i^1]-n)*I);
				printf("Money received %d\n",price[to[i]-n]*flow[i]);
				*/
			}
		}
	/*printf("%lld\n",max(0,-ans));*/
	printf("%lld\n",-ans);
}

int main() {
	int i,j,k,tot;
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	for ( scanf("%d",&ts); ts--; ) {
		printf("Case %d: ",++cs), scanf("%d %d",&n,&I);
	   	src = 0, sink = n+n+1, V = n+n+2, E = 0;
		for ( i = src; i <= sink; pi[i] = 0, last[i++] = -1 );
		for ( tot = 0, i = 1; i <= n; ++i ) {
			scanf("%d %d %d %d %d",manufacturing_cost+i,nn+i,price+i,ss+i,ee+i);
			add_arcs(src,i,nn[i],0), add_arcs(i+n,sink,ss[i],0), tot += (ss[i]+nn[i]);
		}
		for ( i = 1; i <= n; ++i ) {
			assert( ee[i] >= 0 && ee[i] <= n );
			for ( j = i; j <= i+ee[i] && j <= n; ++j ) 
				add_arcs(i,j+n,min(nn[i],ss[j]),I*(j-i)+manufacturing_cost[i]-price[j]);
			for ( j = 1; j <= n; ++j )
				add_arcs(i,j+n,min(nn[i],ss[j]),0);
			/*
			for ( j = i+ee[i]+1; j <= n; ++j )
				add_arcs(i,j+n,min(nn[i],ss[j]),0);
				*/
		}
		mincost_maxflow();
	}
	return 0;
}

