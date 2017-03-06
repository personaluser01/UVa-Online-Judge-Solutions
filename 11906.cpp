/*
 * 11906. Gridland
 * status: Accepted
 */
#include <cassert>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define N 0x80
#define vc(x,y) (0<=(x)&&(x)<m&&0<=(y)&&(y)<n)
#include <set>
using namespace std;

int m,n,a,b,seen[N][N],yes,z[N][N],dt[4],M;
bool water[N][N];

void dfs( int x, int y ) {
	int nx,ny,i,j,k = 0;
	assert( seen[x][y] != yes );
	set<pair<int,int> > s;
	for ( s.clear(), s.insert(make_pair(x,y)), seen[x][y] = yes, z[x][y] = 0, i = 0; i < M; ++i )
		for ( j = 0; j < M; ++j )
				if ( ((i-j)&1) && vc(nx=x+dt[i],ny=y+dt[j]) )
					if ( !water[nx][ny] && ++k ) {
						if ( s.find(make_pair(nx,ny)) != s.end() )
							continue ;
						s.insert(make_pair(nx,ny));
						++z[x][y],z[x][y]&=1;
						if ( seen[nx][ny] != yes )
							dfs(nx,ny);
					}
	// printf("z[%d][%d] = %d\n",x,y,k);
}

int main() {
	int i,j,k,ts,cs = 0,c[2];
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	for ( scanf("%d",&ts); ts-- && printf("Case %d: ",++cs); printf("%d %d\n",c[0],c[1]) ) {
		scanf("%d %d %d %d",&m,&n,&a,&b);
		dt[0] = -(dt[2] = a), dt[1] = -(dt[3] = b), M = 4;
		memset(water,0,sizeof water);
		for ( scanf("%d",&k); k-- && 2 == scanf("%d %d",&i,&j); water[i][j] = 1 );
		for(c[0]=c[1]=0,++yes,dfs(0,0),i=0;i<m;++i)
			for(j=0;j<n;++j)
				if(seen[i][j]==yes)
					++c[z[i][j]];
		if ( !a&&!b ) c[0]=c[1]=0;
	}
	return 0;
}

