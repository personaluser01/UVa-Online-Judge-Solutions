/*
 * 11548. Blackboard Bonanza
 * TOPIC: greedy
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
#include <map>
#define N 0x50
#define oo (1<<29)
using namespace std;

int ts,n,ans,c[N+N][N+N];
string w[N];

int f( string &a, string &b ) {
	int m = a.size(),
		n = b.size(),
		i,j,k,s = 0,ax = 0;
	for ( k = -n; k <= 0; ax = max(ax,s), ++k ) {
		for ( s=0,j=0; j<=n-1 && !(0<=j+k&&j+k<=m-1); ++j );
		for ( i = 0; i<m && j<n; ++i,++j )
			if ( a[i]==b[j] ) ++s;
	}
	for ( k = -m; k <= 0; ax = max(ax,s), ++k ) {
		for ( s=0,i=0; i <= m-1 && !(0<=i+k&&i+k<=n-1); ++i );
		for ( j = 0; j < n && i < m; ++i, ++j )
			if ( a[i] == b[j] ) ++s;
	}
	return ax;
}

int main() {
	int i,j,k;
	char tmp[0x400];
#ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
#endif
	for ( scanf("%d",&ts); ts-- && 1 == scanf("%d",&n); ) {
		for ( i = 0; i < n; ++i )
			scanf("%s",tmp), w[i] = string(tmp);
		for ( ans = 0, i = 0; i < n; ++i )
			for ( j = i+1; j < n; ++j )
				ans = max(ans,f(w[i],w[j]));
		printf("%d\n",ans);
	}
    return 0;
}

