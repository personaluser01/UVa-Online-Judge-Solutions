/*
 * 1711. Catering
 * TOPIC: mincost maxflow
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define xchg(x,y) (((x)==(y))||((x)^=(y),(y)^=(x),(x)^=(y)))
#define bubble (xchg(pos[heap[i]],pos[heap[j]]),xchg(heap[i],heap[j]))
#define MAXV 0x200
#define MAXE (1<<17)
#define N 0x80
#define oo (1<<29)

int min( int x, int y ) { return x<y?x:y; }

int d[MAXV],last[MAXV],E,V,to[MAXE],cost[MAXE],next[MAXE],flow[MAXE],cap[MAXE],src,sink,
	heap[MAXV<<1],pos[MAXV],inq[MAXV],yes,p[MAXV],parent[MAXV],n,m,cnt;

void push( int x ) {
	int i,j;
	if ( inq[x] != yes )
		inq[x] = yes, pos[heap[cnt]=x]=cnt, ++cnt;
	for ( j = pos[x]; j && d[heap[j=(i-1)>>1]] > d[heap[j]]; bubble, j = i );
}

int pop() {
	int i,j,x=*heap;
	inq[x] = 0;
	if ( cnt += (pos[x]=-1) )
		pos[*heap=heap[cnt]] = 0;
	for ( j = 0; (i=j,j<<=1,++j) < cnt; bubble ) {
		if ( j < cnt-1 && d[heap[j]] > d[heap[j+1]] ) ++j;
		if ( d[heap[j]] >= d[heap[i]] ) break ;
	}
	return x;
}

void add_arcs( int x, int y, int c, int w ) {
	int i = E++, j = E++;
	to[i] = y, next[i] = last[x], last[x] = i, cap[i] = c, flow[i] = 0, cost[i] = w;
	to[j] = x, next[j] = last[y], last[y] = j, cap[j] = 0, flow[j] = 0, cost[j] = -w;
}

int dijkstra() {
	int x,y,i;
	for ( x = src; x < V; d[x++] = +oo );
	for ( cnt=0,++yes,d[src]=0,parent[src]=-1,push(src); cnt; )
		for ( i=last[x=pop()]; i>=0; i=next[i] ) 
			if ( flow[i] < cap[i] && d[y=to[i]]>d[x]+p[x]+cost[i]-p[y] )
				d[y]=d[x]+p[x]+cost[i]-p[y], push(y), parent[y]=i;
	for ( x = src; x < V; ++x )
		if ( d[x] < +oo )
			p[x]+=d[x];
	return d[sink]<+oo;
}

int mcmf() {
	int i,df,w=0;
	for (i=src;i<V;p[i++]=0);
	for(;dijkstra();) {
		for ( df=+oo,i=parent[sink]; i!=-1; df=min(df,cap[i]-flow[i]),i=parent[to[i^1]] );
		assert( df > 0 );
		for ( i=parent[sink]; i!=-1; flow[i]+=df,flow[i^1]-=df,i=parent[to[i^1]] );
	}
	for ( i = 0; i < E; w += cost[i]*flow[i], ++i );
	return w/2;
}

int main() {
	int i,j,k,l,w[N][N];
#ifndef ONLINE_JUDGE
	freopen("1711.in","r",stdin);
#endif
	while ( 2 == scanf("%d %d",&n,&m) ) {
		for ( V = 2*n+5, src = 0, sink = V-1, E = 0, i = 0; i < V; last[i++] = -1 );
		for ( i = 1; i <= n; ++i )
			add_arcs(src,i,i==1?m:1,0);
		for ( i = 0; i <= n+1; ++i )
			for ( j = 0; j <= n+1; ++j )
				w[i][j] = +oo;
		for ( i = 1; i <= n; ++i ) 
			for ( l = 1; l <= n-i+1; scanf("%d",&w[i][i+l]), ++l );
		for ( i = 1; i <= n; ++i )
			for ( j = i+1; j <= n+1; ++j )
				if ( w[i][j] < +oo )
					add_arcs(i,n+j,1,w[i][j]);
		for ( j = n+2; j <= n+(1+n); ++j ) add_arcs(j,sink,1,0);
		printf("%d\n",mcmf());
	}
	return 0;
};

