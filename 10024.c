/*
 * 10024. Curling Up the Cube
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define vc(x,y) (0<=(x)&&(x)<6&&0<=(y)&&(y)<6)
#define N 6
enum { West, South, East, North };
enum { LEFT, DOWN, RIGHT, UP, TOP, BOTTOM };
enum { L, D, R, U, T, B};

int g[N][N],p[4][N] = {B,D,T,U,L,R,
		               L,B,R,T,D,U,
					   T,D,B,U,R,L,
					   L,T,R,B,U,D},
	dx[] = {0,1,0,-1},used[N],
	dy[] = {-1,0,1,0},
	who[N][N],seen[N][N],yes;
char *s[] = {"BOTTOM","LEFT","RIGHT","DOWN","UP","TOP"};

void roll_it( int *c, int t, int *x, int *y ) {
	int nx,ny,nc[N],i,j,k,old[N];
	nx = *x + dx[t], ny = *y + dy[t];
	for ( i = 0; i < N; ++i ) nc[i] = c[p[t][i]];
	for ( i = 0; i < N; ++i ) old[i] = c[i];
	for ( i = 0; i < N; ++i ) c[i] = nc[i];
	*x = nx, *y = ny;
	seen[nx][ny] = yes, used[who[nx][ny] = c[B]] = yes;
}

int f( int *c, int *x, int *y, int *k ) {
	int i,t,old[N],nx,ny;
	if ( *k == N )
		return 1;
	seen[*x][*y] = yes, used[who[*x][*y] = c[B]] = yes;
	for ( t = 0; t < 4; ++t ) {
		nx = *x+dx[t], ny = *y+dy[t];
		if ( !vc(nx,ny)||!g[nx][ny]||seen[nx][ny] == yes||used[c[p[t][B]]] == yes )
			continue ;
		for ( i = 0; i < N; ++i ) old[i] = c[i];
		roll_it(c,t,x,y), ++(*k);
		if ( f(c,x,y,k) )
			return 1;
		--(*k), *x -= dx[t], *y -= dy[t], seen[nx][ny] = 0;
		for ( i = 0; i < N; ++i ) c[i] = old[i];
	}
	return *k == N;
}

int main() {
	int ts,i,j,k,x,y,t,c[N],old[N];
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( scanf("%d",&ts); ts--;) {
		for ( x = y = -1, i = 0; i < 6; ++i )
			for ( j = 0; j < 6; ++j ) 
				scanf("%d",&g[i][j]);
		for ( i = L; i <= B; ++i ) c[i] = i;
		for ( i = 0; i < N; ++i )
			for ( j = 0; j < N; ++j )
				if ( g[i][j] && ++yes && (k=1) && f(c,&i,&j,&k) )
					goto good;
		goto bad;
		good: puts(!ts?"correct":"correct\n");
			  continue ;
		bad: puts(!ts?"incorrect":"incorrect\n");
	}
	return 0;
}
