/*
 * 12396. Remoteland
 * TOPIC: number theory, factorials, sieve
 * status: Accepted
 */
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>
#define N (1<<24)
#define MOD (1000000000LL+7LL)
typedef long long i64;
using namespace std;

bool isprime[N];
i64 *p;
int m,n;

i64 pw( i64 x, int n ) {
	i64 ax =1LL;
	for(;n;n>>=1,x*=x,x%=MOD)
		if (n&1) 
			ax *= x, ax %= MOD;
	// printf("ax = %lld\n",ax);
	return ax%MOD;
}

int main() {
	int i,j,k;
	i64 w,q,res;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( isprime[2] = true, i = 3; i < N; isprime[i] = true, i += 2 );
	for ( i = 3; i < N; i += 2 )
		for ( j = i+i; j < N && isprime[i]; isprime[j] = false, j += i );
	for ( i = 0; i < N; ++i )
		if ( isprime[i] ) ++m;
	p = new i64[m];
	for ( k = 0, i = 0; i < N; ++i )
		if ( isprime[i] )
			p[k++] = i;
	assert( k == m );
	for (;1==scanf("%d",&n)&&n>0; printf("%lld\n",res) )
		for ( res = 1LL, i=0; i<m && p[i]<=n; res*=pw(p[i++],k-(k&1)),res%=MOD )
			for ( q=p[i], k=0; n>=q; k+=n/q, q*=p[i] );
	return 0;
}

