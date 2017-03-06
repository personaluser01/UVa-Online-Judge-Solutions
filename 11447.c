/*
 * 11447. Reservoir Logs
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
#define N 10100
#define tol 1e-9

int n;
typedef struct{long double x,y;} cell;
long double W,In,Out,p,A,Vol,Actual,New;
cell c[N];

int main() {
	int i,j,k,ts;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( scanf("%d",&ts); ts--; ) {
		for ( A = 0, scanf("%d",&n), i = 0; i < n; ++i ) 
			scanf("%Lf %Lf",&c[i].x,&c[i].y);
		for ( i = 0; i < n; ++i ) {
			j = (i+1) % n;
			A += (c[i].x-c[j].x)*(c[i].y+c[j].y);
		}
		A = fabs(A)/2, scanf("%Lf",&W), Vol = A*W;
		scanf("%Lf %Lf %Lf",&p,&Out,&In);
		Actual = p*Vol/100;
		if ( fabs(Out-Actual) > tol && Out > Actual ) 
			Actual = 0, printf("Lack of water. ");
		else Actual -= Out;
		New = Actual + In;
		if ( fabs(New-Vol) > tol && New > Vol )
			New = Vol, printf("Excess of water. ");
		printf("Final percentage: %d%%\n",(int)(New*100/Vol+tol));
	}
	return 0;
}
