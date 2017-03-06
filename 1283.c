/*
 * 1283. Infiltration
 * TOPIC: bitmasks, backtracking
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <string.h>
#define BIT(k) (1ULL<<(k))
#define MASK(k) (BIT(k)-1ULL)
#define L(k) ((k)&((~(k))+1ULL))
#define COVERS(i,j) (adj[i][(j)>>6] & BIT((j)&63))
#define N 77
typedef unsigned long long u64;

char which[BIT(20)],bts[BIT(20)],weight[N],
	 best_card,o[N],*ptr=o;
u64 adj[N][(N>>6)+6],ideal[(N>>6)+6],soln[N],cumm[N][N];
int n,z[N];

int howmuch( u64 u ) {
	if ( u < BIT(20) ) return bts[u];
	return howmuch(u>>20)+bts[u&MASK(20)];
};

int who( u64 u ) {
	if ( u >= BIT(60) )
		return 60+which[(u>>60)];
	if ( u >= BIT(40) )
		return 40+which[(u>>40)];
	if ( u >= BIT(20) )
		return 20+which[(u>>20)];
	return which[u];
};

int complete( u64 *u ) {
	int i;
	for ( i = 0; i <= (n>>6); ++i )
		if ( u[i] != ideal[i] )
			return 0;
	return 1;
};

int already_covered( u64 *u, u64 *c ) {
	int i;
	for ( i = 0; i <= (n>>6); ++i )
		if ( (u[i]&c[i]) != u[i] )
			return 0;
	return 1;
};

int not_promising( u64 *c, int x ) {
	int i;
	for ( i = 0; i <= (n>>6); ++i )
		if ( (c[i]|cumm[x][i]) != ideal[i] )
			return 1;
	return 0;
};

void f( int card_so_far, u64 *coverage, int x ) {
	int i;
	u64 ncoverage[(N>>6)+6];
	if ( card_so_far>=best_card || card_so_far >= 7 || 0&&not_promising(coverage,x) ) return ;
	if ( complete(coverage) ) {
		assert( best_card > card_so_far );
		best_card = card_so_far;
		for ( i = 0; i <= (n>>6); soln[i++] = 0 );
		for ( i = 0; i < ptr-o; ++i )
			soln[o[i]>>6]|=BIT(o[i]&63);
		return ;
	}
	if ( x >= n ) return ;
	if ( (coverage[z[x]>>6]&BIT(z[x]&63)) && already_covered(adj[z[x]],coverage) ) 
		f(card_so_far,coverage,x+1);
	else {
		for ( i = 0; i <= (n>>6); ncoverage[i]=(coverage[i]|adj[z[x]][i]), ++i );
		*ptr++ = z[x], f(card_so_far+1,ncoverage,x+1), --ptr;
		f(card_so_far,coverage,x+1);
	}
};

int main() {
	int i,j,k,l,cs = 0;
	u64 coverage[(N>>6)+6],u,v;
	char tmp[0x400];
#ifndef ONLINE_JUDGE
	freopen("1283.in","r",stdin);
#endif
	for ( u = 0; u < BIT(20); ++u )
		bts[u] = bts[u>>1]+(u&1);
	for ( i = 0; i < 20; ++i )
		which[BIT(i)] = i;
	while ( 1 == scanf("%d",&n) ) {
		memset(adj,0,sizeof adj), memset(ideal,0,sizeof ideal);
		for ( i = 0; i < n; ++i )
			for ( adj[i][i>>6]|=BIT(i&63), scanf("%s",tmp), j = 0; j < n; ++j )
				if ( tmp[j] == '1' )
					adj[i][j>>6]|=BIT(j&63);
		for ( i = 0; i < n; ++i )
			for ( weight[i] = 0, j = 0; j <= (n>>6); ++j )
				weight[i] += howmuch(adj[i][j]);
		for ( i = 0; i < n; ++i )
			z[i] = i;
		for ( j = 1; j; )
			for ( j = 0, i = 0; i < n-1; ++i )
				if ( weight[z[i]] < weight[z[i+1]] )
					++j, k = z[i], z[i] = z[i+1], z[i+1] = k;
		for ( memset(cumm,0,sizeof cumm), i = 0; i < n; ++i ) 
			for ( l = i; l < n; ++l )
				for ( cumm[i][l>>6]|=BIT(l&63), k = 0; k <= (n>>6); ++k )
					cumm[i][k] |= adj[z[l]][k];
		for ( i = 0; i < n; ideal[i>>6] |= BIT(i&63), ++i );
		printf("Case %d: ",++cs);
		for ( i = 0; i <= (n>>6); coverage[i++] = 0 );
		best_card = N+1, f(0,coverage,0);
		for ( printf("%d",best_card), i = 0; i <= (n>>6); ++i )
			for ( v = soln[i]; v; v &= ~L(v) )
				printf(" %d",i*64+who(L(v))+1);
		puts("");
	}
	return 0;
};

