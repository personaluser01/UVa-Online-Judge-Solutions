//
// Created by sj on 15/09/19.
//
#include <bits/stdc++.h>
using namespace std;
#define N (0x100)
#define vc(x,y) (0<=min(x,y) and max(x,y)<n)

unsigned int d[N][N];
queue<pair<int,int>> q;
bool untouchable[N][N];
int a[N][N],mark[N][N],n,parent[N][N];

int  main() {
    int i,j,k,x,y;
    freopen("input.txt","r",stdin);
    for ( ;1 == scanf("%d",&n); ) {
        for ( i= 0; i < n; ++i )
            for ( j= 0; j < n; ++j )
                scanf("%d",&a[i][j]);
        memset(d,0xffull,sizeof d), memset(untouchable,0,sizeof untouchable);
        for ( i= 0; i < n; ++i )
            for ( j= 0; j < n; ++j )
                if ( a[i][j] > 0 ) {
                    d[i][j]= 0, mark[i][j]= a[i][j];
                    parent[i][j]= (i|(j<<10)), q.push({i,j});
                }
        while ( not q.empty() ) {
            auto pr= q.front(); q.pop();
            x= pr.first, y= pr.second;
            for ( int nx= x-1; nx <= x+1; ++nx )
                for ( int ny= y-1; ny <= y+1; ++ny )
                    if ( abs(nx-x)+abs(ny-y) == 1 )
                        if ( vc(nx,ny) ) {
                            if ( d[nx][ny] > d[x][y]+1 ) {
                                if ( not untouchable[x][y] ) {
                                    mark[nx][ny] = mark[x][y], d[nx][ny] = d[x][y] + 1;
                                    parent[nx][ny] = parent[x][y], q.push({nx, ny});
                                }
                                else {
                                    mark[nx][ny] = 0, d[nx][ny] = d[x][y] + 1;
                                    untouchable[nx][ny]= true, q.push({nx, ny});
                                }
                            }
                            else if ( d[nx][ny] == d[x][y]+1 and (parent[nx][ny] != parent[x][y] or untouchable[x][y]) ) {
                                untouchable[nx][ny]= true, mark[nx][ny]= 0;
                            }
                        }
        }
        for ( i= 0; i < n; ++i, putchar('\n') )
            for ( printf("%d",mark[i][0]), j= 1; j < n; printf(" %d",mark[i][j++]) ) ;
    }
    return 0;
}
