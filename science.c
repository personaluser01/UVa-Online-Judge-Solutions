/*
 * Science
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int ts;

int main() {
	int i,j,k,w,a,c,n,e;
	for ( scanf("%d",&ts); ts--; ) {
		assert( 4 == scanf("%d %d %d %d",&a,&c,&n,&e) );
		if ( a == 1 ) 
			w = 105;
		else {
			if ( c == 0 ) 
				w = 125;
			else w = 145+50*n+25*e;
		}
		printf("%d\n",w);
	}
	return 0;
}

