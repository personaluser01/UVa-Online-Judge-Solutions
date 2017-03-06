/*
 * 10144. Expression
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 0x80

char num[N][4],s[N*50],*ptr;

void rec( int n ) {
	if ( n == 1 ) { ptr += sprintf(ptr,"((A0|B0)|(A0|B0))"); return ; }
	ptr += sprintf(ptr,"(("), rec(n-1);
	ptr += sprintf(ptr,"|((A%s|A%s)|(B%s|B%s)))|(A%s|B%s))",num[n-1],num[n-1],num[n-1],num[n-1],num[n-1],num[n-1]);
}

int main() {
	int ts,n,k;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for(num[0][0]='0',n=1;n<N;sprintf(num[n],"%d",n),++n);
	for ( scanf("%d",&ts); ts-- && scanf("%d",&n); ) {
		ptr = s, rec(n), printf("%s\n",s);
		if ( ts ) putchar('\n');
	}
	return 0;
}
