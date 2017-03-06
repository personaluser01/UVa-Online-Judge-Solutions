/*
 * 1198. The Geodetic Set Problem
 * TOPIC: bfs
 * status: Accepted
 */
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 0x40
#define BIT(k) (1ULL<<(k))
#define MASK(k) (BIT(k)-1ULL)
#define L(u) ((u)&((~(u))+1ULL))
#define FG (ptr=fgets(buff,sizeof buff,stdin))
typedef unsigned long long u64;
#define oo 0xfffffffful

int n,m,v[N],seen[2][N],yes[2];
char buff[0x400],which[BIT(21)],*ptr;
unsigned int d[2][N][N];
u64 u[N][N],g[N];

int who( u64 u ) { return u>=BIT(20)?20+which[u>>20]:which[u]; }

void bfs( int src, int dst, int t ) {
	int x,y,i,j,k,q[N],*head,*tail;
	u64 v;
	for ( head=tail=q,d[t][src][dst]=+oo,d[t][src][src]=0,seen[t][*tail++=src]=++yes[t]; head < tail; )
		for ( v = g[x=*head++]; v; v &= ~L(v) )
			if ( seen[t][y=who(L(v))] != yes[t] )
				seen[t][*tail++=y]=yes[t], d[t][src][y]=d[t][src][x]+1;
}

int main() {
	int i,j,k,ts;
	u64 w;
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	for ( i = 0; i < 21; ++i ) which[BIT(i)] = i;
	for ( ;FG && 1 == sscanf(ptr,"%d",&n); ) {
		for ( i = 0; i < n; ++i )
			for ( g[i] = 0, j = 0; j < n; u[i][j++] = 0 );
		for ( i = 0; i < n; ++i ) 
			for ( FG, k = 0; 1 == sscanf(ptr,"%d%n",&j,&k); ptr += k, --j, g[i] |= BIT(j), g[j] |= BIT(i) );
		for ( i = 0; i < n; ++i )
			for ( j = i+1; j < n; ++j ) {
				bfs(i,j,0), bfs(j,i,1);
				if ( d[0][i][j] == +oo ) continue ;
				for ( k = 0; k < n; ++k ) 
					if ( seen[0][k] == yes[0] && seen[1][k] == yes[1] )
						if ( d[0][i][k]+d[1][j][k] == d[0][i][j] )
							u[i][j] |= BIT(k);
			}
		for ( sscanf(FG,"%d",&ts); ts--; ) {
			for ( m = 0, FG, k = 0; 1 == sscanf(ptr,"%d%n",&j,&k); ptr += k, v[m++] = --j );
			for ( w = 0, i = 0; i < m; ++i )
				for ( j = 0; j < m; ++j )
					w |= u[v[i]][v[j]];
			puts(w==MASK(n)?"yes":"no");
		}
	}
	return 0;
}

