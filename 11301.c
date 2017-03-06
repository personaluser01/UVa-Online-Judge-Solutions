/*
 * 11301. Great Wall of China
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <limits.h>
#include <float.h>
#define N 0x400
#define M 6
#define vc(x,y) (1<=(x) && (x)<=m && 1<=(y) && (y)<=n)
#define enc(x,y,t) ((t) | ((x)<<1) | ((y)<<4))
#define BIT(k) (1UL << (k))
#define MASK(k) (BIT(k)-1UL)
#define MAXV (1 << 14)
#define MAXE (8*MAXV)
#define xchg(x,y) (((x)==(y))||((x)^=(y),(y)^=(x),(x)^=(y)))
#define bubble (xchg(heap[i],heap[j]),xchg(pos[heap[i]],pos[heap[j]]))
enum{ IN, OUT };

int n,m=5,d[MAXV],E,V,src,sink,heap[2*MAXV],pos[MAXV],cnt,
	dx[] = {-1,0,1,0},
	dy[] = {0,1,0,-1},
	last[MAXV],next[MAXE],to[MAXE],cost[MAXE],cap[MAXE],flow[MAXE],pi[MAXV],
	seen[MAXV],yes,inq[MAXV],indeed,vec[MAXV],out[MAXV],*ptr,parent[MAXV];
char g[M][N];

void push( int x ) {
	int i,j;
	if ( inq[x] != indeed ) pos[heap[cnt] = x] = cnt, ++cnt;
	inq[x] = indeed;
	for ( j = pos[x]; j && d[heap[i=(j-1)>>1]] > d[heap[j]]; bubble, j = i );
}

int pop() {
	int i,j,r = *heap;
	inq[r] = 0;
	if ( --cnt ) pos[heap[0] = heap[cnt]] = 0;
	for ( j = 0; (i = j, j <<= 1, ++j) < cnt;  bubble ) {
		if ( j < cnt-1 && d[heap[j+1]] < d[heap[j]] ) ++j;
		if ( d[heap[i]] <= d[heap[j]] ) break ;
	}
	return r;
}

void add_arcs( int x, int y, int c, int w ) {
	int i,j;
	if ( seen[x] != yes ) seen[x] = yes, last[x] = -1;
	if ( seen[y] != yes ) seen[y] = yes, last[y] = -1;
	i = E++, j = E++;
	to[i] = y, cap[i] = c, cost[i] = w, next[i] = last[x], last[x] = i;
	to[j] = x, cap[j] = 0, cost[j] = (1 << 29), next[j] = last[y], last[y] = j;
	flow[i] = flow[j] = 0;
}

int dijkstra() {
	int x,y,i,j,k;

	cnt = 0, ++indeed, seen[src] = ++yes, parent[src] = -1, d[src] = 0;
	for ( ptr = out, push(*ptr++ = src); cnt;)
		for ( i = last[x = pop()]; i >= 0; i = next[i] ) {
			y = to[i];
			assert( to[i^1] == x );
			if ( flow[i^1] > 0 ) {
				if ( seen[y] != yes || d[y] > d[x]+pi[x]-pi[y]-cost[i^1] ) {
					if ( seen[y] != yes ) *ptr++ = y;
					seen[y] = yes, d[y] = d[x]+pi[x]-pi[y]-cost[i^1], parent[y] = i, push(y);
				}
			}
			if ( flow[i] < cap[i] ) {
				if ( seen[y] != yes || d[y] > d[x]+pi[x]-pi[y]+cost[i] ) {
					if ( seen[y] != yes ) *ptr++ = y;
					seen[y] = yes, d[y] = d[x]+pi[x]-pi[y]+cost[i], parent[y] = i, push(y);
				}
			}
		}
	while ( ptr > out ) x = *--ptr, pi[x] += d[x];
	return seen[sink] == yes;
}

void mcmf() {
	int i,j,k,x,y,bot,Total = 0,weight = 0,res = 0;

	for ( i = 0; i < V; ++i ) pi[vec[i]] = 0;
	while ( dijkstra() ) {
		for ( i = parent[sink]; i >= 0; i = parent[to[i^1]] )
			++flow[i], --flow[i^1];
		if ( (++Total)==3 ) break ;
	}
	for ( res = 0, i = 0; i < V; ++i )
		if ( vec[i] != src && vec[i] != sink )
			if ( !(vec[i]&1) )
				for ( j = last[vec[i]]; j >= 0; j = next[j] )
					if ( flow[j] == cap[j] && flow[j] > 0 )
						res += flow[j]*cost[j];
	printf("%d\n",res);
}

int main() {
	int i,j,k,l,ni,nj;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	while ( 1 == scanf("%d",&n) && n > 0 && ++yes ) {
		for ( i = 1; i <= m; ++i )
			scanf("%s",g[i]+1);
		src = 0, V = 2+n*m*2, sink = enc(m+1,n,OUT), E = 0;
		for ( l = 0, vec[l++] = src, vec[l++] = sink, i = 1; i <= m; ++i ) {
			if ( g[i][1] == '@') 
				g[i][1] = '0', add_arcs(src,enc(i,1,IN),1,0);
			add_arcs(enc(i,n,OUT),sink,1,0);
		}
		for ( i = 1; i <= m; ++i )
			for ( j = 1; j <= n; ++j ) {
				add_arcs(vec[l++]=enc(i,j,IN),vec[l++]=enc(i,j,OUT),1,g[i][j]-'0');
				for ( k = 0; k < 4; ++k ) {
					ni = i+dx[k], nj = j+dy[k];
					if ( !vc(ni,nj) ) continue ;
					add_arcs(enc(i,j,OUT),enc(ni,nj,IN),1,0);
				}
			}
		assert( l == V );
		mcmf();
	}
	return 0;
}

