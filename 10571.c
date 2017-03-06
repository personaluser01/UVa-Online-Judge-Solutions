/*
 * 10571. Products
 * TOPIC: backtracking
 * status: Accepted
 */
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 16
#define L(u) ((u)&((~(u))+1ULL))
#define BIT(k) (1ULL << (k))
#define MASK(k) (BIT(k)-1ULL)
typedef long long i64;

i64 x[N],y[N],last[N],g[N][N];
char bts[BIT(21)],which[BIT(21)],is_divisor[0x400][0x400];
int n,deg[0x400],adj[0x400][0x400],used[0x400],yes;

int f( int r, unsigned int u ) {
	int j,l,j1,j2,lj1,lj2;
	i64 a,b;
	unsigned int v,w,nu;
	if ( r == n ) return 1;
	assert( r < n );
	for ( l = 0; l < deg[x[r]]; ++l ) if ( used[a=adj[x[r]][l]] != yes && used[b=x[r]/adj[x[r]][l]] != yes && a != b )
		for ( v = u; v; v &= ~L(v) ) 
			for ( j1=which[L(v)], w = u; w && is_divisor[y[j1]][a]&&(last[j1]==-1||last[j1]*a==y[j1]); w &= ~L(w) ) 
				if ( (j2=which[L(w)]) != j1 )
					if ( is_divisor[y[j2]][b] && (last[j2] == -1 || last[j2]*b == y[j2]) ) {
						nu = u;
						if ( (lj1=last[j1]) != -1 ) nu &= ~BIT(j1);
						if ( (lj2=last[j2]) != -1 ) nu &= ~BIT(j2);
						last[j1] = a, last[j2] = b;
						used[a] = used[b] = yes, g[r][j1] = a, g[r][j2] = b;
						if ( f(r+1,nu) ) return 1;
						last[j1] = lj1, last[j2] = lj2, g[r][j1] = 0, g[r][j2] = 0;
						used[a] = used[b] = 0, nu = u;
					}	
	return 0;
}

int main() {
	int i,j,k;
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	for ( k = 0; k < BIT(21); ++k ) bts[k]=bts[k>>1]+(k&1);
	for ( k = 0; k < 21; ++k ) which[BIT(k)] = k;
	for ( k = 1; k < 0x400; ++k )
		for ( i = 1; i*i <= k; ++i )
			if ( 0 == (k%i) )
				adj[k][deg[k]++] = i;
	for ( k = 1; k < 0x400; ++k )
		for ( i = 0; i < deg[k]; ++i )
			is_divisor[k][adj[k][i]] = is_divisor[k][k/adj[k][i]] = 1;
	for (;1 == scanf("%d",&n) && n > 0 && ++yes; puts("") ) {
		for ( i = 0; i < n; ++i ) scanf("%lld",y+i);
		for ( j = 0; j < n; ++j ) scanf("%lld",x+j);
		for ( j = 0; j < n; last[j++] = -1 );
		for ( i = 0; i < n; ++i )
			for ( j = 0; j < n; ++j )
				g[i][j] = 0;
		assert( f(0,MASK(n)) );
		for ( i = 0; i < n; ++i, putchar('\n') ) 
			for ( j = 0; j < n; ++j )
				printf("%4lld",g[i][j]);
	}
	return 0;
}

