/*
 * 833. Water Falls
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
#define N 0x400
typedef long long i64;
#define tol 1e-9
#define S(x) ((x)*(x))

int n,m,elim[N],yes;
i64 x[2][N],y[2][N],
	 sx,sy;

i64 max( i64 x, i64 y ) { return x < y ? y:x; }
i64 min( i64 x, i64 y ) { return x > y ? y:x; }

long double dist( i64 sx, i64 sy, int idx ) {
	long double a,b,na,nb,ax,ay,bx,by;
#define X(t) (x[0][idx]+(t)*(x[1][idx]-x[0][idx]))
#define Y(t) (y[0][idx]+(t)*(y[1][idx]-y[0][idx]))

	a = (sx-x[0][idx]+tol)/(x[1][idx]-x[0][idx]);
	ax = sx, ay = Y(a);
	if ( ay > sy )
		return DBL_MAX-1024;
	return S(ax-sx)+S(ay-sy);

	for ( a = 0, b = 1; fabs(b-a) > tol; ) {
		na = (2*a+b)/3, nb = (2*b+a)/3;
		ax = X(na), ay = Y(na);
		bx = X(nb), by = Y(nb);
		if ( S(ax-sx)+S(ay-sy) < S(bx-sx)+S(by-sy) )
			b = nb;
		else
			a = na;
	}
	ax = X(a), ay = Y(a);
	return S(ax-sx)+S(ay-sy);
}

int find_below( i64 sx, i64 sy ) {
	long double w = DBL_MAX-1024,tmp;
	int res = -1,i;
	for ( i = 0; i < n; ++i )
		if ( elim[i] != yes && min(x[0][i],x[1][i]) <= sx && sx <= max(x[0][i],x[1][i]) ) 
			if ( min(y[0][i],y[1][i]) <= sy ) {
				tmp = dist(sx,sy,i);
				if ( tmp < w )
					w = tmp, res = i;
			}
	return res;
}

int main() {
	int i,j,k,ts;
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	for ( scanf("%d",&ts); ts--; ) {
		scanf("%d",&n);
		for ( i = 0; i < n; ++i )
			scanf("%lld %lld %lld %lld",x[0]+i,y[0]+i,x[1]+i,y[1]+i);
		scanf("%d",&m);
		for ( k = 0; k < m; ++k ) {
			scanf("%lld %lld",&sx,&sy);
			for ( ++yes; (i = find_below(sx,sy)) >= 0; ) {
				elim[i] = yes;
				if ( y[0][i] < y[1][i] )
					sx = x[0][i], sy = y[0][i];
				else
					sx = x[1][i], sy = y[1][i];
			}
			printf("%lld\n",sx);
		}
		if ( ts ) putchar('\n');
	}
	return 0;
}

