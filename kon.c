#include <assert.h> 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 64
#define valid_cell(x,y) (0<=(x)&&(x)<n&&0<=(y)&&(y)<n)
#define enc(x,y) ((x) | ((y) << 6))
#define M(k) ((1UL << (k))-1UL)
#define oo 0xfffffffful

int n,posx[2],posy[2],
	dx[] = {-2,-1,1,2},
	dy[] = {-2,-1,1,2},
	q[N*N],*head,*tail;
unsigned int d[1 << 13],move[1 << 13];
char g[N][N]; 

void dump( unsigned int u ) {
	int x,y;
	if ( move[u] < +oo ) {
		x = move[u] & M(6), y = move[u] >> 6;
		g[x][y] = '@';
		dump(move[u]);
	}
}

int main() {
	int i,j,k,x,y,nx,ny;
	unsigned int u,v,dst;
	freopen("input.txt","r",stdin);
	  freopen("output.txt","w",stdout);
	while ( 1 == scanf("%d",&n) ) {
		for ( i = 0; i < n; ++i )
			scanf("%s",g[i]);
		for ( k = 0, i = 0; i < n; ++i )
			for ( j = 0; j < n; ++j )
				if ( g[i][j] == '@' )
					posx[k] = i, posy[k] = j, ++k;
		assert( k == 2 );
		memset(d,0xff,sizeof(d)), head = tail = q;
		for ( d[*tail++ = u = enc(posx[0],posy[0])] = 0, move[u] = +oo; head < tail; )
			for ( u = *head++, x = u & M(6), y = u >> 6, i = 0; i < 4; ++i )
				for ( j = 0; j < 4; ++j )
					if ( abs(dx[i]) + abs(dy[j]) == 3 ) {
						nx = x + dx[i], ny = y + dy[j];
						if ( valid_cell(nx,ny) && g[nx][ny] != '#' && d[v = enc(nx,ny)] > d[u] + 1 )
							d[*tail++ = v] = d[move[v] = u] + 1;
					}
		if ( d[dst = enc(posx[1],posy[1])] < +oo )
			for ( dump(dst), i = 0; i < n;	puts(g[i++]) );
		else puts("Impossible");
	}
	return 0;
}


