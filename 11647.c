/*
 * 11647. Judgement Day
 * TOPIC: mincost circulation, negative cycle canceling, bellman ford
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 0x200
#define MAXC 100
typedef long long i64;
#define MAXE (0x400)
#define MAXS 1000000
#define oo (1LL << 29)
i64 min( i64 x, i64 y ) { if ( x < y ) return x; return y; }
i64 max( i64 x, i64 y ) { if ( x > y ) return x; return y; }
#ifndef ONLINE_JUDGE
#define DBG 1
#else
#define DBG 0
#endif

int m,n,ts,cs,E,V,src,sink,sc[N],to[MAXE],last[N],next[MAXE],seen[N],yes,parent[N],dominated[N];
i64 cost[MAXE],d[MAXE],COST,flow[MAXE],cap[MAXE],low[MAXE],fl[N];

void add_arcs( int x, int y, i64 c, i64 l, i64 w ) {
	int i = E++, j = E++;
	to[i] = y, next[i] = last[x], last[x] = i, cap[i] =  c, cost[i] =  w, low[i] =  l, flow[i] = 0;
	to[j] = x, next[j] = last[y], last[y] = j, cap[j] = -l, cost[j] = -w, low[j] = -c, flow[j] = 0;
}

int bellman_ford( int *v ) {
	int i,k,x,y;
	for ( x = src+1; x < V; d[x++] = +oo );
	for ( d[src] = 0, i = 0; i < V-1; ++i )
		for ( k = 0; k < E; ++k ) 
			if ( flow[k] < cap[k] && d[x=to[k^1]]<+oo && d[y=to[k]]>d[x]+cost[k] ) 
				d[y]=d[x]+cost[parent[y]=k];
	for ( k = 0; k < E; ++k )
		if ( flow[k] < cap[k] && d[x=to[k^1]]<+oo && d[y=to[k]]>d[x]+cost[k] ) {
			d[y]=d[x]+cost[parent[*v=y]=k];
			return 1;
		}
	return 0;
}

int main() {
	int i,j,k,l,t,r,xx[N],yy[N],gg[N],judge[N],mid[N],old_yes;
	i64 mc,e;
	for ( scanf("%d",&ts); ts-- && 2 == scanf("%d %d",&m,&n) && (old_yes = ++yes); putchar('\n')  ) {
		for ( i = 1; i <= n; scanf("%d",&sc[i++]), fl[i-1] = 0 );
		for ( E = 0, src = 0, V = n+2, i = 0; i < V; last[i++] = -1 );
		for ( l = 1; l <= m; ++l ) 
			scanf("%d %d %d",&i,&j,&k), xx[l] = i, yy[l] = j, gg[l] = k;
		for ( k = 1; k; ) 
			for ( k = 0, i = 1; i <= m; ++i )
				for ( j = 1; j <= m && dominated[i] != yes; ++j )
					if ( i != j && gg[i] <= gg[j] && xx[i] <= xx[j] && yy[j] <= yy[i] && dominated[j] != yes )
						dominated[j]=yes, ++k;
		for ( i = 1; i <= m; ++i )
			if ( dominated[i] != yes ) 
				add_arcs(yy[i]+1,xx[i],+oo,0,(i64)gg[i]), judge[i] = (E-2);
		for ( i = 1; i <= n; ++i )
			add_arcs(i,i+1,+oo,(i64)sc[i],0LL), mid[i] = (E-2);
		for ( l = 1; l <= m; ++l ) {
			if ( dominated[l] == yes ) continue ;
			for ( i = xx[l], j = yy[l], mc = 0, t = i; t <= j; ++t ) 
				mc = max(mc,sc[t]-fl[t]);
			if ( mc <= 0 ) continue ;
			t = judge[l], flow[t] += mc, flow[t^1] -= mc;
			for ( k = i; k <= j; ++k ) 
				t = mid[k], flow[t] += mc, flow[t^1] -= mc, fl[k] += mc;
		}

		for ( l = 1; l <= n; ++l ) assert( fl[l] >= sc[l] );
		for ( i = 0; i < E; ++i )  assert( flow[i] <= cap[i] );

		for ( i = 1; i <= n+1; ++i ) add_arcs(src,i,+oo,0,0);

		while ( bellman_ford(&i) ) {
			for(seen[i]=++yes,k=parent[i],i=to[k^1];seen[i]!=yes;seen[i]=yes,k=parent[i],i=to[k^1]);
			for(e=0,mc=MAXC*MAXS+1,j=i,k=parent[i],e+=cost[k],mc=min(mc,cap[k]-flow[k]),i=to[k^1];i!=j;k=parent[i],mc=min(mc,cap[k]-flow[k]),i=to[k^1],e+=cost[k]);
			assert( mc > 0 && e < 0 );
			for(k=parent[i],i=to[k^1],flow[k]+=mc,flow[k^1]-=mc;i!=j;k=parent[i],flow[k]+=mc,flow[k^1]-=mc,i=to[k^1]);
		}
		for ( COST = 0, i = 0; i < E; ++i )
			if ( flow[i] > 0 ) 
				COST += flow[i]*cost[i];
#if DBG
		printf("Case %d:[%lld]",++cs,COST);
#else
		printf("Case %d:",++cs);
		for ( l = 1; l <= m; ++l ) 
			if ( dominated[l] == old_yes ) 
				putchar(' '), putchar('0');
			else printf(" %lld",flow[judge[l]]);
#endif
	}
    return 0;
}

