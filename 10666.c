/*
 * 10666. Eurocup is Here!
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define M(k) ((1UL<<(k))-1UL)
#define L(i) ((i) & ((~(i))+1UL))
typedef long long i64;

unsigned int team_id;
int n;

int idx ( unsigned int u ) {
	int i,j,k;
	assert( !(u & (u-1)) );
	if ( u == 1 )
		return 0;
	for ( i = 0, j = 32; i+1 != j; ) {
		k = (i+j)/2;
		if ( (1ULL << (k)) < u )
			i = k;
		else j = k;
	}
	assert( (1 << j) == u );
	return j;
}

i64 f( unsigned int u, int m ) {
	int i;
	if ( m == 1 ) 
		return (u&1);
	if ( u == 0 )
		return 0;
	i = idx(L(u));
	assert( (u>>i) & 1 );
	return 1+f((u>>i)-1,m-i);
}

i64 g( unsigned int u, int m ) {
	int i;
	if ( u == 0 ) 
		return (1ll << m)-1;
	if ( m == 1 )
		return 1^(u&1);
	assert( m > 1 );
	if (u&1)
		return 0;
	i = idx(L(u));
	return (1ll<<i)-1+g(u>>i,m-i);

}

int main() {
	int i,j,k,ts;
	i64 a,b;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( scanf("%d",&ts); ts--; ) {
		assert( 2 == scanf("%d %u",&n,&team_id) );
		printf("%lld %lld\n",1+f(team_id,n),(1LL<<n)-g(team_id,n));
	}
	return 0;
}

