/*
 * 10174. Couple-Bachelor-Spinster Numbers
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <limits.h>
#include <float.h>
#define NO(n) (puts((n)&1?"Spinster Number.":"Bachelor Number."))

typedef long long i64;
i64 m,n;
char buff[0x400];

int main() {
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	while ( fgets(buff,sizeof(buff),stdin) ) {
		if ( 2 == sscanf(buff,"%lld %lld",&m,&n) ) {
		}
		else {
			assert( 1 == sscanf(buff,"%lld",&n) );
			m = n%8;
			if ( m != 0 && m != 1 && m != 3 && m != 5 && m != 7 ) {
				NO(n);
				continue ;
			}
			if ( m == 0 ) {
				if ( n % 16 ) {
					NO(n);
					continue ;
				}
			}
		}
	}
	return 0;
}
