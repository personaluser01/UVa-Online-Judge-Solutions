/*
 * 815. Flooded!
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
#define N 0x31
typedef long long i64;
#define tol 1e-9

i64 m,n,c[N][N],T,ts,p;
double low,high,mid,lowest,highest;

double Volume( double h ) {
	int i,j;
	double w = 0;
	for ( p = 0, i = 1; i <= m; ++i )
		for ( j = 1; j <= n; ++j )
			if ( c[i][j] < h && fabs(h-c[i][j]) > tol && ++p )
				w += (h-c[i][j]);
	return w*10*10;
}

int main() {
	int i,j,k;
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	while ( 2 == scanf("%lld %lld",&m,&n) && (m||n) ) {
		lowest = DBL_MAX-1024, highest = -(DBL_MAX-1024);
		memset(c,0,sizeof(c));
		for ( i = 1; i <= m; ++i )
			for ( j = 1; j <= n; ++j ) {
				scanf("%lld",&c[i][j]);
				if ( lowest > c[i][j] )
					lowest = c[i][j];
				if ( highest < c[i][j] )
					highest = c[i][j];
			}
		scanf("%lld",&T), printf("Region %lld\n",++ts);
		for ( low = lowest-1, high = T+lowest; fabs(high-low) > tol; \
		Volume(mid=(low+high)/2)<T?(low=mid):(high=mid) );
		printf("Water level is %.2lf meters.\n",high);
		Volume(high);
		printf("%.2lf percent of the region is under water.\n\n",p*100.0/(m*n));
	}
	return 0;
}

