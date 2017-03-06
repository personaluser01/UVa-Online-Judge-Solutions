/*
 * 12886. The Big Painting
 * TOPIC: 2d matching, aho-corasick, similar to matrix matcher
 * status:
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N (0x400<<1)

int m,n,mp,np;
char g[N][N],G[N][N];

int main() {
	int i,j,k;
#ifndef ONLINE_JUDGE
	freopen("12886.in","r",stdin);
#endif
	for ( ;4 == scanf("%d %d %d %d",&mp,&np,&m,&n); ) {
		for ( i = 0; i < mp; scanf("%s",g[i++]) );
		for ( i = 0; i < m; scanf("%s",G[i++]) );
	}
	return 0;
};

