/*
 * 11926. Multitasking
 * status: Accepted
 */
#include <cassert>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>
#include <queue>
#include <set>
#define eps 1e-2
#define N (1 << 19)
#define OPENING 0
#define CLOSING 1
using namespace std;

int x[2][N],r[N],n[2];
bool inner[1 << 21],h[1 << 21];

int main() {
	int i,j,k,l;
	bool ok;
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	for (;2 == scanf("%d %d",n,n+1) && (n[0]||n[1]);) {
		for ( i = 0; i < n[0]; ++i )
			scanf("%d %d",x[OPENING]+i,x[CLOSING]+i), r[i] = 0, ++x[OPENING][i];
		for ( i = n[0]; i < n[0]+n[1]; ++i )
			scanf("%d %d %d",x[OPENING]+i,x[CLOSING]+i,r+i), ++x[OPENING][i];
		memset(inner,0,sizeof inner);
		memset(h,0,sizeof h);
		for ( ok = true, i = 0; i < n[0] && ok; ++i ) {
			for ( j = x[OPENING][i]; j <= x[CLOSING][i] && ok; ++j ) {
				if ( h[j] ) 
					ok = false;
				h[j] = true;
			}
		}
		for ( i = n[0]; i < n[0]+n[1] && ok; ++i ) {
			for ( k = 0; x[CLOSING][i]+k*r[i] <= 1000000 && ok; ++k ) {
				for ( j = x[OPENING][i]+k*r[i]; j <= x[CLOSING][i]+r[i]*k; ++j ) {
					if ( h[j] ) ok = false;
					h[j] = true;
				}
			}
		}
		puts(ok?"NO CONFLICT":"CONFLICT");
	}
	return 0;
}

