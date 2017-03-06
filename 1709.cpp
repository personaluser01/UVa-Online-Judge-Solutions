/*
 * 1709. Amalgamated Artichokes
 * TOPIC: trivial
 * status: Accepted
 */
#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;
#define N 1000001
#define oo (1<<29)

double a,b,c,d,p,w,M[N],x[N];
int n,k,i;

int main() {
	while ( 6 == scanf("%lf %lf %lf %lf %lf %d",&p,&a,&b,&c,&d,&n) ) {
		for ( w = M[0] = -oo, i = 1; i <= n; ++i ) {
			x[i] = p*(sin(a*i+b)+cos(c*i+d)+2);
			if ( x[i] > M[i-1] )
				M[i] = x[i];
			else M[i] = M[i-1];
			if ( M[i]-x[i] > w )
				w = M[i]-x[i];
		}
		if ( w <= 0 )
			printf("%d\n",0);
		else printf("%lf\n",w);
	}
	return 0;
}
