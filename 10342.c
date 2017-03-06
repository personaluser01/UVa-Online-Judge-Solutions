/*
 * 10342. Always Late
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
#define N 0x80
#define xchg(x,y) (((x)==(y))||((x)^=(y),(y)^=(x),(x)^=(y)))
#define bubble (xchg(pos[heap[i]],pos[heap[j]]),xchg(heap[i],heap[j]))
#define enc(x,t) ((t)|((x)<<1))
#define oo 0xfffffffful

int n,E,to[N*N],w[N*N],next[N*N],last[N],
	pos[N*2],heap[4*N],cnt;
unsigned int d[2*N],dist[2*N];

void add_edge( int x, int y, int k ) {
	int i = E++, j = E++;
	to[i] = y, w[i] = k, to[j] = x, w[j] = k;
	next[i] = last[x], last[x] = i, next[j] = last[y], last[y] = j;
}

void push( int u, unsigned int *d ) {
	int i,j;
	if ( pos[u] < 0 ) pos[heap[cnt] = u] = cnt, ++cnt;
	for ( j = pos[u]; j && d[heap[i = (j-1)>>1]] >= d[heap[j]]; bubble, j = i );
}

int pop( unsigned int *d ) {
	int u = *heap,i,j;
	pos[*heap] = -1;
	if ( --cnt )
		pos[heap[0] = heap[cnt]] = 0;
	for(j = 0; (i = j, j <<= 1, ++j) <= cnt-1; bubble ) {
		if ( j < cnt-1 && d[heap[j+1]] < d[heap[j]] ) ++j;
		if ( d[heap[i]] <= d[heap[j]] ) break ;
	}
	return u;
}

unsigned int sssp( int src, int dst ) {
	int i,j,k,t,x,y,u,v;
	unsigned int dw;

	for ( x = 0; x < n; ++x )
		dist[x]=+oo, pos[x]=-1;

	for ( cnt = 0, dist[src] = 0, push(src,dist); cnt;)
		for ( i = last[x = pop(dist)]; i >= 0; i = next[i] )
			if (dist[y=to[i]]>dist[x]+w[i])
				dist[y] = dist[x]+w[i], push(y,dist);

	for ( x = 0; x < n; ++x )
		for ( t = 0; t <= 1; ++t )
			d[enc(x,t)] = +oo, pos[enc(x,t)] = -1;
	for ( cnt = 0, d[enc(src,0)] = 0, push(enc(src,0),d); cnt;)
		for ( i = last[x=(u=pop(d))>>1], t = (u&1); i >= 0; i = next[i] ) {
			y = to[i], dw = w[i];
			if ( d[v=enc(y,t)]>d[u]+dw ) d[v]=d[u]+dw, push(v,d);
			if ( !t && d[v=enc(y,1)]>d[u]+dw && d[u]+dw>dist[y] )
				d[v] = d[u]+dw, push(v,d);
		}
	return d[enc(dst,1)];
}

int main() {
	int i,j,k,cs = 0,roads,l,t;
	unsigned int dw;
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	for ( ;1 == scanf("%d",&n) && printf("Set #%d\n",++cs); ) {
		for ( E = 0, i = 0; i < n; ++i ) last[i] = -1;
		for ( scanf("%d",&roads), l = 0; l < roads; ++l ) 
			scanf("%d %d %d",&i,&j,&k), add_edge(i,j,k);
		for ( scanf("%d",&roads); roads-- && 2 == scanf("%d %d",&i,&j);\
			(dw=sssp(i,j))==+oo?(puts("?")):(printf("%u\n",dw)) );
	}
	return 0;
}
