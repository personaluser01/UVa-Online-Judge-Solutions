/*
 * 11109. Rinse
 * TOPIC: maths, cauchy inequality
 * status: Accepted
 */
#include <assert.h>
#include <math.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define tol 1e-11
#define oo (1<<29)
double min( double x, double y ) { if ( x<y) return x; return y; }
double max( double x, double y ) { if ( x>y) return x; return y; }
double a,b,r,c;

double f( int n, double *t ) {
	double x = min(c-r,b/n),up=a,down=1;
	int i;
	for ( *t=x, i = 0; i < n-1; ++i, up *= r, down *= (x+r) );
	return up/down;
}

int main() {
	int i,j,k,l,optimal_steps;
	double w,best_ratio,y,x,first_run,t,amt,avg;
#ifndef ONLINE_JUDGE
	freopen("E.1.dat","r",stdin);
#endif
	for (;1==scanf("%d",&k)&&k>0;putchar('\n')) {
		scanf("%lf %lf %lf %lf",&b,&a,&r,&c);
		/*printf("b = %.2lf, a = %.2lf, r = %.2lf, c = %.2lf\n",b,a,r,c);*/
		amt = b+a-r;
		if ( amt < 0 ) {
			putchar('0');
			continue ;
		}
		avg = amt/k;
		if ( avg >= c-r ) avg = c-r;
		if ( avg >= a-r ) {
			printf("%d %0.2lf",k,avg-a+r);
			for ( i=1; i < k; ++i )
				printf(" %0.2lf",avg);
			continue ;
		}
		else {
			avg = b/(k-1);
			printf("%d 0.00",k);
			for ( i = 1; i < k; ++i )
				printf(" %0.2lf",avg);
		}
		/*
		t=min(c,(b+a-r)/k+r);
		if ( t-a >= 0 && t-r >= 0 ) { first_run = t-a; goto nx; }
		if ( (first_run=t-a) < 0 ) {
			first_run = 0;
			t = min(c,b/(k-1)+r);
			if ( t-r <= 0 ) { printf("%d",0); continue ; } 
			goto nx;
		}
		if ( t-r < 0 ) {
			if ( first_run > b ) {
				printf("%d",0);
				continue ;
			}
			printf("1 %0.2lf",first_run);
			continue ;
		}
nx:
		if ( fabs(first_run) < tol && fabs(t-r) < tol ) { putchar('0'); continue ; }
		for ( printf("%d",k), printf(" %0.2lf",first_run), i = 1; i < k; ++i )
			printf(" %0.2lf",t-r);
			*/
	}
	return 0;
}

