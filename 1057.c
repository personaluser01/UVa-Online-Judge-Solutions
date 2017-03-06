/*
 * 1057. Routing
 * TOPIC: dijkstra, hard state, world finals, wfi
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N (1<<SH)
#define Q (0x400)
#define oo (1<<29)
#define SH 7
#define MSK (N-1)
#define MAXE (1<<22)
#define MAXV (1<<14)
#define xchg(x,y) (((x)==(y)) || ((x)^=(y),(y)^=(x),(x)^=(y)))
#define bubble (xchg(pos[heap[i]],pos[heap[j]]),xchg(heap[i],heap[j]))

int m,n,g[N][N],yes,d[N][N],shared_segment[1<<21],len,
	pos[MAXV],heap[MAXE],cnt,dst,src,dist[MAXE];

void push( int x ) {
	int i,j;
	if ( pos[x] < 0 )
		pos[heap[cnt] = x] = cnt, ++cnt;
	for ( j = pos[x]; j && dist[heap[i=(j-1)>>1]] > dist[heap[j]]; bubble, j = i );
}

int pop() {
	int i,j,x = *heap;
	if ( cnt+=(pos[x]=-1) )
		pos[*heap=heap[cnt]]=0;
	for ( j = 0; (i=j,j<<=1,++j) < cnt; bubble ) {
		if ( j < cnt-1 && dist[heap[j]] > dist[heap[j+1]] ) ++j;
		if ( dist[heap[i]] <= dist[heap[j]] ) break ;
	}
	return x;
}

int dijkstra() {
	int i,j,k,x,y,z,t;
	for ( cnt = 0, x = 0; x < len; dist[x] = +oo, pos[x++] = -1 );
	for ( dist[src] = 0, push(src); cnt; ) {
		i = pop();
		x = (shared_segment[i]&MSK), y = (shared_segment[i]>>SH);
		for ( j = 0; j < len; ++j ) 
			if ( i != j ) {
				z=(shared_segment[j]&MSK), t=(shared_segment[j]>>SH);
				if ( x == z || x == t || y == z || y == t ) continue ;
				if ( d[y][z] == +oo || d[z][x] == +oo )
					continue ;
				if ( x == t && y == z ) continue ;
				if ( dist[j] > dist[i]+d[y][z]+d[z][t]+d[t][x]-1 ) {
					dist[j] = dist[i]+d[y][z]+d[z][t]+d[t][x]-1;
					push(j);
				}
			}
	}
	return dist[dst];
}

int main() {
	int i,j,k,cs = 0,x,y,z,t,lines = 0;
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	for (;2 == scanf("%d %d",&n,&m) && (n||m) && ++yes && ++lines; ) {
		for ( i = 0; i < n; ++i )
			for ( j = i+1; j < n; ++j )
				d[j][i] = d[i][j] =  +oo;
		printf("Network %d\n",++cs);
		for ( k = 0; k < m; ++k ) {
			scanf("%d %d",&i,&j), ++lines;
			if ( i == j ) continue ;
		   	g[--i][--j] = yes, d[i][j] = 1;
		}
		for ( i = 0; i < n; ++i ) g[i][i] = yes;
		for ( k = 0; k < n; ++k )
			for ( i = 0; i < n; ++i )
				for ( j = 0; j < n; ++j )
					if ( d[i][k] < +oo && d[k][j] < +oo )
						if ( d[i][j] > d[i][k] + d[k][j] )
							d[i][j] = d[i][k]+d[k][j];

		if ( d[0][1] == +oo || d[1][0] == +oo ) {
			/*puts("IMPOSSIBLE\n");*/
nx:
			puts("Impossible\n");
			continue ;
		}

		for ( len = 0, i = 0; i < n; ++i ) 
			for ( j = 0; j < n; ++j )
				if ( d[i][j] < +oo )
					if ( d[0][i] < +oo && d[j][1] < +oo )
						if ( d[1][i] < +oo && d[j][0] < +oo ) 
							shared_segment[len++] = (i|(j<<SH));

		for ( src = dst = -1, i = 0; i < len && (src==-1 || dst==-1); ++i )
			if ( (shared_segment[i]&MSK) == 0 && (shared_segment[i]>>SH) == 0 )
				src = i;
			else if ( (shared_segment[i]&MSK) == 1 && (shared_segment[i]>>SH) == 1 )
				dst = i;

		if ( src == -1 || dst == -1 )
			goto nx;

		printf("Minimum number of nodes = %d\n\n",dijkstra()+1);
	}
	return 0;
}

