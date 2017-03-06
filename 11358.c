/*
 * 11358. Faster Processing Facility
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
#define N 0x40
#define T 10100
#define Q (N*N*8)
#define MAXV (N+N+N)
int min( int x, int y ) { return x < y ? x : y; }
int max( int x, int y ) { return x > y ? x : y; }

int m,n,src,sink,V,is[T],yes,name[T],iname[MAXV],
	a[N],b[N],v[T],seen[MAXV],to[Q],demand[N],
	q[MAXV],*head,*tail,E,cap[Q],next[Q],last[MAXV],
	visited[MAXV],indeed;
unsigned int d[MAXV];

int dfs( int x, int df ) {
	int i,y,w;
	if ( x == sink )
		return df;
	for ( seen[x] = yes, i = last[x]; i >= 0; i = next[i] )
		if ( cap[i] && seen[y = to[i]] != yes && visited[y] == indeed && d[y]+1 == d[x] )
			if ( w = dfs(y,min(df,cap[i])) ) {
				cap[i] -= w, cap[i^1] += w;
				return w;
			}
	return 0;
}

int bfs() {
	int i,j,x,y;
	for (visited[sink]=++indeed,head=tail=q,d[*tail++=sink]=0;head<tail;)
		for(i=last[x=*head++];i>=0;i=next[i])
			if (cap[i^1]&&visited[y=to[i]]!=indeed)
				visited[y]=indeed,d[*tail++=y]=d[x]+1;
	return visited[src]==indeed;
}

void add_arcs( int x, int y, int c ) {
	int i = E++, j = E++;
	cap[i] = c, to[i] = y, next[i] = last[x], last[x] = i;
	cap[j] = 0, to[j] = x, next[j] = last[y], last[y] = j;
}

int main() {
	int i,j,k,cs,Tot;
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	for ( scanf("%d",&cs); cs-- && ++yes; ) {
		scanf("%d %d",&m,&n), Tot = E = src = 0;
		for ( i = 0; i < MAXV; ++i ) last[i] = -1;
		for ( V = n+1, i = 1; i <= n; ++i ) {
			scanf("%d %d %d",a+i,demand+i,b+i);
			if ( !(k = demand[i]) ) continue ;
			is[a[i]] = is[b[i]] = yes;
			add_arcs(src,i,k), Tot += k;
		}
		for ( i = 0; i < T; ++i )
			if ( is[i] == yes )
				iname[name[i] = V++] = i;
		for ( sink = V++, i = 1; i <= n; ++i )
			if ( demand[i] )
				for ( j = name[a[i]]; j+1 < V-1 && iname[j+1] <= b[i]; ++j )
					add_arcs(i,j,iname[j+1]-iname[j]);
		for ( j = n+1; j+1 < V-1; ++j )
			add_arcs(j,sink,(iname[j+1]-iname[j])*m);
		for(;bfs();)for(++yes;i=dfs(src,(1<<29));Tot-=i);
		puts((!Tot)?"FEASIBLE":"NO WAY");
	}
	return 0;
}
