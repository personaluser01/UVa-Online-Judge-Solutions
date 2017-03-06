/*
 * 12578. 10:6:2
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <limits.h>
#include <float.h>
#define pi (acos(-1))

long double L,W,R;

int main() {
	int i,j,k,ts;
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	for ( scanf("%d",&ts); ts--; ) {
		scanf("%Lf",&L);
		W = 6*L/10.00;
		R = L/5.00;
		printf("%.2Lf %.2Lf\n",pi*R*R,L*W-pi*R*R);
	}
	return 0;
}
