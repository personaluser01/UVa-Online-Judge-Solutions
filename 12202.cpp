/*
 * 12202. Haunted Graveyard
 * TOPIC: bellman-ford
 * status: Accepted
 */
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>
#define N 0x30
#define vc(x,y) (0<=(x)&&(x)<m&&0<=(y)&&(y)<n)
#define MAXE (1<<20)
#define MAXV (1<<19)
#define enc(i,j) ((i)|((j)<<5))
#define oo (1LL<<53)
typedef long long i64;
using namespace std;

int m,n,is_stone[N][N],yes,E,to[MAXE],next[MAXE],last[MAXV],from[MAXE],V,
	dx[] = {-1,0,1,0},
	dy[] = {0,1,0,-1},hole[N][N];
i64 d[MAXV],cost[MAXE];
bool neg_cycle,unreachable;

void add_arcs( int x, int y, int t ) {
	int i = E++;
	from[i] = x, to[i] = y, next[i] = last[x], last[x] = i, cost[i] = t;
}

void bellman_ford() {
	int i,j,x,y;
	neg_cycle = unreachable = false ;
	for ( x = 0; x < m; ++x )
		for ( y = 0; y < n; ++y )
			d[enc(x,y)] = +oo;
	d[enc(0,0)] = 0;
	for ( j = 0; j < V; ++j )
	for ( i = 0; i < E; ++i )
		if ( d[x=from[i]]<+oo )
			if ( d[y=to[i]]>d[x]+cost[i] )
				d[y]=d[x]+cost[i];
	for ( i = 0; i < E; ++i )
		if ( d[x=from[i]]<+oo )
			if ( d[y=to[i]]>d[x]+cost[i] ) {
				neg_cycle = true ;
				return ;
			}
	unreachable=!(d[enc(m-1,n-1)]<+oo);
}

int main() {
	int i,j,k,gr,holes,i0,j0,i1,j1,t,ni,nj;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( ;2 == scanf("%d %d",&m,&n) && (m||n); ) {
		for ( scanf("%d",&gr), ++yes, V = m*n-gr; gr-- && 2 == scanf("%d %d",&i,&j); is_stone[i][j] = yes );
		for ( E = 0, i = 0; i < m; ++i )
			for ( j = 0; j < n; ++j )
				last[enc(i,j)] = -1;
		for ( scanf("%d",&holes); holes-- && 5==scanf("%d %d %d %d %d",&i0,&j0,&i1,&j1,&t); hole[i0][j0] = yes, add_arcs(enc(i0,j0),enc(i1,j1),t) );
		for ( i = 0; i < m; ++i )
			for ( j = 0; j < n; ++j )
				if ( !(i==m-1 && j==n-1) && is_stone[i][j] != yes ) {
					if ( hole[i][j] == yes ) continue ;
					for ( k = 0; k < 4; ++k ) {
						ni = i+dx[k], nj = j+dy[k];
						if ( vc(ni,nj) && is_stone[ni][nj] != yes )
							add_arcs(enc(i,j),enc(ni,nj),1);
					}
				}
		bellman_ford();
		if ( neg_cycle ) {
			puts("Never");
			continue ;
		}
		if ( unreachable ) {
			puts("Impossible");
			continue ;
		}
		printf("%lld\n",d[enc(m-1,n-1)]);
	}
	return 0;
}

