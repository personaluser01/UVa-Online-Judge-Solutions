/*
 * 1705. Censor Networks
 * TOPIC: backtracking, bitmasks, largest clique
 * status: in progress
 */
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define L(k) ((k)&((~(k))+1ULL))
#define BIT(k) (1ULL<<(k))
#define MASK(k) (BIT(k)-1ULL)
#define N 0x80
#define xchg(x,y) (((x)==(y))||((x)^=(y),(y)^=(x),(x)^=(y)))
#define S(x) ((x)*(x))
typedef unsigned long long u64;
int min( int x, int y ) { if ( x < y ) return x; return y; }

u64 u[N][(N>>6)+8],M[(N>>6)+8],A[(N>>6)+8];
int n,m,d,xx[N],yy[N],v[N],ans[N],deg[N],D[N],aid[N],id[N],adj[N][N],best_k;
char bts[BIT(21)],which[BIT(21)];

int cnt( u64 u ) { return bts[u>>60]+bts[(u>>40)&MASK(20)]+bts[(u>>20)&MASK(20)]+bts[u&MASK(20)]; }
int who( u64 u ) {
	if ( u >= BIT(60) )
		return 60+which[u>>60];
	if ( u >= BIT(40) )
		return 40+which[u>>40];
	if ( u >= BIT(20) )
		return 20+which[u>>20];
	return which[u];
}

int Size( u64 *u ) {
	int i,s = 0;
	for ( i = 0; i <= (n>>6); s += cnt(u[i++]) );
	return s;
}

void h( u64 *V, u64 *common_neighbors, int k ) {
	u64 w,i,j,l,cn[2];
	if ( k > best_k ) 
		for ( best_k = k, l = 0; l <= (n>>6); A[l] = V[l], ++l );
	if ( k+Size(common_neighbors) <= best_k )
		return ;
	for ( i = 0; i <= (n>>6); ++i )
		for ( w = common_neighbors[i]; w; w &= ~L(w) ) {
			j = (i<<6)+who(L(w));
			for ( l = 0; l <= (n>>6); ++l )
				cn[l] = common_neighbors[l], common_neighbors[l] &= u[j][l];
			V[j>>6] |= BIT(j&63);
			h(V,common_neighbors,k+1);
			V[j>>6] &= ~BIT(j&63);
			for ( l = 0; l <= (n>>6); ++l )
				common_neighbors[l] = cn[l];
		}
}

int g( const int t, u64 *V, u64 *common_neighbors, int k ) {
	u64 w,i,j,l,cn[2];
	if ( k == t ) {
		for ( l = 0, i = 0; i <= (n>>6); ++i )
			for ( w = V[i]; w; w &= ~L(w) )
				ans[l++] = (i<<6)+who(L(w));
		assert( l == t );
		return 1;
	}
	if ( t-k > Size(common_neighbors) )
		return 0;
	for ( i = 0; i <= (n>>6); ++i ) 
		for ( w = common_neighbors[i]; w; w &= ~L(w) ) {
			j = (i<<6)+who(L(w));
			/*
			for ( l = 0; l <= (n>>6); ++l )
				if ( (v[l]&u[j][l]) != v[l] )
					goto next;
					*/
			for ( l = 0; l <= (n>>6); ++l )
				cn[l] = common_neighbors[l], common_neighbors[l] &= u[j][l];
			V[j>>6] |= BIT(j&63);
			if ( g(t,V,common_neighbors,k+1) )
				return 1;
			V[j>>6] &= ~BIT(j&63);
			for ( l = 0; l <= (n>>6); ++l )
				common_neighbors[l] = cn[l];
			/*next: continue ;*/
		}
	return 0;
}

