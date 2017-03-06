/*
 * 11186. Cirum Triangle
 * TOPIC: geometry, sums, vectors
 * status: Accepted
 */
#include <bits/stdc++.h>
#define pi (2*acos(0.00))
#define tol 1e-9
#define N 0x400
typedef long long i64;

long double s,r,theta[N],a[N][N],B[N][N];
int n;

i64 nearest( long double x ) {
	i64 dx = (i64)(x+tol),
		ux = dx+1;
	return x-dx<ux-x?dx:ux;
}

int main() {
	int i,j,k;
#ifndef ONLINE_JUDGE
	freopen("11186.in","r",stdin);
#endif
	while ( 2 == scanf("%d %Lf",&n,&r) ) {
		if ( !n && !r ) continue ;
		for ( r *= r, i = 0; i < n; ++i )
			scanf("%Lf",&theta[i]), theta[i]*=pi, theta[i]/=180.00;
		for ( i = 0; i <= n+1; ++i )
			for ( j = 0; j <= n+1; ++j )
				a[i][j] = B[i][j] = 0;
		for ( i = 0; i < n; ++i )
			for ( j = i+1; j < n; ++j )
				a[j][i] = a[i][j] = fabs(sin((theta[j]-theta[i])/2));
		for ( s = 0, i = 0; i < n; ++i )
			for ( j = i+1; j < n; ++j )
				for ( k = j+1; k < n; ++k )
					s += a[i][j]*a[j][k]*a[k][i];
		printf("%lld\n",nearest(2*s*r));
	}
	return 0;
}

