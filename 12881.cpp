/*
 * 12881. Ricochet Robots
 * TOPIC: bfs
 * status: Accepted
 */
#include <bits/stdc++.h>
#include <queue>
#include <set>
typedef unsigned int state;
typedef unsigned long long u64;
#define enc(x,y) ((x)|((y)<<4))
#define BIT(k) (1ULL<<(k))
#define MASK(k) (BIT(k)-1ULL)
#define oo 0xfffffffful
#define A(v,i) (((v)>>((i)<<3))&MASK(8))
#define X(v,i) (A(v,i)&15)
#define Y(v,i) (A(v,i)>>4)
using namespace std;

char g[0x10][0x10];
int m,n,r,lim,
	dx[] = {-1,0,1,0},
	dy[] = {0,1,0,-1};
set<state> s;
state q[1<<23],*head,*tail;

int vc( int x, int y ) { return 0<= x && x < m && 0 <= y && y < n; };

state move( state s, int i, int dir ) {
	int j,k,nx,ny,x=X(s,i),y=Y(s,i);
	u64 u[4];
	assert( vc(x,y) );
	static int used[256] = {0}, yes = 0;
	for ( ++yes, k = 0; k < r; ++k ) {
		assert( used[A(s,k)] != yes );
		used[A(s,k)] = yes;
	}
	if ( i == 0 ) {
		for ( k = 1; vc(nx=x+dx[dir]*k,ny=y+dy[dir]*k) && g[nx][ny] != 'W' && used[enc(nx,ny)] != yes; ++k );
		nx -= dx[dir], ny -= dy[dir];
		assert( vc(nx,ny) );
		assert( (nx == x && ny == y) || used[enc(nx,ny)] != yes );
		s &= ~0xffull, s |= enc(nx,ny);
		return s;
	}
	assert( i > 0 && i < r );
	for ( k = 1; vc(nx=x+dx[dir]*k,ny=y+dy[dir]*k) && g[nx][ny] != 'W' && used[enc(nx,ny)] != yes; ++k );
	nx -= dx[dir], ny -= dy[dir];
	for ( k = 0; k < r; ++k )
		if ( k == i ) 
			u[k] = enc(nx,ny);
		else u[k] = A(s,k);
	for ( j = 1; j; )
		for ( i = 1, j = 0; i < r-1; ++i )
			if ( u[i] > u[i+1] )
				k = u[i], u[i] = u[i+1], u[i+1] = k, ++j;
	for ( j = 0; j < r; ++j )
		s &= ~(0xffull<<(j*8)), s |= (u[j]<<(j*8));
	return s;
}

unsigned int 
bfs( state src ) {
	int T,dist;
	for ( s.clear(), head = tail = q, T = 1, dist = 0, s.insert(*tail++ = src); head < tail; ) {
		state v,u = *head++;
		if ( dist > lim ) continue ;
		if ( g[A(u,0)&0xfull][A(u,0)>>4] == 'X' ) return dist;
		for ( int i = 0; i < r; ++i ) 
			for ( int j = 0; j < 4; ++j )
				if ( !s.count(v = move(u,i,j)) )
					s.insert(*tail++=v);
		if ( !--T ) ++dist, T = tail-head;
	}
	return +oo;
}

int main() {
	int i,j,k,l,t,place[4];
	unsigned int w;
	state src;
#ifndef ONLINE_JUDGE
	freopen("12881.in","r",stdin);
#endif
	while ( 4 == scanf("%d %d %d %d",&r,&n,&m,&lim) ) {
		for ( i = 0; i < r; place[i++] = -1 );
		for ( i = 0; i < m; ++i )
			for ( scanf("%s",g[i]), j = 0; j < n; ++j )
				if ( '1' <= g[i][j] && g[i][j] <= '4' )
					place[g[i][j]-'1'] = enc(i,j);
		for  ( i = 0; i < r; ++i )
			assert( place[i] != -1 );
		for ( j = 1; j; )
			for ( i = 1, j = 0; i < r-1; ++i )
				if ( place[i] > place[i+1] )
					++j, k = place[i], place[i] = place[i+1], place[i+1] = k;
		for ( j = 1; j < r-1; ++j )
			assert ( place[j] < place[j+1] );
		for ( src = 0, i = 0; i < r; src |= (place[i]<<(i*8)), ++i );
		if ( (w = bfs(src)) < +oo )
			printf("%u\n",w);
		else puts("NO SOLUTION");
	}
	return 0;
};

