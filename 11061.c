/*
 * 11061. Playing War
 * TOPIC: probability, dp, lazy dp
 * status: Accepted
 */
#include <assert.h>
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define oo DBL_MAX
#define N 0x400
#define SH 11
#define BIT(k) (1ULL<<(k))
#define MASK(k) (BIT(k)-1ULL)
#define Q BIT(SH+SH-1)
#define D 6
typedef unsigned int state;
int min( int x, int y ) { return x<y?x:y; };
int mmin( int x, int y, int z ) { return min(min(x,y),z); };

int n,a[4],b[4];
long double z[Q],q[4][4][4],deg[D+1];

state enc( int x, int y ) {
	assert( x >= 0 );
	assert( y >= 0 );
	return x|(y<<SH);
};

int cmp( const void *a, const void *b ) {
	int *x = (int *)a,
		*y = (int *)b;
	return *y-*x;
}

void rec( const int m, const int n, int i, int j, long double *w, const int u ) {
	int k,t,v = 0,A[D],B[D];
	if ( i == m && j == n ) {
		for ( k = 0; k < m; A[k] = a[k], ++k );
		for ( k = 0; k < n; B[k] = b[k], ++k );
		qsort(A,m,sizeof *A,cmp), qsort(B,n,sizeof *B,cmp);
		for ( k = 0; k < m && k < n && v <= u; ++k ) 
			if ( A[k] > B[k] )
				++v;
		if ( u == v ) ++(*w);
		return ;
	}
	if ( i < m && j < n ) {
		for ( k = 1; k <= D; ++k )
			for ( t = 1; t <= D; ++t ) {
				a[i] = k, b[j] = t;
				rec(m,n,i+1,j+1,w,u);
			}
		return ;
	}
	if ( j < n ) {
		for ( t = 1; t <= D; ++t )
			b[j] = t, rec(m,n,i,j+1,w,u);
		return ;
	}
	if ( i < m ) {
		for ( k = 1; k <= D; ++k )
			a[i] = k, rec(m,n,i+1,j,w,u);
		return ;
	}
	assert( 0 );
}

long double calc_q( int m, int n, int k ) {
	long double w;
	if ( q[m][n][k] < +oo )
		return q[m][n][k];
	if ( k > m || k > n ) 
		return q[m][n][k] = 0;
	assert( k <= m && k <= n );
	if ( m == 0 ) 
		return q[m][n][k] = 1;
	if ( n == 0 ) 
		return q[m][n][k] = (k==0?1:0);
	assert( 1 <= m && 1 <= n );
	w = 0, rec(m,n,0,0,&w,k);
	return q[m][n][k] = w*deg[m+n];
};

long double calc_z( state u ) {
	int m,n,i,k;
	if ( z[u] < +oo )
		return z[u];
	m=(u&MASK(SH)),n=(u>>SH);
	if ( m==0 && n==0 )
		return z[u]=1;
	if ( m>=1 && n==0 )
		return z[u]=1;
	if ( m==0 && n>=1 )
		return z[u]=0;
	assert( m>=1 && n>=1 );
	for ( z[u]=0, k=mmin(m,n,3), i=-k; i<=0; z[u]+=calc_q(min(3,m),min(3,n),k+i)*calc_z(enc(m+i,n-k-i)), ++i );
	return z[u];
};

int main() {
	int i,j,k,l,t,m;
	unsigned int u,v;
#ifndef ONLINE_JUDGE
	freopen("11061.in","r",stdin);
#endif
	for ( i = 0; i < 4; ++i )
		for ( j = 0; j < 4; ++j )
			for ( k = 0; k < 4; q[i][j][k++] = +oo );
	for ( u = 0; u < Q; z[u++] = +oo );
	for ( deg[0] = 1, i = 1; i <= D; deg[i] = deg[i-1]/6, ++i );
	for ( ;1 == scanf("%d",&n) && n > 0; printf("%d\n",++m) )
		for ( m = n; m <= (n<<1)+1 && calc_z(enc(m,n)) <= 0.5; ++m );
	return 0;
};

