/*
 * status: Accepted
 * TOPIC: havel-hakimi, recursion
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
using namespace std;

int ts,d[N],n;

bool f( int *d, int n ) {
	int i,j,k,*m;
	if ( n <= 0 ) return true;
	if ( n == 1 )
		return d[0] == 0;
	assert( n >= 2 );
	if ( d[0] < 0 || d[0] >= n || d[n-1] < 0 )
		return 0;
	m = (int *)malloc((n-1)*sizeof *m);
	for ( k = d[0], j = 0, i = 1; i <= k; m[j++] = d[i++]-1 );
	for ( i = k+1; i < n; m[j++] = d[i++] );
	sort(m,m+n-1,greater<int>());
	return f(m,n-1);
}

int main() {
	int i,j,k;
	for ( scanf("%d",&ts); ts--; ) {
		for ( scanf("%d",&n), i = 0; i < n; ++i )
			scanf("%d",&d[i]);
		sort(d,d+n,greater<int>());
		puts(f(d,n)?"Yes":"No");
	}
    return 0;
}
