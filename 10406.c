/*
 * 10406. Cutting Tabletops
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
#define tol 1e-9
#define N (1 << 15)

long double d,x[N],y[N],A,B,C,nx[N],ny[N];
int n,determined[N],yes;

int main() {
	int i,j,k,l;
	long double low,high,mid,ti,tj,NOR,
			a,b,c,na,nb,sx,sy,px,py,qx,qy;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for(;2==scanf("%Lf %d",&d,&n) && !(fabs(d)<tol&&n==0) && ++yes; ) {
		for ( i = 0; i < n; ++i ) 
			scanf("%Lf %Lf",x+i,y+i);
		for ( i = 0; i < n; ++i ) {
			j = (i+1)%n;
			l = (i+n-1)%n, k = (j+1)%n;
			A = (y[j]-y[i]), B = -(x[j]-x[i]), C = -x[i]*(y[j]-y[i])+y[i]*(x[j]-x[i]);
			NOR = sqrt(A*A+B*B);
			for ( low = 0, high = 1; fabs(high-low) > tol;) {
				mid = (low+high)/2;
				sx = x[i] + (x[l]-x[i])*mid;
				sy = y[i] + (y[l]-y[i])*mid;
				if ( fabs(A*sx + B*sy+C)/NOR < d )
					low = mid;
				else high = mid;
			}
			ti = high;
			for ( low = 0, high = 1; fabs(high-low) > tol;) {
				mid = (low+high)/2;
				sx = x[j] + (x[k]-x[j])*mid;
				sy = y[j] + (y[k]-y[j])*mid;
				if ( fabs(A*sx + B*sy+C)/NOR < d )
					low = mid;
				else high = mid;
			}
			tj = high;
			px = x[i]+ti*(x[l]-x[i]);
			py = y[i]+ti*(y[l]-y[i]);
			qx = x[j]+tj*(x[k]-x[j]);
			qy = y[j]+tj*(y[k]-y[j]);
			if ( determined[i] != yes ) {
				A = (y[l]-y[i]), B = -(x[l]-x[i]), C = -x[i]*(y[l]-y[i])+y[i]*(x[l]-x[i]);
				NOR = sqrt(A*A+B*B);
				for ( low = 0, high = 1; fabs(high-low) > tol; ) {
					mid = (low+high)/2;
					sx = px + mid*(qx-px);
					sy = py + mid*(qy-py);
					if ( fabs(A*sx+B*sy+C)/NOR < d )
						low = mid;
					else high = mid;
				}
				nx[i] = px + high*(qx-px);
				ny[i] = py + high*(qy-py);
				determined[i] = yes;
			}
			if ( determined[j] != yes ) {
				A = (y[k]-y[j]), B = -(x[k]-x[j]), C = -x[j]*(y[k]-y[j])+y[j]*(x[k]-x[j]);
				NOR = sqrt(A*A+B*B);
				for ( low = 0, high = 1; fabs(high-low) > tol; ) {
					mid = (low+high)/2;
					sx = qx + mid*(px-qx);
					sy = qy + mid*(py-qy);
					if ( fabs(A*sx+B*sy+C)/NOR < d )
						low = mid;
					else high = mid;
				}
				nx[j] = qx + high*(px-qx);
				ny[j] = qy + high*(py-qy);
				determined[j] = yes;
			}
		}
		for ( A = 0, i = 0; i < n; ++i ) {
			j = (i+1)%n;
			A += (ny[j]-ny[i])*(nx[i]+nx[j]);
		}
		printf("%.3Lf\n",(long double)fabs(A)/2);
	}
	return 0;
}
