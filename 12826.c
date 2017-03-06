/*
 * 12826. Incomplete Chessboard
 * TOPIC: bfs
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define enc(x,y) ((x)|((y)<<3))
#define Q (1<<10)
#define vc(x,y) (0<=(x)&&(x)<8&&0<=(y)&&(y)<8)

int ts,cs,x[3],y[3];
unsigned int q[Q],*head,*tail,d[Q];

int main()  {
	int i,j,k,xx,yy,nx,ny;
	unsigned int u,v;
	while ( 6 == scanf("%d %d %d %d %d %d",x,y,x+1,y+1,x+2,y+2) ) {
		for ( i = 0; i < 3; ++i ) --x[i], --y[i];
		for ( memset(d,0xff,sizeof d), head = tail = q, d[*tail++ = enc(x[0],y[0])] = 0; head < tail;)
			for ( u=(*head++),xx=(u&7),yy=(u>>3), i = -1; i <= 1; ++i )
				for ( j = -1; j <= 1; ++j )
					if ( vc(nx=xx+i,ny=yy+j) && !(nx==x[2] && ny==y[2]) && d[v=enc(nx,ny)] > d[u]+1 )
						d[*tail++=v]=d[u]+1;
		printf("Case %d: %u\n",++cs,d[enc(x[1],y[1])]);
	}
	return 0;
}

