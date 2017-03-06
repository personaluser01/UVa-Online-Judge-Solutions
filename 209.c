/*
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define N 0x10
#define tol 1e-9
#define S(x) ((x)*(x))
#define BIT(k) (1ULL<<(k))
#define MASK(k) (BIT(k)-1ULL)
#define pi (2*acos(0.0))
typedef long long i64;

double x[N],y[N],d[N][N],dist;
int n,c[N],cnt[N];
char buff[0x400],*ptr;

i64 H( i64 n ) { return (n*(n+1))>>1; }

void convert( int c, double *x, double *y ) {
	int row,col,i,j,k,low,high,mid,middle;
	assert( c >= 1 );
	if ( c == 1 ) { *x = *y = 0; return ; }
	low = 1, high = (1<<16);
	assert( H(low) < c );
	assert( H(high) >= c );
	for (;low+1 < high;) 
		if ( H(mid = (low+high)/2) < c ) low = mid;
		else high = mid;
	assert( H(low) < c );
	assert( H(row = high) >= c );
	assert( low+1 == high );
	middle = (H(high)+H(low)+1)/2;
	if ( row&1 ) 
		*x = c-middle;
	else 
		*x = c-middle-0.5;
	*y = -(row-1)*sqrt(3.0)/2;
}

int along_grid( int i, int j ) {
	double yy = y[j]-y[i],
		   xx = x[j]-x[i],
		   tg,a;
	if ( fabs(yy) < tol )
		return 1;
	if ( fabs(xx) < tol )
		return 0;
	a = atan(tg = yy/xx);
	return fabs(a-pi/3)<tol || fabs(a+pi/3)<tol;
}

int f( int idx, unsigned int u ) {
	int i,j,k = 0;
	if ( cnt[idx] == 2 ) 
		return u==MASK(n);
	assert( cnt[idx] == 1 );
	for ( i = 0; i < n && !k; ++i ) 
		if ( cnt[i] < 2 && fabs(dist-d[idx][i]) < tol && along_grid(idx,i) )
			++cnt[i],k|=f(i,u|BIT(i)),--cnt[i];
	return k;
}

int g( int T ) {
	int i,j,k=0;
	if ( n!=T ) return 0;
	for ( i=0; i<n && !k; ++i )
		for ( j=i+1; j<n && !k; ++j ) 
			dist=d[i][j],++cnt[0],k|=f(0,0),--cnt[0];
	return k;
}

int main() {
	int i,j,k,s[] = {3,4,6};
	double aa,bb;
	const char *p[] = {"triangle","parallelogram","hexagon"};
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	for (;ptr = fgets(buff,sizeof(buff),stdin);) {
		for ( n = 0; 1 == sscanf(ptr,"%d%n",c+n,&j); ptr += j, convert(c[n],x+n,y+n), printf("%d ",c[n++]) );
		for ( i = 0; i < n; ++i )
			for ( j = 0; j < n; ++j )
				d[i][j] = sqrt(S(x[i]-x[j])+S(y[i]-y[j]));
		for ( k = 0, i = 0; i < 3 && !k; ++i )
			if ( k |= g(s[i]) ) 
				printf("are the vertices of a %s\n",p[i]);
		if ( !k ) puts("are not the vertices of an acceptable figure");
	}
	return 0;
}

