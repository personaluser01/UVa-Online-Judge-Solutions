/*
 * 10663. Non-powerful subsets
 * TOPIC: greedy, dp
 * status: Accepted
 */
#include <cassert>
#include <cstdio>
#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <cmath>
#include <vector>
#include <set>
#define N 0x400
#define M (N*N/2)
typedef long long i64;
using namespace std;

bool ispower[M];
int c[N],m,a[N];
set<int> s;

int main() {
	i64 i,j,k,aa,bb,t,left,right;
	set<int>::iterator it;
#ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
#endif
	for ( i = 2; i < N; ++i )
		for (j=i*i;j<M;ispower[j]=true,j*=i);
	for (;2==scanf("%lld %lld",&aa,&bb);) {
		for ( s.clear(), m = 0, s.insert(0), i = aa; i <= bb; ++i ) {
			for ( it = s.begin(); it != s.end(); ++it )
				if ( ispower[*it+i] ) goto next;
			for ( k = 0, it = s.begin(); it != s.end(); ++it )
				if (s.find(*it+i)==s.end()) a[k++]=*it+i;
			c[m++] = i;
			for (;--k >= 0; s.insert(a[k]) );
			next: continue ;
		}
		for ( i = 0; i < m-1; ++i ) printf("%d ",c[i]);
		printf("%d\n",c[i]);
	}
    return 0;
}

