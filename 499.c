/*
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

int cnt[256];
char st[0x400],*top;

int main() {
	int i,j,k,ch;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	while ( ch != EOF ) {
		for ( memset(cnt,0,sizeof(cnt)); (ch = getchar()) != EOF && ch != '\n'; ++cnt[ch] );
		for ( k = -1, i = 'A'; i <= 'Z'; ++i )
			if ( cnt[i] > k ) k = cnt[i], top = st, *++top = i;
			else if ( cnt[i] == k ) *++top = i;
		for ( i = 'a'; i <= 'z'; ++i )
			if ( cnt[i] > k ) k = cnt[i], top = st, *++top = i;
			else if ( cnt[i] == k ) *++top = i;
		if ( k <= 0 ) 
			continue ;
		for ( i = 1; i <= top-st; ++i )
			printf("%c",st[i]);
		printf(" %d\n",k);
	}
	return 0;
}
