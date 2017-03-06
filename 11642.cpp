/*
 * 11642. Bangladesh Premier League
 */
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iostream>
#include <vector>
#include <set>
#include <map>
using namespace std;
#define N 51

int cs,n,wins[N],losses[N],left[N],gmat[N][N];
char tname[N][0x100];

int main() {
	int i,j,k;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( ;1 == scanf("%d",&n) && n != -1; ) {
		printf("Case %d:\n",++cs);
		for ( i = 0; i < n+4; ++i ) {
			scanf("%s %d %d %d",tname[i],wins+i,losses+i,left+i);
			for ( j = 0; j < n; ++j )
				scanf("%d",&gmat[i][j]);
		}
	}
	return 0;
}

