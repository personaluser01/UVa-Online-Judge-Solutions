/*
 * 11281. Triangular Pegs in Round Holes
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
#define N 0x80
#define pi (2*acos(0.0))

int n,m;
long double r[N],x[N],y[N],z[N],a[N],b[N],c[N],w;

int f( long double x, long double y, long double z, long double r ) {
	long double p = (x+y+z)/2,
		 	a = sqrt(p*(p-x)*(p-y)*(p-z));
	return x*y*z <= r*4*a;
}

int main() {
	int i,j,k;
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	while ( 1 == scanf("%d",&n) ) {
		for ( i = 0; i < n; ++i )
			scanf("%Lf",r+i), r[i]/=2;
		assert( 1 == scanf("%d",&m) );
		for ( i = 0; i < m; ++i ) {
			scanf("%Lf %Lf %Lf",x+i,y+i,z+i);
			a[i] = ((y[i]*y[i]+z[i]*z[i]-x[i]*x[i])/(2*y[i]*z[i]));
			b[i] = ((x[i]*x[i]+z[i]*z[i]-y[i]*y[i])/(2*x[i]*z[i]));
			c[i] = ((y[i]*y[i]+x[i]*x[i]-z[i]*z[i])/(2*x[i]*y[i]));
			if ( a[i] >= 0  && b[i] >= 0 && c[i] >= 0 ) {
				for ( k = 0, j = 0; j < n; ++j ) 
					if ( f(x[i],y[i],z[i],r[j]) && ++k ) {
						if ( k == 1 )
							printf("Peg %c will fit into hole(s):",i+'A');
						printf(" %d",j+1);
					}
				if ( !k )
					printf("Peg %c will not fit into any holes",i+'A');
				putchar('\n');
			}
			else {
				if ( a[i] < 0 )
					w = x[i];
				else if ( b[i] < 0 )
					w = y[i];
				else
					w = z[i];
				assert( w >= x[i] && w >= y[i] && w >= z[i] );
				for ( k = 0, j = 0; j < n; ++j ) 
					if ( r[j] >= w/2 && ++k ) {
						if ( k == 1 )
							printf("Peg %c will fit into hole(s):",i+'A');
						printf(" %d",j+1);
					}
				if ( !k )
					printf("Peg %c will not fit into any holes",i+'A');
				putchar('\n');
			}
		}
	}
	return 0;
}
