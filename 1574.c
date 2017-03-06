/*
 * 1574. Surely You Congest
 * TOPIC: maxflow
 * status: Accepted
 */
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define xchg(x,y) (((x)==(y))||((x)^=(y),(y)^=(x),(x)^=(y)))
#define MAXV (1<<16)
#define MAXN MAXV
#define MAXE (1<<21)
#define oo   (1<<29)
#define bubble (xchg(heap[i],heap[j]),xchg(pos[heap[i]],pos[heap[j]]))
enum { S, T };
int min( int x, int y ) { if ( x < y ) return x; return y; }

int to[MAXE],cap[MAXE],last[MAXN],flow[MAXE],m,n,cc,V,E,commuter[0x400],next[MAXE],**adj,**w,
	heap[MAXV],pos[MAXV],d[MAXV],cost[MAXE],deg[MAXV],cnt,src,sink,seen[MAXV],yes,D[MAXV],
	*head,*tail,q[MAXV];

void add_arc( int x, int y, int ca, int co ) {
	int i = E++, j = E++;
	to[i] = y, next[i] = last[x], last[x] = i, cap[i] = ca, cost[i] = co;
	to[j] = x, next[j] = last[y], last[y] = j, cap[j] = 0,  cost[j] = co;
	flow[i] = flow[j] = 0;
}

void heap_push( int x, int *d ) {
	int i,j;
	if ( pos[x] < 0 )
		pos[heap[cnt]=x]=cnt, ++cnt;
	for ( j = pos[x]; j && d[heap[i=(j-1)/2]] > d[heap[j]]; bubble, j = i );
}

int pop( int *d ) {
	int i,j,x = *heap;
	if ( pos[*heap]=-1,--cnt ) 
		pos[*heap=heap[cnt]]=0;
	for ( j=0; (i=j,j<<=1,++j)<cnt; bubble ) {
		if ( j<cnt-1 && d[heap[j]]>d[heap[j+1]] ) ++j;
		if ( d[heap[i]]<=d[heap[j]] ) break ;
	}
	return x;
}

typedef struct { int x,d; } vx;
vx e[0x400];

int cmp( const void *a, const void *b ) {
	vx *p = (vx *)a,
	   *q = (vx *)b;
	if ( p->d == q->d )
		return p->x-q->x;
	if ( p->d < q->d ) return -1;
	return 1;
}

int dfs( int x, int df ) {
	int i,y,dt;
	if ( x == sink )
		return df;
	if ( seen[x] == yes || !df ) return 0;
	for ( seen[x] = yes, i = last[x]; i >= 0; i = next[i] )
		if ( flow[i] < cap[i] && d[y=to[i]] < +oo && d[y]+1 == d[x] )
			if ( (dt = dfs(y,min(df,cap[i]-flow[i]))) > 0 ) {
				flow[i] += dt, flow[i^1] -= dt;
				return dt;
			}
	return 0;
}

int bfs( int sink ) {
	int x,y,i;
	for ( head=tail=q, d[sink]=0, seen[*tail++=sink]=++yes; head<tail; )
		for ( i=last[x=*head++]; i>=0; i=next[i] )
			if ( flow[i^1]<cap[i^1] && (seen[y=to[i]]!=yes||d[y]>d[x]+1) ) 
				seen[*tail++=y]=yes,d[y]=d[x]+1;
	return seen[src]==yes;
}

int maxflow() {
	int t,res = 0;
	for (;bfs(0);) for ( ++yes; (t=dfs(src,+oo)); res += t );
	return res;
}

int main() {
	int i,j,k,l,t,x,y,ans;
#ifndef ONLINE_JUDGE
	freopen("c.txt","r",stdin);
#endif
	for (;3==scanf("%d %d %d",&n,&m,&cc)&&(n||m||cc);) {
		for ( E=0, i=0; i<n; deg[i]=0, last[i++]=-1 );
		for ( k = 0; k < m; ++k ) {
			scanf("%d %d %d",&x,&y,&l), --x, --y;
			i=E++,to[i]=y,next[i]=last[x],last[x]=i,cost[i]=l,++deg[x];
			j=E++,to[j]=x,next[j]=last[y],last[y]=j,cost[j]=l,++deg[y];
		}
		for ( i = 0; i < cc; scanf("%d",commuter+i), --commuter[i++] );
		/* shortest paths from 0 to all other vertices */
		for ( i = 0; i < n; d[i] = +oo, pos[i++] = -1 );
		for ( cnt=0,d[0]=0,heap_push(0,d); cnt; )
			for ( i=last[x=pop(d)]; i>=0; i=next[i] ) 
				if ( d[y=to[i]]>d[x]+cost[i] )
					d[y]=d[x]+cost[i],heap_push(y,d);
		for ( x = 0; x < n; D[x] = d[x], ++x );
		for ( i = 0; i < cc; ++i )
			e[i].d=d[e[i].x=commuter[i]];
		/* temporarily store all the graph info */
		adj = (int **)malloc((n+2)*sizeof *adj);
		w = (int **)malloc((n+2)*sizeof *w);
		for ( x = 0; x < n; last[x++] = -1 ) {
			w[x] = (int *)malloc((deg[x]+1)*sizeof *w[x]);
			adj[x]=(int *)malloc((deg[x]+1)*sizeof *adj[x]);
			assert( D[x] < +oo );
			for ( deg[x]=0, i=last[x]; i>=0; i=next[i] )
				adj[x][deg[x]]=to[i], w[x][deg[x]++]=cost[i];
		}
		for ( E = 0, src = n, V = n+1, x = src; x < V; last[x++] = -1 );
		adj[src] = (int *)malloc((cc+2)*sizeof *adj[src]);
		w[src] = (int *)malloc((cc+2)*sizeof *adj[src]);
		/* shortest paths from source (i.e. src) to all the other vertices */
		for ( ans = 0, qsort(e,cc,sizeof *e,cmp), i = 0; i < cc; i = j ) {
			for ( j = i+1; j < cc && e[j].d == e[i].d; ++j );
			for ( deg[src] = 0, l = i; l < j; ++l ) 
				adj[src][deg[src]] = e[l].x, w[src][deg[src]++] = 1;
			for ( cnt = 0, k = 0; k < V; pos[k++] = -1, d[k-1] = +oo );
			for ( d[src] = 0, heap_push(src,d); cnt; )
				for ( x = pop(d), l = 0; l < deg[x]; ++l )
					if ( d[y=adj[x][l]] > d[x]+w[x][l] )
						d[y] = d[x]+w[x][l], heap_push(y,d);
			/* build a network consisting of those edges only that lie on a shortest path */
			assert( d[0] < +oo );
			for ( l = i; l < j; ++l ) add_arc(src,e[l].x,1,1);
			for ( x = 0; x < n; ++x )
				for ( l = 0; l < deg[x]; ++l ) {
					y = adj[x][l];
					if ( d[x] < +oo && D[y] < +oo && d[x]+w[x][l]+D[y] == d[0] )
						add_arc(x,y,1,1);
				}
			ans += maxflow();
			for ( E = 0, x = 0; x < V; last[x] = -1, pos[x++] = -1 );
		}
		for ( i = 0; i < n; free(adj[i]), free(w[i]), ++i );
		free(adj), free(w);
		printf("%d\n",ans);
	}
	return 0;
};


