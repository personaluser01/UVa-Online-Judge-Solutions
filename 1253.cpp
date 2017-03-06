/*
 * 1253. Infected Land
 * TOPIC: bfs
 * status: Accepted
 */
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <set>
#include <vector>
#define BIT(k)  (1ULL<<(k))
#define MASK(k) (BIT(k)-1ULL)
#define N 8
#include <map>
#define SH 3
#include <queue>
using namespace std;
typedef unsigned int u32;
typedef unsigned long long u64;
#define oo 0xfffffffful
#define BIT(k) (1ULL<<(k))
#define MASK(k) (BIT(k)-1ULL)
#define SET_FREE(u,i,j) ((u) &= ~BIT((i)*n+(j)))
#define INFECT(u,i,j) ((u) |= BIT((i)*n+(j)))
#define IS_FREE(u,i,j) (!((u)&BIT((i)*n+(j))))
#define vc(x,y) (0<=(x)&&(x)<n&&0<=(y)&&(y)<n)

int n;
char g[N][N];
u32 enc( int x, int y, u32 u ) 
{ return (u32)( (((u64)x) | (((u64)y)<<SH) | (((u64)u)<<(SH+SH)) ) & MASK(32)); }
map<u32,unsigned int> d;
queue<u32> q;

int count_neighbors( unsigned int u, int x, int y, int i, int j ) {
	int di,dj,ni,nj,k = 0;
	for ( di = -1; di <= 1; ++di )
		for ( dj = -1; dj <= 1; ++dj )
			if ( abs(di)+abs(dj) )
				if ( vc(ni=i+di,nj=j+dj) )
					if ( ni==x&&nj==y || !IS_FREE(u,ni,nj) ) ++k;
	return k;
}

unsigned int f( int x, int y, unsigned int u ) {
	unsigned int v = 0;
	int i,j,k;
	for ( i = 0; i < n; ++i )
		for ( j = 0; j < n; ++j ) {
			if ( x == i && y == j ) continue ;
			if ( IS_FREE(u,i,j) ) {
				if ( (k = count_neighbors(u,x,y,i,j)) == 3 )
					INFECT(v,i,j);
			}
			else {
				if ( (k = count_neighbors(u,x,y,i,j)) == 3 || k == 2 )
					INFECT(v,i,j);
			}
		}
	return v;
}

unsigned int bfs( u32 src ) {
	unsigned int u,v,w = +oo;
	u32 s,t;
	int i,j,k,x,y,nx,ny,dx,dy;
	for ( d.clear(); !q.empty(); q.pop() );
	for ( d[src] = 0, q.push(src); !q.empty(); ) {
		k=d[s=q.front()], q.pop();
		if ( (s>>(SH+SH)) == 0 && w > k ) w = k;
		if ( k >= w ) continue ;
		x=(s&MASK(SH)),y=((s>>SH)&MASK(SH)),u=(s>>(SH+SH));
		for ( dx=-1; dx<=1; ++dx )
			for ( dy=-1; dy<=1; ++dy )
				if ( abs(dx)+abs(dy) )
					if ( vc(nx=x+dx,ny=y+dy) && IS_FREE(u,nx,ny) ) 
						if ( d.find(t=enc(nx,ny,v=f(nx,ny,u))) == d.end() ) 
							d[t] = k+1, q.push(t);
	}
	return w;
}

int main() {
	int i,j,k,sx,sy;
	unsigned int u;
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	for(;1==scanf("%d",&n)&&n>0;) {
		for ( u = MASK(n*n), i = 0; i < n; ++i )
			for ( scanf("%s",g[i]), j = 0; j < n; ++j )
				if ( g[i][j] == '@' ) 
					g[sx=i][sy=j]='.', SET_FREE(u,i,j);
				else if ( g[i][j] == '.' )
					SET_FREE(u,i,j);
		printf("%d\n",bfs(enc(sx,sy,u)));
	}
	return 0;
}

