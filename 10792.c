/*
 * 10792. Laurel and Hardy
 * status: Accepted
 * KEYWORDS: SET, SAT
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <limits.h>
#include <float.h>

int ts,cs;
long double r,d,h1,l,a,L,b,B;

int main() {
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( scanf("%d",&ts); ts-- && 3 == scanf("%Lf %Lf %Lf",&r,&d,&h1); ) {
		l = r-d;
		a = asin(l/r);
		L = 2*r*cos(a);
		b = asin((r-h1)/r)-a;
		B = L*cos(b);
		printf("Case %d: %.4Lf\n",++cs,h1+sqrt(L*L-B*B));
	}
	return 0;
}
