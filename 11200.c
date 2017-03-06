/*
 * 11200. Sapitaur's Labirynth
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
#define SH 9
#define N (1 << (SH+2))
#define Q (1 << 21)
#define MASK(k) ((1UL<<(k))-1UL)
#define vc(x,y) (1<=(x)&&(x)<=m&&1<=(y)&&(y)<=n)
typedef unsigned long long u64;
#define oo 0xffffffffffffffffull

int ts,cs,m,n,last[Q],next[Q],E;
char indeg[Q];
unsigned int to[Q];
unsigned long long z[Q],w,q[Q],*head,*tail;
char g[512][512],
	 dx[] = {-1,0,0,1},
	 dy[] = {0,-1,1,0};

void add_arc( unsigned int u, unsigned int v ) {
	int i = E++;
	++indeg[to[i] = v], next[i] = last[u], last[u] = i;
}

unsigned int enc( unsigned int x, unsigned int y, unsigned int t ) {
	return x|(y<<SH)|(t<<(SH+SH));
}

u64 f( unsigned int u, unsigned int p ) {
	int i;
	if (z[u]<+oo) 
		return z[u];
	for ( z[u] = 0, i = last[u]; i >= 0; i = next[i] )
		if ( p != to[i] )
			z[u] += f(to[i],u);
	return z[u];
}

int main() {
	int i,j,k,l,t,ni,nj;
	unsigned int u,v;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( scanf("%d",&ts); ts-- && 2 == scanf("%d %d",&n,&m); ) {
		for ( i = 1; i <= m; ++i )
			scanf("%s",g[i]+1);
		E = 0, memset(last,-1,sizeof(last));
		memset(indeg,0,sizeof(indeg));
		for ( i = 1; i <= m; ++i )
			for ( j = 1; j <= n; ++j ) 
				if ( g[i][j] == '/' ) {
					u = enc(i,j,0);
					for ( k = 0; k < 2; ++k ) {
						ni = i+dx[k], nj = j+dy[k];
						if ( !vc(ni,nj) ) continue ;
						if ( k == 0 ) {
							if ( g[ni][nj] == '/' ) { v = enc(ni,nj,1); add_arc(u,v); }
							else { v = enc(ni,nj,3); add_arc(u,v); }
						}
						else {
							if ( g[ni][nj] == '/' ) { v = enc(ni,nj,1); add_arc(u,v); }
							else { v = enc(ni,nj,2); add_arc(u,v); }
						}
					}
					u = enc(i,j,1);
					for ( k = 2; k < 4; ++k ) {
						ni=i+dx[k], nj = j+dy[k];
						if ( !vc(ni,nj) ) continue ;
						if ( k == 2 ) {
							if ( g[ni][nj] == '/' ) { v = enc(ni,nj,0); add_arc(u,v); }
							else { v = enc(ni,nj,3); add_arc(u,v); }
						}
						else {
							if ( g[ni][nj] == '/' ) { v = enc(ni,nj,0); add_arc(u,v); }
							else { v = enc(ni,nj,2); add_arc(u,v); }
						}
					}
				}
				else {
					/*assert( g[i][j] == '\\' );*/
					k = 0, ni = i+dx[k], nj = j+dy[k];
					u = enc(i,j,2);
					if ( vc(ni,nj) ) {
						if ( g[ni][nj] == '/' ) { v = enc(ni,nj,1); add_arc(u,v); }
						else { v = enc(ni,nj,3); add_arc(u,v); }
					}
					k = 2, ni = i+dx[k], nj = j+dy[k];
					if ( vc(ni,nj) ) {
						if ( g[ni][nj] == '/' ) { v = enc(ni,nj,0); add_arc(u,v); }
						else { v = enc(ni,nj,3); add_arc(u,v); }
					}
					u = enc(i,j,3);
					k = 1, ni = i+dx[k], nj = j+dy[k];
					if ( vc(ni,nj) ) {
						if ( g[ni][nj] == '/' ) { v = enc(ni,nj,1); add_arc(u,v); }
						else { v = enc(ni,nj,2); add_arc(u,v); }
					}
					k = 3, ni = i+dx[k], nj = j+dy[k];
					if ( vc(ni,nj) ) {
						if ( g[ni][nj] == '/' ) { v = enc(ni,nj,0); add_arc(u,v); }
						else { v = enc(ni,nj,2); add_arc(u,v); }
					}
				}
		memset(z,0xffull,sizeof(z));
		/*
		head = tail = q;
		for ( i = 1, j = 1; j <= n; ++j )
			if ( g[i][j] == '/' )
				z[u = enc(i,j,0)] = 0, *tail++ = u;
			else z[u = enc(i,j,3)] = 0, *tail++ = u;
		for ( ;head < tail; )
			for ( u = *head++, i = last[u]; i >= 0; i = next[i] )
				if ( z[v = to[i]] > z[u]+1 )
					z[*tail++ = v] = z[u]+1;
		for ( i = m, j = 1; j <= n; ++j )
			if ( z[u = enc(i,j,1)] < +oo )
				printf("Reachable (%d,%d) with %d\n",u&MASK(SH),(u>>SH)&MASK(SH),(u>>(SH+SH)));
		continue ;
		*/
		for ( i = m, j = 1; j <= n; ++j )
			if ( g[i][j] == '/' )
				z[enc(i,j,1)] = 1;
			else z[enc(i,j,3)] = 1;
		for ( w = 0, i = 1, j = 1; j <= n; ++j )
			if ( g[i][j] == '/' )
				w += f(enc(i,j,0),0xfffffffful);
			else w += f(enc(i,j,2),0xfffffffful);
		printf("%llu\n",w);
	}
	return 0;
}

