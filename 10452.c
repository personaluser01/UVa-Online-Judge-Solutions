/*
 * 10452. Markus
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <limits.h>
#include <float.h>
#define N 0x80
#define vc(x,y) (0<=(x)&&(x)<m&&0<=(y)&&(y)<n)
#define M(k) ((1UL << ((k)))-1UL)
#define enc(x,y) ((x)|((y)<<3))
#define oo 0xfffffffful

char dir[][7] = {"forth","left","right"},
	 *iehova = "@IEHOVA#",*ptr,path[N*N],g[N][N];
int m,n,sx,sy,tx,ty,move[N][N],
	dx[] = {-1,0,0},
	dy[] = {0,-1,1};
unsigned int d[N*N],*head,*tail,queue[N*N];

void dump( int x, int y ) {
	if(x!=sx||y!=sy)
		dump(x-dx[move[x][y]],y-dy[move[x][y]]), *ptr++ = move[x][y];
}

int main() {
	int i,j,k,ts,x,y,nx,ny;
	unsigned int u,v;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( scanf("%d\n",&ts); ts-- && scanf("%d %d",&m,&n);)  {
		for(i=0;i<m;++i)
			for(scanf("%s",g[i]),j=0;j<n;++j)
				if(g[i][j]=='@')sx=i,sy=j;
				else/**/if(g[i][j]=='#')tx=i,ty=j;
		memset(d,0xfful,sizeof(d)), head = tail = queue;
		for(d[*tail++=enc(sx,sy)]=0;head<tail;)
			for(u=*head++,x=(u&M(3)),y=(u>>3),i=0;d[u]<7&&i<3;++i)
				if(vc(nx=x+dx[i],ny=y+dy[i])&&g[nx][ny]==iehova[d[u]+1])
					d[*tail++=enc(nx,ny)]=d[u]+1,move[nx][ny]=i;
		assert( d[enc(tx,ty)] < +oo );
		ptr = path, dump(tx,ty);
		for ( i = 0; i < ptr-path-1; ++i )
			printf("%s ",dir[path[i]]);
		printf("%s\n",dir[path[i]]);
	}
	return 0;
}
