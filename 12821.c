/*
 * 12821. Double Shortest Paths
 * TOPIC: mincost maxflow
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 0x200
#define M (1<<14)
typedef long long i64;
#define xchg(x,y) (((x)==(y))||((x)^=(y),(y)^=(x),(x)^=(y)))
#define bubble (xchg(pos[heap[i]],pos[heap[j]]),xchg(heap[i],heap[j]))
#define oo (1LL<<43)

i64 min( i64 x, i64 y ) { return x<y?x:y; }

int last[N],next[M],cap[M],flow[M],to[M],from[M],m,n,E,V,src,sink,
	heap[M],cnt,pos[N],p[N];
i64 pi[N],d[N],cost[M];

void add_arcs( int x, int y, int c, int w ) {
	int i = E++, j = E++;
	to[i]=y,next[i]=last[x],last[x]=i,cap[i]=c,flow[i]=0,from[i]=x,cost[i]= w;
	to[j]=x,next[j]=last[y],last[y]=j,cap[j]=0,flow[j]=0,from[j]=y,cost[j]=-w;
}

void push( int x ) {
	int i,j;
	if ( pos[x] < 0 ) pos[heap[cnt]=x]=cnt,++cnt;
	for ( j = pos[x]; j && d[heap[i=(j-1)>>1]] > d[heap[j]]; bubble, j = i );
}

int pop() {
	int i,j,x = *heap;
	if ( cnt+=(pos[x]=-1) ) pos[heap[0]=heap[cnt]]=0;
	for ( j = 0; (i=j,j<<=1,++j) < cnt; bubble ) {
		if ( j < cnt-1 && d[heap[j+1]] < d[heap[j]] ) ++j;
		if ( d[heap[i]] <= d[heap[j]] )  break ;
	}
	return x;
}

int dijkstra() {
	int i,x,y;
	i64 df;
	for ( cnt = 0, x = 0; x < n; d[x] = +oo, pos[x] = -1, p[x++] = -1 );
	for ( d[src] = 0, push(src), p[src]=-1; cnt; )
		for ( i=last[x=pop()]; i>=0 && (y=to[i])>=0; i=next[i] )
			if ( flow[i] < cap[i] && d[y] > d[x]+pi[x]-pi[y]+cost[i] )
				d[y] = d[x]+pi[x]-pi[y]+cost[i], push(y), p[y]=i;
	if ( d[sink] == +oo ) return 0;
	for ( df = 1, i = p[sink]; i != -1; flow[i] += df, flow[i^1] -= df, i = p[from[i]] );
	for ( x = 0; x < n; ++x )
		if ( d[x]<+oo ) pi[x] += d[x];
	return df;
}

i64 mcmf() {
	i64 res = 0;
	int i,fl = 0,df,j = 0;
	for(;(df=dijkstra())&&(fl+=df)<2;);
	for(i=0;i<E;res+=cost[i]*flow[i],++i);
	0&&printf("Flow = %d\n",fl);
	return res;
}

int main() {
	int i,j,k,l,t,x,y,cs = 0;
#ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
#endif
	for(;2 == scanf("%d %d",&n,&m); printf("Case %d: %lld\n",++cs,mcmf()/2) ) {
		for ( src=0,sink=n-1,E = V = 0, i = 0; i < n; ++i ) last[i]=-1,pi[i]=0;
		for ( l = 0; l < m && 4 == scanf("%d %d %d %d",&x,&y,&i,&j); ++l ) 
			if ( x != y ) add_arcs(--x,--y,1,i), add_arcs(x,y,1,i+j);
	}
    return 0;
}

