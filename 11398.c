/*
 * 11398. Base-1 Number System
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
typedef unsigned long long u64;

u64 n,t;
char mess[0x100],s[0x100],*ptr;

int main() {
	int i,j,k;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for (;0[mess] != '~'; printf("%llu\n",n) ) {
		for ( ptr = s, t = 0; 1 == scanf("%s",mess) && 0[mess] != '~' && 0[mess] != '#'; ) {
			if ( (n = strlen(mess)) == 1 ) { t = 1; continue ; }
			if ( n == 2 ) { t = 0; continue; }
			assert( n >= 3 );
			for ( k = n-2; k--; *ptr++ = t+'0' );
		}
		if ( 0[mess] == '~' ) break ;
		for ( n = 0, i = 0; i < ptr-s; n = (n<<1)+s[i++]-'0' );
	}
	return 0;
}
