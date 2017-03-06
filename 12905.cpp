/*
 * 12905. Volume of Revolution
 * TOPIC: neat, pappus-guldenus, maths, calculus
 * status: Accepted
 */
#include <bits/stdc++.h>
#define pi (2*acos(0.00))
#define N 0x100

double c[N],C[N],a,b,phi,d,x[1<<16],v[1<<16],si,volume,Volume,e[N],E[N];
int n,slices,stacks,m;

double eval( double *x, int n, double t ) {
	double val = 0;
	for ( int i = n; i >= 0; val *= t, val += x[i--] );
	return val;
}

int main() {
	int i,j,k,ts,cs = 0;
#ifndef ONLINE_JUDGE
	freopen("12905.in","r",stdin);
#endif
	for ( scanf("%d",&ts); ts--; ) {
		for ( scanf("%d",&n), i = n; i >= 0; scanf("%lf",&c[i--]) );
		scanf("%lf %lf %d %d",&a,&b,&slices,&stacks), phi = 2*pi/slices, d = (b-a)/stacks;
		for ( i = 0; i <= (m=stacks); ++i ) v[i] = fabs(eval(c,n,x[i] = a+d*i));
		for ( volume = 0, si = sin(phi), i = 0; i <= m-1; ++i )
			volume += (v[i+1]*v[i+1]+v[i+1]*v[i]+v[i]*v[i]);
		volume *= d*si, volume /= 6, volume *= slices;
		for ( i = 0; i <= n+n+n; e[i++] = 0 );
		for ( i = 0; i <= n; ++i )
			for ( j = 0; j <= n; ++j )
				e[i+j] += c[i]*c[j];
		for ( i = n+n+n; i >= 1; --i ) E[i] = e[i-1]/i;
		Volume = pi*(eval(E,n+n+n,b)-eval(E,n+n+n,a));
		printf("Case %d: %.4lf\n",++cs,100.00*fabs(1-volume/Volume));
	}
	return 0;
};

