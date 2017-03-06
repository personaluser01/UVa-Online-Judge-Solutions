/*
 * 10592. Freedom Fighter
 * status: Accepted
 * TOPIC: DFS, floodfill
 */
#include <cassert>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#define N 64
#define vc(x,y) (0<=(x)&&(x)<n&&0<=(y)&&(y)<n)
#include <set>
using namespace std;
const char *str = "BP";

int n,e[N][N],cc,seen[N][N],yes,visited[N][N],indeed,cd[256],id[N][N],
	dx[] = {-1,0,1,0},
	dy[] = {0,-1,0,1},m[2];
char g[N][N];
vector<pair<int,int> > v[2];

void floodfill( int x, int y, int mark ) {
	int i,nx,ny;
	assert( seen[x][y] != yes );
	if ( g[x][y] == 'B' || g[x][y] == 'P' )
		v[cd[g[x][y]]].push_back(make_pair(x,y));
	for ( seen[x][y] = yes, e[x][y] = mark, i = 0; i < 4; ++i ) {
		nx = x+dx[i], ny = y+dy[i];
		if ( vc(nx,ny) && seen[nx][ny] != yes && g[nx][ny] != '.' )
			floodfill(nx,ny,mark);
	}
}

void fill_group( int x, int y, const int mark, int idx, const char ch ) {
	int i,nx,ny;

	assert( vc(x,y) && g[x][y] == ch );
	for ( id[x][y] = idx, visited[x][y] = indeed, i = 0; i < 4; ++i ) {
		nx = x+dx[i], ny = y+dy[i];
		if ( !vc(nx,ny) || indeed == visited[nx][ny] || e[nx][ny] != mark ) continue ;
		if ( g[nx][ny] == ch ) fill_group(nx,ny,mark,idx,ch);
	}
}

int main() {
	int i,j,k,l,t,nx,ny,x,y,sector,ans;
	set<int> s[2];
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	for ( cd['B'] = 0, cd['P'] = 1 ;1 == scanf("%d",&n) && n >= 1; ) {
		for ( i = 0; i < n; scanf("%s",g[i++]) );
		for ( ++yes, ans = 0, sector = 0, cc = 0, i = 0; i < n; ++i )
			for ( j = 0; j < n; ++j )
				if ( g[i][j] != '.' && seen[i][j] != yes ) {
					v[0].clear(), v[1].clear(), floodfill(i,j,++cc);
					for ( t = 0; t <= 1; ++t )
						for ( m[t] = 0, ++indeed, k = 0; k < (int)v[t].size(); ++k )
							if ( visited[v[t][k].first][v[t][k].second] != indeed )
								fill_group(v[t][k].first,v[t][k].second,cc,++m[t],str[t]);
					for ( s[0].clear(), s[1].clear(), l = 0; l < (int)v[0].size(); ++l ) {
						x = v[0][l].first, y = v[0][l].second;
						for ( k = 0; k < 4; ++k ) {
							nx = x+dx[k], ny = y+dy[k];
							if ( !vc(nx,ny) || g[nx][ny] == '.' || g[nx][ny] == '*' ) continue ;
							if ( g[nx][ny] != g[x][y] )
								s[0].insert(id[x][y]), s[1].insert(id[nx][ny]);
						}
					}
					ans += s[0].size(), ans += s[1].size();
					printf("Sector #%d: contain %d freedom fighter group(s) & %d enemy group(s)\n",++sector,m[0],m[1]);
				}
		printf("Total %d group(s) are in fighting position.\n\n",ans);
	}
	return 0;
}

