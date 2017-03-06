/*
 * 1078. Steam Roller
 * TOPIC: dijkstra, nontrivial states
 * status: Accepted
 */
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BIT(k) (1ULL<<(k))
#define MASK(k) (BIT(k)-1ULL)
#define SH 7
#define MAXV (BIT(SH+SH))
#define MAXE (8*MAXV)
#define vc(x,y) (0<=(x)&&(x)<m&&0<=(y)&&(y)<n)
#define Q (BIT(21))
#define xchg(x,y) (((x)==(y))||((x)^=(y),(y)^=(x),(x)^=(y)))
#define bubble (xchg(pos[heap[i]],pos[heap[j]]),xchg(heap[i],heap[j]))
#define enc(x,y) ((x)|((y)<<SH))
#define oo 0xfffffffful
#define S(t,dir,u) ((t)|((dir)<<2)|((u)<<4))
enum {DECC,ACC,FULL_SPEED};
typedef unsigned int state;

unsigned int d[Q];
int m,n,last[MAXV],to[MAXE],cost[MAXE],next[MAXE],E,V,pos[Q],cnt,
	dx[] = {-1,0,1,0},
	dy[] = {0,1,0,-1};
state heap[Q];

void add_arcs( int x, int y, int k ) {
	int i,j;
	if ( !k ) return ;
	i = E++, j = E++;
	to[i] = y, next[i] = last[x], last[x] = i, cost[i] = k;
	to[j] = x, next[j] = last[y], last[y] = j, cost[j] = k;
}

void push( state x ) {
	int i,j;
	if ( pos[x] < 0 )
		pos[heap[cnt]=x]=cnt, ++cnt;
	for ( j = pos[x]; j && d[heap[i=(j-1)>>1]] > d[heap[j]]; bubble, j = i );
}

state pop() {
	int i,j;
	state x = *heap;
	if ( cnt += (pos[x]=-1) )
		pos[*heap=heap[cnt]]=0;
	for ( j = 0; (i=j,j<<=1,++j) < cnt; bubble ) {
		if ( j < cnt-1 && d[heap[j+1]] < d[heap[j]] ) ++j;
		if ( d[heap[i]] <= d[heap[j]] ) break ;
	}
	return x;
}

int f( unsigned int u, unsigned int v ) {
	int x = (u&MASK(SH)), y = (u>>SH),
		nx = (v&MASK(SH)), ny = (v>>SH);
	switch ( nx-x ) {
		case -1: return 0;
		case 1: return 2;
		default: switch ( ny-y ) {
						case -1: return 3;
						default: return 1;
				 }
	}
}

unsigned int 
dijkstra( unsigned int src, unsigned int dst ) {
	int i,j,x,y,k,l,t,dir;
	unsigned int w = +oo;
	state u,v;

	for ( cnt=0, i=0; i<m; ++i )
		for ( j=0; j<n; ++j )
			for ( t=DECC; t<=FULL_SPEED; ++t )
				for ( dir=0; dir <= 3; ++dir )
					d[u=S(t,dir,enc(i,j))] = +oo, pos[u] = -1;
	for ( i = last[src]; i >= 0; i = next[i] ) 
		d[u=S(ACC,f(src,to[i]),to[i])]=cost[i]<<1, push(u), d[u=S(DECC,f(src,to[i]),to[i])]=cost[i]<<1, push(u);
	for(;cnt;)
		for ( i=last[(u=pop())>>4], t = (u&3ULL), dir = ((u>>2)&3ULL); i >= 0; i = next[i] )
			switch ( t ) {
				case DECC: if ( d[v=S(DECC,f(u>>4,to[i]),to[i])] > d[u]+(cost[i]<<1) )
								  d[v] = d[u]+(cost[i]<<1), push(v);
						   if ( d[v=S(ACC,f(u>>4,to[i]),to[i])] > d[u]+(cost[i]<<1) )
								  d[v] = d[u]+(cost[i]<<1), push(v);
						   continue ;
				case ACC:  if ( f(u>>4,to[i]) == dir && d[v=S(FULL_SPEED,dir,to[i])] > d[u]+cost[i] )
								  d[v] = d[u]+cost[i], push(v);
						   if ( f(u>>4,to[i]) == dir && d[v=S(DECC,dir,to[i])] > d[u]+(cost[i]<<1) )
								  d[v] = d[u]+(cost[i]<<1), push(v);
						   break ;
				default: if ( f(u>>4,to[i])==dir && d[v=S(FULL_SPEED,dir,to[i])]>d[u]+cost[i] )
									d[v] = d[u]+cost[i], push(v);
						 if ( f(u>>4,to[i])==dir && d[v=S(DECC,dir,to[i])]>d[u]+(cost[i]<<1) )
						 			d[v] = d[u]+(cost[i]<<1), push(v);
						 break ;
			}
	for ( dir = 0; dir < 4; ++dir )
		if ( w > d[u=S(DECC,dir,dst)] ) w = d[u];
	return w;
}

int main() {
	int i,j,k,x0,y0,x1,y1,l,cs = 0;
	unsigned int w;
#ifndef ONLINE_JUDGE
	freopen("1078.in","r",stdin);
#endif
	for ( ;6 == scanf("%d %d %d %d %d %d",&m,&n,&x0,&y0,&x1,&y1); ) {
		if ( !m && !n && !x0 && !y0 && !x1 && !y1 ) break ;
		for ( E = 0, i = 0; i < m; ++i )
			for ( j = 0; j < n; last[enc(i,j)] = -1, ++j );
		--x0,--y0,--x1,--y1,printf("Case %d: ",++cs);
		for ( l = 0; l < 2*m-1; ++l ) 
			if ( !(l&1) ) 
				for ( i = (l>>1), j = 0; j < n-1; scanf("%d",&k), add_arcs(enc(i,j),enc(i,j+1),k), ++j );
			else 
				for ( i = (l>>1), j = 0; j < n;  scanf("%d",&k), add_arcs(enc(i,j),enc(i+1,j),k), ++j );
		w = dijkstra(enc(x0,y0),enc(x1,y1));
		if ( w < +oo )
			printf("%u\n",w);
		else puts("Impossible");
	}
	return 0;
}

