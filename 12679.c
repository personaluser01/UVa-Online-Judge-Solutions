/*
 * 12679. It Can Be Arranged
 * TOPIC: mincost circulation, negaitve cycles, bellman ford, vertex capacities
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define N 0x80
#define MAXN (2*N)
#define MAXE (N*N)
typedef long long i64;
#define oo (1LL << 43)
#define IN(x)  ( ((x)<<1)+1 )
#define OUT(x) ( ((x)<<1)+2 )
#define tol 1e-9
#define MAXC (10001*N)

i64 min( i64 x, i64 y ) { if ( x < y ) return x; return y; }
		    
int ts,cs,n,st[N],fin[N],g[N][N],to[MAXE],visited[MAXN],indeed,parent[MAXN],next[MAXE],
	last[MAXN],V,E,src,sink,into_src[MAXN],out_of_src[MAXN],seen[MAXN],yes,mid[MAXN];
i64 rc,students[N],cost[MAXE],d[MAXN],T,flow[MAXE],cap[MAXE],low[MAXE],fl[MAXN];

void add_arcs( int x, int y, i64 c, i64 l, i64 w ) {
	int i = E++, j = E++;
	to[i] = y, cap[i] =  c, low[i] =  l, next[i] = last[x], last[x] = i, flow[i] = 0, cost[i] =  w;
	to[j] = x, cap[j] = -l, low[j] = -c, next[j] = last[y], last[y] = j, flow[j] = 0, cost[j] = -w;
}

int bf( int *v ) {
	int i,j,k,x,y;
	for ( x = 0; x < V; ++x ) d[x] = +oo;
	for ( parent[src] = -1, d[src] = 0, i = 0; i < V-1; ++i )
		for ( k = 0; k < E; ++k )
			if ( d[x=to[k^1]] < +oo && flow[k] < cap[k] && d[y=to[k]] > d[x]+cost[k] )
				d[y]=d[x]+cost[parent[y]=k];
	for ( k = 0; k < E; ++k )
		if ( d[x=to[k^1]] < +oo && flow[k] < cap[k] && d[y=to[k]] > d[x]+cost[k] ) {
			d[*v=y]=d[x]+cost[parent[y]=k];
			return 1;
		}
	return 0;
}

int main() {
	int i,j,k,x,y,v;
	i64 df,ans,mc,e;
	for ( scanf("%d",&ts); ts--; printf("%lld\n",-ans) ) {
		printf("Case %d: ",++cs), scanf("%d %lld",&n,&rc);
		for ( i = 0; i < n; ++i ) {
			assert( 3 == scanf("%d %d %lld",st+i,fin+i,students+i) );
			if ( students[i]%rc )
				students[i] /= rc, ++students[i];
			else students[i] /= rc;
		}
		for ( i = 0; i < n; ++i )
			for ( j = 0; j < n; ++j ) 
				scanf("%d",&g[i][j]);
		for ( i = 0, sink = 2*n+1; i < 2*n+2; ++i ) last[i] = -1, fl[i] = 0;
		for ( E = 0, V = 2*n+2, i = 0; i < n; ++i ) {
			add_arcs(IN(i),OUT(i),MAXC,students[i],0), mid[i] = (E-2);
			add_arcs(OUT(i),sink,MAXC,0,1), into_src[i] = (E-2);
			add_arcs(sink,IN(i),MAXC,0,0), out_of_src[i] = (E-2);
		}
		for ( i = 0; i < n; ++i )
			add_arcs(src,IN(i),MAXC,0,0), add_arcs(src,OUT(i),MAXC,0,0);
		add_arcs(src,sink,MAXC,0,0);
		for ( i = 0; i < n; ++i )
			for ( j = 0; j < n; ++j )
				if ( i != j && fin[i]+g[i][j] < st[j] )
					add_arcs(OUT(i),IN(j),MAXC,0,0);
		for ( i = 0; i < n; ++i ) 
			if ( fl[i] < students[i] ) {
				k = out_of_src[i], flow[k] += (students[i]-fl[i]), flow[k^1] -= (students[i]-fl[i]);
				k = into_src[i],   flow[k] += (students[i]-fl[i]), flow[k^1] -= (students[i]-fl[i]);
				k = mid[i],		   flow[k] += (students[i]-fl[i]), flow[k^1] -= (students[i]-fl[i]);
				fl[i] += (students[i]-fl[i]);
				assert( fl[i] == students[i] );
			}
		for ( i = 0; i < E; ++i ) {
			assert( low[i] <= flow[i] );
			assert( flow[i] <= cap[i] );
		}
		for ( i = 0; i < n; ++i )
			assert( fl[i] >= students[i] );
		while ( bf(&v) ) {
			for(seen[i]=++yes,k=parent[i],i=to[k^1];k!=-1&&seen[i]!=yes;seen[i]=yes,k=parent[i],i=to[k^1]);
			assert( k != -1 );
			for(e=0,mc=+oo,j=i,k=parent[i],e+=cost[k],mc=min(mc,cap[k]-flow[k]),i=to[k^1];i!=j;k=parent[i],mc=min(mc,cap[k]-flow[k]),i=to[k^1],e+=cost[k]);
			assert( mc > 0 && e < 0 );
			for(k=parent[i],i=to[k^1],flow[k]+=mc,flow[k^1]-=mc;i!=j;k=parent[i],flow[k]+=mc,flow[k^1]-=mc,i=to[k^1]);
		/*		printf("%d --> %d\n",to[k^1],to[k]);
			printf("%d --> %d\n",to[k^1],to[k]);
			printf("mc = %lld\n",mc);*/
			/*
			for(seen[v]=++yes,i=parent[v];i!=-1&&seen[x=to[i^1]]!=yes;seen[x]=yes,i=parent[x]);
			assert( i != -1 );
			for(df=+oo,i=parent[x];i!=-1&&to[i^1]!=x;df=min(df,cap[i]-flow[i]),i=parent[to[i^1]]);
			printf("df = %lld\n",df);
			assert( df < +oo );
			assert( i != -1 );
			assert( df > 0 );
					for(i=parent[x],flow[i]+=df,flow[i^1]-=df;i!=-1&&to[i^1]!=x;i=parent[to[i^1]],flow[i]+=df,flow[i^1]-=df);
			*/
		}
		for ( ans = 0, i = 0; i < E; ++i )
			if ( flow[i] > 0 && to[i] == sink )
				ans -= flow[i];
	}
    return 0;
}

