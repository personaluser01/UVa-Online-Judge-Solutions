/*
 * 1524. Hot or Cold?
 * TOPIC: integration, horner rule
 * status: Accepted
 */
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 0x80

double p[N],s,e;
int n;

double eval( double *p, int n, double t ) {
	double s = 0;
	int i;
	for ( i = n; i >= 0; --i )
		s *= t, s += p[i];
	return s;
}

int main() {
	int i,j,k,cs;
#ifndef ONLINE_JUDGE
	freopen("c.txt","r",stdin);
#endif
	for (;1 == scanf("%d",&n) && n>0; ) {
		for ( i = n+1; i >= 1; --i ) 
			scanf("%lf",&p[i]), p[i]/=i;
		scanf("%lf %lf",&s,&e);
		printf("%.3lf\n",(eval(p,n+1,s)-eval(p,n+1,e))/(s-e));
	}
	return 0;
}

