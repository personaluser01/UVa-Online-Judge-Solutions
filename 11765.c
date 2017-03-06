/*
 * 11765. Component Placement
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <limits.h>
#include <float.h>
#define N 256
#define M (N*N*4)
#define oo 0xfffffffful
enum { BOTTOM = -1, TOP = 1, BOTH = 0 };

int min(int x,int y){return x<y?x:y;}

int n,up[N],down[N],indicator[N],ts,
	a[N*N/2],b[N*N/2],c[N*N/2],mm,seen[N],
	next[M],last[N],to[M],cap[M],flow[M],
	is_source[N],is_sink[N],yes,src,sink,
	card_src,card_sink,E,q[M],*head,*tail;
unsigned int d[N];

void add_arcs( int x, int y, int c ) {
	int i,j;
	to[i=E++]=y,cap[i]=c,flow[i]=0;
	to[j=E++]=x,cap[j]=0,flow[j]=0;
	next[i] = last[x], last[x] = i;
	next[j] = last[y], last[y] = j;
}

int bfs() {
	int i,x,y;
	for (x=src;x<=sink;d[x++]=+oo);
	for (head=tail=q,d[*tail++=sink]=0;head<tail;)
		for (i=last[x=*head++];i>=0;i=next[i])
			if (d[y=to[i]]>d[x]+1)
				if (cap[i^1]>flow[i^1])
					d[*tail++=y]=d[x]+1;
	return d[src]<+oo;
}

int dfs( int x, int df ) {
	int i,y,w;
	if (x==sink)
		return df;
	for (seen[x]=yes,i=last[x];i>=0;i=next[i])
		if ( d[y = to[i]] < +oo && d[y]+1==d[x] && seen[y]!=yes )
			if ( cap[i] > flow[i] ) {
				w = dfs(y,min(cap[i]-flow[i],df));
				if ( !w ) continue ;
				flow[i] += w, flow[i^1] -= w;
				return w;
			}
	return 0;
}

int main() {
	int i,j,k;
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	for ( scanf("%d",&ts); ts-- && 2 == scanf("%d %d",&n,&k); printf("%d\n",k) ) {
		for ( i = 1; i <= n; ++i ) scanf("%d",up+i);
		for ( i = 1; i <= n; ++i ) scanf("%d",down+i);
		for ( i = 1; i <= n; ++i ) scanf("%d",indicator+i);
		src = 0, sink = n+1, E = 0;
		for ( i = src; i <= sink; ++i ) last[i] = -1;
		for ( mm = k, k = 1; k <= mm; ++k ) 
			if ( 3 == scanf("%d %d %d",a+k,b+k,c+k) && indicator[a[k]] && indicator[b[k]] )
				if ( indicator[a[k]] != indicator[b[k]] ) 
					add_arcs(src,sink,c[k]);
		for ( k = 1; k <= mm; ++k ) {
			if ( indicator[a[k]] == BOTH && indicator[b[k]] == BOTH ) {
				add_arcs(a[k],b[k],c[k]), add_arcs(b[k],a[k],c[k]);
				continue ;
			}
			if ( indicator[a[k]] == BOTH && indicator[b[k]] != BOTH ) {
				(indicator[b[k]]==TOP)?add_arcs(src,a[k],c[k]):add_arcs(a[k],sink,c[k]);
				continue ;
			}
			if ( indicator[b[k]] == BOTH && indicator[a[k]] != BOTH ) {
				(indicator[a[k]]==TOP)?add_arcs(src,b[k],c[k]):add_arcs(b[k],sink,c[k]);
				continue ;
			}
		}
		for ( i = 1; i <= n; ++i )
			if ( indicator[i] == BOTH )
				add_arcs(src,i,down[i]), add_arcs(i,sink,up[i]);
		for ( k = 0, i = 1; i <= n; ++i )
			if ( indicator[i] )
				k += (indicator[i]==TOP?up[i]:down[i]);
		for(;bfs();)for(++yes;i=dfs(src,(1<<29));k+=i);
	}
	return 0;
}

