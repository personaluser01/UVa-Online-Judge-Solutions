/*
 * 10841. Lift Hopping in the Real World
 * TOPIC: dijkstra
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 0x40
#define L 0x80
#define MAXV 0x400
#define MAXE (1<<21)
#define xchg(x,y) (((x)==(y)) || ((x)^=(y),(y)^=(x),(x)^=(y)))
#define bubble (xchg(pos[heap[i]],pos[heap[j]]), xchg(heap[i],heap[j]))
#define oo 0xfffffffful

int heap[MAXV],cnt,pos[MAXV],len[MAXV],lst[L][N],V,loc[N][L],deg[N],T[N],m,n;
unsigned int d[MAXV];
char buff[0x400],*ptr;

void push( int x ) {
	int i,j;
	if ( pos[x] < 0 )
		pos[heap[cnt] = x] = cnt, ++cnt;
	for ( j = pos[x]; j && d[heap[i = (j-1)>>1]] > d[heap[j]]; bubble, j = i );
}

int pop() {
	int i,j,x = *heap;
	if ( cnt += (pos[x] = -1) )
		pos[*heap=heap[cnt]]=0;
	for ( j = 0; (i=j,j<<=1,++j) < cnt; bubble ) {
		if ( j < cnt-1 && d[heap[j]] > d[heap[j+1]] ) ++j;
		if ( d[heap[i]] <= d[heap[j]] ) break ;
	}
	return x;
}

void dijkstra( int src, int dst ) {
	int x,y,i,j,k,l,elevator,furthest_floor,time_elapsed,dt;

	if ( src == dst ) {
		puts("0");
		return ;
	}

	for ( cnt = 0, x = 0; x < V; pos[x] = -1, d[x++] = +oo );
	for ( d[src] = 0, push(src); cnt; )
		for ( x = pop(), i = 0; i < len[x]; ++i ) {
			elevator = lst[x][i];
			if ( !deg[elevator] ) continue ;
			furthest_floor = (abs(x-loc[elevator][0])<abs(loc[elevator][deg[elevator]-1]-x)?loc[elevator][deg[elevator]-1]:loc[elevator][0]);
			time_elapsed = T[elevator]*abs(furthest_floor-x)+5;
			for ( l = 0; l < deg[elevator]; ++l ) {
				y = loc[elevator][l];
				dt = abs(y-x)*T[elevator];
				if ( d[y] > d[x]+dt+time_elapsed )
					d[y] = d[x]+dt+time_elapsed, push(y);
			}
		}
	if ( d[dst] < +oo )
		printf("%u\n",d[dst]-5);
	else puts("IMPOSSIBLE");
}

int main() {
	int i,j,k;
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	for(;2==scanf("%d %d",&n,&m);dijkstra(0,m)) {
		for ( i = 0; i < n; deg[i] = 0, scanf("%d\n",&T[i++]) );
		for ( i = 0; i < L; len[i++] = 0 );
		for ( V = L, i = 0; i < n; ++i ) 
			for(ptr=fgets(buff,sizeof buff,stdin);1==sscanf(ptr,"%d%n",&j,&k);ptr+=k,lst[j][len[j]++]=i,loc[i][deg[i]++]=j);
	}
	return 0;
}

