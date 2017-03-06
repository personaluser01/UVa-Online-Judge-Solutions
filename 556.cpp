/*
 * 556. Amazing
 * status: Accepted
 * TOPIC: mazes, right-hand rule, bfs, states
 */
#include <cassert>
#include <cstdio>
#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <cmath>
#include <vector>
#define SH 10
#define N 0x400
#define vc(x,y) (0<=(x)&&(x)<=m+1&&0<=(y)&&(y)<=n+1)
#define BIT(k) (1ULL<<(k))
#define MASK(k) (BIT(k)-1ULL)
#define enc(x,y,t) ((x)|((y)<<SH)|((t)<<(SH+SH)))
#include <queue>
using namespace std;

int m,n,c[1 << 20],h[5],in[1 << 20],out[1 << 20];
char g[N][N],
     dx[] = {0,-1,0,1},
     dy[] = {1,0,-1,0};
queue<unsigned int> q;

int main() {
    int i,j,k,x,y,nx,ny,nnx,nny,nnt,t,K,walls;
    unsigned int u,v,src;
#ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
#endif
    for (;2 == scanf("%d %d",&m,&n) && (m||n);) {
        for ( i = 0; i <= m+1; ++i)
            for ( j = 0; j <= n+1; ++j )
                g[i][j] = '1', c[i|(j<<SH)] = 0, in[i|(j<<SH)] = out[i|(j<<SH)] = 0;
        for ( i = 1; i <= m; scanf("%s",g[i]+1), g[i++][n+1] = '1' );
        assert( g[m][1] == '0' );
        for(;!q.empty();q.pop());
        K = 0, walls = 0;
        for ( i = 1; i <= m; ++i )
            for ( j = 1; j <= n; ++j )
                if ( g[i][j] == '1' )
                    ++walls;
        for(q.push(src=u=enc(m,1,0)),++c[src&MASK(SH+SH)],++out[src&MASK(SH+SH)];c[src&MASK(SH+SH)] < 2;){
            u = q.front(), q.pop();
            x = (u&MASK(SH)), y = ((u>>SH)&MASK(SH)), t = (u>>(SH+SH));
            for ( k = 0, nx = x+dx[t], ny = y+dy[t]; ((!vc(nx,ny))||g[nx][ny]=='1'); ++k ) 
                t=((t+1)%4), nx=x+dx[t], ny=y+dy[t];
            // printf("At (%d,%d) with %d\n",nx,ny,t);
            nnx = nx+dx[(t+3)%4], nny = ny+dy[(t+3)%4];
            // printf("probing (%d,%d) from (%d,%d)\n",nnx,nny,nx,ny);
            if ( !vc(nnx,nny) || g[nnx][nny] == '1' )
                v = enc(nx,ny,t);
            else {
                v = enc(nx,ny,t), ++in[v&MASK(SH+SH)], ++out[v&MASK(SH+SH)];
                nnt = ((t+3)&3), v = enc(nnx,nny,nnt);
            }
            ++in[v&MASK(SH+SH)], ++out[u&MASK(SH+SH)];
            ++c[v&MASK(SH+SH)], q.push(v);
            // if ( ++K >= 20 ) break ;
            if ( in[src&MASK(SH+SH)] ) break ;
        }
        for ( memset(h,0,sizeof h), i = 1; i <= m; ++i )
            for ( j = 1; j <= n; ++j )
                ++h[min(in[i|(j<<SH)],out[i|(j<<SH)])];
        h[0] = h[0]-walls;
        for ( k = 0; k <= 4; printf("%3d",h[k++]) );
        putchar('\n');
    }
    return 0;
}

