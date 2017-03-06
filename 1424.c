/*
 * 1424. Salesmen
 * TOPIC: dp, bfs
 * status: Accepted
 */
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 0x80
#define M 2*N
#define Q (1<<21)
#define oo 0xfffffffful
#define enc(x,y) ((x)|((y)<<8))

int adj[N][N],deg[N],m,n,c[M];
unsigned int z[Q],*head,*tail,q[Q],w;

int main() {
	int i,j,k,ts,x,y;
	unsigned int u,v;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( scanf("%d",&ts); ts--; printf("%u\n",w) ) {
		scanf("%d %d",&n,&m);
		for ( i = 0; i < n; deg[i++] = 0 );
		for ( k=m; k-- && 2==scanf("%d %d",&i,&j);\
		--i,--j,adj[i][deg[i]++]=j,adj[j][deg[j]++]=i );
		for ( scanf("%d",&m), k = 0; k < m && 1 == scanf("%d",&c[k++]); --c[k-1] );
		for ( memset(z,0xff,sizeof z), head = tail = q, i = 0; i < n; ++i )
			if ( i == c[0] )
				z[*tail++=u=enc(0,i)] = 0;
			else z[*tail++=u=enc(0,i)] = 1;
		for ( ;head < tail; ) {
			for ( u = *head++, i = (u&255), x = (u>>8), k=0; k < deg[x] && i+1<m; ++k ) 
				if ( c[i+1] == (y=adj[x][k]) ) {
					if ( z[v = enc(i+1,y)] > z[u] )
						z[*tail++ = v] = z[u];
				}
				else {
					if ( z[v = enc(i+1,y)] > z[u]+1 )
						z[*tail++ = v] = z[u]+1;
				}
			if ( i+1 < m && c[i+1] == x )
				if ( z[v = enc(i+1,x)] > z[u] )
					z[*tail++ = v] = z[u];
		}
		for ( w = +oo, x = 0; x < n; ++x )
			if ( w > z[u = enc(m-1,x)] )
				w = z[u];
	}
	return 0;
}

