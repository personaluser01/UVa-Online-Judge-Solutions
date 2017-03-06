/*
 * 13075. Ice-Cream Cones
 * TOPIC: STL, permutations, basic combinatorics
 * status: Accepted
 */
#include <algorithm>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;
#define N 0x10

int m,n,ts;
char a[N];

int main() {
	int i,j,k;
	for ( scanf("%d",&ts); ts--; ) {
		scanf("%d %d",&m,&n);
		for ( k = 0, i = 0; i < m; a[k++] = 'C', ++i );
		for ( j = 0; j < n; a[k++] = 'V', ++j );
		j = 0;
		do {
			if ( ++j > 1 ) putchar(' ');
			for ( i = 0; i < k; putchar(a[i++]) );
		} while ( next_permutation(a,a+k) );
		puts("");
	}
	return 0;
}

