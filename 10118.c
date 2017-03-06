/*
 * 10118. Free Candies
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 41

int m,n = 4,c[N][4];

int main() {
	int i,j,k;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	while ( 1 == scanf("%d",&m) && m > 0 ) {
		for ( i = 0; i < m; ++i ) 
			for ( j = 0; j < n; scanf("%d",&c[i][j++]), --c[i][j-1] );
	}
	return 0;
}
