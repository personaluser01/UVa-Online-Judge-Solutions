/*
 * 10740. Not The Best
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
#define K 10
#define N 0x80
#define MAXV (0x400*K)
#define M(k) ((1ULL<<(k))-1ULL)
#define oo 0xfffffffful
#define xchg(x,y) (((x)==(y))||((x)^=(y),(y)^=(x),(x)^=(y)))
#define bubble (xchg(pos[heap[i]],pos[heap[j]]),xchg(heap[i],heap[j]))

int V,pos[MAXV],cnt,n,last[N],m,next[0x400],E,to[0x400];
unsigned int d[MAXV],heap[MAXV*2],w[0x400];
unsigned char c[N],h[MAXV];

void push( unsigned int u ) {
	int i,j;
	if ( pos[u] < 0 ) pos[heap[cnt] = u] = cnt, ++cnt;
	for ( j = pos[u]; j && d[heap[i=(j-1)>>1]]>d[heap[j]]; bubble, j = i );
}

unsigned int
pop() {
	unsigned int u = *heap;
	int i,j;
	if ( --cnt )
		pos[heap[0] = heap[cnt]] = 0;
	for ( j = 0; (i = j, j <<= 1, ++j) <= cnt-1; bubble ) {
		if ( j < cnt-1 && d[heap[j+1]] <= d[heap[j]] ) ++j;
		if ( d[heap[i]] <= d[heap[j]] ) break ;
	}
	return u;
}

void add_arc( int x, int y, int k ) {
	int i = E++;
	to[i] = y, w[i] = k, next[i] = last[x], last[x] = i;
}

unsigned int sssp( int src, int dst ) {
	int i,j,k,x,y,t;
	unsigned int u,v,dw,W=+oo;
	memset(c,0,sizeof(c));
	V = 0, h[V++] = src, pos[V-1] = -1;
	for ( d[V-1] = cnt = 0, push(V-1); cnt; ) {
		i = last[x = h[u = pop()]], ++c[x];
		if ( dst == x && c[x] == m ) { W = d[u]; break ; }
		if ( c[x] > m ) continue ;
		for (;i >= 0; i = next[i] ) {
			h[v = V++] = to[i], dw = w[i], pos[v] = -1;
			d[v] = d[u]+dw, push(v);
		}
	}
	return W;
}

int main() {
	int i,j,k,l,t,edges,src,dst;
	unsigned int u;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for(;2 == scanf("%d %d",&n,&edges) && (n||edges); ) {
		scanf("%d %d %d",&src,&dst,&m), --src, --dst;
		for ( i = 0; i < n; ++i ) last[i] = -1;
		for ( E = 0, l = 0; l < edges; ++l ) 
			scanf("%d %d %d",&i,&j,&k), add_arc(--i,--j,k);
		printf("%d\n",(u = sssp(src,dst))<+oo?(int)u:-1);
	}
	return 0;
}

