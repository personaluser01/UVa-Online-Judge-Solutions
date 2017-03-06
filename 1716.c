/*
 * 1716. Qanat
 * TOPIC: maths, dp, recursion, integration
 * status: Accepted
 */
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 0x400
#define S(x) ((x)*(x))

int n;
double x[N],v[N],h,w,prod[N];

void solve( int n, double h ) {
	double a,b,c;
	if ( n == 1 ) {
		b = -2*(1-h)*(1+h), a = S(1+h)-S(1-h)-2+4*(1-h), c = 2*S(h)-2-S(1+h)+4*(1+h);
		x[n] = -b/(2*a), v[n] = (S(x[n])*a+x[n]*b+c)/4;
		return ;
	}
	solve(n-1,h);
	b = -2*(1-h)*(1+h), a = 4*v[n-1]-S(1-h)-2+4*(1-h), c = 2*S(h)-2-S(1+h)+4*(1+h);
	x[n] = -b/(2*a), v[n] = (S(x[n])*a+x[n]*b+c)/4;
}

int main() {
	int i,j,k;
	double val;
#ifndef ONLINE_JUDGE
	freopen("1716.in","r",stdin);
#endif
	for (;3 == scanf("%lf %lf %d",&w,&h,&n); ) {
		h /= w, v[n+1] = w;
		solve(n,h), val = v[n]*S(w);
		for ( prod[n] = w, i = n-1; i >= 1; --i )
			prod[i] = prod[i+1]*x[i+1];
		for ( i = 1; i <= n; ++i )
			x[i] *= prod[i], v[i] *= S(x[i]);
		printf("%lf\n",val);
		for ( i = 1; i <= n && i <= 10; ++i )
			printf("%lf\n",x[i]);
	}
	return 0;
}

