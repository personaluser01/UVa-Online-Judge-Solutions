/*
 * 10136. Chocolate Chip Cookies
 * status: Accepted
 */
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 0x200
#define FG (ptr = fgets(buff,sizeof(buff),stdin))
#define R (2.5000)
#define tol 1e-9
#define S(x) ((x)*(x))
#include <float.h>
#define oo (DBL_MAX-10000)

int n;
long double x[N],y[N],d,a,b,cx,cy;
char buff[0x400],*ptr;

int main() {
	int i,j,k,l,ax,ts;
	long double low,high,t;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for (scanf("%d\n",&ts),FG;ts--;) {
		for ( ax = 0, n = 0; FG && 2 == sscanf(buff,"%Lf %Lf",x+n,y+n) && ++n;);
		if ( n ) ax = 1;
		for ( i = 0; i < n; ++i )
			for ( j = i+1; j < n; ++j ) {
				d = sqrt(S(x[i]-x[j])+S(y[i]-y[j]));
				if ( d > 2*R ) continue ;
				a = x[i]-x[j], b = y[i]-y[j];
				for ( low = 0, high = +oo; fabs(low-high) > tol; ) {
					t = (low+high)/2;
					cx = (x[i]+x[j])/2-b*t;
					cy = (y[i]+y[j])/2+a*t;
					if ( sqrt(S(cx-x[i])+S(cy-y[i])) <= R )
						low = t;
					else high = t;
				}
				cx = (x[i]+x[j])/2-b*low;
				cy = (y[i]+y[j])/2+a*low;
				for ( l = k = 0; k < n; ++k )
					if ( sqrt(S(x[k]-cx)+S(y[k]-cy)) <= R && ++l );
				ax=(ax<l)?l:ax;
				cx = (x[i]+x[j])/2+b*low;
				cy = (y[i]+y[j])/2-a*low;
				for ( l = k = 0; k < n; ++k )
					if ( sqrt(S(x[k]-cx)+S(y[k]-cy)) <= R && ++l );
				ax=(ax<l)?l:ax;
			}
		printf("%d\n",ax);
		if ( ts ) putchar('\n');
	}
	return 0;
}
