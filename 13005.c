/*
 * 13005. Blood Groups
 * TOPIC: mincost circulation
 * status:
 */
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define N 0x80
#define MAXV (N+N)
#define BIT(k) (1ULL<<(k))
#define MASK(k) (BIT(k)-1ULL)
#define TST(u,k) (((u)>>(k))&1UL)
#define MAXE (N*N)
#define L(k) ((k)&((~(k))+1ULL))
typedef unsigned long long u64;

int min( int x, int y ) { if ( x < y ) return x; return y; }

int n,qr,src,sink,d[MAXV],seen[MAXV],yes,p[MAXV],BB,
	to[MAXE],next[MAXE],last[MAXV],cap[MAXE],flow[MAXE],E,V,lower[MAXE],cost[MAXE];
char which[BIT(20)],bts[BIT(20)];
u64 LST[N][N>>6];

int Bits( u64 u ) 
{ return bts[u>>60]+bts[(u>>40)&MASK(20)]+bts[(u>>20)&MASK(20)]+bts[u&MASK(20)]; }

int who( const u64 u ) {
	if ( u >= BIT(60) ) return 60+which[u>>60];
	if ( u >= BIT(40) ) return 40+which[u>>40];
	if ( u >= BIT(20) ) return 20+which[u>>20];
	return which[u];
}

void add_arcs( int x, int y, int l, int c, int w ) {
	int i = E++, j = E++;
	to[i]=y, next[i]=last[x], last[x]=i, flow[i]=0;
	to[j]=x, next[j]=last[y], last[y]=j, flow[j]=0;
	lower[i] = l, lower[j] = -c, cap[i] = c, cap[j] = -l;
	cost[i] = w, cost[j] = -w;
}

int bellman_ford( int *t ) {
	int i,j;
	for ( seen[src] = ++yes, d[src] = 0, i=0; i<2+n+BB+1; ++i )
		for ( j=0; j<E; ++j ) 
			if ( seen[to[j^1]]==yes && flow[j]<cap[j] && (seen[to[j]]!=yes || d[to[j]]>d[to[j^1]]+cost[j]) )
				d[to[j]]=d[to[j^1]]+cost[j], seen[to[j]]=yes, p[to[j]]=j;
	for ( j=0;j<E; ++j )
		if ( seen[to[j^1]]==yes && flow[j]<cap[j] && (seen[to[j]]!=yes || d[to[j]]>d[to[j^1]]+cost[j]) ) {
			*t = to[j];
			return 1;
		}
	return 0;
}

int initial_circulation() {
	int i,balance[MAXV];
	for ( i = 0; i < V; balance[i++] = 0 );
	for ( i = 0; i < E; i += 2 ) {
		if ( cap[i] < lower[i] ) return 0;
		flow[i] = cap[i], flow[i^1] -= cap[i];
		balance[to[i^1]] -= cap[i], balance[to[i]] += cap[i];
	}
	for ( i = 0; i < V && 0 == balance[i]; ++i );
	return i == V;
}

int mincost_circulation() {
	int i,t,w=0,df=(1<<29);
	if ( !initial_circulation() ) return 0;
	for(;bellman_ford(&t);) {
		for ( seen[t]=++yes, i=p[t]; seen[to[i^1]] != yes; seen[to[i^1]] = yes, i = p[to[i^1]] );
		for ( t=to[i^1], i=p[t]; ;i=p[to[i^1]] ) {
			df = min(df,cap[i]-flow[i]);
			if ( to[i^1] == t ) break ;
		}
		for ( i = p[t]; ; i = p[to[i^1]] ) {
			flow[i] += df, flow[i^1] -= df;
			assert( lower[i] <= flow[i] && flow[i] <= cap[i] );
			if ( to[i^1] == t ) break ;
		}
	}
	for ( i = 0; i < E; w += cost[i]*flow[i], ++i );
	return w/2;
}

int main() {
	int i,j,k,l,t,B,absent[N],len,o_allele,outdeg[N],indeg[N],sumdeg;
	u64 LL[(N>>6)+2],u;
#ifndef ONLINE_JUDGE
	freopen("13005.in","r",stdin);
#endif
	for ( i=0; i<20; which[1<<i]=i, ++i );
	for ( i=0; i<BIT(20); bts[i]=bts[i>>1]+(i&1), ++i );
	for (;2==scanf("%d %d",&n,&qr);) {
		for ( i = 0; i < n; ++i ) for ( j = 0; j <= (n>>6)+1; LST[i][j++] = 0 );
		for ( i = 0; i < n; ++i ) {
			for ( scanf("%d",&k), l = 0; l < k; scanf("%d",&j), LST[i][j>>6] |= BIT(j&63), ++l );
			for ( k = 0, j = 1; j <= n; ++j )
				if ( LST[i][j>>6]&BIT(j&63) ) ++k;
			if ( k < n ) LST[i][0>>6] |= BIT(0&63);
		}
		for (;qr--&&1==scanf("%d",&B);) {
			for ( V = 2*n+3,src=V-2,sink=V-1,E=0, i = 0; i < V; last[i++] = -1 );
			for ( l = 0; l <= (n>>6)+1; LL[l++] = 0 );
			for ( BB = B; B-- && 1==scanf("%d",&j); LL[j>>6] |= BIT(j&63) );
			assert( B == -1 );
			for ( o_allele=0,j=0; j<=n; o_allele=o_allele||(j>0&&!(LL[j>>6]&BIT(j&63))),indeg[j++]=0 );
			for ( i=0; i<n; add_arcs(src,i,1,outdeg[i],1), ++i )
				for ( outdeg[i] = 0, j=0; j<=(n>>6)+1; ++j )
					for ( u = LST[i][j]; u; u &= ~L(u) )
						if ( t = who(L(u))+j*64 ) {
							if ( LL[t>>6] & BIT(t&63) )
								add_arcs(i,n+t,0,1,0), ++indeg[t], ++outdeg[i];
						}
						else if ( o_allele )
							add_arcs(i,n,0,1,0), ++indeg[0], ++outdeg[i];
			for ( sumdeg = 0, i = 0; i < n; sumdeg += outdeg[i++] );
			for ( j = 0; j <= (n>>6)+1; ++j )
				for ( u = LL[j]; u && (t=who(L(u)))>=0; u &= ~L(u) )
					add_arcs(n+j*64+t,sink,1,indeg[j*64+t],0);
			if ( o_allele ) add_arcs(n,sink,0,indeg[0],0);
			add_arcs(sink,src,0,sumdeg,0);
			if ( mincost_circulation() == n ) puts("Y"); else puts("N");
		}
	}
	return 0;
}

