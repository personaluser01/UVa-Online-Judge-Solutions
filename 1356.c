/*
 * 1356. Bridge
 * TOPIC: binary search, integration, newton-raphson, hyperbolic functions
 * status: Accepted
 */
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define tol 1e-12
#define oo (1<<29)

long double D,H,B,L;

long double F( long double z ) {
	long double r = z+sqrt(1+z*z), R = r*r;
	return R-1/R+4*log(r)-8*L*z/B;
}

long double DF( long double z ) {
	long double s = sqrt(1+z*z), r = z+s, R = r*r, TR = R*r, v = 2*(1+2*z/s);
	return v*(r+1/TR+2/r)-8*L/B;
}

long double f( int n ) {
	long double d = B/(n+1),x[2];
	int t;
	/*printf("%lf %lf\n",d,D);*/
	assert( d<=D );
	for ( x[t=0]=3*H/4, x[t^1]=+oo; fabs(x[0]-x[1]) > tol; x[t^1] = x[t]-F(x[t])/DF(x[t]), t ^= 1 );
	return H-d*x[t]/4.00;
}

int main() {
	int i,j,k,ts,cs = 0,good,bad,mid;
	long double w;
#ifndef ONLINE_JUDGE
	freopen("c.txt","r",stdin);
#endif
	for ( scanf("%d",&ts); ts--; ) {
		printf("Case %d:\n",++cs), scanf("%Lf %Lf %Lf %Lf",&D,&H,&B,&L);
		for ( k = (int)(B/D); B/k > D; ++k );
		if ( (w=f(k-1)) > 0 ) {
			printf("%.2Lf\n",w);
			goto next;
		}
		for ( bad = k-1, good = +oo; good>bad+1; )
			if ( f(mid=(good+bad)/2) > 0 )
				good = mid;
			else bad = mid;
		printf("%.2Lf\n",f(good));
next:
		if ( ts ) putchar('\n');
	}
	return 0;
}

