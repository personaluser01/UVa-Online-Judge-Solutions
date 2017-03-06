/*
 * 1577. Low Power
 * TOPIC: binary search, greedy
 * status: Accepted
 */
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N (1<<21)
#define oo (1LL<<43)
typedef long long i64;

i64 p[N],M;
int m,n;

int cmp( const void *x, const void *y ) {
	if ( *(i64 *)x == *(i64 *)y ) return 0;
	if ( *(i64 *)x < *(i64 *)y ) return -1;
	return 1;
}

int main() {
	int i,j,k;
	i64 good,bad,mid;
#ifndef ONLINE_JUDGE
	freopen("c.txt","r",stdin);
#endif
	for ( ;2==scanf("%d %d",&n,&m) && n>0; ) {
		for ( i = 0; i < 2*n*m; scanf("%lld",&p[i++]) );
		qsort(p,M=2*n*m,sizeof *p,cmp);
		for ( good = +oo, bad = -1; bad+1 != good; ) {
			mid = (good+bad)/2;
			for ( k = 0, j = 0, i = 0; i < M-1 && k < n && j <= k*2*m; ) 
				if ( p[i+1]-p[i] <= mid ) 
					i += 2, ++k, j += 2;
				else 
					++i, ++j;
			if ( k == n ) good = mid;
			else bad = mid;
		}
		printf("%lld\n",good);
	}
	return 0;
}


