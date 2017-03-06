/*
 * 1006. Fixed Partition Memory Management
 * TOPIC: mincost maxflow
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define tol 1e-12
#define MAXV (1<<10)
#define MAXE (1<<20)
#define xchg(x,y) (((x)==(y))||((x)^=(y),(y)^=(x),(x)^=(y)))
#define bubble (xchg(pos[heap[i]],pos[heap[j]]),xchg(heap[i],heap[j]))
#define oo (1L<<29)
#define N 0x40
#define K 0x10
typedef int i64;

i64 min( i64 x, i64 y ) { if ( x < y ) return x; return y; }

int m,n,E,V,to[MAXE],next[MAXE],last[MAXV],
	sink,src,heap[MAXV<<1],pos[MAXV],cnt,parent[MAXV];
i64 p[MAXV],d[MAXV],cap[MAXE],cost[MAXE],flow[MAXE];

void add_arcs( int x, int y, i64 c, i64 w ) {
	int i = E++, j = E++;
	to[i] = y, next[i] = last[x], last[x] = i, cap[i] = c, cost[i] =  w;
	to[j] = x, next[j] = last[y], last[y] = j, cap[j] = 0, cost[j] = -w;
	flow[i] = flow[j] = 0;
}

void push( int x ) {
	int i,j;
	if ( pos[x] < 0 )
		pos[heap[cnt] = x] = cnt, ++cnt;
	for ( j = pos[x]; j && d[heap[i=(j-1)>>1]] > d[heap[j]]; bubble, j = i );
}

int pop() {
	int i,j,x=*heap;
	if ( cnt+=(pos[x]=-1) )
		pos[*heap=heap[cnt]]=0;
	for ( j=0; (i=j,j<<=1,++j)<cnt; bubble ) {
		if ( j<cnt-1 && d[heap[j+1]]<d[heap[j]] ) ++j;
		if ( d[heap[i]]<=d[heap[j]] ) break ;
	}
	return x;
}

int dijkstra() {
	int x,y,i;
	for ( x=0; x<V; pos[x]=-1,d[x++]=+oo );
	for ( parent[src]=-1, d[src]=0, cnt=0, push(src); cnt; )
		for ( i=last[x=pop()]; i>=0 && (y=to[i])>=0; i=next[i] )
			if ( cap[i]>flow[i] && d[y]>d[x]+p[x]+cost[i]-p[y] )
				d[y]=d[x]+p[x]+cost[i]-p[y],push(y),parent[y]=i;
	for ( x = 0; x < V; ++x )
		if ( d[x]<+oo ) p[x]+=d[x];
	return d[sink]<+oo;
}

void mcmf() {
	int i;
	for ( i = 0; i < V; p[i++] = 0 );
	for (;dijkstra();) 
		for(i=parent[sink];i!=-1;++flow[i],--flow[i^1],i=parent[to[i^1]]);
}

typedef struct { int partition_id,slot,pid,t; } cell ;

int cmp( const void *a, const void *b ) {
	cell *x = (cell *)a,
		 *y = (cell *)b;
	if ( x->partition_id==y->partition_id ) 
		return x->slot-y->slot;
	return x->partition_id-y->partition_id;
}

cell c[MAXE];
int L,left[N],right[N],which[N];

int main() {
	int i,j,k,l,t,tm[N][K],sz[N][K],kk[N],psize[K],x,y,cs = 0,pref,bin[K];
	double C;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for (;2==scanf("%d %d",&m,&n)&&(m||n);) {
		for ( i=0; i<m; bin[i]=0, scanf("%d",&psize[i++]) );
		for ( i=0; i<n; sz[i][kk[i]]=(1<<29), ++i )
			for ( scanf("%d",kk+i), j=0; j<kk[i]; scanf("%d %d",sz[i]+j,tm[i]+j), ++j );
		for ( E=0, src=n+m*n, sink=src+1, V=sink+1, i=0; i<V; last[i++]=-1 );
		for ( i=0; i<n; add_arcs(src,i++,1,0) );
		for ( i=0; i<n; ++i )
			for ( l=0; l<kk[i]; ++l )
				for ( j=0; j<m; ++j )
					if ( sz[i][l]<=psize[j] && psize[j]<sz[i][l+1] )
						for ( k=0; k<n; ++k )
							add_arcs(i,n+j*n+k,1,(k+1)*tm[i][l]);
		for ( j = 0; j < m; ++j )
			for ( k = 0; k < n; add_arcs(n+j*n+k,sink,1,0), ++k );
		for ( C = 0, mcmf(), i = 0; i < E; ++i )
			if ( flow[i] == cap[i] && 0 <= to[i^1] && to[i^1] < n )
				if ( n <= to[i] && to[i] < n+m*n ) 
					++bin[(to[i]-n)/n];
		for ( L = 0, i = 0; i < E; ++i )
			if ( flow[i] == cap[i] && 0 <= to[i^1] && to[i^1] < n )
				if ( n <= to[i] && to[i] < n+m*n ) {
					C += flow[i]*cost[i];
					x=to[i^1], y=(to[i]-n)/n, k=(to[i]-n-y*n);
					c[L].pid=x, c[L].partition_id=y, c[L].t=cost[i]/(k+1), c[L++].slot=bin[y]-k;
				}
		assert( L == n );
		for ( qsort(c,L,sizeof *c,cmp), i=0; i<L; i=j ) {
			for ( j=i+1; j<L && c[j].partition_id==c[i].partition_id; ++j );
			for ( pref=0,l=c[i].partition_id, k=i; k<j; ++k ) 
				which[t=c[k].pid]=l,left[t]=pref,(right[t]=(pref+=c[k].t));
		}
		printf("Case %d\n",++cs), printf("Average turnaround time = %.2lf\n",C/n+tol);
		for ( i = 0; i < n; printf("Program %d runs in region %d from %d to %d\n",1+i,1+which[i],left[i],right[i]), ++i );
		putchar('\n');
	}
	return 0;
}

