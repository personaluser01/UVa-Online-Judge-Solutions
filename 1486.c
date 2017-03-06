/*
 * 1486. Transportation
 * TOPIC: mincost maxflow
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#define MAXN 0x400
#define MAXE (1<<21)
#define xchg(x,y) (((x)==(y))||((x)^=(y),(y)^=(x),(x)^=(y)))
#define bubble (xchg(pos[heap[i]],pos[heap[j]]),xchg(heap[i],heap[j]))
#define oo (1LL<<43)
typedef long long i64;
i64 min( i64 x, i64 y ) {return x<y?x:y;}

int m,n,K,V,E,to[MAXE],last[MAXN],next[MAXE],flow[MAXE],cap[MAXE],heap[MAXN<<1],cnt,pos[MAXN],p[MAXN],src,sink;
i64 pi[MAXN],d[MAXN],cost[MAXE];
char out[1<<20],*ptr = out;

void wr( i64 n ) {
	if ( n < 10 ) *ptr++ = (n+'0');
	else wr(n/10), *ptr++ = ((n%10)+'0');
}

int getint() {
	int ch,n;
	static int dig[256] = {0};
	if ( !dig['0'] )
		for ( n = '0'; n <= '9'; dig[n++] = 1 );
	for (;(ch = getchar()) != EOF && !dig[ch]; );
	if ( ch == EOF )
		return -1;
	for ( n = ch-'0'; (ch = getchar()) != EOF && dig[ch]; n = 10*n+(ch-'0') );
	return n;
}

void add_arcs( int x, int y, int c, i64 w ) {
	int i = E++, j = E++;
	to[i] = y, next[i] = last[x], last[x] = i, cost[i] = w,  cap[i] = c;
	to[j] = x, next[j] = last[y], last[y] = j, cost[j] = -w, cap[j] = 0;
	flow[i] = flow[j] = 0;
}

void push( int x ) {
	int i,j;
	if ( pos[x] < 0 )
		pos[heap[cnt] = x] = cnt, ++cnt;
	for ( j = pos[x]; j && d[heap[i=(j-1)>>1]] > d[heap[j]]; bubble, j = i );
}

int pop() {
	int i,j,x = *heap;
	if ( cnt+=(pos[x]=-1) )
		pos[*heap=heap[cnt]]=0;
	for ( j=0; (i=j,j<<=1,++j) < cnt; bubble ) {
		if ( j < cnt-1 && d[heap[j]] > d[heap[j+1]] ) ++j;
		if ( d[heap[i]] <= d[heap[j]] ) break ;
	}
	return x;
}

int dijkstra() {
	int i,x,y;
	for ( cnt=0, x=0; x<V; d[x]=+oo, pos[x++]=-1 );
	for ( p[src]=-1,d[src]=0, push(src); cnt; )
		for ( i = last[x = pop()]; i>=0 && (y=to[i]) >= 0; i = next[i] )
			if ( cap[i] > flow[i] )
				if ( d[y] > d[x]+pi[x]-pi[y]+cost[i] )
					d[y] = d[x]+pi[x]-pi[y]+cost[p[y]=i], push(y);
	for ( x = 0; x < V; ++x )
		if ( d[x] < +oo ) pi[x] += d[x];
	return d[sink] < +oo;
}

void mincost_maxflow() {
	int x,df,F = 0,i;
	i64 T = 0;
	for ( x = 0; x < V; pi[x++] = 0 );
	while ( dijkstra() ) {
		for ( df=cap[p[sink]]-flow[p[sink]],x=to[p[sink]^1]; x!=src; df=min(df,cap[p[x]]-flow[p[x]]), x=to[p[x]^1] );
		assert( df > 0 );
		for ( F+=df, flow[p[sink]]+=df,flow[p[sink]^1]-=df,T+=df*cost[p[sink]],x=to[p[sink]^1]; x!=src; flow[p[x]]+=df,flow[p[x]^1]-=df, T+=df*cost[p[x]], x=to[p[x]^1] );
	}
	if ( F < K ) *ptr++ = '-', *ptr++ = '1';
	else 
		wr(T);
	*ptr++ = '\n';
}

int main() {
	int i,j,k,l,t,coeff,times,x,y;
#ifndef ONLINE_JUDGE
	freopen("1486.in","r",stdin);
#endif
	for (;(n=getint())!=-1;mincost_maxflow()) {
		m = getint();
		K = getint();
		for ( E = 0, V = n+1, src = 0, sink = n, i = 0; i < V; last[i++] = -1 );
		for ( l = 0; l < m; ++l ) 
			for ( x=getint(),y=getint(),coeff=getint(),times=getint(), t = 1; t <= times; add_arcs(x,y,1,coeff*(t*t-(t-1)*(t-1))), ++t );
		add_arcs(src,1,K,0);
	}
	printf("%s",out);
	return 0;
}

