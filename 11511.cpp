/*
 * 11511. Frieze Patterns
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
#define N 0x400
typedef long long i64;
using namespace std;

i64 v[N],c[N][2];
int n,row,col,P;

bool equal( const int t ) {
	for ( int i = 1; i <= n; ++i )
		if ( c[i][t] != v[i] )
			return false;
	return true;
}

int main() {
	int i,j,k,l,t,rem;
	for (;1 == scanf("%d",&n) && n > 0;) {
		scanf("%d %d",&row,&col);
		for ( i = 1; i <= n; scanf("%lld",&v[i++]) );
		for ( j = 0; j <= 1; c[1][j] = c[n][j] = 1, ++j );
		for ( t = 0, i = 2; i <= n-1; ++i ) c[i][t] = v[i];
		for ( j = 2; !equal(t); ++j ) 
			for ( t ^= 1, i = 2; i <= n-1; ++i ) 
				c[i][t] = (c[i+1][t^1]*c[i-1][t]+1)/c[i][t^1];
		P = (n-2)*(j-1), k = (n-2)*(j-1)+(i-1), rem = k%P;
		if ( rem <= n-2 ) {
			printf("%lld\n",v[rem+2]);
		}
		else {
			for ( j = 0; j <= 1; c[1][j] = c[n][j] = 1, ++j );
			for ( t = 0, i = 2; i <= n-1; ++i ) c[i][t] = v[i];
			for ( l = n-2,j = 2; !equal(t) && l < rem; ++j ) 
				for ( t ^= 1, i = 2; i <= n-1 && l < rem; ++i, ++l ) 
					c[i][t] = (c[i+1][t^1]*c[i-1][t]+1)/c[i][t^1];
			printf("%lld\n",c[i][t]);
		}
	}
    return 0;
}

