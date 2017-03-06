/*
 * 225. Golygons
 * TOPIC: backtracking
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 20
#define M 0x40
#define SH (BIT(L))
#define BIT(k) (1ULL<<(k))
#define MASK(k) (BIT(k)-1ULL)
#define MAXC 0xff
typedef unsigned long long u64;
typedef long long i64;
typedef int state;
#define oo 0xffffffffffffffffull
enum { X, Y };
#define L 9

int cmp( const void *a, const void *b ) {
	return *(int *)a - *(int *)b;
}

int cmpu64( const void *a, const void *b ) {
	u64 x = *(u64 *)a,
		y = *(u64 *)b;
	if ( x == y ) 
		return 0;
	return x<y?-1:1;
}

state origin = MAXC|(MAXC<<L);
int dx[] = {0,-1,0,1}, dy[] = {-1,0,1,0},  m,n, roadblock[2][SH+SH][SH+SH], pref[2][SH+SH][SH+SH];
u64 tt[] = {2,3,1,0};
char c[] = {'s','w','n','e'}, cc[] = {'e','n','s','w'};
int seen[BIT(L+L)],yes;
u64 e[1<<N],*head,*tail;

u64 move( state u, int dir, int length ) {
	int x = (u&MASK(L)), y = (u>>L)&MASK(L), nx,ny, low,high;
	assert( length <= N );
	nx = x+dx[dir]*length, ny = y+dy[dir]*length;
	assert( length <= N );
	assert( nx >= 0 && ny >= 0 );
	assert( length <= N );
	assert( nx < SH+SH && ny < SH+SH );
	assert( (nx==x)^(ny==y) );
	if ( nx == x ) {
		low = y<ny?y:ny;
		high = y<ny?ny:y;
		if ( pref[X][x][high]-(low==0?0:pref[X][x][low-1]) >= 1 )
			return +oo;
	}
	if ( ny == y ) {
		low = x<nx?x:nx;
		high = x<nx?nx:x;
		if ( pref[Y][y][high]-(low==0?0:pref[Y][y][low-1]) >= 1 )
			return +oo;
	}
	assert( nx < BIT(L) );
	return nx|(ny<<L);
}

void rec( state u, int i, int dir, u64 path ) {
	int j,new_dir;
	state v;

	if ( i == n ) {
		if ( u == origin ) 
			*tail++ = path;
		return ;
	}
	assert( i < n );
	assert( u < +oo );
	if ( seen[u] == yes ) return ;
	seen[u] = yes;
	for ( j = 0; j < 2; ++j )
		if ( (v = move(u,new_dir=((dir+1+2*j)&3),i+1)) < +oo )
			rec(v,i+1,new_dir,path|(tt[new_dir]<<(2*n-2-2*i)));
	seen[u] = 0;
}

void display( u64 path ) {
	int i;
	for ( i = n-1; i >= 0; --i )
		printf("%c",cc[(path>>(2*i))&3]);
	putchar('\n');
}

int main() {
	int i,j,k,ts,t;
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	for ( scanf("%d",&ts); ts-- && ++yes; ) {
		for ( scanf("%d %d",&n,&m), i = 0; i < m; ++i ) {
			scanf("%d %d",&j,&k);
			if ( j < -MAXC || j > MAXC || j < -MAXC || j > MAXC )
				continue ;
			j += (int)MAXC, k += (int)MAXC;
			roadblock[X][j][k] = roadblock[Y][k][j] = yes;
		}
		for ( t = X; t <= Y; ++t ) 
			for ( i = 0; i < SH+SH; ++i ) {
				pref[t][i][0] = roadblock[t][i][0]==yes?1:0;
				for ( j = 1; j < SH+SH; ++j )
					pref[t][i][j] = pref[t][i][j-1]+(roadblock[t][i][j]==yes?1:0);
			}
		head = tail = e;
		for ( k = 0; k < 2; rec(origin,0,k++,0) );
		qsort( e, tail-head, sizeof *e, cmpu64 );
		for ( ;head < tail; display(*head++) );
		printf("Found %u golygon(s).\n\n",tail-e);
	}
	return 0;
}

