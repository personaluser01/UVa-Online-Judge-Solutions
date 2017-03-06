/*
 * 10940. Throwing Cards Away
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int n;
char idx[1 << 15];

int f( unsigned int n ) {
	if ( !(n & (n-1)) )
		return (1 << idx[n])-1;
	if ( n == 1 )
		return 0;
	if ( n & 1 ) 
		return 1+(((f(n/2)+1)%(n/2))<<1);
	return (f(n/2)<<1)+1;
}

int main() {
	unsigned int u,i,j,k;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( i = 0; i < 15; idx[1 << i] = i, ++i );
	while ( 1 == scanf("%d",&n) && n > 0 ) {
		printf("%d\n",f(n)+1);
	}
	return 0;
}

