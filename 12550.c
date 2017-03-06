/*
 * 12550. How do spider walk on water?
 * TOPIC: maths, recurrences, simulation
 * status: Accepted
 */
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define tol 1e-9
#define MAXD 10100
#define N (1<<16)
typedef long long i64;

char buff[N],*ptr;
int n;
i64 D,P;
long double det,da,db,a,b,c[N],cand,coeff;

int main() {
	int i,j,k,ok;
	for (;ptr = fgets(buff,sizeof buff,stdin);) {
		sscanf(ptr,"%lld%n",&D,&k), ptr += k, sscanf(ptr,"%lld%n",&P,&k);
		if ( D == 0 && P == 0 ) break ;
		for ( i = 0, ptr += k; 1 == sscanf(ptr,"%Lf%n",c+i,&k); ptr += k, ++i );
		assert( (n=i) >= 4 );
		det = c[2]*c[0]-c[1]*c[1];
		da = c[0]*c[3]-c[1]*c[2];
		db = c[2]*c[2]-c[1]*c[3];
		if ( fabs(det) < tol) {
			if ( c[0] == c[1] && c[1] == c[2] && c[2] == c[3] )
				for (;n <= D; c[n] = c[n-1], ++n );
			else {
				coeff = c[2]/c[1];
				for ( ;n<=D; c[n] = coeff*c[n-1], ++n );
			}
			nx:
			if ( c[0] > P ) {
				puts("The spider is going to fall!");
				continue ;
			}
			for ( c[n] = (1LL<<53), i = 0; i < n; ++i )
				if ( c[i] <= P && c[i+1] > P ) break ;
			assert( i <= D );
			if ( D-i == 0 ) {
				puts("The spider may fall!");
				continue ;
			}
			printf("%lld\n",D-i);
			continue ;
		}
		a = da/det, b = db/det;
		for ( ok = 1, i = 4; i < n && ok; ++i ) {
			cand = a*c[i-1]+b*c[i-2];
			if ( fabs(cand-c[i]) >= tol ) ok = 0;
		}
		if ( !ok ) 
			goto nx;
		for (;n<=D; ++n)
			c[n] = a*c[n-1]+b*c[n-2];
		goto nx;
	}
	return 0;
}

