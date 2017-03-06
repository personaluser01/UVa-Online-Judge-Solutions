/*
 * 121. Pipe Fitters
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
#define pi (2*acos(0.00))
#define tol 1e-9

int max( int x, int y ) { return x < y ? y : x; }

long double m,n;
int g,s;

int grid( long double m, long double n ) {
	int x = (int)(n+tol),
		y = (int)(m+tol);
	return x*y;
}

int skew( long double m, long double n ) {
	int rows = (int)(2*(n-1)/sqrt(3)+tol)+1,
		cols = (int)(m+tol),sk = -1;
	long double h = m-cols,t = sqrt(1-h*h);
	if ( rows < 1 ) rows = 0;
	if ( cols < 1 ) cols = 0;
	if ( !rows||!cols ) return 0;
	if ( rows & 1 )
		sk = max(sk,((rows+1)/2)*(cols)+(rows/2)*(cols-1));
	else sk = max(sk,(cols+cols-1)*rows/2);
	if ( m >= cols+.5 )
		sk = max(sk,rows*cols);
	/*rows = (int)((n-1)/t+tol)+1;
	sk = max(sk,rows*cols);*/
	return sk;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for (;2 == scanf("%Lf %Lf",&m,&n);) {
		if ( (int)(m+tol)<1||((int)(n+tol))<1 ) {
			puts("0 grid");
			continue ;
		}
		g = max(grid(m,n),grid(n,m));
		s = max(skew(m,n),skew(n,m));
		printf("%d %s\n",max(g,s),g>=s?"grid":"skew");
	}
	return 0;
}
