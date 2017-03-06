/*
 * 10250. The Other Two Trees
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

double x[4],y[4],mx,my,u,v,nu,nv;

int main() {
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	while ( 4 == scanf("%lf %lf %lf %lf",x,y,x+1,y+1) ) {
		mx = x[0]+x[1], mx /= 2;
		my = y[0]+y[1], my /= 2;
		u = x[0]-mx, v = y[0]-my;
		nu = -v, nv = u;
		x[2] = nu+mx, y[2] = nv+my;
		nu = v, nv = -u;
		x[3] = nu+mx, y[3] = nv+my;
		printf("%.10lf %.10lf %.10lf %.10lf\n",x[2],y[2],x[3],y[3]);
	}
	return 0;
}
