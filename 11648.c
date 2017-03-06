/*
 * 11648. Divide the Land
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
#define tol 1e-11
#define pi (2*acos(0.00))

long double S( long double x ) { return x*x; }
long double ab,cd,bc,ad,
	 AX,AY,BX,BY,CX,CY,DX,DY;

long double f( long double phi ) {
	return ad*ad + cd*cd + ab*ab - 2*ab*cd - 2*ab*ad*cos(phi)+2*cd*ad*cos(phi) - bc*bc;
}

long double g( long double phi ) {
	return 2*(ab-cd)*sin(phi);
}

int main() {
	int i,j,k,ts,cs = 0,t;
	long double low,high,mid,x,phi[2],len,h,am,bn,lower,upper,MX,MY,NX,NY,area;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( scanf("%d",&ts); ts--; ) {
		printf("Land #%d: ",++cs);
		scanf("%Lf %Lf %Lf %Lf",&ab,&cd,&ad,&bc);
		x = sqrt((ab*ab+cd*cd)/2);
		phi[0] = acos( (ad*ad+cd*cd+ab*ab-2*ab*cd-bc*bc)/(2*ad*(ab-cd)) );
		/*
		for ( phi[t = 0] = 0, phi[t^1] = pi; fabs(phi[0]-phi[1]) > tol; ) 
			t ^= 1, phi[t] = phi[1-t]-f(phi[1-t])/g(phi[1-t]);
			*/
		t = 0;
		/*printf("Here %Lf\n",phi[t]);*/
		AX = -ab/2, AY = 0;
		BX = ab/2, BY = 0;
		DX = -ab/2+ad*cos(phi[t]),    DY = ad*sin(phi[t]);
		CX = -ab/2+ad*cos(phi[t])+cd, CY = ad*sin(phi[t]);
		h = ad*sin(phi[0]);
		area = h*(ab+cd)/2;
		for ( low = 1, high = 0; fabs(low-high) > tol; ) {
			mid = (low+high)/2;
			MX = AX*mid + DX*(1-mid), MY = AY*mid + DY*(1-mid);
			NX = BX*mid + CX*(1-mid), NY = BY*mid + CY*(1-mid);
			len = sqrt(S(MX-NX)+S(MY-NY));
			assert( ab >= len );
			assert( cd <= len );
			lower = (ab+len)*h*(1-mid)/2;
			if ( lower < area/2 )
				low = mid;
			else high = mid;
		}
		mid = (low+high)/2;
		MX = AX*mid + DX*(1-mid), MY = AY*mid + DY*(1-mid);
		NX = BX*mid + CX*(1-mid), NY = BY*mid + CY*(1-mid);
		len = sqrt(S(MX-NX)+S(MY-NY));
		am = sqrt(S(MX-AX)+S(MY-AY));
		bn = sqrt(S(NX-BX)+S(NY-BY));
		printf("%.6Lf %.6Lf\n",am+tol,bn+tol);
	}
	return 0;
}
