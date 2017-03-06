/*
 * 13000. VIP Treatment
 * TOPIC: maxflow, binary search
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 0x400
#define MAXV (N+N+2)
#define MAXE (8*N*N)
#define oo (1LL<<62)
typedef long long i64;

i64 min( i64 x, i64 y ) { if ( x < y ) return x; return y; }

int m,n,time_needed[N],vip[N],reg[N],len[N],mat[N][N],src,sink,
	last[MAXV],next[MAXE],to[MAXE],q[MAXV],*head,*tail,
	E,visited[MAXV],indeed,seen[MAXV],yes,sink_vip,sink_reg;
i64 cap[MAXE],flow[MAXE],d[MAXV],T,R,K;

void add_arcs( int x, int y, i64 c ) {
	int i = E++, j = E++;
	to[i] = y, next[i] = last[x], last[x] = i, cap[i] = c;
	to[j] = x, next[j] = last[y], last[y] = j, cap[j] = 0;
	flow[i] = flow[j] = 0;
}

int bfs() {
	int x,y,i;
	for ( head=tail=q, seen[*tail++=sink]=++yes; head<tail; )
		for ( i=last[x=*head++]; i>=0; i=next[i] )
			if ( cap[i^1]>flow[i^1] && (seen[y=to[i]] != yes || d[y] > d[x]+1) ) 
				seen[*tail++ = y] = yes, d[y] = d[x]+1;
	return seen[src] == yes;
}

int dfs( int x, i64 df ) {
	int i,y;
	i64 dt;

	if ( x == sink ) return df;
	for(visited[x]=indeed,i=last[x];i>=0;i=next[i])
		if ( seen[y=to[i]] == yes && d[y]+1 == d[x] && visited[y] != indeed )
			if ( cap[i] > flow[i] )
				if ( (dt = dfs(y,min(df,cap[i]-flow[i]))) ) {
					flow[i] += dt, flow[i^1] -= dt;
					return dt;
				}
	return 0;
}

i64 maxflow() {
	int x,y,i,j,k;
	i64 tot = 0,dt;
	for(;bfs();)for(;++indeed && (dt=dfs(src,+oo));tot+=dt);
	return tot;
}

int main() {
	int i,j,k,l,t,ts,cs = 0;
	i64 good,bad,mid;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( scanf("%d",&ts); ts--; printf("%lld\n",good) ) {
		scanf("%d %d %lld",&m,&n,&K), printf("Case %d: ",++cs);
		for ( i = 0; i < n; scanf("%d",&time_needed[i++]) );
		for ( T=0,R=0,j=0; j<m; ++j ) 
			for(scanf("%d %d %d",vip+j,reg+j,len+j),T+=vip[j],R+=reg[j],l=0;l<len[j];scanf("%d",&mat[j][l++]),--mat[j][l-1]);
		for(good=+oo,bad=-1;bad+1<good;) {
			mid = (good+bad)/2;
			for ( E = 0, src = 0, sink_vip = m+m+n+1, sink_reg = m+m+n+2, sink = m+m+n+3, i = src; i <= sink; last[i++] = -1 );
			for ( i = 0; i < n; ++i )
				add_arcs(src,1+i,mid/time_needed[i]);
			for ( j = 0; j < m; ++j ) {
				l = n+j+1, t = n+m+j+1, add_arcs(l,sink_reg,reg[j]), add_arcs(t,sink_vip,vip[j]);
				for ( k = 0; k < len[j]; ++k )
					i = mat[j][k], add_arcs(i+1,l,+oo), add_arcs(i+1,t,+oo);
			}
			add_arcs(sink_reg,sink,K), add_arcs(sink_vip,sink,T);
			if ( maxflow() >= T+K )
				good = mid;
			else bad = mid;
		}
	}
	return 0;
}


