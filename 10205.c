/*
 * 10205. Stack Them Up
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
#define N 0x80
#define enc(s,v) ((s)|((v)<<3))
#define VAL 13
#define S   4

int c[N][52],n,x[52];
char buff[0x400];

void apply( int t ) {
	int y[52],i,j;
	for ( j = 0; j < 52; ++j ) 
		i = c[t][j], y[j] = x[i];
	for ( i = 0; i < 52; ++i )
		x[i] = y[i];
}

char suit[S][12] = {"Clubs","Diamonds","Hearts","Spades"},
	 value[VAL][6] = {"2","3","4","5","6","7","8","9","10","Jack","Queen","King","Ace"};

void display( int u ) {
	int s = u & 3,
		v = u >> 3;
	printf("%s of %s\n",value[v],suit[s]);
}

int main() {
	int i,j,k,ts;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( scanf("%d\n",&ts); ts--; ) {
		scanf("%d\n",&n);
		for ( k = 0, i = 0; i < S; ++i )
			for ( j = 0; j < VAL; ++j )
				x[k++] = enc(i,j);
		assert( k == 52 );
		for ( k = 1; k <= n; ++k ) 
			for ( i = 0; i < 52; ++i )
				scanf("%d\n",c[k]+i), --c[k][i];
		for ( ;fgets(buff,sizeof(buff),stdin) && 1 == sscanf(buff,"%d",&k); apply(k) );
		for ( i = 0; i < 52; ++i )
			display(x[i]);
		if ( ts ) putchar('\n');
	}
	return 0;
}
