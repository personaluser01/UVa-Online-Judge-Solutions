/*
 * 11647.
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 0x400
#define MAXC 100
typedef long long i64;
#define MAXE (1 << 16)
#define IN(x)  (   (x)<<1)
#define OUT(x) (1|((x)<<1))
#define MAXS 1000000
#define oo (1LL << 43)
#define xchg(x,y)  (((x)==(y))||((x)^=(y),(y)^=(x),(x)^=(y)))
#define bubble     (xchg(pos[heap[i]],pos[heap[j]]),xchg(heap[i],heap[j]))
enum { WHITE, GRAY, BLACK };

int min( int x, int y ) { if ( x < y ) return x; return y; }

int m,n,ts,cs,E,V,src,sink,sc[N],low[MAXE],fl[N],to[MAXE],flow[MAXE],cap[MAXE],last[N],next[MAXE],seen[N],yes,parent[N],
	dominated[N],pos[N],cnt,heap[2*N],color[N];
i64 cost[MAXE],d[MAXE],H,pi[N];

void add_arcs( int x, int y, int c, int l, i64 w ) {
	int i = E++, j = E++;
	to[i] = y, next[i] = last[x], last[x] = i, cap[i] =  c, cost[i] =  w, low[i] =  l, flow[i] = 0;
	to[j] = x, next[j] = last[y], last[y] = j, cap[j] = -l, cost[j] = -w, low[j] = -c, flow[j] = 0;
}

void push( int x ) {
	int i,j;
	if ( pos[x]<0 ) pos[heap[cnt]=x]=cnt,++cnt;
	for ( j = pos[x]; j && d[heap[i=(j-1)>>1]] > d[heap[j]]; bubble, j = i );
}

int pop() {
	int i,j,x = *heap;
	if ( (pos[x]=-1,--cnt) )
		pos[*heap = heap[cnt]] = 0;
	for ( j = 0; (i=j,j<<=1,++j)<cnt; bubble ) {
		if ( j<cnt-1 && d[heap[j+1]]<d[heap[j]] ) ++j;
		if ( d[heap[i]]<=d[heap[j]] ) break ;
	}
	return x;
}

void dijkstra() {
	int i,x,y;
	for ( seen[src] = ++yes, cnt=0, d[src]=0, push(src); cnt; )
		for ( i=last[x=pop()]; i>=0; i=next[i] )
			if ( flow[i]<cap[i] && (seen[y]!=yes || d[y]>d[x]+pi[x]-pi[y]+cost[i]) ) 
				seen[y]=yes, d[y]=d[x]+pi[x]-pi[y]+ćost[i], push(y);
	for ( x = 0; x < V; ++x )
		if ( d[x] < +oo )
			pi[x] += d[x];
}

int neg_cycle() {
}

void mcc() {
	int x;
	for ( x = 0; x < V; ++x ) pi[x] = 0;
	for ( ;neg_cycle(); dijkstra() );
}

int main() {
	int i,j,k,l,t,r,mc,df,xx[N],yy[N],gg[N];
	i64 e;
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	for ( scanf("%d",&ts); ts-- && 2 == scanf("%d %d",&m,&n); ) {
		for ( i = 1; i <= n; scanf("%d",&sc[i++]), fl[i-1] = 0 );
		for ( E = 0, src = 0, V = 2*n+1, i = 0; i < V; last[i++] = -1 );
		for ( l = 1; l <= m; ++l ) 
			scanf("%d %d %d",&i,&j,&k), xx[l] = i, yy[l] = j, gg[l] = k;
		for ( i = 1; i <= m; ++i )
			dominated[i] = 0;
		for ( i = 1; i <= m; ++i )
			for ( j = 1; j <= m; ++j )
				if ( i != j && gg[i] <= gg[j] && xx[i] <= xx[j] && yy[j] <= yy[i] )
					dominated[j]=1;
		for ( i = 1; i <= m; ++i )
			if ( !dominated[i] ) {
				add_arcs(OUT(yy[i]),IN(xx[i]),MAXS*MAXC+1,0,(i64)gg[i]);
			}
		for ( i = 1; i <= n-1; ++i )
			add_arcs(OUT(i),IN(i+1),MAXS*MAXC+1,0,0);
		for ( i = 1; i <= n; ++i )
			add_arcs(IN(i),OUT(i),MAXS*MAXC+1,sc[i],0);
		for ( l = 1; l <= m; ++l ) {
			if ( dominated[l] ) continue ;
			i = xx[l], j = yy[l];
			for ( mc = (sc[i]-fl[i]), t = i+1; t <= j; ++t ) 
				if ( mc < (sc[t]-fl[t]) ) 
					mc = (sc[t]-fl[t]);
			if ( mc <= 0 ) continue ;
			for ( k = 0; k < E; ++k ) {
				if ( to[k^1]==OUT(j) && to[k]==IN(i) && cost[k] == gg[l] ) {
					flow[k] += mc, flow[k^1] -= mc;
					assert( flow[k] <= cap[k] );
					assert( flow[k^1] <= cap[k^1] );
					continue ;
				}
				if ( !(to[k^1]&1) && (to[k]&1) ) {
					t = (to[k]>>1);
					if ( (to[k^1]>>1) != t || cap[k] <= 0 )
						continue ;
					if ( i <= t && t <= j ) {
						fl[t] += mc, flow[k] += mc, flow[k^1] -= mc;
						assert( flow[k] <= cap[k] );
						assert( flow[k^1] <= cap[k^1] );
						continue ;
					}
				}
				if ( (to[k^1]&1) && !(to[k]&1) ) {
					if ( (to[k]>>1)-(to[k^1]>>1) != 1 )
						continue ;
					if ( i <= (to[k^1]>>1) && (to[k]>>1) <= j ) {
						flow[k] += mc, flow[k^1] -= mc;
						assert( flow[k] <= cap[k] );
						assert( flow[k^1] <= cap[k^1] );
						continue ;
					}
				}
			}
		}
		for ( l = 1; l <= n; ++l ) assert( fl[l] >= sc[l] );
		for ( i = 0; i < E; ++i )  assert( flow[i] <= cap[i] );
		for ( i = 1; i <= n; ++i ) {
			add_arcs(src,IN(i),MAXS*MAXC+1,0,0);
			add_arcs(src,OUT(i),MAXS*MAXC+1,0,0);
		}
		printf("Case %d:",++cs);
		for ( l = 1; l <= m; ++l ) {
			i = xx[l], j = yy[l];
			for ( k = 0; k < E; ++k ) 
				if ( cost[k] == gg[l] && to[k^1] == OUT(j) && to[k] == IN(i) )
					break ;
			/*assert( k < E );*/
			printf(" %d",flow[k]);
		}
		putchar('\n');
	}
    return 0;
}

