/*
 * 989 How Many?
 * status: Accepted
 */
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <queue>
#define N 22
using namespace std;
typedef long long i64;
#define mp make_pair
enum {UP=0,DOWN=1};

typedef pair<pair<int,int>,pair<int,char> > state;
queue<state> q;
i64 z[2*N][N][N][2];
char cnt[2*N][N][N][2];
bool is[2][2*N][N];
queue<pair<int,int> > Q;

void update( int x, int y, int j, char t, i64 w ) {
	z[x][y][j][t] += w;
	if ( !--cnt[x][y][j][t] )
		q.push(mp(mp(x,y),mp(j,t)));
}

int main() {
	int n,r,K,i,j,k,t,x,y,nx,ny;
	i64 w;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	while ( 3 == scanf("%d %d %d",&n,&r,&K) ) {
		memset(z,0,sizeof(z));
		memset(cnt,0,sizeof(cnt));
		memset(is,0,sizeof(is));
		for ( Q.push(mp(0,0)), is[0][0][0] = true; !Q.empty(); ) {
			pair<int,int> tmp = Q.front();
			Q.pop();
			x = tmp.first, y = tmp.second;
			nx = x + 1, ny = y-1;
			if ( nx <= 2*n && ny >= 0 )
				if ( !is[0][nx][ny] )
					Q.push(mp(nx,ny)),is[0][nx][ny] = true;
			nx = x+1, ny = y+1;
			if ( nx <= 2*n && ny <= n )
				if ( !is[0][nx][ny] )
					Q.push(mp(nx,ny)), is[0][nx][ny] = true;
		}
		for ( Q.push(mp(2*n,0)), is[1][2*n][0] = true; !Q.empty(); ) {
			pair<int,int> tmp = Q.front();
			Q.pop();
			x = tmp.first, y = tmp.second;
			nx = x - 1, ny = y-1;
			if ( nx >= 0 && ny >= 0 )
				if ( !is[1][nx][ny] )
					Q.push(mp(nx,ny)),is[1][nx][ny] = true;
			nx = x-1, ny = y+1;
			if ( nx >= 0 && ny <= n )
				if ( !is[1][nx][ny] )
					Q.push(mp(nx,ny)), is[1][nx][ny] = true;
		}
		for ( cnt[1][1][0][UP] = 1, x = 2; x <= 2*n; ++x )
			for ( y = 0; y <= x && y <= n; ++y ) {
				if ( !is[0][x][y] || !is[1][x][y] )
					continue ;
				if ( y-1 >= 0 ) {
					for ( j = 0; j <= r; ++j )
						if ( cnt[x-1][y-1][j][UP] || cnt[x-1][y-1][j][DOWN] )
							++cnt[x][y][j][UP];
				}
				if ( y == K-1 ) {
					for ( j = 1; j <= r; ++j )
						if ( cnt[x-1][y+1][j-1][UP] )
							++cnt[x][y][j][DOWN];
					for ( j = 0; j <= r; ++j )
						if ( cnt[x-1][y+1][j][DOWN] )
							++cnt[x][y][j][DOWN];
				}
				else {
					for ( j = 0; j <= r; ++j )
						if (cnt[x-1][y+1][j][UP]||cnt[x-1][y+1][j][DOWN])
							++cnt[x][y][j][DOWN];
				}
			}
		q.push(mp(mp(1,1),mp(0,0))), z[1][1][0][UP] = 1, cnt[1][1][0][UP] = 0;
		while ( !q.empty() ) {
			state s = q.front();
			q.pop();
			x = s.first.first, y = s.first.second, j = s.second.first, t = s.second.second;
			if (x>=2*n+1||j>r)
				continue ;
			w = z[x][y][j][t];
			if ( y == K && t == UP ) {
				update(x+1,y-1,j+1,DOWN,w);
				update(x+1,y+1,j,UP,w);
				continue ;
			}
			if ( y == 0 ) {
				update(x+1,y+1,j,UP,w);
				continue ;
			}
			update(x+1,y+1,j,UP,w);
			update(x+1,y-1,j,DOWN,w);
		}
		printf("%lld\n",z[2*n][0][r][DOWN]);
	}
	return 0;
}
