/*
 * status: Accepted
 * TOPIC: havel-hakimi, graphic sequence
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
#define N (1 << 16)
using namespace std;

int n,d[N];

bool f( int *d, int n ) {
	int i,j,k = d[0],*m;
	if ( n == 1 ) 
		return d[0] == 0;
	assert( n >= 2 );
	if ( d[0] >= n || d[n-1] < 0 )
		return  false;
	m = (int *)malloc((n-1)*sizeof *m);
	for ( j = 0, i = 1; i <= k; ++i )
		m[j++] = d[i]-1;
	for ( i = k+1; i < n; ++i )
		m[j++] = d[i];
	sort(m,m+n-1,greater<int>());
	bool ok = f(m,n-1);
	free(m);
	return ok;
}

int main() {
	int i,j,k;
	for (;1 == scanf("%d",&n) && n > 0;) {
		for ( i = 0; i < n; ++i )
			scanf("%d",d+i);
		sort(d,d+n,greater<int>());
		puts(f(d,n)?"Possible":"Not possible");
	}
    return 0;
}

