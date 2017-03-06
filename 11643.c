/*
 * 11643. Knight Tour
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <limits.h>
#include <float.h>
#define M 17
#define N 0x400
#define vc(x,y) (0<=(x)&&(x)<n&&0<=(y)&&(y)<n)
#define S(x) ((x)*(x))
#define enc(x,y) ((x)|((y)<<10))
#define MASK(k) ((1UL << (k))-1UL)
#define Q (1 << 20)
#define oo 0xfffffffful
#define L(i) ((i) & ((~(i))+1))
#define xchg(x,y) (((x)==(y))||((x)^=(y),(y)^=(x),(x)^=(y)))

int ts,cs,n,is[N][N],m,
	r[N],c[N],seen[N][N],yes;
unsigned int q[Q],*head,*tail,g[M][M],
			 z[1 << M][M],d[Q],dist[Q];
char who[1 << M];

void bfs() {
	int x,y,nx,ny,i,j,k,l,t = 1,
		sx = 0, sy = 0;
	unsigned int u,v;
	for ( seen[sx][sy]=++yes,head=tail=q,d[*tail++=enc(sx,sy)]=0;head<tail;)
		for ( u=*head++, x = u&MASK(10), y = u>>10, i = -2; i <= 2; ++i )
			for ( j = -2; j <= 2; ++j )
				if ( S(i)+S(j) == 5 ) {
					nx = x+i, ny = y+j;
					if ( !vc(nx,ny)||seen[nx][ny] == yes )
						continue ;
					seen[nx][ny]=yes,d[*tail++=v=enc(nx,ny)]=d[u]+1;
				}
}

void bfs2( int sx, int sy, int idx ) {
	int x,y,nx,ny,i,j,k,l,t = 1;
	unsigned int u,v;
	for ( seen[sx][sy]=++yes,head=tail=q,d[*tail++=enc(sx,sy)]=0;head<tail;)
		for ( u=*head++, x = u&MASK(10), y = u>>10, i = -2; i <= 2; ++i )
			for ( j = -2; j <= 2; ++j )
				if ( S(i)+S(j) == 5 ) {
					nx = x+i, ny = y+j;
					if ( !vc(nx,ny)||seen[nx][ny] == yes )
						continue ;
					seen[nx][ny]=yes,d[*tail++=v=enc(nx,ny)]=d[u]+1;
					if ( is[nx][ny] >= 0 )
						g[idx][is[nx][ny]] = d[v];
				}
}


unsigned int 
sssp( unsigned int src, unsigned int dst ) {
	unsigned int u,v;
	int i,j,k,l,t,x,y,nx,ny;
	head=tail=q;
	dist[dst]=+oo;
	seen[src&MASK(10)][src>>10] = ++yes;
	for(dist[*tail++=src]=0;head < tail&&dist[dst] == +oo;)
		for ( u = *head++, x = u&MASK(10), y = u>>10, i = -2; i <= 2; ++i )
			for ( j = -2; j <= 2; ++j )
				if ( S(i)+S(j) == 5 ) {
					nx = x+i, ny = y+j;
					if ( !vc(nx,ny) ) continue ;
					if ( seen[nx][ny] == yes )
						continue ;
					seen[nx][ny] = yes;
					dist[*tail++=v=enc(nx,ny)] = dist[u]+1;
				}
	return dist[dst];
}

unsigned int min( unsigned int x, unsigned int y ) {
	return x < y ? x:y;
}

int main() {
	int i,j,k,l,t,sx,sy,tx,ty;
	unsigned int u,v,w,e,s;
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	for ( i = 0; i < M; ++i ) who[1 << i] = i;
	n = N, bfs();
	for ( scanf("%d",&ts); ts-- && 2 == scanf("%d %d",&n,&m);) {
		for ( i = 0; i < n; ++i )
			for ( j = 0; j < n; ++j )
				is[i][j] = -1;
		for ( i = 0; i < m; ++i )
			scanf("%d %d",&r[i],&c[i]), is[--r[i]][--c[i]] = i;
		if ( m == 1 ) {
			w = 0;
			goto next;
		}
		for ( i = 0; i < m; ++i )
			for ( g[i][i] = 0, j = i+1; j < m; ++j ) {
				sx = r[i], sy = c[i];
				tx = r[j], ty = c[j];
				g[i][j] = g[j][i] = d[enc(abs(tx-sx),abs(ty-sy))];
				if ( abs(sx-tx)+abs(sy-ty) < 20 ) {
					g[i][j] = g[j][i] = sssp(enc(sx,sy),enc(tx,ty));
					continue ;
				}
				if ( (sx==0&&sy==0&&tx==1&&ty==1)||(sx==1&&sy==1&&tx==0&&ty==0)||(sx==n-1&&sy==n-1&&tx==n-2&&ty==n-2) ) {
					g[i][j] = g[j][i] = sssp(enc(sx,sy),enc(tx,ty));
					continue ;
				}
				if ( (sx==n-2&&sy==n-2&&tx==n-1&&ty==n-1)||(sx==n-1&&sy==0&&tx==n-2&&ty==1) ) {
					/*g[i][j] = g[j][i] = min(g[i][j],sssp(enc(sx,sy),enc(tx,ty)));*/
					g[i][j] = g[j][i] = sssp(enc(sx,sy),enc(tx,ty));
					continue ;
				}
				if ( (sx==n-2&&sy==1&&tx==n-1&&ty==0) ) {
					/*g[i][j] = g[j][i] = min(g[i][j],sssp(enc(sx,sy),enc(tx,ty)));*/
					g[i][j] = g[j][i] = sssp(enc(sx,sy),enc(tx,ty));
					continue ;
				}
				if ( (sx==0&&sy==n-1&&tx==1&&ty==n-2) ) {
					/*g[i][j] = g[j][i] = min(g[i][j],sssp(enc(sx,sy),enc(tx,ty)));*/
					g[i][j] = g[j][i] = sssp(enc(sx,sy),enc(tx,ty));
					continue ;
				}
				if ( (sx==1&&sy==n-2&&tx==0&&ty==n-1) ) {
					/*g[i][j] = g[j][i] = min(g[i][j],sssp(enc(sx,sy),enc(tx,ty)));*/
					g[i][j] = g[j][i] = sssp(enc(sx,sy),enc(tx,ty));
					continue ;
				}
			}
		/*for ( i = 0; i < m; ++i ) g[i][i] = 0, bfs2(r[i],c[i],i);*/
		for ( u = 0; u < (1UL<<m); ++u )
			for ( i = 0; i < m; ++i )
				z[u][i] = +oo;
		for ( z[1<<0][0] = 0, u = 0; u < (1UL << m); ++u )
			for ( v = u; v && (i = who[L(v)]) >= 0; v -= L(v) )
				if ( z[u][i] < +oo )
				for ( w = (~u)&MASK(m), e = w; e && (j = who[L(e)]) >= 0; e -= L(e) )
					if ( z[s=u|(1UL<<j)][j] > z[u][i]+g[i][j] )
						z[s][j] = z[u][i]+g[i][j];
		for ( w = +oo, i = 1; i < m; ++i )
			if ( w > z[MASK(m)][i] + g[i][0] )
				w = z[MASK(m)][i] + g[i][0];
		next:
		 printf("Case %d: %u\n",++cs,w);
	}
	return 0;
}

