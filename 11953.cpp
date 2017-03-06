/*
 * 11953.
 * status: Accepted
 */
#include <cassert>
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define vc(x,y) (0<=(x)&&(x)<m&&0<=(y)&&(y)<n)
#define N 0x400
using namespace std;

int m,n,seen[N][N],yes,a,b,ans,ships,
	dx[] = {-1,0,1,0},
	dy[] = {0,-1,0,1};
char g[N][N],e[N][N];

void dfs( int x, int y, int t ) {
	int nx,ny,i,j,k,l;
	if ( seen[x][y] == yes ) return ;
	if ( g[x][y] == '@' ) ++b;
	else { assert(g[x][y] == 'x'); ++a; }
	for ( e[x][y] = '#', seen[x][y] = yes, i = t; i < 4; i += 2 ) {
		nx = x+dx[i], ny = y+dy[i];
		if ( !vc(nx,ny) || g[nx][ny] == '.' || seen[nx][ny] == yes ) continue ;
		dfs(nx,ny,t);
	}
}

int main() {
	int i,j,k,l,t,cs = 0,ts;
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	for ( scanf("%d",&ts); ts-- && printf("Case %d: ",++cs) && 1 == scanf("%d",&n); printf("%d\n",ships-ans) ) {
		for ( i = 0; i < n; ++i )
			for ( j = 0; j < n; ++j )
				e[i][j] = '.';
		for ( m = n, i = 0; i < m; scanf("%s",g[i++]) );
		for ( ships = ans = 0, ++yes, i = 0; i < m; ++i )
			for ( j = 0; j < n; ++j )
				if ( seen[i][j] != yes && g[i][j] != '.' && e[i][j] != '#' ) {
					++ships;
					a = b = 0, ++yes, dfs(i,j,0), l = a, t = b;
					a = b = 0, ++yes, dfs(i,j,1);
					assert( a+b <= n/2 );
					assert( l+t <= n/2 );
					if ( a+b > l+t ) {
						if ( !a ) ++ans;
					}
					else if ( !l ) ++ans;
				}
	}
	return 0;
}

