/*
 * 10510. Cactus
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define M 10100
#define N 10100
#define oo N
enum { D, T };
enum { WHITE, GRAY, BLACK };

int m,n,E,ts,scc,in[N],out[N],tick,
	last[2][N],next[2][M],to[2][M],st[N],*top,seen[N],yes;
char isdig[256],color[N],cross,forward;

void add_arc( int x, int y ) {
	int i = E++;
	to[D][i] = y, next[D][i] = last[D][x], last[D][x] = i;
	to[T][i] = x, next[T][i] = last[T][y], last[T][y] = i;
}

int getnum() {
	int ch,n = 0;
	for(;(ch=getchar())!=EOF&&!isdig[ch];);
	assert( ch != EOF );
	for(n=ch-'0';(ch=getchar())!=EOF&&isdig[ch];n=(n<<1)+(n<<3)+(ch-'0'));
	return n;
}

void dfs( int t, int x ) {
	int i,y;
	assert( seen[x] != yes );
	for ( seen[x] = yes, i = last[t][x]; i >= 0; i = next[t][i] )
		if ( seen[y = to[t][i]] != yes )
			dfs(t,y);
	if ( t == D ) *++top = x;
}

int not_cactus( int x ) {
	int i,y;
	assert( seen[x] != yes );
	assert( color[x] == WHITE );
	for ( seen[x] = yes, in[x] = ++tick, color[x] = GRAY, i = last[D][x]; i >= 0; i = next[D][i] )
		if ( seen[y = to[D][i]] != yes ) {
			if ( not_cactus(y) )
				return 1;
		}
		else {
			if ( color[y] == BLACK ) {
				if ( out[y] < in[x] )
					cross = 1;
				else {
					assert( in[x] <= in[y] );
					forward = 1;
				}
				return 1;
			}
		}
	color[x] = BLACK, out[x] = ++tick;
	return 0;
}

int main() {
	int i,j,k;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( i = '0'; i <= '9'; isdig[i++] = 1 );
	for ( ts = getnum(); ts--; ) {
		n = getnum(), m = getnum();
		tick = 0, cross = forward = 0;
		for ( E = 0, i = 0; i < n; ++i )
			for ( k = D; k <= T; ++k )
				last[k][i] = -1;
		for ( k = 0; k < m; ++k ) 
			i = getnum(), j = getnum(),	add_arc(i,j);
		if ( n == 1 ) { puts("YES"); continue ; }
		for ( scc = 0,  ++yes, top = st, i = 0; i < n && scc <= 1; ++i )
			if ( seen[i] != yes && (++scc <= 1) )
				dfs(D,i);
		if ( scc >= 2 ) { puts("NO"); continue ; }
		for ( ++yes, scc = 0; top > st && scc <= 1; --top )
			if ( seen[*top] != yes && (++scc) <= 1 )
				dfs(T,*top);
		if ( scc >= 2 ) { puts("NO"); continue ; }
		for ( i = 0; i < n; color[i++] = WHITE );
		puts((++yes,not_cactus(0))?"NO":"YES");
	}
	return 0;
}

