/*
 * 10276. Hanoi Towers Trouble Again
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <limits.h>
#include <float.h>
#define N 51
typedef long long i64;
#define Q (1 << 16)

int n,sq[Q],*ptr,cur,max_k,empty[N],yes;
char which_peg[Q];

void rec( int k ) {
	int i,j,t;
nx: 
	if ( k-1 > max_k ) max_k = k-1;
	for(i=0,j=ptr-sq-1;i+1<j;sq[t=(i+j)/2]<=k?(i=t):(j=t));
	assert( sq[j] > k && sq[i] <= k );
	for ( i = j; sq[i] < 2*k && i < ptr-sq; ++i )
		if ( which_peg[sq[i]-k] ) {
			which_peg[k] = which_peg[sq[i]-k], which_peg[sq[i]-k] = 0;
			++k;
			goto nx;
		}
	for ( i = 1; i <= n; ++i )
		if ( empty[i] == yes ) {
			empty[which_peg[k] = i] = 0;
			++k;
			goto nx;
		}
	return ;
}

int main() {
	int ts,i,j,k;
	i64 ax;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( ptr = sq, ax = 0; ax < (1<<29) && ptr-sq <Q; *ptr++ = ax*ax, ++ax );
	for ( scanf("%d",&ts); ts-- && 1 == scanf("%d",&n);) {
		for ( max_k = 0, k = 1, ++yes; k <= n; empty[k++] = yes );
		memset(which_peg,0,sizeof(which_peg));
		rec(1);
		printf("%d\n",max_k);
	}
	return 0;
}
