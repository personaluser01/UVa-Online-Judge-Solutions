/*
 * 11167. Monkeys in the Emei Mountain
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <limits.h>
#define N 0x80
#define T 50100
#define Q (1UL<<22)
#define oo 0xfffffffful

int min( int x, int y ) { return x < y ? x:y; }
int n,m,seen[Q],yes,E,V,a[N],b[N],litres[N],is[T],
	src,sink,q[N+T],*head,*tail,next[Q],last[N+T],
	to[Q],cap[Q],flow[Q],filled[N],
	name[T],out[T],*ptr,iname[N+T],
	A[T],B[T];
unsigned int d[Q];

void send_flow( int i, int t ) {
	int j,k;
	for ( j = last[src]; j >= 0 && to[j] != i; j = next[j] );
	++flow[j], --flow[j^1];
	for ( j = last[i]; j >= 0 && to[j] != name[t]; j = next[j] );
	++flow[j], --flow[j^1];
	for ( j = last[name[t]]; j >= 0 && to[j] != sink; j = next[j] );
	++flow[j], --flow[j^1];
}

void add_arcs( int x, int y, int c ) {
	int i,j;
	(i = E++); (j = E++);
	to[i] = y, cap[i] = c, flow[i] = 0;
	next[i] = last[x], last[x] = i;
	to[j] = x, cap[j] = 0, flow[j] = 0;
	next[j] = last[y], last[y] = j;
	assert( (i^1) == j );
	assert( (j^1) == i );
}

int bfs() {
	int i,j,k,x,y;
	for ( x = 0; x < V; ++x ) d[x] = +oo;
	for(head=tail=q,d[*tail++=sink]=0;head<tail;)
		for(i=last[x=*head++];i>=0;i=next[i])
			if(d[y=to[i]]>d[x]+1)
				if(cap[i^1]>flow[i^1])
					d[*tail++=y]=d[x]+1;
	return d[src]<+oo;
}

int dfs( int x, int df ) {
	int i,k,y,w;
	if ( x == sink )
		return df;
	for (seen[x]=yes, i = last[x]; i >= 0; i = next[i] )
		if ( cap[i]>flow[i] )
			if (d[y=to[i]]<+oo && d[y]+1==d[x]&&seen[y]!=yes) {
				w = dfs(y,min(df,cap[i]-flow[i]));
				if ( !w )
					continue ;
				assert( w > 0 );
				flow[i] += w, flow[i^1] -= w;
				return w;
			}
	return 0;
}

int cmp( const void *a, const void *b ) {
	int *x = (int *)a,
		*y = (int *)b;
	if ( *x == *y )
		return 0;
	return *x < *y ? -1 : 1;
}

int main() {
	int i,j,k,l,t,x,y,cs = 0,Total,w,S;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for (;2 == scanf("%d %d",&n,&m) && n > 0 && printf("Case %d: ",++cs);) {
		src = 0, E = 0, ++yes, V = n+1;
		for ( i = 0; i <= n+T; ++i ) last[i] = -1;
		for ( Total = 0, i = 1; i <= n; ++i ) {
			scanf("%d %d %d",litres+i,a+i,b+i);
			Total += litres[i];
			if ( !litres[i] ) continue ;
			add_arcs(src,i,litres[i]);
			for ( j = a[i]; j <= b[i]; ++j )
				is[j] = yes;
		}
		for ( j = 1; j < T; ++j )
			if ( is[j] == yes )
				iname[name[j] = V++] = j;
		for ( sink = V++, i = 1; i <= n; ++i )
			for ( j = a[i]; litres[i] && j < b[i]; ++j )
				add_arcs(i,name[j],1);
		for ( j = 1; j < T; ++j )
			if ( is[j] == yes ) add_arcs(name[j],sink,m);
		for(i=1;i<=n;++i)filled[i]=0;
		for ( S = 0, t = 0; t <= 50000 && S < Total; ++t )
			if ( is[t] == yes )
				for ( l = 0; l < m && S < Total; ++l ) {
					for ( w = (1<<29), i = 1; i <= n; ++i )
						if ( filled[i] < litres[i] && a[i] <= t && t < b[i] && b[i] < w )
							w = b[i], k = i;
					if ( w < (1<<29) ) {
						++filled[k];
						send_flow(k,t), ++S;
					}
				}
		goto nx;
		for(;bfs();) 
			for(++yes;dfs(src,(1<<29)););
		nx: 
		for ( k = 0, i = 0; i < E; ++i )
			if ( to[i] == sink )
				k += flow[i];
		if ( k != Total ) { puts("No"); continue ; }
		puts("Yes");
		for ( x = 1; x <= n; ++x ) {
			if (!litres[x]) {
				puts("0");
				continue ;
			}
			for ( ptr = out, i = last[x]; i >= 0; i = next[i] ) 
				if ( flow[i] > 0 && 1+n <= (y = to[i]) && y < sink ) 
					*ptr++ = iname[y];
			qsort(out,ptr-out,sizeof *out,cmp);
			for ( m = 0, A[++m] = out[0], B[m]=A[m]+1,i = 1; i < ptr-out; i = j+1 ) {
				for ( k = 1, j = i; j < ptr-out && out[j] == A[m]+k; ++B[m], ++k, ++j );
				if ( j < ptr-out ) A[++m] = out[j], B[m]=A[m]+1;
			}
			for ( printf("%d",m), i = 1; i <= m; ++i )
				printf(" (%d,%d)",A[i],B[i]);
			putchar('\n');
		}
	}
	return 0;
}
