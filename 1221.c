/*
 * 1221. Against Mammoths
 * TOPIC: binary search, bipartite matching
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 0x200
#define M ((1UL<<10)-1UL)
enum { S, T };
#define NX(x) (((x)+1)&M)
#define oo (1<<28)
typedef long long i64;

int n[2],seen[2][N],yes[2],mate[2][N],adj[2][N][N],deg[2][N],q[M+1],head,tail,cnt;
i64 a[2][N],p[2][N],g[N][N],rhs[N][N],lhs[N][N],upper_limit;

int alt_path( int x ) {
	int i,y;
	if ( seen[S][x] == yes[S] ) return 0;
	for ( seen[S][x] = yes[S], i = 0; i < deg[S][x]; ++i )
		if ( mate[T][y=adj[S][x][i]] == -1 || alt_path(mate[T][y]) ) 
			return mate[S][mate[T][y]=x]=y, 1;
	return 0;
}

int f( int TT ) {
	int x,y,i,j,k,t,flag;
	i64 tau,param;
	/* TT is the time when the last rocket lands on alien planet */
#define enqueue(x) (q[tail]=(x),tail=NX(tail),++cnt)
	for ( t = S; t <= T; ++t )
		for ( i = 0; i < n[t]; ++i )
			deg[t][i] = 0, mate[t][i] = -1;
	for ( x = 0; x < n[S]; ++x )
		for ( y = 0; y < n[T]; ++y ) {
			if ( lhs[x][y] == 0 ) {
				if ( rhs[x][y] <= 0 ) 
					adj[S][x][deg[S][x]++] = y, adj[T][y][deg[T][y]++] = x;
				continue ;
			}
			if ( lhs[x][y] > 0 ) {
				if ( rhs[x][y] <= 0 ) {
					adj[S][x][deg[S][x]++] = y, adj[T][y][deg[T][y]++] = x;
					continue ;
				}
				if ( TT >= g[x][y] && a[S][x]+(TT-g[x][y])*p[S][x]>=a[T][y]+TT*p[T][y] )
					adj[S][x][deg[S][x]++] = y, adj[T][y][deg[T][y]++] = x;
				continue ;
			}
			assert( lhs[x][y] < 0 );
			if ( rhs[x][y] <= 0 ) {
				if ( (rhs[x][y]%lhs[x][y]) == 0 )
					tau = rhs[x][y]/lhs[x][y];
				else tau = rhs[x][y]/lhs[x][y]+1;
				if ( tau+g[x][y] <= TT ) {
					assert( a[S][x]+tau*p[S][x]>=a[T][y]+(tau+g[x][y])*p[T][y] );
					adj[S][x][deg[S][x]++] = y, adj[T][y][deg[T][y]++] = x;
				}
			}
		}
	for ( head = tail = 0, cnt = 0, x = 0; x < n[S]; ++x ) enqueue(x);
	do {
		for ( flag = 0, k = cnt, ++yes[S]; k--; ) {
			x=q[head],head=NX(head),--cnt;
			if ( alt_path(x) ) flag = 1;
			else enqueue(x);
		}
	}while(flag);
	return n[S]-cnt;
}

int main() {
	int i,j,k,t,good,bad,mid;
#ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
#endif
	for(;2==scanf("%d %d",n+S,n+T) && (n[S]||n[T]);) {
		for ( t = 0; t <= 1; ++t ) 
			for ( i = 0; i < n[t]; ++i )
				scanf("%lld %lld",&a[t][i],&p[t][i]);
		for ( i = 0; i < n[S]; ++i )
			for ( j = 0; j < n[T]; ++j )
				scanf("%lld",&g[i][j]);
		for ( i = 0; i < n[S]; ++i )
			for ( j = 0; j < n[T]; ++j ) {
				rhs[i][j] = g[i][j]*p[T][j]+a[T][j]-a[S][i];
				lhs[i][j] = p[S][i]-p[T][j];
			}
		for ( upper_limit = -oo, i = 0; i < n[S]; ++i )
			for ( j = 0; j < n[T]; ++j )
				if ( lhs[i][j] > 0 && rhs[i][j] >= 0 )
					if ( rhs[i][j]/lhs[i][j]+1+g[i][j] > upper_limit )
						upper_limit = rhs[i][j]/lhs[i][j]+1+g[i][j];
		if ( f(good=upper_limit+1) < n[T] ) { puts("IMPOSSIBLE"); continue ; }
		if ( f(bad=0)>=n[T] ) good = bad;
		else 
			for (;good>bad+1;f(mid=(good+bad)/2)<n[T]?(bad=mid):(good=mid));
		printf("%d\n",good);
	}
    return 0;
}

