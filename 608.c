/*
 * 608. Counterfeit Dollar
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
#define N 0x10

int ts,g[N][N],yes;
char bts[1 << N],m[2][7] = {"light","heavy"};
unsigned int u[3],v[3],res[3],W[2];

int consistent( int idx, int t ) {
	int weight[3][2],i,j,k;
	for ( k = 0; k < 3; ++k ) {
		weight[k][0] = weight[k][1] = 0;
		for ( i = 0; i < 12; ++i )
			weight[k][0] += ((u[k]>>i)&1)*(idx == i ? W[t] : 2);
		for ( i = 0; i < 12; ++i )
			weight[k][1] += ((v[k]>>i)&1)*(idx == i ? W[t] : 2);
		if ( weight[k][0] == weight[k][1] && res[k] )
			continue ;
		if ( weight[k][0] < weight[k][1] && !res[k] )
			continue ;
		return 0;
	}
	return 1;
}

int main() {
	int i,j,k,l;
	char s[N],t[N],r[N],tmp[N];
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	W[0] = 1, W[1] = 3;
	for ( scanf("%d",&ts); ts-- && ++yes; ) {
		for ( k = 0; k < 3; res[k++] = (*r == 'e'?1:0) ) {
			scanf("%s %s %s",s,t,r);
			if ( *r == 'u' ) 
				strcpy(tmp,s), strcpy(s,t), strcpy(t,tmp);
			for ( u[k] = 0, i = 0; s[i]; u[k]|=(1UL<<(s[i++]-'A')) );
			for ( v[k] = 0, i = 0; t[i]; v[k]|=(1UL<<(t[i++]-'A')) );
		}
		for ( i = 0; i < 12; ++i )
			for ( l = 0; l <= 1; ++l )
				if ( consistent(i,l) ) {
					printf("%c is the counterfeit coin and it is %s.\n",i+'A',m[l]);
					goto next;
				}
		assert( 0 );
next:;
	}
	return 0;
}

