/*
 * 10634. Say NO To Memorisation
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 0x400
typedef unsigned long long u64;

int n,vars;
u64 c[N][N],ax;

int main() {
	int i,j,k;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( i = 0; i < N; ++i )
		c[i][0] = 1;
	for ( i = 1; i < N; ++i )
		for ( j = 1; j <= i; ++j )
			c[i][j] = c[i-1][j] + c[i-1][j-1];
	while ( 2 == scanf("%d %d",&n,&vars) && (n||vars) ) {
		for ( ax = 0, i = 0; 2*i+(n&1) <= n; ++i )
			ax += c[2*i+(n&1)+vars-1][vars-1];
		printf("%llu\n",ax);
	}
	return 0;
}

