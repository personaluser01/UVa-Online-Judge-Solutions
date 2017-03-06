/*
 * 11522. Pyramid Number
 * TOPIC: maths, ad hoc, precalc
 * status: Accepted
 */
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define tol (1e-11)
#define N (1<<21)

int c[N],a,b,is[100],
	e[] = {1, 11, 24, 30, 31, 32, 37, 38, 43, 45, 50, 52, 53, 54, 55, 57, 59, 60, 61, 62, 64, 65, 66, 67, 69, 71, 73, 74, 75, 76, 78, 79};

int is_pyra( int n, int m, double w ) {
	if ( fabs(w-1.00) < tol ) 
		return n == 0;
	if ( w > 1 ) return 0;
	if ( n <= 0 )
		return 0;
	assert( n >= 1 );
	for ( ;m >= 1; --m )
		if ( is_pyra(n-m,m-1,w+1.0/m) )
			return 1;
	return 0;
}

int main() {
	int i,j,k,n = 150,ts;
	/*
	for ( j = 0, k = 1; k <= n; ++k ) 
		if ( is_pyra(k,k,0) ) printf("%d ",k), c[k] = c[k-1]+1;
		else c[k] = c[k-1];
	puts("");
	*/
	for ( j = 0; j < sizeof(e)/sizeof(0[e]); ++j )
		is[e[j]] = 1;
	for ( j = 0, k = 1; k <= 79; ++k ) 
		c[k] = c[k-1]+is[k];
	for ( n = 80; n < N; ++n )
		c[n] = c[n-1]+1;
	for ( scanf("%d",&ts); ts--; ) {
		scanf("%d %d",&a,&b);
		if ( a > b ) {
			printf("%d\n",c[a]-c[b-1]);
			continue ;
		}
		printf("%d\n",c[b]-c[a-1]);
	}
	return 0;
}

