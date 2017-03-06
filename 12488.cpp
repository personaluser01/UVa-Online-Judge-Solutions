/*
 * TOPIC: inversions
 * status: Accepted
 */
#include <cassert>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;
#define N 32

int n,c[N],p[N];

int main() {
	int i,j,k;
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	while ( 1 == scanf("%d",&n) ) {
		for ( i = 0; i < n; ++i )
			scanf("%d",&c[i]), --c[i];
		for ( i = 0; i < n; ++i )
			scanf("%d",&k), p[--k] = i;
		for ( i = 0; i < n; ++i )
			c[i] = p[c[i]];
		for ( k = 0, i = 0; i < n; ++i )
			for ( j = i+1; j < n; ++j )
				if ( c[i] > c[j] ) ++k;
		printf("%d\n",k);
	}
	return 0;
}

