/*
 * 1269. In-circles Again
 * TOPIC: geometry
 * status: Accepted
 */
#include <bits/stdc++.h>

double r[4],h[4],H[4],s;

int main() {
	int i,j,k,cs = 0;
	while ( 4 == scanf("%lf %lf %lf %lf",r,r+1,r+2,r+3) ) {
		if ( r[0] < 0 && r[1] < 0 && r[2] < 0 && r[3] < 0 ) break ;
		for ( i = 1; i < 4; ++i ) {
			H[i] = 2*sqrt(r[0]*r[i]);
			h[i] = r[i]/(r[0]-r[i])*H[i];
		};
		for ( s = 0, i = 1; i < 4; ++i ) {
			j = (i+1)&3;
			if ( j == 0 ) ++j;
			s += r[0]*(h[i]+H[i]+H[j]+h[j])/2;
		};
		printf("Case %d: %.2lf\n",++cs,s);
	};
	return 0;
};

