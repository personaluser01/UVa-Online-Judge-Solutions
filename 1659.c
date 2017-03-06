/*
 * 1659. Help Little Laura
 * TOPIC: mincost circulation
 * status: Accepted
 */
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#define tol 1e-9
#define N 0x200
#define MAXV N
#define MAXE (1<<17)
#define S(x) ((x)*(x))
#define xchg(x,y) (((x)==(y))||((x)^=(y),(y)^=(x),(x)^=(y)))
#define bubble (xchg(pos[heap[i]],pos[heap[j]]),xchg(heap[i],heap[j]))
#define oo (DBL_MAX-0x400)

double max( double x, double y ) {
	if ( x < y ) return y;
	return x;
}

double min( double x, double y ) {
	if ( x < y ) return x;
	return y;
}

int X,Y,n,deg[N],adj[N][N],last[N],next[MAXE],from[MAXE],to[MAXE],flow[MAXE],cap[MAXE],V,E,src,p[N],seen[N],yes;
double cost[MAXE],d[MAXV];

void add_arcs( int x, int y, int c, double w ) {
	int i = E++, j = E++;
	to[i] = y, cost[i] = w, flow[i] = 0, next[i] = last[x], last[x] = i, from[i] = x, cap[i] = c;
	to[j] = x, cost[j] = -w,flow[j] = 0, next[j] = last[y], last[y] = j, from[j] = y, cap[j] = 0;
}

int neg_cycle( int *t ) {
	int x,y,i,k;
	for ( seen[src] = ++yes, d[src] = 0, k = 0; k < V-1; ++k )
		for ( i = 0; i < E; ++i )
			if ( flow[i] < cap[i] && (seen[x=from[i]]==yes && (seen[y=to[i]]!=yes || d[y]>d[x]+cost[i])) ) 
				d[y]=d[x]+cost[p[y]=i], seen[y] = yes;
	for ( i = 0; i < E; ++i )
		if ( flow[i] < cap[i] && (seen[x=from[i]]==yes && (seen[y=to[i]]!=yes || d[y]>d[x]+cost[i])) ) {
			d[*t=y]=d[x]+cost[p[y]=i], seen[y] = yes;
			return 1;
		}
	return 0;
}

void cancel_cycle( int t ) {
	int x,y,i,j,k,v[N],*ptr=v;
	double df = +oo;
	for ( seen[t]=++yes, x=from[p[t]]; seen[x]!=yes; seen[x]=yes, x=from[p[x]] );
	for ( y=x,x=from[k=p[y]],df=cap[k]-flow[k]; x!=y; k=p[x], df=min(df,cap[k]-flow[k]), x=from[k] );
	assert( x == y );
	assert( df > 0 );
	for ( x=from[k=p[y]], flow[k]+=df, flow[k^1]-=df; x != y; k = p[x], flow[k] += df, flow[k^1] -= df, x = from[k] );
}

double mincost_circulation() {
	int t;
	double val = 0;
	for(;neg_cycle(&t);cancel_cycle(t));
	for ( t = 0; t < E; val += flow[t]*cost[t], ++t );
	return val;
}

int main() {
	int i,j,k,l,t,cs = 0;
	double xx[N],yy[N],w;
#ifndef ONLINE_JUDGE
	freopen("c.txt","r",stdin);
#endif
	for ( ;1 == scanf("%d",&n) && n > 0 && 2 == scanf("%d %d",&X,&Y) && printf("Case %d: ",++cs); ) {
		for ( i=0; i<n; ++i )
			for ( last[i]=-1,deg[i]=0, scanf("%lf %lf",&xx[i],&yy[i]); 1==scanf("%d",&k) && k>0; adj[i][deg[i]++]=--k );
		for ( last[src=n]=-1,V=n+1,E=0,i=0; i<n; add_arcs(src,i++,1,0) ) 
			for ( l=0; l<deg[i]; ++l ) 
				j=adj[i][l], w=(sqrt(S(xx[i]-xx[j])+S(yy[i]-yy[j])))*X-Y, add_arcs(i,j,1,-w);
		printf("%.2lf\n",-mincost_circulation()/2+tol);
	}
	return 0;
}

