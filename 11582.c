/*
 * 11582. Colossal Fibonacci Numbers!
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MOD 0x400
typedef unsigned long long u64;

u64 a,b,n,A[2][2],P,Q,m;

u64 f( u64 m ) {
	u64 i,j,k,x[2][2],r[2][2],t[2][2];

	if ( m == 0 )
		return 0;

	if ( m == 1 || m == 2 )
		return 1;

	for ( --m, i = 0; i < 2; ++i )
		for ( j = 0; j < 2; ++j ) {
			if ( i == j )
				r[i][j] = 1;
			else r[i][j] = 0;
			x[i][j] = A[i][j];
		}
	while ( m ) {
		if ( m & 1 ) {
			for ( i = 0; i < 2; ++i )
				for ( j = 0; j < 2; ++j )
					for ( t[i][j]=0, k = 0; k < 2; ++k )
						t[i][j] += r[i][k]*x[k][j], t[i][j] %= n;
			for ( i = 0; i < 2; ++i )
				for ( j = 0; j < 2; ++j )
					r[i][j] = t[i][j];
		}
		for ( m >>= 1, i = 0; i < 2; ++i )
			for ( j = 0; j < 2; ++j )
				for ( t[i][j] = 0, k = 0; k < 2; ++k )
					t[i][j] += x[i][k]*x[k][j], t[i][j] %= n;
		for ( i = 0; i < 2; ++i )
			for ( j = 0; j < 2; ++j )
				x[i][j] = t[i][j];
	}
	return (r[0][0])%n;
}

void find_period() {
	u64 px,x,py,y,i,j,k,w;
#define advance(px,x) (w=(px),(px)=(x),(x)=w+(px),(x)%=n)
	for ( k = 2, px = 0, x = 1, py = 1, y = (2%n); !(px == py && x == y); ++k )
		advance(px,x), advance(py,y), advance(py,y);
	for ( P = k, py = 0, y = 1, i = 0; i < k; ++i )
		advance(py,y);
	for ( m = 0, px = 0, x = 1; !(px == py && x == y); ++m )
		advance(px,x), advance(py,y);
}

int main() {
	int ts;
	u64 x,y,res,i,j,k;
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	A[0][0] = A[0][1] = A[1][0] = 1ULL;
	for ( scanf("%d",&ts); ts-- && 3 == scanf("%llu %llu %llu",&a,&b,&n); ) {
		if ( n == 1 || a == 0 ) {
			puts("0");
			continue ;
		}
		find_period();
		/*printf("[m = %llu, P = %llu] These %llu %llu %llu %llu\n",m,P,f(P),f(P+1),f(P+2),f(P+3));*/
		for( res = 1ULL, a %= P; b; b >>= 1, a *= a, a %= P )
			if(b&1)res*=a,res%=P;
		printf("%llu\n",f(res));
	}
	return 0;
}

