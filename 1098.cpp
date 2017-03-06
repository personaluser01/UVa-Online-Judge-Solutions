/*
 * 1098. Robots on Ice
 * TOPIC: NP
 * status: Accepted
 */
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <map>
#define vc(x,y) (0<=(x)&&(x)<m&&0<=(y)&&(y)<n)
#define N 8
#define BIT(k) (1ULL<<(k))
#define MASK(k) (BIT(k)-1ULL)
typedef long long i64;
typedef unsigned long long u64;
using namespace std;
#define K (N*N)
#define enc(x,y) ((x)|((y)<<3))
#define X(s) ((int)((s).c&7UL))
#define Y(s) ((int)((s).c>>3))
#define L(u) ((u)&((~(u))+1ULL))

u64 M,ans;
char bts[1<<21],which[1<<21];
int m,n,r[3],c[3],tm[3],
	dx[] = {-1,0,1,0},
	dy[] = {0,1,0,-1};

int how_much( u64 u ) { return bts[u&MASK(20)]+bts[(u>>20)&MASK(20)]+bts[(u>>40)&MASK(20)]+bts[u>>60]; }

typedef struct {
	u64 u;
	unsigned char c;
} cell;

bool operator < ( const cell &a, const cell &b ) {
	if ( a.u == b.u ) return a.c<b.c;
	return a.u<b.u;
}

map<cell,i64> w;

int who( const u64 u ) {
	if ( u < BIT(20) )
		return which[u];
	if ( u < BIT(40) )
		return 20+which[u>>20];
	if ( u < BIT(60) )
		return 40+which[u>>40];
	return 60+which[u>>60];
}

int first_free_cell( const u64 u ) { return who(L(u)); }

bool is_terminal( const cell &a ) { return a.u==M&&a.c==enc(0,1); }

u64 seen;

int floodfill( int x, int y ) {
	int i,j,k,nx,ny,s = 1;
	if ( seen == M ) return 0;
	for ( seen |= BIT(n*x+y), i = 0; i < 4 && seen != M; ++i ) 
		if ( vc(nx=x+dx[i],ny=y+dy[i]) && !(seen&BIT(nx*n+ny)) ) 
			s += floodfill(nx,ny);
	return s;
}

int dfs( const u64 u ) {
	if ( (seen=u) == M )
		return 0;
	u64 v = first_free_cell(~u&M);
	return floodfill(v/n,v%n);
}

void f( cell s ) {
	int ts = how_much(s.u),nx,ny,i;
	cell ns;
	if ( is_terminal(s) ) { ++ans; return ; }
	if ( X(s)==0 && Y(s)==1 ) return ;
	if ( s.u == M ) return ;
	if ( dfs(s.u) != m*n-ts ) 
		return ;
	if ( ts < tm[0] && abs(X(s)-r[0])+abs(Y(s)-c[0]) > tm[0]-ts ) return ;
	if ( ts==tm[0] && (X(s)!=r[0]||Y(s)!=c[0]) ) return ;
	if ( ts < tm[1] && abs(X(s)-r[1])+abs(Y(s)-c[1]) > tm[1]-ts ) return ;
	if ( ts==tm[1] && (X(s)!=r[1]||Y(s)!=c[1]) ) return ;
	if ( ts < tm[2] && abs(X(s)-r[2])+abs(Y(s)-c[2]) > tm[2]-ts ) return ;
	if ( ts==tm[2] && (X(s)!=r[2]||Y(s)!=c[2]) ) return ;
	for ( i = 0; i < 4; ++i ) {
		nx=X(s)+dx[i],ny=Y(s)+dy[i];
		if ( !vc(nx,ny)||(s.u&BIT(nx*n+ny)) ) continue ;
		ns.u=(s.u|BIT(nx*n+ny)); ns.c=enc(nx,ny);
		f(ns);
	}
}

int main() {
	int i,j,k,cs = 0;
	cell s;
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	for ( k = 0; k < (1<<21); ++k )
		bts[k] = bts[k>>1]+(k&1);
	for ( k = 0; k < 21; ++k )
		which[1<<k]=k;
	for(;2==scanf("%d %d",&m,&n)&&(m||n);){
		if ( m == 8 && n == 8 )
			M = 0xffffffffffffffffull;
		else M = MASK(m*n);
		for(i=0;i<3;++i) 
			scanf("%d %d",r+i,c+i), tm[i]=(((i+1)*m*n)>>2);
		s.u = 1, s.c = enc(0,0), ans = 0, f(s), printf("Case %d: %llu\n",++cs,ans);
	}
	return 0;
}

