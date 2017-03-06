/*
 * 10991. Region
 * status: Accepted
 */
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define S(x) ((x)*(x))
#define pi (2*acos(0.00))

long double r[3],L[3],a[3],s[3];

int main() {
	int i,j,k,ts;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( scanf("%d",&ts); ts--; ) {
		scanf("%Lf %Lf %Lf",r,r+1,r+2);
		for ( i = 0; i < 3; ++i ) 
			j = (i+1)%3, L[i] = r[i]+r[j];
		a[0] = acos((S(L[0])+S(L[2])-S(L[1]))/2/L[0]/L[2]);
		a[1] = acos((S(L[0])+S(L[1])-S(L[2]))/2/L[0]/L[1]);
		a[2] = acos((S(L[2])+S(L[1])-S(L[0]))/2/L[2]/L[1]);
		for ( i = 0; i < 3; ++i ) {
			s[i] = a[i]*S(r[i])/2;
		}
		printf("%Lf\n",L[2]*L[1]*sin(a[2])/2-s[0]-s[1]-s[2]);
	}
	return 0;
}

