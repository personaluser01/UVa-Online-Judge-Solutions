/*
 * 1534. Taekwondo
 * TOPIC: dp, alignments
 * status: Accepted
 */
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 0x200
typedef long long i64;
#define oo (1LL<<43)

int cmp( const void *a, const void *b ) {
	if ( *(int *)a == *(int *)b )
		return 0;
	if ( *(int *)a < *(int *)b )
		return -1;
	return 1;
}

i64 A( i64 x ) {
	if ( x < 0 ) return -x;
	return x;
}

int a[N],b[N],m,n;
i64 z[N][N];

void solve( int *a, int *b, int m, int n ) {
	int i,j,k;
	i64 w = +oo;
	assert( m <= n );
	for ( i = 0; i <= m; ++i )
		for ( j = 0; j <= n; z[i][j++] = +oo );
	for ( j = 0; j <= n; z[0][j++] = 0 );
	for ( i = 1; i <= m; ++i )
		for ( j = i; j <= n && n-j >= m-i; ++j ) 
			for ( z[i][j] = z[i][j-1], k = j; k >= i; --k )
				if ( z[i-1][k-1] < +oo && z[i][j] > z[i-1][k-1]+A(a[i]-b[k]) )
					z[i][j] = z[i-1][k-1]+A(a[i]-b[k]);
	for ( j = m; j <= n; ++j )
		if ( w > z[m][j] ) 
			w = z[m][j];
	printf("%lld.%lld\n",w/10,w%10);
}

int main() {
	int i,j,k,ts;
#ifndef ONLINE_JUDGE
	freopen("c.txt","r",stdin);
#endif
	for ( scanf("%d",&ts); ts--; ) {
		scanf("%d %d",&m,&n);
		for ( i = 1; i <= m; ++i )
			scanf("%d.%d",&j,&k), a[i] = j*10+k;
		for ( i = 1; i <= n; ++i )
			scanf("%d.%d",&j,&k), b[i] = j*10+k;
		qsort(a+1,m,sizeof *a,cmp);
		qsort(b+1,n,sizeof *b,cmp);
		if ( m > n ) solve(b,a,n,m);
		else solve(a,b,m,n);
	}
	return 0;
}

