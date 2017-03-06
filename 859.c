/*
 * 859. Chinese Checkers
 * TOPIC: bfs
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define  N 		  0x80
#define  BIT(k)   (1UL<<(k))
#define  MASK(k)  (BIT(k)-1UL)
#define  SH       7
#define Q BIT(SH+SH+2)
#define vc(x,y) (0<=(x)&&(x)<m&&0<=(y)&&(y)<n)
#define enc(x,y,t) ((x) | ((y)<<SH) | ((t)<<(SH+SH+1)))
#define oo 0xfffffffful
unsigned int min( unsigned int x, unsigned int y ) { return x<y?x:y; }

int g[N][N],yes,m,n,o[N][N];
unsigned int q[Q],*head,*tail,d[Q];

void bfs( const unsigned int src ) {
	unsigned int u,v,w;
	int x,y,nx,ny,i,j,k,t,nnx,nny,ok,
		dx[] = {0,1,1,1,0},
		dy[] = {-1,-1,0,1,1};

	for ( x = 0; x < m; ++x )
		for ( y = 0; y < n; ++y )
			for ( t = 0; t <= 1; ++t )
				d[enc(x,y,t)] = +oo;

	for ( head = tail = q, d[*tail++=src]=0; head < tail; ) {
		u = *head++, x=(u&MASK(SH)),y=((u>>SH)&MASK(SH)), t = (u>>(SH+SH)), ok = 1;
		if ( t == 0 && d[u] >= 1 ) continue ;
		if ( t == 0 ) {
			assert( d[u] == 0 );
			for ( i = 0; i < 5; ++i ) {
				nx = x+dx[i], ny = y+dy[i];
				if ( !vc(nx,ny) ) continue ;
				if ( !(i&1) && g[nx][ny] != yes ) 
					if ( d[v=enc(nx,ny,0)] > d[u]+1 )
						d[*tail++ = v] = d[u]+1, ok = 0;
				if ( g[nx][ny] == yes && vc(nnx=nx+dx[i],nny=ny+dy[i]) && g[nnx][nny] != yes ) 
					if ( d[v=enc(nnx,nny,1)] > d[u]+1 )
						d[*tail++=enc(nnx,nny,1)] = d[u]+1, ok = 0;
			}
		}
		else {
			for ( i = 0; i < 5; ++i ) {
				nx = x+dx[i], ny = y+dy[i];
				if ( !vc(nx,ny) ) continue ;
				if ( g[nx][ny] == yes && vc(nnx=nx+dx[i],nny=ny+dy[i]) && g[nnx][nny] != yes ) 
					if ( d[v = enc(nnx,nny,1)] > d[u]+1 ) 
						d[*tail++ = v] = d[u]+1, ok = 0;
				/*if ( !(i&1) && g[nx][ny] != yes ) 
					if ( d[v = enc(nx,ny,0)] > d[u]+1 )
						d[*tail++ = v] = d[u]+1, ok = 0;*/
			}
		}
		if ( ok ) o[x][y] = yes;
	}
	for ( i = m-1; i >= 0; --i )
		for ( j = 0; j < n; ++j )
			if ( (w=min(d[u=enc(i,j,0)],d[v=enc(i,j,1)])) < +oo && w > 0 )
				printf("%d %d %u\n",i+1,j+1,w);
}

int main() {
	int i,j,k,ts = 0;
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	for(;2 == scanf("%d %d",&m,&n) && ++yes;) {
		if ( ++ts > 1 ) putchar('\n');
		for ( i = 0; i < 4*n; ++i ) {
			assert( 2 == scanf("%d %d",&j,&k) ); 
			g[--j][--k] = yes;
		}
		assert( 2 == scanf("%d %d",&i,&j) );
	   	--i,--j, bfs(enc(i,j,0));
	}
	return 0;
}

