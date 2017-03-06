/*
 * 1063. Marble Game
 * TOPIC: bfs
 * status: Accepted
 */
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 4
typedef unsigned long long u64;
typedef unsigned int state;
#define   BIT(k)   (1ULL<<(k))
#define   MASK(k)  (BIT(k)-1ULL)
#define   L(k) 	   ((k)&((~(k))+1ULL))
#define vc(x,y) (0<=(x)&&(x)<n&&0<=(y)&&(y)<n)
#define A(u,k) (((u)>>(4*(k)))&0xfull)
#define in_place(u,i) (holeid[A(u,i)&3ULL][A(u,i)>>2] == (i))
#define oo 0xfffffffful
#include <queue>
#include <set>
#include <iostream>
using namespace std;

int m,n,walls,iswall[N][N][N][N],yes,
	holeid[N][N],lowest[BIT(6)],highest[BIT(6)],which[1<<4],
	dx[] = {-1,0,1,0},
	dy[] = {0,1,0,-1};
unsigned int r[N],c[N];

void display( const state u ) {
	int i,j,k,g[N][N];
	puts("*************");
	for ( i = 0; i < n; ++i )
		for ( j = 0; j < n; g[i][j++] = -1 );
	for ( i = 0; i < m; ++i )
		if ( !in_place(u,i) )
			g[A(u,i)&3][A(u,i)>>2] = i;
	for ( i = 0; i < n; ++i ) {
		for ( j = 0; j < n; ++j )
			if ( g[i][j] == -1 ) {
				if ( holeid[i][j] == -1 ) 
					printf("E  ");
				else printf("H%d ",holeid[i][j]+1);
			}
			else {
				printf("%d  ",g[i][j]+1);
			}
		puts("");
	}
}

state tilt( const state u, const int t ) {
	int i,j,k,ni,nj,nk,it = 0,row,col,g[N][N];
	bool flag,ok;
	unsigned int w = 0;
	state v,nu,pu = u;
	for ( i = 0; i < n; ++i )
		for ( j = 0; j < n; g[i][j++] = -1 );
	for ( i = 0; i < n; ++i )
		r[i] = c[i] = 0;
	for ( i = 0; i < m; ++i )
		if ( !in_place(u,i) )
			g[j=A(u,i)&3ULL][k=A(u,i)>>2] = i, r[j] |= BIT(k), c[k] |= BIT(j);
	if ( t&1 ) {
		if ( t == 1 ) 
			for ( row = 0; row < n; ++row ) 
				for ( i = row, w = r[i]; w; w &= ~BIT(highest[w]) ) {
					if ( g[i][j=highest[w]] != -1 ) {
						if ( holeid[i][j] != -1 && !in_place(pu,holeid[i][j]) )
							return +oo;
						assert( holeid[i][j] != g[i][j] );
						for ( ni=i+dx[t],nj=j+dy[t]; vc(ni,nj) && iswall[ni-dx[t]][nj-dy[t]][ni][nj] != yes; ni += dx[t], nj += dy[t] ) {
							if ( holeid[ni][nj] == g[i][j] ) {
								pu &= ~(0xfull<<(g[i][j]*4));
								pu |= ((ni|(nj<<2))<<(g[i][j]*4));
								g[i][j] = -1;
								assert( in_place(pu,holeid[ni][nj]) );
								goto next01;
							}
							if ( holeid[ni][nj] != -1 && !in_place(pu,holeid[ni][nj]) ) 
								return +oo;
							if ( g[ni][nj] != -1 ) {
								cap01:
								ni -= dx[t], nj -= dy[t];
								if ( ni == i && nj == j ) goto next01;
								pu &= ~(0xfull<<(g[i][j]*4));
								pu |= ((ni|(nj<<2))<<(g[i][j]*4));
								g[ni][nj] = g[i][j], g[i][j] = -1;
								goto next01;
							}
						}
						goto cap01;
					}
					next01: ;
				}
		else 
			for ( row = 0; row < n; ++row ) 
				for ( i = row, w = r[i]; w; w &= ~BIT(lowest[w]) ) {
					if ( g[i][j=lowest[w]] != -1 ) {
						if ( holeid[i][j] != -1 && !in_place(pu,holeid[i][j]) )
							return +oo;
						assert( holeid[i][j] != g[i][j] );
						for ( ni=i+dx[t],nj=j+dy[t]; vc(ni,nj) && iswall[ni-dx[t]][nj-dy[t]][ni][nj] != yes; ni += dx[t], nj += dy[t] ) {
							if ( holeid[ni][nj] == g[i][j] ) {
								pu &= ~(0xfull<<(g[i][j]*4));
								pu |= ((ni|(nj<<2))<<(g[i][j]*4));
								g[i][j] = -1;
								assert( in_place(pu,holeid[ni][nj]) );
								goto next02;
							}
							if ( holeid[ni][nj] != -1 && !in_place(pu,holeid[ni][nj]) ) 
								return +oo;
							if ( g[ni][nj] != -1 ) {
								cap02:
								ni -= dx[t], nj -= dy[t];
								if ( ni == i && nj == j ) goto next02;
								pu &= ~(0xfull<<(g[i][j]*4));
								pu |= ((ni|(nj<<2))<<(g[i][j]*4));
								g[ni][nj] = g[i][j], g[i][j] = -1;
								goto next02;
							}
						}
						goto cap02;
					}
					next02: ;
				}
	}
	else {
		if ( t == 2 ) {
			for ( col = 0; col < n; ++col ) 
				for ( j = col, w = c[j]; w; w &= ~BIT(highest[w]) ) {
					if ( g[i=highest[w]][j] != -1 ) {
						if ( holeid[i][j] != -1 && !in_place(pu,holeid[i][j]) )
							return +oo;
						assert( holeid[i][j] != g[i][j] );
						for ( ni=i+dx[t],nj=j+dy[t]; vc(ni,nj) && iswall[ni-dx[t]][nj-dy[t]][ni][nj] != yes; ni += dx[t], nj += dy[t] ) {
							if ( holeid[ni][nj] == g[i][j] ) {
								pu &= ~(0xfull<<(g[i][j]*4));
								pu |= ((ni|(nj<<2))<<(g[i][j]*4));
								g[i][j] = -1;
								assert( in_place(pu,holeid[ni][nj]) );
								goto next03;
							}
							if ( holeid[ni][nj] != -1 && !in_place(pu,holeid[ni][nj]) ) 
								return +oo;
							if ( g[ni][nj] != -1 ) {
								cap03:
								assert( g[i][j] != -1 );
								ni -= dx[t], nj -= dy[t];
								if ( ni == i && nj == j ) goto next03;
								pu &= ~(0xfull<<(g[i][j]*4));
								pu |= ((ni|(nj<<2))<<(g[i][j]*4));
								g[ni][nj] = g[i][j], g[i][j] = -1;
								goto next03;
							}
						}
						goto cap03;
					}
					next03: ;
				}
		}
		else 
			for ( col = 0; col < n; ++col ) 
				for ( j = col, w = c[j]; w; w &= ~BIT(lowest[w]) ) {
					if ( g[i=lowest[w]][j] != -1 ) {
						if ( holeid[i][j] != -1 && !in_place(pu,holeid[i][j]) )
							return +oo;
						assert( holeid[i][j] != g[i][j] );
						for ( ni=i+dx[t],nj=j+dy[t]; vc(ni,nj) && iswall[ni-dx[t]][nj-dy[t]][ni][nj] != yes; ni += dx[t], nj += dy[t] ) {
							if ( holeid[ni][nj] == g[i][j] ) {
								pu &= ~(0xfull<<(g[i][j]*4));
								pu |= ((ni|(nj<<2))<<(g[i][j]*4));
								g[i][j] = -1;
								assert( in_place(pu,holeid[ni][nj]) );
								goto next04;
							}
							if ( holeid[ni][nj] != -1 && !in_place(pu,holeid[ni][nj]) ) 
								return +oo;
							if ( g[ni][nj] != -1 ) {
								cap04:
								ni -= dx[t], nj -= dy[t];
								pu &= ~(0xfull<<(g[i][j]*4));
								pu |= ((ni|(nj<<2))<<(g[i][j]*4));
								if ( ni == i && nj == j ) goto next04;
								g[ni][nj] = g[i][j], g[i][j] = -1;
								goto next04;
							}
						}
						goto cap04;
					}
					next04: ;
				}
	}
	return pu;
}

