/*
 * Movie
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
	int ts,m,p;
	for ( scanf("%d",&ts); ts-- && 2 == scanf("%d %d",&m,&p); printf("%d\n",10*m+(m>=10?p:2*p)) );
	return 0;
}

