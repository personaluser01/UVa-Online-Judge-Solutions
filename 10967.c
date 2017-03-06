/*
 * 10967. The Great Escape
 * TOPIC: dijkstra
 * status: Accepted
 */
#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BIT(k) (1UL<<(k))
#define MASK(k) (BIT(k)-1UL)
#define N 0x80
#define vc(x,y) (0<=(x)&&(x)<m&&0<=(y)&&(y)<n)
#define enc(x,y,dir) ((x)|((y)<<7)|((dir)<<14))
#define Q (1<<18)
#define xchg(x,y) (((x)==(y))||((x)^=(y),(y)^=(x),(x)^=(y)))
#define bubble (xchg(pos[heap[i]],pos[heap[j]]),xchg(heap[i],heap[j]))
#define oo 0xfffffffful

int ts,m,n,sx[0x200],sy[0x200],doors,
	id[N][N],tm[0x200],
	dx[]={-1,0,1,0},
	dy[]={0,-1,0,1},
	heap[Q],cnt,pos[Q],inq[Q],yes;
char g[N][N],which[256];
const char *alph = "NWSE";
unsigned int d[Q];

void push( unsigned int x ) {
	int i,j;
	if ( pos[x] < 0 ) pos[heap[cnt]=x]=cnt,++cnt,inq[x]=yes;
	for ( j = pos[x]; j && d[heap[i=(j-1)>>1]] > d[heap[j]]; bubble, j = i ) ;
}

unsigned int dw( int x, int y, int t ) {
	if ( t == 2 ) 
		return 2*tm[id[x][y]];
	if ( t == 1 || t == 3 )
		return tm[id[x][y]];
	return 0;
}

unsigned int pop() {
	int i,j;
	unsigned int x = *heap;
	if ( (pos[x]=-1,--cnt) )
		pos[*heap=heap[cnt]]=0;
	for ( j = 0; (i=j,j<<=1,++j) < cnt; bubble ) {
		if ( j < cnt-1 && d[heap[j+1]] < d[heap[j]] ) ++j;
		if ( d[heap[i]] <= d[heap[j]] ) break ;
	}
	return x;
}

unsigned int 
dijkstra() {
	int i,j,k,t,x,y,nx,ny,nnx,nny;
	unsigned int u,v,w = +oo;
	for ( x = 0; x < m; ++x )
		for ( y = 0; y < n; ++y )
			for ( i = 0; i < 4; ++i )
				d[u = enc(x,y,i)] = +oo, pos[u] = -1;
	++yes, d[u=enc(m-1,0,0)] = 0, push(u);
	for(;cnt;) {
		u=pop(),x=(u&MASK(7)),y=((u>>7)&MASK(7)),k=(u>>14);
		if ( x == 0 && y == n-1 ) 
			if ( w > d[u] ) w = d[u];
		if ( w <= d[u] ) continue ;
		if ( g[x][y] == '.' ) {
			for ( k = 0; k < 4; ++k ) {
				nx = x+dx[k], ny = y+dy[k];
				if ( !vc(nx,ny)||g[nx][ny] == '#' ) continue ;
				if ( g[nx][ny] == '.' ) {
					/*for ( i = 0; i < 4; ++i ) 
						if ( ((k-i+4)&3) != 2 )*/
							if ( d[v=enc(nx,ny,0)]>d[u]+1 )
								d[v]=d[u]+1,push(v);
					continue ;
				}
				assert(isupper(g[nx][ny]));
				j = which[g[nx][ny]];
				if ( ((k-j+4)&3) != 2 ) continue ;
				for ( t = 1; t < 4; ++t ) 
					if ( d[v=enc(nx,ny,(t+j)&3)]>d[u]+dw(nx,ny,t)+1 )
						d[v]=d[u]+dw(nx,ny,t)+1, push(v);
			}
		}
		else {
			nx = x+dx[k], ny = y+dy[k];
			if ( !vc(nx,ny)||g[nx][ny] == '#' ) continue ;
			if ( g[nx][ny] == '.' ) {
				/*for ( i = 0; i < 4; ++i ) 
					if ( ((k-i+4)&3) != 2 )*/
						if ( inq[v=enc(nx,ny,0)] != yes || d[v]>d[u]+1 )
							d[v]=d[u]+1,push(v);
				continue ;
			}
			assert(isupper(g[nx][ny]));
			j = which[g[nx][ny]];
			if ( ((k-j+4)&3) != 2 ) continue ;
			for ( t = 1; t < 4; ++t ) 
				if ( inq[v=enc(nx,ny,(t+j)&3)] != yes || d[v] > d[u]+dw(nx,ny,t)+1 )
					d[v]=d[u]+dw(nx,ny,t)+1, push(v);
		}
	}
	return w;
}

int main() {
	int i,j,k;
	unsigned int w;
#ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
#endif
	for ( i = 0; i < 4; ++i ) which[alph[i]] = i;
	for ( scanf("%d",&ts); ts-- && 2 == scanf("%d %d",&m,&n); ) {
		for ( doors = 0, i = 0; i < m; ++i ) 
			for ( scanf("%s",g[i]), j = 0; j < n; ++j ) 
				if ( (id[i][j]=-1) && isupper(g[i][j]) ) 
					id[sx[doors]=i][sy[doors]=j]=doors,++doors;
		for ( i = 0; i < doors; scanf("%d",&tm[i++]) );
		if ( (w=dijkstra()) < +oo )
			printf("%u\n",w);
		else puts("Poor Kianoosh");
	}
    return 0;
}

