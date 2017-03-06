/*
 * 1640. The Counting Problem
 * TOPIC: dp
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 0x40
typedef long long i64;

i64 min( i64 x, i64 y ) { return x<y?x:y; }
i64 max( i64 x, i64 y ) { return x>y?x:y; }

i64 c[N][N],D[N],deg[N],e[N],E[N];
int m,n;

i64 f( char *a, int n, int d ) {
	i64 res = 0,k;
	if ( n == 1 ) 
		return *a-'0'<d?0:1;
	assert( n >= 2 );
	for ( k = 0; k <= d-1 && k <= *a-'0'-1; ++k )
		res += e[n-1];
	for ( k = d+1; k <= *a-'0'-1; ++k )
		res += e[n-1];
	if ( d < *a-'0' )
		res += E[n-1];
	if ( d == *a-'0' )
		res += (atoi(a+1)+1);
	res += f(a+1,n-1,d);
	return res;
}

i64 g( char *a, int m, char *b, int n, int d ) {
	i64 aa = 0, bb = 0, l;
	if ( d > 0 ) return f(b,n,d)-f(a,m,d);
	for ( l = 1; l <= m-1; ++l )
		aa += l*9*deg[m-1-l];
	for ( l = 1; l <= n-1; ++l )
		bb += l*9*deg[n-1-l];
	aa += m, bb += n;
	return f(b,n,d)-f(a,m,d)-bb+aa;
}

int main() {
	i64 i,j,k,t,a,b;
	char A[N],B[N];
#ifndef ONLINE_JUDGE
    freopen("in.txt","r",stdin);
#endif
	for ( i = 0; i < N; c[i++][0] = 1LL );
	for ( i = 1; i < N; ++i )
		for ( j = 1; j <= i; ++j )
			c[i][j]=c[i-1][j]+c[i-1][j-1];
	for ( D[0]=deg[0]=1LL, i=1; i<N; deg[i]=deg[i-1]*10LL,D[i]=D[i-1]*9LL,++i );
	for ( m=1; m<N; ++m )
		for ( E[0]=1, t=0; t<=m; E[m]+=(t+1)*c[m][t]*D[m-t], e[m]+=t*c[m][t]*D[m-t], ++t );
	for ( ;2==scanf("%lld %lld",&a,&b)&&(a||b); ) {
		if ( a > b ) k=a,a=b,b=k;
		assert( a <= b );
		sprintf(A,"%lld",a-1), m = strlen(A), sprintf(B,"%lld",b), n = strlen(B);
		for ( i = 0; i <= 9; printf("%lld%c",g(A,m,B,n,i),i==9?'\n':' '), ++i );
	}
    return 0;
}

