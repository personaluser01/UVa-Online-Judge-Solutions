/*
 * 1244. Palindromkic Paths
 * TOPIC: dp
 * status: Accepted
 */
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 0x40
#define oo 0xfffffffful
#define BIT(k) (1ULL<<(k))
#define MASK(k) (BIT(k)-1ULL)
#define L(k) ((k)&((~(k))+1ULL))
#define A 26
#define NO puts("NO PALINDROMIC PATH")
typedef unsigned long long u64;

int n,seen[N][N][N],yes;
unsigned int z[N][N][N],way[N][N][N];
char g[N][N],which[BIT(21)],bts[BIT(21)],*ptr,e[N],
	 r[N][N][N][N];
u64 u[N][A],v[N][A];

int who( u64 u ) {
	if ( u >= BIT(60) )
		return 60+which[u>>60];
	if ( u >= BIT(40) )
		return 40+which[u>>40];
	if ( u >= BIT(20) )
		return 20+which[u>>20];
	return which[u];
}

int cnt( u64 u ) 
{ return bts[u>>60]+bts[(u>>40)&MASK(20)]+bts[(u>>20)&MASK(20)]+bts[u&MASK(20)]; }

void dump( int i, int j, int k ) {
	int ii,jj;
	if ( k == 0 ) {
		assert( i == j );
		return ;
	}
	assert( i < j );
	if ( k == 1 ) { *ptr++ = g[i][j]; return ; }
	ii = (way[i][j][k]&MASK(6)), jj = (way[i][j][k]>>6);
	*ptr++ = g[i][ii], dump(ii,jj,k-2), *ptr++ = g[jj][j];
}

int cmp( int i, int j, int p, int q, int k ) {
	if ( seen[i][j][k] != yes )
		ptr = e, dump(i,j,k), *ptr = '\0', strcpy(r[i][j][k],e);
	if ( seen[p][q][k] != yes )
		ptr = e, dump(p,q,k), *ptr = '\0', strcpy(r[p][q][k],e);
	return strcmp(r[i][j][k],r[p][q][k]);
}

int main() {
	int i,j,k,cs,ii,jj,t;
	u64 a,b;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( i = 0; i < 21; which[BIT(i)] = i, ++i );
	for ( i = 0; i < BIT(21); bts[i]=bts[i>>1]+(i&1), ++i );
	for (scanf("%d",&cs);cs--&&1==scanf("%d",&n)&&++yes;) {
		for ( i = 0; i < n; scanf("%s",g[i++]) );
		for ( i = 0; i < n; ++i )
			for ( k=0; k<A; u[i][k]=v[i][k]=0,++k );
		for ( i = 0; i < n; ++i )
			for ( j = i+1; j < n; ++j )
				k=g[i][j]-'A',v[i][k]|=BIT(j),u[j][k]|=BIT(i);
		for ( memset(z,0,sizeof z), i = 0; i < n; z[i][i][0] = 1, ++i );
		for ( i = 0; i < n; ++i )
			for ( j = i+1; j < n; z[i][j++][1] = 1 );
		for ( k = 2; k <= n; ++k )
			for ( i = 0; i+k-1 < n; ++i ) 
				for ( j = i+k-1; j < n; ++j )
				for ( t = 0; t < A && !z[i][j][k]; ++t )
					for ( a = v[i][t]; a && (ii=who(L(a))) >= 0; a &= ~L(a) )
						for ( b = u[j][t]; b && (jj=who(L(b))) >= 0; b &= ~L(b) ) 
							if ( ii <= jj && z[ii][jj][k-2] )
								if ( !z[i][j][k] || cmp(ii,jj,way[i][j][k]&MASK(6),way[i][j][k]>>6,k-2) < 0 )
									z[i][j][k] = 1, way[i][j][k] = (ii|(jj<<6));
		for ( k = n; k >= 0 && !z[0][n-1][k]; --k );
		if ( k < 0 ) NO;
		else 
			ptr = e, dump(0,n-1,k), *ptr = '\0', puts(e);
	}
	return 0;
}

