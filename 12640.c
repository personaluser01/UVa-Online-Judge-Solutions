/*
 * 12640. Largest Sum Game
 * TOPIC: dp
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N (1<<17)
typedef long long i64;
#define FG (ptr = fgets(buff,sizeof buff,stdin))
#define oo (1LL<<43)

int n;
i64 x[N];
char buff[1 << 21],*ptr;

int rin() {
	int j;
	for ( n = 0; 1 == sscanf(ptr,"%lld%n",x+n,&j); ptr += j, ++n );
	return n;
}

int main() {
	i64 s,ax,i,j,k;
	while ( FG && rin() ) {
		for ( s = -oo, ax = 0, i = 0; i < n; ++i ) {
			if ( ax > s ) 
				s = ax;
			if ( ax+x[i] <= 0 ) ax = 0;
			else ax += x[i];
		}
		if ( s < ax ) s = ax;
		printf("%lld\n",s);
	}
	return 0;
}

