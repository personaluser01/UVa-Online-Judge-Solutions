/*
 * 1074. Net Loss
 * TOPIC: maths, ternary search
 * status: Accepted
 */
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define tol ((double)1e-13)
#define oo ((double)(1LL<<15))
#define N 0x80

double f[N],fsquare[N],c;
int n,m;

double eval( double *p, int n, double t ) {
	double s = 0;
	for ( ;n>=0; s *= t, s += p[n--] );
	return s;
};

double P( double A, double B ) {
	return (B*B*B-A*A*A)/3-c*(B*B-A*A)+c*c*(B-A);
};

double Q( double A, double B, double t ) {
	double q[N],iq[N];
	int i,j,k;
	for ( i = 0; i <= n+2; ++i ) q[i] = 0;
	for ( i = 0; i <= n; ++i )
		q[i] -= f[i]*c;
	for ( i = 1; i <= n+2; ++i )
		q[i] += f[i-1];
	q[1] -= t, q[0] += c*t;
	for ( i = 0; i <= n+2; ++i ) q[i] *= 2;
	for ( i = 1; i <= n+3; ++i )
		iq[i] = q[i-1]/i;
	return -eval(iq,n+3,B)+eval(iq,n+3,A);
};

double R( double A, double B, double t ) {
	double q[N],iq[N];
	int i,j,k;
	for ( i = 0; i <= n+n+2; ++i )
		q[i] = fsquare[i];
	q[0] += t*t;
	for ( i = 0; i <= n+1; ++i )
		q[i] -= 2*t*f[i];
	for ( i = 1; i <= n+n+3; ++i )
		iq[i] = q[i-1]/i;
	return eval(iq,n+n+3,B)-eval(iq,n+n+3,A);
};

double left( double t ) {
	double B = Q(-1,c,t),
		   A = P(-1,c),
		   C = R(-1,c,t),
		   v = -B/(2*A);
	return A*v*v + B*v + C;
};

double right( double t ) {
	double B = Q(c,1,t),
		   A = P(c,1),
		   C = R(c,1,t),
		   v = -B/(2*A);
	return A*v*v + B*v + C;
};

double F( double t ) { return left(t)+right(t); };

int main() {
	int i,j,k,cs = 0;
	double a,b,na,nb,A[2],B[2],r,t,v,aa,bb,cc;
#ifndef ONLINE_JUDGE
	freopen("1074.in","r",stdin);
#endif
	for (;1==scanf("%d",&n)&&n;) {
		memset(f,0,sizeof f);
		for ( i = n; i >= 0; --i )
			scanf("%lf",&f[i]);
		scanf("%lf",&c);
		if ( n == 1 ) {
			printf("Case %d: %.3lf %.3lf %.3lf %.3lf\n",++cs,f[1],f[0],f[1],f[0]);
			continue ;
		}
		memset(fsquare,0,sizeof fsquare);
		for ( i = 0; i <= n; ++i )
			for ( j = 0; j <= n; ++j )
				fsquare[i+j] += f[i]*f[j];
		for ( a = -oo, b = +oo; fabs(b-a)>tol; ) {
			na = (2*a+b)/3.00, nb = (a+2*b)/3.00;
			if ( F(na) < F(nb) )
				b = nb;
			else a = na;
		}
		t = (a+b)/2;
		aa = P(-1,c), bb = Q(-1,c,t), cc = R(-1,c,t);
		A[1] = -bb/(2*aa), A[0] = t-A[1]*c;
		aa = P(c,1), bb = Q(c,1,t), cc = R(c,1,t);
		B[1] = -bb/(2*aa), B[0] = t-B[1]*c;
		printf("Case %d: %.3lf %.3lf %.3lf %.3lf\n",++cs,A[1]+tol,A[0]+tol,B[1]+tol,B[0]+tol);
	}
	return 0;
};

