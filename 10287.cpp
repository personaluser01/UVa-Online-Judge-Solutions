/*
 * 10287. Gifts in a Hexagonal Boxes
 * TOPIC: geometry, medium
 * status: Accepted
 */
#include <stdio.h>
#include <cmath>
#include <iostream>
using namespace std;

	void doIt() {
		double r,r1,r2,r3,r4,low,high,mid,tol = 1e-9,x,oo = (1<<29),si = sqrt(3.0)/2,h,H,y,a,b,c,d;
			while ( 1 == scanf("%lf",&r) ) {
				H = r*si;
				r1 = r*si;
				r2 = (sqrt(3.0)*r)/(sqrt(3.0)+2);
				r3 = (sqrt(3.0)*r)/4;
				/*
				for ( low = 0, high = r; abs(high-low) >= tol; ) {
					mid = (low+high)/2;
					x = (r-mid)*si;
					h = sqrt(4*x*x-mid*mid);
					y = H-h;
					if ( y < x )
						low = mid;
					else high = mid;
				}
				mid = (low+high)/2;
				r4 = (r-mid)*si;
				*/
				a = 5.0/3; b = 7.0*r/(2*si); c = -7.0/4.0*r*r;
				d = sqrt(b*b-4*a*c);
				r4 = (-b+d)/2/a;
				printf("%.10f %.10f %.10f %.10f\n",r1,r2,r3,r4);
			}
	}

int main() {
	doIt();
	return 0;
}

