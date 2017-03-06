/*
 * 1217. Route Planning
 * TOPIC: hamiltonian path
 * status: Accepted
 */
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 0x80
#define M 21
#define FG (ptr = fgets(buff,sizeof buff,stdin))
#define L(u) ((u)&((~(u))+1ULL))
#define BIT(k) (1ULL << (k))
#define MASK(k) (BIT(k)-1ULL)
typedef unsigned long long u64;

int n,rt,a[N],b[N],c[N][N],m[N];
char buff[0x400],*ptr,which[BIT(21)];
unsigned int d[N][N];

int who( u64 u ) {
	if ( u >= BIT(60) )
		return 60+which[u>>60];
	if ( u >= BIT(40) )
		return 40+which[u>>40];
	if ( u >= BIT(20) )
		return 20+which[u>>20];
	return which[u];
}

unsigned int z[BIT(M)][M];
#define oo 0xfffffffful

u64 solve( int *v, int src, int dst, const int m ) {
	int i,j,k,l,t,deg[M],adj[M][M];
	u64 e[M],D[M][M],w,ww,ee,ans;
	assert ( m-2 <= M );

	k = v[m-2], v[m-2] = v[0], v[0] = k;
	assert( src == v[m-2] );
	assert( dst == v[m-1] );
	for ( src=m-2, dst=m-1, i = 0; i < m; ++i )
		for ( deg[i] = e[i] = 0, j = 0; j < m; ++j ) 
			if ( d[v[i]][v[j]] < +oo ) 
				D[i][adj[i][deg[i]++]=j]=d[v[i]][v[j]];
			else D[i][j] = +oo;
	if ( m == 2 ) 
		return D[src][dst]<+oo?D[src][dst]:0;
	for ( i = 0; i < m; ++i )
		for ( l = 0; l < deg[i]; ++l )
			if ( adj[i][l] != dst && adj[i][l] != src )
				e[i] |= BIT(adj[i][l]);
	for ( w = 0; w < BIT(m-2); ++w )
		for ( ww = w; ww; ww &= ~L(ww) )
			z[w][who(L(ww))] = +oo;
	for ( i = 0; i < deg[src]; ++i )
		if ( (j = adj[src][i]) != dst ) {
			z[BIT(j)][j] = D[src][j];
			assert( D[src][j] < +oo );
		}
	for ( w = 0; w < BIT(m-2); ++w )
		for ( ww = w; ww; ww &= ~L(ww) )
			if ( z[w][i=who(L(ww))] < +oo )
				for ( ee = ((~w)&e[i]); ee; ee &= ~L(ee) )
					if ( (k=who(L(ee))) >= 0 && z[w|BIT(k)][k] > z[w][i]+D[i][k] )
						z[w|BIT(k)][k] = z[w][i]+D[i][k];
	for ( ans = +oo, w = MASK(m-2), i = 0; i < m-2; ++i )
		if ( z[w][i] < +oo && D[i][dst] < +oo )
			if ( z[w][i]+D[i][dst] < ans )
				ans = z[w][i]+D[i][dst];
	return ans<+oo?ans:0;
}

int main() {
	int i,j,k,l,t;
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	scanf("%d %d\n",&n,&rt);
	for ( i = 0; i < 21; ++i )
		which[BIT(i)] = i;
	for ( i = 0; i < n; ++i )
		for ( j = 0; j < n; ++j ) {
			scanf("%u\n",&d[i][j]);
			if ( !d[i][j] ) d[i][j] = +oo;
		}
	for ( t = 0; rt-- && FG; a[t] = c[t][0], b[t] = c[t][m[t]-1], ++t ) 
		for ( m[t] = 0; 1 == sscanf(ptr,"%d%n",&i,&k); ptr += k, c[t][m[t]++] = --i );
	for ( rt = t, t = 0; t < rt; ++t ) 
		printf("%llu\n",solve(c[t],a[t],b[t],m[t]));
	return 0;
}

