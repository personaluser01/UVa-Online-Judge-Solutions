/*
 * 10273. Eat or Not To Eat?
 */
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <vector>
#include <queue>
#include <cassert>
using namespace std;
#define N 0x400
#define MAXT 11
typedef long long i64;

i64 gcd( i64 x, i64 y ) { return !y?x:gcd(y,x%y); }
i64 lcm( i64 x, i64 y ) { return x*(y/gcd(x,y));  }

int n,T[N],m[N][MAXT];

int main() {
	int i,j,k,l,t,ts;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( scanf("%d",&ts); ts-- && scanf("%d",&n) == 1; ) {
		for ( i = 0; i < n; ++i ) 
			for ( scanf("%d",T+i), j = 0; j < T[i]; ++j )
				scanf("%d",m[i]+j);
	}
	return 0;
}

