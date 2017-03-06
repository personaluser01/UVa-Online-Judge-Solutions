/*
 * 11932. Net Profit
 * TOPIC: neat dp
 * status: Accepted
 */
#include <bits/stdc++.h>
#define BIT(k) (1ULL<<(k))
#define MASK(k) (BIT(k)-1ULL)
#define L(u) ((u)&((~(u))+1ULL))
#define N 0x10
#define oo (1LL<<43)
typedef long long i64;
using namespace std;
typedef unsigned int state;

int n,p[N];
char which[BIT(20)];
unsigned int adj[N];
i64 w[BIT(N)];
i64 z[BIT(N)];
//map<pair<state,state>,i64> z;

i64 calc_z( state u ) {
	state v,i;
	if ( z[u] > -oo )
		return z[u];
	if ( !u ) return z[u] = 0;
	auto &ret = z[u];
	auto rems = (MASK(n)&~u);
	for ( v = u; v && (i=which[L(v)])>=0; v &= ~L(v) ) 
		if ( u==MASK(n) || (rems&adj[i]) )
			ret = max(ret,p[i]-calc_z(u&~L(v)));
	return ret;
}

int main() {
	int i,j,k,m;
	i64 a,b,sum;
#ifndef ONLINE_JUDGE
	freopen("11932.in","r",stdin);
#endif
	for ( i = 0; i < 20; which[BIT(i)] = i, ++i );
	for (;1==scanf("%d",&n)&&n;) {
		for ( sum = 0, i=0; i<n; adj[i]=0, scanf("%d",&p[i++]), sum += p[i-1] );
		for ( scanf("%d",&m), k=0; k<m && 2==scanf("%d %d",&i,&j); --i,--j,adj[i]|=BIT(j),adj[j]|=BIT(i),++k );
		for ( k = 0; k < BIT(n); z[k++] = -oo );
		a = calc_z(MASK(n));
		if ( a == 0 ) 
			printf("Tie game! %lld all.\n",sum/2);
		else if ( a > 0 )
			printf("First player wins! %lld to %lld.\n",(sum+a)/2,(sum-a)/2);
		else printf("Second player wins! %lld to %lld.\n",(sum-a)/2,(sum+a)/2);
	}
	return 0;
}

