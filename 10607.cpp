/*
 * 10607. Siege
 * status: Accepted
 */
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
#include <queue>
#define N 0x200
using namespace std;
#define FG (ptr = fgets(buff,sizeof(buff),stdin))
#define MAXV (1 << 16)
#define vc(x,y) (1<=(x)&&(x)<=m&&1<=(y)&&(y)<=n)
#define enc(x,u) ((x)|((u)<<SH))
#define M(k) ((1ULL<<(k))-1ULL)
#define oo 0xfffffffful

int m,n,num[256],mark,SH,
	dx[] = {-1,0,1,0},K,Q,c[N][N],
	dy[] = {0,1,0,-1},Capital;
char g[N][N],buff[0x400],*ptr;
vector<int> adj[MAXV];
unsigned int d[1 << 21],w;
bool is_bordering[1 << 21];
unsigned char id[0x400];
queue<unsigned int> q;
set<int> s[MAXV];

void dfs( int x, int y, int p ) {
	int i,nx,ny;
	for ( c[x][y] = p, i = 0; i < 4; ++i ) {
		nx = x + dx[i], ny = y + dy[i];
		if ( vc(nx,ny) && !c[nx][ny] && g[x][y] == g[nx][ny] )
			dfs(nx,ny,p);
	}
}

int main() {
	int i,j,k,l,t,x,y;
	unsigned int u,v,msk;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for (;FG && sscanf(buff,"%d %d",&m,&n) == 2 && (m||n);) {
		memset(num,-1,sizeof(num));
		for ( i = 1; i <= m; ++i )
			fgets(g[i]+1,sizeof(g[i]),stdin), g[i][n+1] = '\0';
		memset(g[m+1],'\0',sizeof(g[m+1]));
		memset(c,0,sizeof(c));
		Capital = -1;
		for ( mark = 0, i = 1; i <= m; ++i )
			for ( j = 1; j <= n; ++j )
				if ( !c[i][j] ) {
					dfs(i,j,++mark);
					if ( g[i][j] == 'A' ) {
						assert( Capital == -1 );
						Capital = mark;
					}
				}
		if ( Capital < 0 ) {
			puts("-1");
			continue ;
		}
		for ( i = 0; i <= mark; ++i ) adj[i].clear(), s[i].clear();
		for ( i = 0; i <= m+1; ++i )
			for ( j = 0; j <= n+1; ++j ) {
				if ( !i||i==m+1||!j||j==n+1 )
					x = 0;
				else x = c[i][j];
				for ( k = 0; k < 4; ++k ) {
					int ni = i+dx[k],
						nj = j+dy[k];
					if ( !vc(ni,nj) )
						continue ;
					if ( c[i][j] == c[ni][nj] )
						continue ;
					if ( s[x].find(c[ni][nj]) != s[x].end() )
						continue ;
					adj[x].push_back(c[ni][nj]);
					s[x].insert(c[ni][nj]);
				}
			}
		memset(is_bordering,0,sizeof(is_bordering));
		for ( i = 0; i < (int)adj[Capital].size(); ++i )
			is_bordering[adj[Capital][i]] = true;
		for ( i = 0; i <= mark; ++i ) d[i] = +oo;
		for ( d[0] = 0, q.push(0); !q.empty();)
			for ( x = q.front(), q.pop(), i = 0; x != Capital && i < (int)adj[x].size(); ++i ) 
				if ( d[y = adj[x][i]] > d[x]+1 )
					d[y] = d[x]+1, q.push(y);
		for ( w = +oo, x = 0; x <= mark; ++x )
			if ( (x == Capital||is_bordering[x]) && d[x] == +oo ) {
				puts("-1");
				goto next;
			}
		printf("%d\n",(int)(d[Capital]+adj[Capital].size()-2));
next: continue ;
	}
	return 0;
}


