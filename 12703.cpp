/*
 * 12703. Little Rakin
 * TOPIC: primes, fibonaccie, matrix powers
 * status: Accepted
 */
#include <cassert>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#define N 0x400
typedef long long i64;
using namespace std;

bool isprime[N];
int m,*p;

struct mat {
	i64 a[2][2];
	mat() { for ( int i = 0; i < 2; ++i )
			for ( int j = 0; j < 2; ++j )
				a[i][j] = 0; };
};

mat operator * ( const mat &p, const mat &q ) {
	mat r;
	for ( int j,k,i = 0; i < 2; ++i )
		for ( j = 0; j < 2; ++j )
			for ( k = 0; k < 2; ++k )
				r.a[i][j] += p.a[i][k]*q.a[k][j];
	return r;
};

mat operator ^ ( const mat &p, int n ) {
	mat ax,x = p;
	ax.a[0][0] = ax.a[1][1] = 1LL;
	for ( ;n; n >>= 1, x = x*x ) 
		if ( n & 1 ) 
			ax = ax*x;
	return ax;
};

struct signature {
	i64 d[172];
	signature() {memset(d,0,sizeof d);};
};

signature convert( int n ) {
	signature s;
	for ( int i = 0; i < m; ++i )
		for ( ;0==(n%p[i]); ++s.d[i], n /= p[i] );
	return s;
};

int main() {
	int i,j,k,cs,a,b,n,ts;
	for ( i = 3; i < N; i += 2 ) isprime[i] = true ;
	for ( isprime[2] = true, i = 3; i < N; i += 2 )
		if ( isprime[i] )
			for ( j = i+i; j < N; isprime[j] = false, j += i );
	for ( m = 0, i = 0; i < N; ++i )
		if ( isprime[i] ) ++m;
	p = new int[m+1];
	for ( k = 0, i = 0; i < N; ++i )
		if ( isprime[i] )
			p[k++] = i;
	assert( m == k );
	for ( scanf("%d",&ts); ts--; ) {
		scanf("%d %d %d",&n,&a,&b);
		signature A = convert(a),
				  B = convert(b);
		mat T;
		T.a[0][0] = 1, T.a[0][1] = 1, T.a[1][0] = 1;
		mat R = T^(n-1);
		signature s;
		for ( i = 0; i < m; ++i ) 
			if ( s.d[i] = R.a[0][0]*B.d[i]+R.a[0][1]*A.d[i] )
				printf("%d %lld\n",p[i],s.d[i]);
		puts("");
	}
	return 0;
}

