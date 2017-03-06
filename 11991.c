/*
 * 11991. Easy Problem
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
typedef long long i64;
#define M 1000001
#define N 100100

int m,n,*lst[M],deg[M],cur[M];
i64 v[N],t;

int main() {
	int i,j,k,low,high,mid;
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	while ( 2 == scanf("%d %d",&n,&m) ) {
		memset(deg,0,sizeof(deg));
		for ( i = 1; i <= n; scanf("%lld",&v[i++]), ++deg[v[i-1]] );
		for ( i = 1; i < M; ++i )
			if ( deg[i] ) 
				lst[i] = (int *)malloc((deg[i]+1)*sizeof *lst[i]), cur[i] = 0;
		for ( i = 1; i <= n; ++i )
			lst[v[i]][cur[v[i]]++] = i;
		while ( m-- && 2 == scanf("%d %lld",&k,&t) ) {
			if ( deg[t] < k ) puts("0");
			else {
				printf("%d\n",lst[t][k-1]);
			}
		}
	}
	return 0;
}