state q[1<<22],*head,*tail;
set<state> s;
unsigned int dist;

unsigned int bfs( state src, state dst ) {
	state u,v;
	int i,j,k,len;
	for ( s.clear(),tail=head=q,dist=0,s.insert(src),*tail++=src,len=tail-head; head < tail; ) {
		u = *head++;
		if ( u == dst ) return dist;
		for ( i=0; i<4; ++i )
			if ( (v=tilt(u,i))<+oo )
				if ( s.find(v) == s.end() ) 
					s.insert(v), *tail++ = v;
		if ( !--len ) ++dist, len = tail-head;
	}
	return +oo;
}

int main() {
	int i,j,k,l,ok,cs = 0;
	state u,v;
	unsigned int w;
#ifndef ONLINE_JUDGE
	freopen("c.txt","r",stdin);
#endif
	for ( i = 0; i < 4; ++i ) which[1<<i] = i;
	for ( u = 0; u < BIT(4); highest[u++] = j ) 
		for ( lowest[u] = which[L(u)], j = 3; j >= 0 && !((u>>j)&1); --j );
	for ( ;3==scanf("%d %d %d",&n,&m,&walls)&&(m||n||walls) && ++yes; ) {
		for ( u = 0, i = 0; i < m; ++i ) 
			scanf("%d %d",&j,&k), u |= (j|(k<<2))<<(i*4);
		for ( i = 0; i < n; ++i )
			for ( j = 0; j < n; holeid[i][j++] = -1 );
		for ( i = 0; i < m; ++i ) {
			scanf("%d %d",&j,&k);
			assert( holeid[j][k] == -1 );
		   	holeid[j][k] = i;
		}
		for ( ;walls-- && 4 == scanf("%d %d %d %d",&i,&j,&k,&l); iswall[i][j][k][l] = iswall[k][l][i][j] = yes );
		printf("Case %d: ",++cs);
		for ( v = 0, i = 0; i < n; ++i )
			for ( j = 0; j < n; ++j )
				if ( holeid[i][j] != -1 )
					v |= ((i|(j<<2))<<(4*holeid[i][j]));
		//display(u), u=tilt(u,3), display(u), u = tilt(u,2), display(u);
		// 	dx[] = {-1,0,1,0},
		// dy[] = {0,1,0,-1};

		/*display(u), u = tilt(u,2);
		assert( u != +oo );
		display(u);
		return 0;*/
		w = bfs(u,v);
		if ( w == +oo ) puts("impossible\n");
		else printf("%u moves\n\n",w);
	}
	return 0;
}

