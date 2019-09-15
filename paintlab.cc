//
// Created by sj on 14/09/19.
//
#include <bits/stdc++.h>
#define N 35
#define vc(x,y) (1<=(x) and (x)<=n and 1<=(y) and (y)<=n)
enum { WALL= '#', SPACE= '.' };
#define MY_LEFT(k) (((k)+3)&3)
#define MY_RIGHT(k) (((k)+1)&3)
#define valid(x,y) (0<=(x) and (x) <= n+1 and  0<=(y) and (y) <= n+1)
using namespace std;
using t_state= unsigned int;

char g[N][N];
int dx[]= {-1,0,1,0},
    dy[]= {0,1,0,-1},n;
bool seen[N][N][5];

bool good_state( int x, int y, int t) {
    return vc(x,y) and g[x][y] == SPACE and valid(x+dx[MY_LEFT(t)],y+dy[MY_LEFT(t)]) and
           g[x+dx[MY_LEFT(t)]][y+dy[MY_LEFT(t)]] == WALL;
}

void bfs( int sx, int sy, int t, int &res ) {
#define enc(x,y,t) ((x)|((y)<<6)|((t)<<12))
    assert( good_state(sx,sy,t) );
    if ( seen[sx][sy][t] ) return ;
    queue<t_state> q;
    for ( seen[sx][sy][t]= true, q.push(enc(sx,sy,t)); not q.empty(); ) {
        auto u = q.front(); q.pop(), ++res;
        int x= (u&63), y= ((u>>6)&63), i= (u>>12), nx= x+dx[i], ny= y+dy[i];
        assert( good_state(x,y,i) );
        if ( good_state(nx,ny,i) and not seen[nx][ny][i] ) {
            seen[nx][ny][i]= true, q.push(enc(nx,ny,i));
        }
        else if ( g[nx][ny] == WALL and not seen[x][y][MY_RIGHT(i)] ) {
            assert( good_state(x,y,MY_RIGHT(i)) );
            seen[x][y][MY_RIGHT(i)]= true, q.push(enc(x,y,MY_RIGHT(i)));
        }
        else if ( vc(nx,ny) and g[nx][ny] == SPACE ) {
            int j= MY_LEFT(i);
            nx+= dx[j], ny+= dy[j];
            if ( good_state(nx,ny,j) and not seen[nx][ny][j] )
                seen[nx][ny][j]= true, q.push(enc(nx,ny,j));
        }
    }
}

void seed( int x, int y ) {
    if ( seen[x][y][4] ) return ;
    seen[x][y][4]= true;
    for ( int i= 0; i < 4; ++i )
        if ( vc(x+dx[i],y+dy[i]) and g[x+dx[i]][y+dy[i]] == SPACE )
            seed(x+dx[i],y+dy[i]);
}

int main() {
    int i,j,res;
    freopen("input.txt","r",stdin);
    for (;1==scanf("%d",&n);printf("%d\n",(res-4)*9)) {
        for ( memset(g,WALL,sizeof g), i= 1; i <= n; scanf("%s",1+g[i++]), g[i-1][n+1]= WALL ) ;
        memset(seen,0,sizeof seen), seed(1,1), seed(n,n);
        for ( res= 0, i= 1; i <= n; ++i )
            for ( j= 1; j <= n; ++j )
                for ( int l= 0; l < 4 and seen[i][j][4]; ++l )
                    if ( good_state(i,j,l) )
                        bfs(i,j,l,res);
    }
    return 0;
}
