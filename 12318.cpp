/*
 * 12318. Digital Roulette
 * TOPIC: trivial, horner's scheme
 * status: Accepted
 */
#include <cassert>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <set>
#include <vector>
using namespace std;
typedef long long i64;
#define MAXDEG 11

i64 n,m,a[MAXDEG];
set<i64> s;

i64 eval( i64 *c, int d, i64 t ) {
	i64 s = 0;
	for ( int i = d; i >= 0; --i )
		s *= t, s += c[i], s %= (n+1);
	return s%(n+1);
}

int main() {
	int i,j,k;
	i64 t;
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	for ( ;2==scanf("%lld %lld",&n,&m)&&(n||m); ) {
		scanf("%d",&k);
		for ( i = 0; i <= k; ++i )
			scanf("%lld",a+i);
		s.clear();
		if ( m <= n ) {
			for ( t = 0; t <= m; ++t ) 
				s.insert(eval(a,k,t));
		}
		else {
			for ( t = 0; t <= n; ++t ) 
				s.insert(eval(a,k,t));
		}
		printf("%u\n",s.size());
	}
	return 0;
}


