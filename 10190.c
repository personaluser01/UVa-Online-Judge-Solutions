/*
 * 10190. Divide, but not quite Conquer!
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef long long i64;

i64 m,n;
unsigned long int *ptr,a[1 << 21];

int rec() {
	if ( *(ptr-1) == 1 )
		return 1;
	if ( (*(ptr-1))%m||(*(ptr-1))/m >= *(ptr-1) )
		return 0;
	*ptr = (*(ptr-1))/m, ++ptr;
	return rec();
}

int main() {
	int i;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	while ( 2 == scanf("%lld %lld",&n,&m) ) {
		ptr = a, *ptr++ = n;
		if (!m||m<2||n<2||!rec()) {
			nx: puts("Boring!");
			continue ;
		}
		else {
			for ( i = 0; i < ptr-a-1; ++i )
				printf("%lu ",a[i]);
			printf("%lu\n",a[i]);
		}
	}
	return 0;
}
