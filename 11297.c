/*
 * 11297. Census
 * TOPIC: 2D Range Queries
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <limits.h>
#include <float.h>
#define N 512

int n,m,c[N][N],qr;

int main() {
	int i,j,k,l,t;
	char tmp[0x400];
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	scanf("%d %d",&m,&n);
	for ( i = 1; i <= m; ++i )
		for ( j = 1; j <= n; ++j )
			scanf("%d",&c[i][j]);
	for ( scanf("%d",&qr); qr--; ) {
		scanf("%s",tmp);
		switch ( 0[tmp] ) {
			case 'c': assert( 3 == scanf("%d %d %d",&i,&j,&k) );
					  break ;
			case 'q': assert( 4 == scanf("%d %d %d %d",&i,&j,&k,&l) ); 
					  break; 
		}
	}
	return 0;
}

