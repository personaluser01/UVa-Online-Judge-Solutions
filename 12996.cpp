/*
 * 12996. Ultimate Mango Challenge
 * TOPIC: ad hoc, trivial
 * status: Accepted
 */
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>
#define N 0x10
using namespace std;

int n,L,a[N],b[N];
bool ok;

int main() {
	int i,j,k,cs = 0,ts;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( scanf("%d",&ts); ts--; ) {
		for ( scanf("%d %d",&n,&L), k = 0, ok = true, i = 0; i < n; ++i )
			scanf("%d",a+i), k += a[i];
		for ( ok &= (k<=L), j = 0; j < n; ++j )
			scanf("%d",b+j), ok &= (a[j]<=b[j]);
		printf("Case %d: %s\n",++cs,ok?"Yes":"No");
	}
	return 0;
}

