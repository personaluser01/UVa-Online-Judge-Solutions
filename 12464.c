/*
 * 12464. Professor Lazy, Ph.D.
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
typedef long long i64;
#define advance(x,y) (w=(x),(x)=(y),(y)=((y)+1)/w)
#define tol 1e-9

long double a,b,X,Y;
i64 d,n,m;

void find_period() {
	long double x,y,z,t,w;
	i64 i;
	for ( x = a, y = b, z = (b+1)/a, t = (z+1)/b, d = 1; !(fabs(x-z)<tol && fabs(y-t)<tol); ++d ) 
		advance(x,y), advance(z,t), advance(z,t);
	for ( x = a, y = b, z = a, t = b, i = 0; i <= d; ++i, advance(z,t) );
	for ( m = 0; !(fabs(x-z)<tol && fabs(y-t)<tol); advance(x,y), advance(z,t), ++m );
	X = x, Y = y;
}

int main() {
	long double x,y,w;
	i64 rem,i;
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	while ( 3 == scanf("%Lf %Lf %lld",&a,&b,&n) ) {
		if ( !n && fabs(a) < tol && fabs(b) < tol ) break ;

		if ( n <= (1LL<<15) ) {
			if ( n == 0 )
				printf("%.Lf\n",a+tol);
			else if ( n == 1 )
				printf("%.Lf\n",b+tol);
			else {
				for ( x = a, y = b, i = 0; i < n; ++i )
					advance(x,y);
				printf("%.Lf\n",x+tol);
			}
			continue ;
		}
		find_period();
		if ( n <= m ) {
			for ( x = a, y = b, i = 0; i < n; ++i )
				advance(x,y);
			printf("%.Lf\n",x+tol);
		}
		else {
			rem = (n-m)%(d+1);
			if ( rem == 0 )
				printf("%.Lf\n",X+tol);
			else if ( rem == 1 )
				printf("%.Lf\n",b+tol);
			else {
				for ( x = X, y = Y, i = 0; i < rem; ++i )
					advance(x,y);
				printf("%.Lf\n",x+tol);
			}
		}
	}
	return 0;
}

