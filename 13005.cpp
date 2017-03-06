/*
 * 13005. Blood Types
 * TOPIC: maxflow
 * status: Accepted
 */
#include <cassert>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>
#include <set>
#define N 0x80 
#define MAXV (1<<10)
#define MAXE (1<<20)
typedef unsigned long long u64;
using namespace std;

int m,n,qr,last[MAXV],next[MAXE],to[MAXE],cap[MAXE],flow[MAXE],V,E,src,sink,
	d[MAXV],q[MAXV],*head,*tail,seen[MAXV],yes,visited[MAXV],indeed,p[MAXV],sz[N];
u64 A[N][N];
bool covered[N];

void add_arcs( int x, int y, int c ) {
	int i = E++, j = E++;
	to[i] = y, next[i] = last[x], last[x] = i, cap[i] = c, flow[i] = 0;
	to[j] = x, next[j] = last[y], last[y] = j, cap[j] = 0, flow[j] = 0;
}

bool bfs() {
	for ( head=tail=q,visited[sink]=++indeed,d[*tail++=sink]=0; head<tail; )
		for ( int i=last[*head++]; i>=0; i=next[i] )
			if ( flow[i^1]<cap[i^1] && (visited[to[i]]!=indeed || d[to[i]]>d[to[i^1]]+1) )
				visited[to[i]]=indeed, d[*tail++=to[i]]=d[to[i^1]]+1, p[to[i]]=i;
	return visited[src] == indeed;
}

int dfs( int x, int df ) {
	int dt,y,i;
	if ( sink == x ) return df;
	if ( !df || seen[x]==yes )
		return 0;
	for ( seen[x]=yes, i=last[x]; i>=0 && (y=to[i])>=0; i=next[i] )
		if ( seen[y] != yes && flow[i]<cap[i] && visited[y]==indeed && d[y]+1==d[x] )
			if ( dt=dfs(y,min(df,cap[i]-flow[i])) ) {
				flow[i]+=dt, flow[i^1]-=dt;
				return dt;
			}
	return 0;
}

int maxflow() {
	int total=0,dt;
	for (;bfs();) for(;++yes && (dt=dfs(src,(1<<29)));total+=dt);
	return total;
}

int main() {
	int i,j,k,b[N],len,l;
	bool o_allele,ok;
#ifndef ONLINE_JUDGE
	freopen("13005.in","r",stdin);
#endif
	for (;2==scanf("%d %d",&n,&qr);) {
		for ( i = 0; i < n; ++i ) 
			for ( scanf("%d",&k), sz[i] = k, memset(A[i],0,sizeof A[i]); k-- && 1 == scanf("%d",&j); A[i][j>>6]|=(1ULL<<(j&63)) );
		for (;qr-- && 1 == scanf("%d",&m);)  {
			for ( i = 0; i < n; covered[i++] = false );
			for ( ok = true, len = 0; m-- && 1 == scanf("%d",&i); b[len++] = i );
			for ( o_allele=(m=len)<n, E=0, V=n+n+0x20, src=V-2, sink=V-1, i=0; i<V; last[i++]=-1 );
			for ( i = 0; i < n && ok; add_arcs(src,i,1), ok &= covered[i++] ) {
				if ( sz[i] < n && o_allele ) covered[i] = true ;
				for ( l = 0; l < len; ++l )
					if ( A[i][b[l]>>6]&(1ULL<<(b[l]&63)) ) 
						covered[i] = true, add_arcs(i,n+b[l],1);
			}
			for ( i = 0; i < len && ok; add_arcs(n+b[i++],sink,1) );
			puts(ok && maxflow()==m?"Y":"N");
		}
	}
	return 0;
}

