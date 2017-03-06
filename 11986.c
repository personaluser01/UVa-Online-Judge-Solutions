/*
 * 11986. Save from Radiation
 * TOPIC: logarithms, maths
 * status: Accepted
 */
#include <stdio.h>
#include <math.h>
#define tol (1e-9)

int f( double x ) {
    int dx = (int)(x);
    return ++dx;
}

int main() {
    int ts,cs = 0,k;
	unsigned long long n;
    for(scanf("%d",&ts);ts--&&1==scanf("%llu",&n);) {
		printf("Case %d: ",++cs);
		for( k = 0; n; n >>= 1, ++k );
		printf("%d\n",k);
	}
    return 0;
}

