/*
 * 11021. Tribbles
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 0x400
#define tol 1e-9

int ts,cs,n,m,K;
double p[N],z[N];

double eval( double x ) {
	double w = 0;
	int i;
	for ( i = n-1; i >= 0; --i )
		w *= x, w += p[i];
	return w;
}

double mypow( double x, int n ) {
	double ax = 1.00;
	for (;n;n>>=1,x*=x)
		if (n&1) ax *= x;
	return ax;
}

int main() {
	int i,j,k;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( scanf("%d",&ts); ts-- && printf("Case #%d: ",++cs);) {
		scanf("%d %d %d",&n,&K,&m); 
		for ( i = 0; i < n; scanf("%lf",&p[i++]) );
		if ( K == 0 )
			puts("1.0000000");
		else {
			if ( m == 0 ) {
				puts("0.0000000");
				continue ;
			}
			for ( z[i=1] = 0; (++i) <= m+1; z[i] = eval(z[i-1]) );
			printf("%.7lf\n",mypow(z[m+1],K)+tol);
		}
	}
	return 0;
}

