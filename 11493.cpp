/*
 * 11493. The Club Ballroom
 * TOPIC: ad hoc, greedy
 * status: Accepted
 */
#include <cassert>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;
typedef long long i64;
#define N 100100
#define IMP (puts("impossivel"))
#define oo (1 << 29)

i64 m,n,L,x[N],y[N];
int K,E;

int f( i64 m, i64 n ) {
	int i,j,k,ans = 0,rows,r = 0;
	assert( L );
	if ( (m%L) ) return +oo;
	for ( rows = m/L, E = i = 0; i < K; ++i )
		if ( 100*x[i] <= n ) y[E++] = 100*x[i];
	for ( sort(y,y+E), j = E-1, i = 0; i <= j && r < rows; ) {
		if ( y[j] == n ) {
			++ans, ++r, --j;
			continue ;
		}
		assert( y[j] < n );
		for ( ;i < j && y[i]+y[j] < n; ++i );
		if ( i < j && y[i]+y[j] > n ) {
			--j;
			continue ;
		}
		if ( i >= j ) {
			break ;
		}
		assert ( i < j && y[i]+y[j] == n );
		++i, --j, ++r, ans += 2;
	}
	return r >= rows ? ans : +oo;
}

int main() {
	int i,j,k;
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	for ( ;2 == scanf("%lld %lld",&m,&n) && (m||n); ) {
		assert( 2 == scanf("%lld %d",&L,&K) );
		for ( i = 0; i < K; scanf("%lld",&x[i++]) );
		m *= 100, n *= 100;
		i = f(m,n), j = f(n,m);
		k = (i<j?i:j);
		if ( k == +oo ) { IMP; continue ; }
		printf("%d\n",k);
	}
	return 0;
}

