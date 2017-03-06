/*
 * 1326. Period
 * TOPIC: kmp
 * status: Accepted
 */
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N (1<<21)

char s[N];
int n,p[N];

int main() {
	int i,j,k,cs = 0;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for(;1==scanf("%d",&n)&&n>0&&1==scanf("%s",s+1);putchar('\n')) {
		printf("Test case #%d\n",++cs);
		for ( p[0] = -1, p[1] = 0, i = 2, k = p[i-1]; i <= n; p[i++] = ++k ) 
			for (;k >= 0 && s[k+1] != s[i]; k = p[k] );
		for ( i = 2; i <= n; ++i )
			if ( p[i] >= 1 && 0 == (p[i]%(i-p[i])) )
				printf("%d %d\n",i,i/(i-p[i]));
	};
	return 0;
};

