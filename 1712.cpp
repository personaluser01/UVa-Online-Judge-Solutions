/*
 * 1712. Cutting Cheese
 * TOPIC: maths, binary search
 * status: Accepted
 */
#include <bits/stdc++.h>
#define N (1<<17)
#define D 100000LL
#define tol 1e-9
#define M 0x80
#define pi (2*acos(0.00))
#define C(x) ((x)*(x)*(x))
typedef long long i64;

int n,m;
double x[N],y[N],z[N],r[N],vol[N],V,v,w,cut[M],sr[N],cr[N];

double f( double h ) {
	double holes = 0,d;
	for ( int i = 0; i < n; ++i )
		if ( z[i]+r[i] <= h ) 
			holes += vol[i];
		else if ( !(z[i]-r[i] >= h) ) {
			if ( z[i] >= h ) {
				d = r[i]-z[i]+h;
				assert( d >= 0 );
				holes += pi*(sr[i]*d-cr[i]/3+C(r[i]-d)/3);
			}
			else {
				d = r[i]-h+z[i];
				assert( d >= 0 );
				holes += vol[i]-pi*(sr[i]*d-cr[i]/3+C(r[i]-d)/3);
			}
		}
	return h*D*D-holes;
}

int main() {
	int i,j,k;
	double low,high,mid,H;
	while ( 2 == scanf("%d %d",&n,&m) ) {
		for ( H = 0, i = 0; i < n; ++i ) {
			scanf("%lf %lf %lf %lf",r+i,x+i,y+i,z+i);
		   	vol[i] = 4*pi*r[i]*r[i]*r[i]/3;
		   	sr[i] = r[i]*r[i], cr[i] = sr[i]*r[i];
			H += cr[i]*pi*4.00/3.00;
		}
		for ( V = D*D*D-H, v = V/m, i = 1; i <= m-1; cut[i++] = (low+high)/2 )
			for ( w = v*i, low = 0.00, high = D; fabs(high-low) > tol; ) {
				mid = (low+high)/2;
				if ( f(mid) < w ) low = mid;
				else high = mid;
			}
		for ( cut[m] = D, i = 0; i < m; ++i )
			printf("%lf\n",(cut[i+1]-cut[i])/1000);
	}
	return 0;
}