int f( int k ) {
	int mid,low,high,left,i;
	u64 vx[2] = {0};
	if ( deg[n-1] < k-1 ) return 0;
	if ( deg[0] >= k-1 ) left = 0;
	else {
		for ( low = 0, high = n-1; low+1<high; )
			if ( deg[mid=(low+high)/2] >= k-1 )
				high = mid;
			else low = mid;
		left = high;
	}
	assert( left == 0 || deg[left-1] < k-1 && deg[left] >= k-1 );
	for ( i = 0; i <= (n>>6); M[i++] = 0 );
	for ( i = left; i < n; M[i>>6] |= BIT(i&63), ++i );
	for ( i = 0; i <= (n>>6); vx[i++] = 0 );
	return g(k,vx,M,0);
}

int main() {
	int i,j,k,bad,good,middle,id[N],x,y,l;
	u64 V[(N>>6)+8],common_neighbors[(N>>6)+8],w;
#ifndef ONLINE_JUDGE
	freopen("c.txt","r",stdin);
#endif
	for ( i=0; i<BIT(21); bts[i]=bts[i>>1]+(i&1), ++i );
	for ( i = 0; i < 21; which[BIT(i)] = i, ++i );
	while ( 2 == scanf("%d %d",&n,&d) ) {
		for ( d *= d, i = 0; i < n; ++i )
			for ( D[i] = 0, j = 0; j <= (n>>6); u[i][j++] = 0 );
		for ( i = 0; i < n; scanf("%d %d",&xx[i],&yy[i]), ++i );
		for ( i = 0; i < n; ++i )
			for ( j = i+1; j < n; ++j ) 
				if ( S(xx[i]-xx[j])+S(yy[i]-yy[j]) <= d ) 
					u[i][j>>6]|=BIT(j&63), u[j][i>>6]|=BIT(i&63), adj[i][D[i]++] = j, adj[j][D[j]++] = i;
		for ( i = 0; i < n; ++i ) 
			for ( deg[i] = 0, id[i] = i, j = 0; j <= (n>>6); ++j )
				deg[i] += cnt(u[i][j]);
		for ( i = 0; i < n; ++i ) assert( deg[i] == D[i] );
		for ( j = 1; j; )
			for ( j = i = 0; i < n-1; ++i )
				if ( deg[i] > deg[i+1] )
					++j, xchg(deg[i],deg[i+1]), xchg(id[i],id[i+1]);
		for ( i = 0; i < n; ++i ) aid[id[i]] = i;
		for ( i = 0; i < n-1; ++i )
				assert( deg[i] <= deg[i+1] );
		for ( m = 0, i = 0; i < n; m += deg[i++] );
		assert( !(m&1) );
		for ( m >>= 1, i = 0; i < n; ++i )
			for ( j = 0; j <= (n>>6); u[i][j++] = 0 );
		for ( i = 0; i < n; ++i )
			for ( l = 0; l < D[i]; ++l ) {
				j = adj[i][l];
				x = aid[i], y = aid[j];
				u[x][y>>6] |= BIT(y&63);
				u[y][x>>6] |= BIT(x&63);
			}
#if 0
		bad = min((int)((1+sqrt(1+8*m))/2.00)+4,n+1);
		for ( good = 1; good+1 != bad; ) {
			if ( f(middle = (good+bad)/2) ) good = middle;
			else bad = middle;
		}
		assert( !f(bad) );
		assert( f(good) );
		assert( good+1 == bad );
		for ( printf("%d\n",good), i = 0; i < good; ++i ) {
			if ( i ) putchar(' ');
			printf("%d",1+id[ans[i]]);
		}
		putchar('\n');
#else
		for ( i = 0; i <= (n>>6); V[i++] = 0, common_neighbors[i-1]=0 );
		for ( i = 0; i < n; ++i )
			common_neighbors[i>>6] |= BIT(i&63);
		best_k = -1, h(V,common_neighbors,0);
		for ( m = 0, i = 0; i <= (n>>6); ++i )
			for ( w = A[i]; w; w &= ~L(w) ) 
				ans[m++] = (i<<6)+who(L(w));
		for ( printf("%d\n",best_k), i = 0; i < best_k; ++i ) {
			if ( i ) putchar(' ');
			printf("%d",1+id[ans[i]]);
		}
		putchar('\n');
#endif
	}
	return 0;
}

