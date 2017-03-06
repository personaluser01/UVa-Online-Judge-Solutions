/*
 * 10357. Playball !!!
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <limits.h>
#include <float.h>
#define N 0x40
#define tol 1e-9
typedef long long i64;

char buff[0x400];
int m,n;
long double x[N],y[N],v[N],
	 a,b,c,d,e,f,g;
i64 T;

long double F( i64 t ) { return a*t*t + b*t + c; }

i64 hit_time() {
	i64 low,high,mid;
	if ( F(low = 1) <= 0 )
		return low;
	for ( high = (1LL<<29); low+1 < high; ) {
		mid = (low+high)/2;
		if ( F(mid) > 0 ) low = mid;
		else high = mid;
	}
	return high;
}

int main() {
	int i,j,k;
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	while ( 2 == scanf("%[^=]=%d",buff,&m) ) {
		printf("m = %d\n",m);
		for ( i = 1; i <= m; ++i ) {
			scanf("%Lf %Lf %Lf",x+i,y+i,v+i);
		}
		assert( 2 == scanf("%[^=]=%d",buff,&n) );
		printf("n = %d\n",n);
		for ( j = 1; j <= n; ++j ) {
			scanf("%Lf %Lf %Lf %Lf %Lf %Lf %Lf",&a,&b,&c,&d,&e,&f,&g);
			printf("Ball %d was ",j);
			T = hit_time();
		}
	}
	return 0;
}

