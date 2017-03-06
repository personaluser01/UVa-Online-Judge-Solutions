/*
 * 10934. Drobbing water balloons
 * TOPIC: dp, binary search
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef unsigned long long u64;
#define N 0x80
#define oo 0xffffffffffffffffull

u64 n,k;
u64 z[N][N];

u64 calc_z( int k, int t ) {
	if ( z[k][t] < +oo )
		return z[k][t];
	if ( t == 0 || k == 0 ) 
		return z[k][t] = 0;
	assert( k >= 1 && t >= 1 );
	return z[k][t] = calc_z(k,t-1)+1+calc_z(k-1,t-1);
}

int main() {
	int i,j,t;
#ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
#endif
	memset(z,0xff,sizeof z);
	for(;2 == scanf("%llu %llu",&k,&n) && k > 0; ) {
		if ( calc_z(k,j=63) < n ) {
			puts("More than 63 trials needed.");
			continue ;
		}
		for ( i = 0, j = 63; i+1 < j; calc_z(k,t=(i+j)/2)<n?(i=t):(j=t) );
		printf("%d\n",j);
	}
    return 0;
}

