/*
 * 1040. The Travelling Judges Problem
 * status: Accepted
 * TOPIC: dijkstra, bitmasks, search space, search state, meet-in-the-middle, backtracking
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 20
#define Q (1 << N)
#define MAXN N
#define MAXE (N*N+N)
#define xchg(x,y) (((x)==(y))||((x)^=(y),(y)^=(x),(x)^=(y)))
#define bubble ( xchg(pos[heap[i]],pos[heap[j]]),xchg(heap[i],heap[j]) )
#define oo 0xfffffffful
#define L(i) ((i)&((~(i))+1UL))
#define MAXK 10
enum { S, T };

int n,m,K,to[MAXE],weight[MAXE],last[MAXN],next[MAXE],E,city[N],cs,cnt,cnt,pos[MAXN],dst,
    *ptr[MAXK],lst[MAXK][N+N],path[MAXK][N+N],best_len[MAXK];
unsigned int heap[Q],d[2][Q];
char bts[Q],which[Q];

void add_arcs( int x, int y, int k ) {
	int i = E++, j = E++;
	to[i] = y, next[i] = last[x], last[x] = i, weight[i] = k;
	to[j] = x, next[j] = last[y], last[y] = j, weight[j] = k;
}

void push( unsigned int u, int t ) {
	int i,j;
	if ( pos[u] < 0 ) pos[heap[cnt]=u]=cnt,++cnt;
	for ( j = pos[u]; j && d[t][heap[i=(j-1)>>1]] > d[t][heap[j]]; bubble, j = i );
}

unsigned int pop( int t ) {
	unsigned int x = *heap;
	int i,j;
	if ( --cnt ) pos[*heap = heap[cnt]] = 0;
	for ( j = 0; (i=j,j<<=1,++j) < cnt; bubble ) {
		if ( i < cnt-1 && d[t][heap[j+1]] < d[t][heap[j]] ) ++j;
		if ( d[t][heap[i]] <= d[t][heap[j]] ) break ;
	}
	return x;
}

void dijkstra( unsigned int src, int t ) {
	unsigned int u,v,w;
	int i,j,k,x,y;
	for ( cnt = 0, u = 0; u < (1<<n); ++u )
		d[t][u] = +oo, pos[u] = -1;
	for ( d[t][src] = 0, push(src,t); cnt; )
		for ( w = u = pop(t); w; w -= L(w) )
			for ( i = last[x = which[L(w)]]; i >= 0; i = next[i] ) {
				if ( d[t][v = u&~(1UL<<x)|(1UL<<to[i])] > d[t][u]+weight[i] )
					d[t][v] = d[t][u]+weight[i], push(v,t);
				if ( t == T && d[t][v = u|(1UL<<to[i])] > d[t][u]+weight[i] && bts[v] <= K )
					d[t][v] = d[t][u]+weight[i], push(v,t);
			}
}

int cmp_solns() {
    int i,k;
    for ( k = 0; k < K; ++k ) {
        if ( best_len[k] > ptr[k]-lst[k] )
            return -1;
        if ( best_len[k] < ptr[k]-lst[k] )
            return 1;
        for ( i = 0; i < best_len[k]; ++i )
            if ( path[k][i] != lst[k][i] ) {
                if ( path[k][i] > lst[k][i] )
                    return -1;
                return 1;
            }
    }
    return 0;
}

void check_it_out() {
    int i,k;
    if ( cmp_solns() < 0 )
        for ( k = 0; k < K; ++k )
            for ( best_len[k]=ptr[k]-lst[k], i=0; i<ptr[k]-lst[k]; ++i )
                path[k][i]=lst[k][i];
}

void f( int *c, unsigned int u ) {
    int i,j,k,x,nc[MAXK],ok;
    unsigned int v;

    assert( bts[u] <= K );
    if ( !(d[S][u] < +oo && d[T][u] < +oo && d[S][u]+d[T][u] == d[S][1<<dst]) )
        return ;

    if ( u == (1UL<<dst) ) {
        check_it_out();
        return ;
    }

    for ( v = u; v; v -= L(v) ) 
        for ( i=last[x=which[L(v)]]; i>=0; i=next[i] ) {
            for ( ok = 1,  k = 0; k < K; ++k ) 
                if ( (nc[k]=c[k]) == x ) {
                    *ptr[k]++ = (nc[k] = to[i]);
                    if ( ptr[k]-lst[k] > n ) ok = 0;
                }
            if ( ok ) f(nc,u&~(1UL<<x)|(1UL<<to[i]));
            for ( k = 0; k < K; ++k )
                if ( c[k] == x )
                    --ptr[k];
        }
}

int main() {
	int i,j,k,l,t;
	unsigned int u;
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	for ( u = 0; u < Q; ++u ) bts[u] = bts[u>>1]+(u&1);
	for ( i = 0; i < N; ++i ) which[1<<i] = i;
    for ( i = 0; i < MAXK; ++i ) ptr[i] = lst[i];
	for(;3==scanf("%d %d %d",&n,&dst,&m) && n != -1 && printf("Case %d: ",++cs);) {
		for ( i = 0; i < n; last[i++] = -1 );
		for ( --dst, E = 0, l = 0; l < m; ++l ) {
			assert( 3 == scanf("%d %d %d",&i,&j,&k) ); 
            add_arcs(--i,--j,k);
        }
        assert( 1 == scanf("%d",&K) );
		for ( i = 0; i < K; scanf("%d",&city[i]), --city[i++] );
		for ( u = 0, j = 0; j < K; best_len[j] = (1<<29), u|=(1<<city[j++]) );
		dijkstra(u,S), printf("distance = %u\n",d[S][1<<dst]);
		dijkstra(1<<dst,T);
		assert( d[S][1<<dst] == d[T][u] );
        for ( f(city,u), k = 0; k < K; ++k, putchar('\n') ) 
            for ( printf("   %d",city[k]+1), i = 0; i < best_len[k]; printf("-%d",path[k][i++]+1) );
        puts("");
	}
	return 0;
}


